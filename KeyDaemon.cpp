#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>


#define SC_NUMPADDEL 0x53
#define SC_NUMPADINS 0x52
#define SC_NUMPADEND 0x4F
#define SC_NUMPADHOME 0x47
#define SC_NUMPADCLEAR 0x4C
#define SC_NUMPADUP 0x48
#define SC_NUMPADDOWN 0x50
#define SC_NUMPADLEFT 0x4B
#define SC_NUMPADRIGHT 0x4D
#define SC_NUMPADPGUP 0x49
#define SC_NUMPADPGDN 0x51

#define SC_NUMPADDOT SC_NUMPADDEL
#define SC_NUMPAD0 SC_NUMPADINS
#define SC_NUMPAD1 SC_NUMPADEND
#define SC_NUMPAD2 SC_NUMPADDOWN
#define SC_NUMPAD3 SC_NUMPADPGDN
#define SC_NUMPAD4 SC_NUMPADLEFT
#define SC_NUMPAD5 SC_NUMPADCLEAR
#define SC_NUMPAD6 SC_NUMPADRIGHT
#define SC_NUMPAD7 SC_NUMPADHOME
#define SC_NUMPAD8 SC_NUMPADUP
#define SC_NUMPAD9 SC_NUMPADPGUP

#undef assert
void assert(bool cond, const char *error) {
    if (cond) return;
    printf("Assert failed: ");
    printf(error);
    printf("\n");
    exit(1);
}

void ReadScreen(int x, int y, int width, int height, unsigned char *buffer) {
    HDC hdc = GetDC(NULL);
    HDC sdc = NULL;
    HBITMAP hbitmap_screen = NULL;
    HGDIOBJ sdc_orig_select = NULL;
    BITMAPINFO bmapinfo;

    // Create an empty bitmap to hold all the pixels currently visible on the screen (within the search area):
    assert(sdc = CreateCompatibleDC(hdc), "sdc");
    assert(hbitmap_screen = CreateCompatibleBitmap(hdc, width, height), "hbitmap_screen");		
    assert(sdc_orig_select = SelectObject(sdc, hbitmap_screen), "sdc_orig_select");

    // Copy the pixels in the search-area of the screen into the DC to be searched:
    assert(BitBlt(sdc, 0, 0, width, height, hdc, x, y, SRCCOPY), "BitBlt");
    
    // get at the bits
    bmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmapinfo.bmiHeader.biBitCount = 32;
    bmapinfo.bmiHeader.biHeight = -height;
    bmapinfo.bmiHeader.biWidth = width;
    bmapinfo.bmiHeader.biPlanes = 1;
    bmapinfo.bmiHeader.biCompression = BI_RGB;
    
    GetDIBits(sdc, hbitmap_screen, 0, height, buffer, &bmapinfo, DIB_RGB_COLORS);

    // clean up
    SelectObject(sdc, sdc_orig_select); 
    DeleteDC(sdc);
    DeleteObject(hbitmap_screen);	
    ReleaseDC(NULL, hdc);

    fflush(stdout);
}


void SendKey(char key) {
    HWND window = NULL;
    DWORD myThreadId, windowThreadId;

    for (int i = 0; i < 10; i++) {
	window = GetForegroundWindow();
	if (window) break;
	Sleep(10*i + 10);
    }
    if (!window) {
	printf("Couldn't get foreground window\n");
	fflush(stdout);
	return;
    }
    //assert(myThreadId = GetCurrentThreadId(), "myThreadId");
    //assert(windowThreadId = GetWindowThreadProcessId(window, NULL), "windowThreadId");

    // attach to the thread associated to the current window
    //assert(AttachThreadInput(myThreadId, windowThreadId, TRUE), "attach to foreground window's input thread");

    // get the keyboard state
    //unsigned char keyboard[256];
    //assert(GetKeyboardState(keyboard), "GetKeyboardState");
    // print it
    
    //for (int i = 0; i < 256; i++) {
    //printf("%i ", keyboard[i]);
    //}
    //printf("\n");

    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_NUMPAD0;
    input.ki.wScan = SC_NUMPAD0;
    input.ki.dwFlags = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    SendInput(1, &input, sizeof(INPUT));

    Sleep(10);

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));

    // detach the thread
    //assert(AttachThreadInput(myThreadId, windowThreadId, FALSE), "detach from foreground window's input thread");
}




int main(int argc, const char **argv) {
    unsigned char buffer[1024];

    while (1) {

	//printf("Looping\n");
	Sleep(500);

	// spy 
	ReadScreen(0, 0, 8, 1, buffer);

	// print them out
	for (int i = 0; i < 8*4; i++) {
	    printf(("%i "), buffer[i]);
	}
	
	//SendKey(VK_NUMPAD0);

	printf("\n");



    }
}

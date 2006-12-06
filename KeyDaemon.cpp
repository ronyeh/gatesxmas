#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>
#include <process.h>
#define SC_ESC 0x01
#define SC_Q   0x10
#define SC_W   0x11
#define SC_E   0x12
#define SC_A   0x1E
#define SC_S   0x1F
#define SC_D   0x20



#define VK_Q   'q'
#define VK_W   'w'
#define VK_E   'e'
#define VK_A   'a'
#define VK_S   's'
#define VK_D   'd'

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


void SendEsc() {
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
    input.ki.wVk = VK_ESCAPE;
    input.ki.wScan = SC_ESC;
    input.ki.dwFlags = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    SendInput(1, &input, sizeof(INPUT));

    Sleep(100);

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));

    // detach the thread
    //assert(AttachThreadInput(myThreadId, windowThreadId, FALSE), "detach from foreground window's input thread");
}


void SendPan() {
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

    if (rand()<RAND_MAX/2) {
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = VK_Q;
	    input.ki.wScan = SC_Q;
	input.ki.dwFlags = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	SendInput(1, &input, sizeof(INPUT));
	
	Sleep(3000);
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
    }
    input.ki.wVk = VK_W;
    input.ki.wScan = SC_W;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
    Sleep(2000);
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));


    input.ki.wVk = VK_D;
    input.ki.wScan = SC_D;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
    Sleep(3000);
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
    

    if (rand()<RAND_MAX/2) {

	input.ki.wVk = VK_E;
    input.ki.wScan = SC_E;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
    Sleep(6000);
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
    }

    // detach the thread
    //assert(AttachThreadInput(myThreadId, windowThreadId, FALSE), "detach from foreground window's input thread");
}

int nearl (int a,int b) {
    return a==b;
}
int iswhite(unsigned char * a) {
    int r=a[0];
    int g=a[1];
    int b=a[2];
    if ((!nearl(r,g))||!nearl(g,b)) {
	return false;
    }
    if (r<220) return false;
    return true;
}
bool issame(unsigned char *a, unsigned char *b) {
    int r=(a[0]>b[0]?a[0]-b[0]:b[0]-a[0]);
    int g=(a[1]>b[1]?a[1]-b[1]:b[1]-a[1]);
    int bb=(a[2]>b[2]?a[2]-b[2]:b[2]-a[2]);
    if (r<20||g<20||bb<20) return true;
    return false;
}
int pcmp(unsigned char * newbuffer, unsigned char*  oldbuffer,unsigned int numpix) {
    for (unsigned int i=0;i<numpix;++i) {
	if (!issame(newbuffer+i*4,oldbuffer+i*4)) {//iswhite(newbuffer+i*4)!=iswhite(oldbuffer+i*4)) {
	    return 1;
	}
    }
    return 0;
}
int main(int argc, const char **argv) {
    unsigned int width=1024;
    unsigned int height=768;
    unsigned char *buffer=(unsigned char*)malloc(width*height*4);
    unsigned char *oldbuffer=(unsigned char*)malloc(width*height*4);
    bool lastsame=false;
    while (1) {

	//printf("Looping\n");
	//Sleep(6500);

	// spy 

	ReadScreen(0, 0, width, height, buffer);
	bool same=false;

	if (!pcmp(buffer,oldbuffer,width*height)) {
	    FILE * fp=fopen("YAY.txt","a");
	    fprintf (fp,"Same\n");
	    same=true;
	    fclose(fp);
	    Sleep(6500);
	    if (lastsame) {
		//SendEsc();
		spawnl(P_WAIT,"escrestart.exe","escrestart.exe",NULL);
	    }
	    lastsame=true;
	}else {
	    FILE * fp=fopen("YAY.txt","a");
	    fprintf (fp,"Diff\n");
	    fclose(fp);
	    //SendPan();
	    lastsame=false;
	}
	unsigned char *tmpbuffer=oldbuffer;
	oldbuffer=buffer;
	buffer=tmpbuffer;
	
	char data[102];
	static int count=0;
	if (!same) {
	    sprintf(data,"output%d.ppm",count++);

	}else {
	    sprintf(data,"output%dX.ppm",count++);
	}
#if 0
	FILE * fp = fopen(data,"wb");
	char* p6head="P6\n1024 768 255\n";
	fwrite(p6head,1,strlen(p6head),fp);
	for (unsigned int i=0;i<height*width;++i) {
	    if (iswhite(&buffer[i*4]) ) {
		unsigned char tmp=0xff;
		fwrite(&tmp,1,1,fp);
		fwrite(&tmp,1,1,fp);
		fwrite(&tmp,1,1,fp);
	    }else {
		unsigned char tmp=0x0;
		fwrite(&tmp,1,1,fp);
		fwrite(&tmp,1,1,fp);
		fwrite(&tmp,1,1,fp);
	    }
	}
	fclose(fp);
#endif
	//SendKey(VK_NUMPAD0);

	printf("DONE DONE DONE\n");
	
	//break;


    }
}

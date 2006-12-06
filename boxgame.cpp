// server_browser.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <iostream>
#include <istream>
#include <vector>
#include<string>
#include <string.h>
#include <map>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#include <process.h>
#include "stdafx.h"
#include "phidget21.h"

#endif
#define NUM_RFID_READERS 4

char input_text[3][8192]={'\0'};
char handle[19]={'\0'};
char * cur_input_text=&input_text[0][0];

CPhidgetRFIDHandle RFID[NUM_RFID_READERS];
bool RFIDpresent[NUM_RFID_READERS];
int RFIDserials[NUM_RFID_READERS]={5603,5573,5626,5616};
volatile bool ready=false;
//#define __APPLE__
#ifdef _WIN32
HANDLE mutex;
#else
pthread_mutex_t mutex;
#endif

void mygetline(char * dat, unsigned int len) {
  std::cin.getline(dat,len);
  return;
  unsigned int i;
  for (i=0;i+1<len;++i) {
    //scanf("%c",&dat[i]);
    //dat[i]=getc(stdio);
    std::cin.get(dat[i]);
    if (dat[i]=='\r'||dat[i]=='\n'){
      dat[i]='\0';
      break;
    }
  }
  if (i+1==len) dat[i]='\0';
}
void mymicro_sleep(int mtime) {
#ifdef _WIN32
    if (mtime>1000)mtime/=1000;
    else mtime=1;
    Sleep(mtime);
#else
    
    struct timeval tv = { 0, 0 };
    tv.tv_usec = mtime%1000000;
    tv.tv_sec=mtime/1000000;
    select(0, NULL, NULL, NULL, &tv);
#endif
}
void * input_thread (void *) {
    while(true) {
	bool dorelease=false;
#ifdef _WIN32
	dorelease= (WaitForSingleObject(mutex,INFINITE)==WAIT_OBJECT_0);
#else
        dorelease=(pthread_mutex_lock(&mutex)==0);
#endif
	do {
  	  mygetline(cur_input_text,4096);
	  cur_input_text[80]='\0';
	  //std::cin.seekg(0,std::ios_base::end);
	}while (strlen(cur_input_text)<2);
	if (dorelease){
#ifdef _WIN32
          ReleaseMutex(mutex);
#else
          pthread_mutex_unlock(&mutex);
#endif
          
        }
	ready=true;
	while(ready){
          //mymicro_sleep(4000);
	}
    }
    
}
bool myisblank(char c) {
 return c==' '||c=='\r'||c=='\n'||c=='\t';
}
std::vector<std::string> presents;
std::map<int,int> rfid_serials;
std::vector<std::string> continents;
std::map<std::string,int> tag_serials;
std::map<std::string,std::string> locations;
std::map<std::string,std::string> goals;
volatile int curloc=-1;
volatile int curpres=-1;
void init_presents() {
		if (RFIDpresent[0]) {
		   rfid_serials[RFIDserials[0]]=continents.size();
           continents.push_back("america");		
		}
		if (RFIDpresent[1]) {
		   rfid_serials[RFIDserials[1]]=continents.size();

           continents.push_back("russia");			
		}
		if (RFIDpresent[2]) {
					   rfid_serials[RFIDserials[2]]=continents.size();

           continents.push_back("europe");			
		}
		if (RFIDpresent[3]) {
          rfid_serials[RFIDserials[3]]=continents.size();

           continents.push_back("china");			
		}
	std::string dolltag;
	dolltag.push_back(0x01);
	dolltag.push_back(0x00);
	dolltag.push_back(0x54);
	dolltag.push_back(0xf0);
	dolltag.push_back(0x97);
	tag_serials[dolltag]=presents.size();
    presents.push_back("doll");
	std::string clothestag;
	clothestag.push_back(0x01);
	clothestag.push_back(0x00);
	clothestag.push_back(0x55);
	clothestag.push_back(0x11);
	clothestag.push_back(0x45);

	tag_serials[clothestag]=presents.size();
    presents.push_back("clothes");
	std::string traintag;
	traintag.push_back(0x01);
	traintag.push_back(0x00);
	traintag.push_back(0x55);
	traintag.push_back(0x44);
	traintag.push_back(0x75);

	tag_serials[traintag]=presents.size();
    presents.push_back("train");
	std::string legotag;
	legotag.push_back(0x01);
	legotag.push_back(0x02);
	legotag.push_back(0x2f);
	legotag.push_back(0x70);
	legotag.push_back(0x05);

	tag_serials[legotag]=presents.size();

    presents.push_back("lego");

	std::string atitag;
	atitag.push_back(0x01);
	atitag.push_back(0x00);
	atitag.push_back(0x56);
	atitag.push_back(0x0a);
	atitag.push_back(0x94);

	tag_serials[atitag]=presents.size();

    presents.push_back("ATI Radeon X1950");
	std::string cookiestag;
	cookiestag.push_back(0x10);
	cookiestag.push_back(0x00);
	cookiestag.push_back(0x02);
	cookiestag.push_back(0xec);
	cookiestag.push_back(0xf9);

	tag_serials[cookiestag]=presents.size();

    presents.push_back("cookies");
	std::string coaltag;
	coaltag.push_back(0x01);
	coaltag.push_back(0x00);
	coaltag.push_back(0x55);
	coaltag.push_back(0xde);
	coaltag.push_back(0x32);

	tag_serials[coaltag]=presents.size();

    presents.push_back("coal");
	std::string housetag;
	housetag.push_back(0x01);
	housetag.push_back(0x02);
	housetag.push_back(0x2f);
	housetag.push_back(0x7f);
	housetag.push_back(0x3f);

	tag_serials[housetag]=presents.size();
    presents.push_back("toy house");
	std::string wiitag;
	wiitag.push_back(0x01);
	wiitag.push_back(0x00);
	wiitag.push_back(0x55);
	wiitag.push_back(0x6f);
	wiitag.push_back(0x06);

	tag_serials[wiitag]=presents.size();

    presents.push_back("wii");
	std::string kittentag;
	kittentag.push_back(0x10);
	kittentag.push_back(0x00);
	kittentag.push_back(0x03);
	kittentag.push_back(0x07);
	kittentag.push_back(0x38);

	tag_serials[kittentag]=presents.size();
    presents.push_back("kitten");
	std::string puppytag;
	puppytag.push_back(0x01);
	puppytag.push_back(0x00);
	puppytag.push_back(0x54);
	puppytag.push_back(0xbd);
	puppytag.push_back(0x52);

	tag_serials[puppytag]=presents.size();
    presents.push_back("puppy");
}
std::string itos(int i) {
  char tmp[10];
  sprintf(tmp,"%d",i);
  return tmp;
}
void make_goals() {
    goals.clear();
	std::string commandline="mplayer.exe --really-quiet intro.wav ";
    for (unsigned int i=0;i<presents.size();++i) {
	if (rand()<RAND_MAX/2) {
	    unsigned int j=(unsigned int)(rand()%continents.size());
	    if (locations[presents[i]]!=continents[j]) {
		goals[presents[i]]=continents[j];
		commandline+=itos(((i+1)/10)%10)+itos((i+1)%10)+itos(j+1)+".wav blank.wav ";
		printf("Deliver %s to %s\n",presents[i].c_str(),continents[j].c_str());
	    }
	}
    }
	system(commandline.c_str());
}
bool check_goals() {
    for (std::map<std::string,std::string>::iterator i=goals.begin();i!=goals.end();++i) {
	if (locations[i->first]!=i->second) {
	    return false;
	}
    }
    return true;
}


volatile bool dorelease=false;
int __stdcall RFID_AttachHandler(CPhidgetHandle RFID, void *userptr)
{
	int serial;
	CPhidget_getSerialNumber((CPhidgetHandle)RFID,&serial);
	printf("RFID_AttachHandler handler ran for ID %d!\n",serial);
	static bool initted=false;
	if (!initted) {
		initted=true;
#ifdef _WIN32
	//dorelease= (WaitForSingleObject(mutex,INFINITE)==WAIT_OBJECT_0);
#else
     dorelease=(pthread_mutex_lock(&mutex)==0);
#endif
	}
	return 0;
}

int __stdcall RFID_DetachHandler(CPhidgetHandle RFID, void *userptr)
{
	int serial;
	CPhidget_getSerialNumber((CPhidgetHandle)RFID,&serial);
	printf("RFID_DetachHandler handler ran for ID %d!\n",serial);
	return 0;
}

int __stdcall RFID_ErrorHandler(CPhidgetHandle RFID, void *userptr, int ErrorCode, const char *unknown)
{
	int serial;
	CPhidget_getSerialNumber((CPhidgetHandle)RFID,&serial);
	printf("RFID_ErrorHandler handler ran for ID %d, Error code %d!\n",serial,ErrorCode);
	return 0;
}

/**
* This is the callback when an RFID tag was received.
* TODO: link this to game logic code
*/
int __stdcall RFID_Handler(CPhidgetRFIDHandle RFID, void *userptr, unsigned char *buf)
{
	int serial;
	CPhidget_getSerialNumber((CPhidgetHandle)RFID,&serial);
	printf("RFID ID: %d; ",serial);	
	printf("TAG: %x%x%x%x%x%x%x%x%x%x\n", buf[0]/16,buf[0]%16,buf[1]/16,buf[1]%16, buf[2]/16,buf[2]%16, buf[3]/16,buf[3]%16, buf[4]/16,buf[4]%16);
	std::string tagid((char*)buf,5);
	if (tag_serials.find(tagid)!=tag_serials.end()) { 
		;
		curpres=tag_serials[tagid];
		curloc=rfid_serials[serial];
		//sprintf(cur_input_text,"%s %s",continents[rfid_serials[serial]].c_str(),presents[tag_serials[tagid]].c_str());

		printf ("SCANNED %s",presents[tag_serials[tagid]].c_str());
	}else {
		printf ("NOT A PRESENT");
	}
	printf (" DELIVERED to %s\n",continents[rfid_serials[serial]].c_str()); 

     bool no_busy=false;
	if (no_busy&&dorelease){
#ifdef _WIN32
          ReleaseMutex(mutex);
#else
          pthread_mutex_unlock(&mutex);
#endif
          
        }
	ready=true;
	//while(ready){
          //mymicro_sleep(4000);
	//}
	if(no_busy) {
#ifdef _WIN32
	dorelease= (WaitForSingleObject(mutex,INFINITE)==WAIT_OBJECT_0);
#else
        dorelease=(pthread_mutex_lock(&mutex)==0);
#endif
	}
	return 0;
}
void RFID_Init() 
{
	int RFIDresult;
	const char *RFIDerr;
	
	for(int j=0;j<NUM_RFID_READERS; j++) {
		RFID[j]=0;
		RFIDpresent[j]=false;
		CPhidgetRFID_create(&(RFID[j]));
		CPhidget_set_OnAttach_Handler((CPhidgetHandle)(RFID[j]), RFID_AttachHandler, NULL);
		CPhidget_set_OnDetach_Handler((CPhidgetHandle)(RFID[j]), RFID_DetachHandler, NULL);
		CPhidget_set_OnError_Handler((CPhidgetHandle)(RFID[j]), RFID_ErrorHandler, NULL);
		RFIDresult = CPhidgetRFID_set_OnTag_Handler(RFID[j], RFID_Handler, NULL);
	}

	//hardcoded serial numbers


	// Try to attach the readers
	printf("Looking for %d RFID readers (for up to 5 seconds each)...\n",NUM_RFID_READERS);
	for(int j=0;j<NUM_RFID_READERS; j++) {
		//Wait for 5 seconds, otherwise exit
		CPhidget_open((CPhidgetHandle)(RFID[j]),RFIDserials[j] ); 

		if(RFIDresult = CPhidget_waitForAttachment((CPhidgetHandle)(RFID[j]), 5000))
		{
			CPhidget_getErrorDescription(RFIDresult, &RFIDerr);
			printf("Problem waiting for attachment: %s\n", RFIDerr);
			RFIDpresent[j]=false;
		} else {
			RFIDpresent[j]=true;
			CPhidgetRFID_setAntennaOn(RFID[j], true);
			CPhidgetRFID_setLEDOn(RFID[j], true);
		}
	}
}
void RFID_Cleanup() {
	for(int j=0; j<NUM_RFID_READERS; j++) {
		CPhidget_close((CPhidgetHandle)(RFID[j]));
		CPhidget_delete((CPhidgetHandle)(RFID[j]));
	}
}

int main(int argc, char ** argv)
{
  {
    char *parentdir;
    int pathlen=(int)strlen(argv[0]);
    parentdir=new char[pathlen+1];
    char *c;
    strncpy ( parentdir, argv[0], pathlen+1 );
    c = (char*) parentdir;
    while (*c != '\0')     /* go to end */
      c++;
    
    while ((*c != '/')&&(*c != '\\')&&c>parentdir)      /* back up to parent */
      c--;
    
    *c = '\0';             /* cut off last part (binary name) */
    if (strlen (parentdir)>0) {  
      chdir (parentdir);/* chdir to the binary app's parent */
    }
    delete []parentdir;
  }    
  chdir("data");
  
  RFID_Init(); /* connect all the rfid readers */
  init_presents();

  char tmphandle[2048]="santa";
 /* while (strlen(tmphandle)>16) {
    std::cout << "What is your handle (under 16 chars please)?\n";
    mygetline(tmphandle,2047);
  }*/
  strncpy(handle,tmphandle,16);
  if (strlen(handle))
    strcat(handle,"> ");
#ifdef _WIN32
  DWORD tid;
#else
  pthread_t thread_id;
#endif
  int total_score=0;
  while(1) {
#ifdef _WIN32
      mutex=CreateMutex(NULL,FALSE,NULL);
#else
      pthread_mutex_init(&mutex,NULL);
#endif
#if 0
#ifdef _WIN32
      CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)input_thread,NULL,0,&tid);
#else
      pthread_create(&thread_id,NULL,input_thread,NULL);
#endif
#endif
      mymicro_sleep(131000);
      int total_time=45;
      make_goals();
      while(total_time>=0) {
	  bool forcepost=false;
          bool doexit=false;
	  if (ready){
            //printf  ("DOSending %s\n",input_text[0]);

	      ready=false;
		  if (curloc>=0&&curpres>=0) {
		    std::string continent=continents[curloc];
		    std::string toy=presents[curpres];
		  
		    locations[toy]=continent;
			if (goals[toy]==continent) {
				printf("YAYYY\n");
				system("mplayer.exe --really-quiet yay.wav");
			}
		  }
              if (check_goals())
                doexit=true;
	      
	      forcepost=true;
	  }
          int ttimeout=1000;//wait a second before checking inputs
          if (forcepost) {
	      printf ("%s\n",input_text[2]);
          }else {
			  if (total_time%10==0||total_time<10){
				  char str[128];
		         printf ("Timeout %d\n",total_time);
 				 sprintf (str,"mplayer.exe --really-quiet %dseconds.wav\n",total_time);
				 system(str);
			  }
          }
          if (doexit){
            break;
          }
#ifdef _WIN32
		  /*
	  if (WaitForSingleObject(mutex,ttimeout)==WAIT_OBJECT_0) {
	      ReleaseMutex(mutex);
	  }*/
		  Sleep(1000);
#else
          for (int i=0;i<ttimeout;++i){
            if (0==pthread_mutex_trylock(&mutex)) {
              pthread_mutex_unlock(&mutex);
              break;
            }
            mymicro_sleep(1000);
          }
#endif
          total_time-=1;
      }
      if (total_time<0) {
        printf ("You Lose\n");
		system ("mplayer.exe --really-quiet youwin.wav");
	total_score-=1;
      }else {
        printf ("You Win\n");
	total_score+=100;
      }
		system ("mplayer.exe --really-quiet youlose.wav");
	  printf ("Your total score is %d\n",total_score);
      
  }
  // always cleanup 
  RFID_Cleanup();

  return 0;
}

// server_browser.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <iostream>
#include <istream>
#include <vector>
#include<string>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#include <process.h>
#endif
char input_text[3][8192]={'\0'};
char handle[19]={'\0'};
char * cur_input_text=&input_text[0][0];
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


  char tmphandle[2048]="12345678910111213141516";
  while (strlen(tmphandle)>16) {
    std::cout << "What is your handle (under 16 chars please)?\n";
    mygetline(tmphandle,2047);
  }
  strncpy(handle,tmphandle,16);
  if (strlen(handle))
    strcat(handle,"> ");
#ifdef _WIN32
  DWORD tid;
#else
  pthread_t thread_id;
#endif
  if(1) {
#ifdef _WIN32
      mutex=CreateMutex(NULL,FALSE,NULL);
#else
      pthread_mutex_init(&mutex,NULL);
#endif
#ifdef _WIN32
      CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)input_thread,NULL,0,&tid);
#else
      pthread_create(&thread_id,NULL,input_thread,NULL);
#endif
      mymicro_sleep(131000);
      int total_time=45;
      while(total_time>=0) {
	  bool forcepost=false;
          bool doexit=false;
	  if (ready){
            //printf  ("DOSending %s\n",input_text[0]);
	      strcpy(input_text[1],input_text[0]);
              strcpy(input_text[2],handle);
	      strcat(input_text[2],input_text[0]);
	      ready=false;
              if (strncmp(input_text[1],"exit",4)==0)
                doexit=true;
	      forcepost=true;
	  }
          int ttimeout=1000;//wait a second before checking inputs
          if (forcepost) {
            printf ("%s\n",input_text[2]);
          }else {
            printf ("Timeout\n");

          }
          if (doexit){
            break;
          }
#ifdef _WIN32
	  if (WaitForSingleObject(mutex,ttimeout)==WAIT_OBJECT_0) {
	      ReleaseMutex(mutex);
	  }
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
      }else {
        printf ("You Win\n");
      }
      
  }
  // always cleanup 

  return 0;
}

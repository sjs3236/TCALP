/*
 * Filename test.cc
 * Date 11/10/2020
 * Author Junsik Seo
 * Email jxs161930@utdallas.edu
 * Version 1.0
 * Copyright 2020, All Rights Reserved
 * Description:
 * This is a program design for UNIX style daemon process 
 * When -d option is given, it will run as daemon in background, otherwise run in foreground
 * This program will parse command and config file.
 * This program will create pid file.
 * This program will use inotify for file modification in some directoy.
 */


#include <iostream>
#include <string.h>
#include <fstream>
#include <map>
#include <tclap/CmdLine.h>
#include <rude/config.h>
#include <unistd.h>
#include <stdio.h>
#include <csignal>
#include <sys/wait.h>
#include "header.h"
#include <sys/inotify.h>
#include <sys/stat.h>
#include <ctime>

using namespace std;
using namespace rude;

std::map <int,string> optionMap;
std::map <int,string> optionMap3;

void signalHandler (int signum);
void createpid (string& name, int content);
void logging (int option);
void parseconf(int option);

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024*(EVENT_SIZE+16))


int main(int argc, char*argv[]){
  
  //Phase 2
  TCLAP::CmdLine cmd("CS3377.001 Program 5",' ',"1.0");
  TCLAP::SwitchArg daemonSwitch("d","daemon","Run in  daemon mode",cmd,false);
  TCLAP::UnlabeledValueArg<std::string> confArg("conf","the name of config file name.",false,"cs3377dirmon.conf","config filename",true);

  // parse command line
  cmd.add(confArg);
  cmd.parse(argc, argv);
  
  //creaet map object that hold values from command line
  enum argumnet {conf};

  map<int, bool> optionMap2;
  enum argument2 {daemon};
  
  //for phase3
  enum arugments3 {Verbose, LogFile, Password, NumVersions,WatchDir};


  optionMap[conf]=confArg.getValue();
  optionMap2[daemon]=daemonSwitch.getValue();

  //Phase 3
  Config config;

  //open config file
  cout<<"Open Config File"<<endl;

   config.load(optionMap[conf].c_str());
   config.setSection("Parameters");
  
  //place config file parameters into map object
   optionMap3[Verbose]=config.getStringValue("Verbose");
   optionMap3[LogFile]=config.getStringValue("LogFile");
   optionMap3[Password]=config.getStringValue("Password");
   optionMap3[NumVersions]=config.getStringValue("NumVersions");
   optionMap3[WatchDir]=config.getStringValue("WatchDir");

   cout<<"Done parse config file"<<endl;

   //phase4
     string pidfile="cs3377dirmon.pid";

   if(optionMap2[daemon]==1){
     pid_t forkvalue;
     forkvalue=fork();

     int status;

    if(forkvalue==-1){
      perror("There was an error in the fork. No child was created.");
      return 1;
    }

    else if (forkvalue==0 ){
      cout<<"Running in background"<<endl;


      FILE *file;
      if (file=fopen(pidfile.c_str(),"r"))
	{
	  cout<<"Pid file detected, delete it and exit fork"<<endl;
	  remove(pidfile.c_str());
	  
	  exit(0);
	}

      char version[20]="/.versions";
      char path1[100];
      strcpy(path1,optionMap3[WatchDir].c_str());
      strcat(path1,version);

      struct stat st1={0};
      if(stat(optionMap3[WatchDir].c_str(),&st1)==-1){
    	mkdir(optionMap3[WatchDir].c_str(),0700);
     }

      struct stat st2={0};
      if(stat(path1,&st2)==-1){
    	mkdir(path1,0700);
     }


      //code for inotify
      // strcpy(path1,optionMap3[WatchDir].c_str());
       int fd;
       int wd;
       char buffer[BUF_LEN];
       fd=inotify_init();
       if(fd<0){
	 perror("inotify_init");
       }
       wd=inotify_add_watch(fd,optionMap3[WatchDir].c_str(),IN_MODIFY);

 
    

       int length, i=0;
	length=read(fd,buffer,BUF_LEN);
	 
	 if(length<0){
	   perror("read");
	 }


   
	 while(i<length){

	   struct inotify_event *event=(struct inotify_event *) &buffer[i];
	    if (event->len){
	     if(event->mask &IN_MODIFY| IN_CREATE | IN_DELETE){
	       printf("The file %s was modified.\n",event->name);
               time_t rawtime;
	       struct tm* timeinfo;
	       char buffer[80];
	       time(&rawtime);
	       timeinfo=localtime(&rawtime);
	       strftime(buffer,sizeof(buffer),".%Y.%d.%m-%H:%M:%S",timeinfo);
	       string str(buffer);

	       char temp[200]="cp -f ";
	       string blank=" ";
	       string slash="/";
	       strcat(temp,optionMap3[WatchDir].c_str());
	       strcat(temp,slash.c_str());
	       strcat(temp,event->name);
	       strcat(temp,blank.c_str());
	       strcat(temp,optionMap3[WatchDir].c_str());
	       strcat(temp,version);
	       strcat(temp,slash.c_str());
	       strcat(temp,event->name);
	       strcat(temp,str.c_str());
	       int tmp=system(temp); 
	       cout<<"File dedected, create copy"<<endl;
	     }
	    }
	    i+=EVENT_SIZE+event->len;
	 }
       

       inotify_rm_watch(fd,wd);
       close(fd);


       createpid(pidfile,getpid());
    }
 
    else{
      int ret;
      ret= waitpid(forkvalue,&status,WNOHANG);
      exit (0);       
     }
   }
  
   logging(1);
   signal (SIGHUP,signalHandler);
   signal (SIGINT,signalHandler); 
   signal (SIGTERM,signalHandler);
   
   while(1){
     sleep(10);
   }

  return 0;

}

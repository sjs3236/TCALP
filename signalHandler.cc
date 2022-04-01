/*
 * Filename signalHandler.cc
 * Date 11/17/2020
 * Author Junsik Seo
 * Email jxs161930@utdallas.edu
 * Version 1.0
 * Copyright 2020, All Rights Reserved
 * Description:
 * This program handler signal that has interrupted in program5.cc 
 */


#include <iostream>
#include <csignal>
#include <stdlib.h>
#include <stdio.h>
#include "header.h"

using namespace std;

void logging(int option);
void parseconf(int option);

void signalHandler(int signum ){
  

  if(signum==SIGINT || signum==SIGTERM){
  cout<<"Interrupt signal ("<<signum<<") received."<<endl;
  remove("cs3377dirmon.pid");
 
  logging(3);

  exit(signum);}
  
  else if(signum==SIGHUP){
    parseconf(1);
    logging(2);
    
      }
}

/*
 * Filename logging.cc
 * Date 11/16/2020
 * Author Junsik Seo
 * Email jxs161930@utdallas.edu
 * Version 1.0
 * CopyRights 2020, All Rights Reserved
 *
 * Description:
 * This is a file that create log file, write a context and exit
 */

#include<iostream>
#include<fstream>
#include"header.h"

using namespace std;

void logging( int option) {
   ofstream logfile;
   enum argumnet{Verbose,LogFile};
    logfile.open(optionMap3[LogFile].c_str(),ios::app);
   

   if (option==1){
     logfile<<"The logfile has created"<<endl;
  }

  else if (option==2){
    logfile<<"log file has modified."<<endl;
  }
  else{
    logfile<<"log file closing."<<endl;
     logfile.close();
  }

}

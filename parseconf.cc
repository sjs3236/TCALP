/*
 * Filename parseconf.cc
 * Date 11/17/2020
 * Author Junsik Seo
 * Email jxs161930@utdallas.eduu
 * Version 1.0
 * Copyright 2020, All Rights Reserved
 * Description:
 * This program parse config file when config file has modified.
 */
#include <iostream>
#include <rude/config.h>
#include "header.h"
#include <map>

using namespace std;
using namespace rude;

void parseconf(int option){
  Config config;
  enum argument{conf,daemon};
  enum argument2{Verbose, LogFile,Password,NumVersions};

  if (option==1){
    config.load(optionMap[conf].c_str());
    config.setSection("Parameters");
    optionMap3[Verbose] =config.getStringValue("Verbose");
    optionMap3[LogFile] =config.getStringValue("LogFile");
    optionMap3[NumVersions] =config.getStringValue("NumVersions");    
    config.save();

  }



}

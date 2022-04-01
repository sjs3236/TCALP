/* 
 * Filename header.h
 * Date 11/10/2020
 * Author Junsik Seo
 * Email jxs161930@utdallas.edu
 * Course CS 3377.001 Fall 2020
 * Version 1.0
 * Copyright 2020, All Rights Reserved
 *
 * Description
 * This is header file that contains prototype of my functions and include guard 
 */

#ifndef __MYSYMBOL__
#define __MYSYMBOL__

#include <string>
#include <map>


extern std::map<int,std::string> optionMap3;
extern std::map<int,std::string> optionMap;


void signalHandler(int signum);
void createpid(std::string& name, int content);
void logging (int option);
void parseconf(int option);

#endif 


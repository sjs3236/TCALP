/*
 * Filename createpid.cc
 * Date 11/10/2020
 * Author Junsik Seo
 * Email jxs161930@utdallas.edu
 * Course CS 3377.001 Fall 2020
 * Version 1.0
 * Copyright 2020, All Right Reserved
 *
 * Description
 * This is a program that create pid file
 */

#include <iostream>
#include <fstream>

using namespace std;

void createpid(string& name, int  content){
  


  ofstream writeFile;
  writeFile.open(name.c_str());
  
  writeFile<<content<<endl;

  writeFile.close();
}

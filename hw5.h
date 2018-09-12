//name:Eric Rogers
//email:ejr140230@utdallas.edu
//course number:CS3376.001

#ifndef HW5_H
#define HW5_H

#include<iostream>
#include<map>
#include"tclap/CmdLine.h"
#include<fstream>
#include"rude/config.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<cstring>
#include<signal.h>
#include<stdio.h>
#include<sys/inotify.h>
#include<linux/limits.h>
#include<ctime>
#include<errno.h>
#include<string>

using namespace std;

extern volatile sig_atomic_t sig_caught; //used for signalHandling
extern ofstream logfile; //output to logfile
extern map<int, string> cmla; //our map of values

extern enum cmlaNames {d, c, v, lf, p, nv, wdir} cmlaVar; //The command line argument's enums for use with cmla map

void reconfigure();//parseConfig.cc

//signalHandling.cc
void handleSIGINT(int signum);
void handleSIGTERM(int signum);
void handleSIGHUP(int signum);

//parseCommandLine.cc
void parseCommandLine(int n, char *v[]);

//inotifyFunctions.cc
void inotify();

//loggingFunctions.cc
void log(string str);

#endif

//name:Eric Rogers
//email:ejr140230@utdallas.edu
//course number:CS3376.001

#include<sstream>

#include"hw5.h"

volatile sig_atomic_t sig_caught = 0; //needed for signal handling(returns number that coincides with signal caught)
ofstream logfile; //creating/accessing logfile
map<int, string> cmla; //holds the values read from command line and the return from reading the config file
enum cmlaNames cmlaVar; //enums mapped to the values stored in the map cmla


int main(int argc, char* argv[])
{
  cout << "Starting hw5." << endl;
  
  //parse the command line with extern function
  parseCommandLine(argc, argv);

  //check if pidfile already exists(daemon already running)
  if(ifstream("cs3376dirmond.pid"))
    {
      //log error message
      printf("Daemon already running(found pidfile). Exiting...\n");
      return 2;
    }

  //check if ran in daemon mode
  if(strcmp(cmla[d].c_str(),"true") == 0)
    {
      cout << "Running in daemon mode." << endl;

      //fork and hold return value
      pid_t daemon = fork();
      if(daemon != 0)
        {
          if(strcmp(cmla[d].c_str(), "true") == 0)
            printf("Killing parent.\n");

          return 0;
	}
    }

  //stdout logging
  cout << "Opening log file" << endl;

  //configure with extern function(adding to map values in config file), then check if all info was available(would return 1 if something missing) 
  reconfigure();

  if(strcmp(cmla[v].c_str(),"true") == 0)
    log("Creating PidFile");

  //create pid file
  ofstream pidfile("cs3376dirmond.pid");

  //print verbose stuff
  if(strcmp(cmla[v].c_str(),"true") == 0)
    {
      stringstream hold;
      hold << "Pid of process ";
      hold << getpid();
      log(hold.str());
    }
      
  //write pid of current process to pidfile
  pidfile << getpid() << endl;
  pidfile.close();
  
  //setup signal handling
  signal(SIGINT, handleSIGINT);
  signal(SIGTERM, handleSIGTERM);
  signal(SIGHUP, handleSIGHUP);

  //loop to keep it running
  while(true)
    { 
      //run inotify function to wait on a modify
      inotify();
    }
}      


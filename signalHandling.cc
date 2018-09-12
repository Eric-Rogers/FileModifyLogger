//name:Eric Rogers
//email:ejr140230@utdallas.edu
//course number:CS3376.001

#include"hw5.h"

void handleSIGINT(int signum)
{
  //double check that the signal is SIGINT
  if(signum == SIGINT)
    {
      log("Signal caught in function(SIGINT)\nexiting...");

      //check if ran in daemon mode and if so delete pidfile
      if(remove("cs3376dirmond.pid") != 0)
	{
	  log("Cannot delete pid file\n");
	}

      //format the log
      log("\n");
      
      //close our logfile
      logfile.close();
      
      //exit the process
      exit(0);
    }
}

void handleSIGTERM(int signum)
{
  //double check that the signal is SIGTERM
  if(signum == SIGTERM)
    {
      log("Signal caught in function(SIGTERM)\nexiting....");
      
      if(remove("cs3376dirmond.pid") != 0)
	{
	  log("Cannot delete pid file\n");
	}

      //format the log
      log("\n");
      
      //close logfile
      logfile.close();
      
      //exit process
      exit(0);
    }
}

void handleSIGHUP(int signum)
{
  //double check if signal is SIGHUP
  if(signum == SIGHUP)
    {
      log("Signal caught in function(SIGHUP)");

      //reread config and redo map stuff
      reconfigure();       
    }
}

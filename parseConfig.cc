//name:Eric Rogers
//email:ejr140230@utdallas.edu
//course number:CS3376.001

#include"hw5.h"

void reconfigure()
{
  //open config file for reading with rudeconfig
  rude::Config config;

  config.load(cmla[c].c_str());

  //go to Parameters section
  config.setSection("Parameters", false);
  
  //check if any of the configs are missing and if so exit 
  if(!config.exists("Verbose") || !config.exists("LogFile") || !config.exists("Password") || !config.exists("NumVersions") || !config.exists("WatchDir"))
    {
      printf("Not all definitions given in conf file or conf file missing\nexiting\n");
      exit(1);
    }
  else
    {
      //save the value of Verbose
      cmla[v] = config.getStringValue("Verbose");

      //check if different logfile, if so close the old and open the new one
      if(strcmp(config.getStringValue("LogFile"), cmla[lf].c_str()))
        {
          cmla[lf] = config.getStringValue("LogFile");

	  //close old and clear
          logfile.close();
          logfile.clear();

	  //open the new
          logfile.open(cmla[lf].c_str(), ios::out);
        }

      //only change password field if it has not already been set
      if(strcmp(cmla[p].c_str(),"") == 0)
        {
          cmla[p] = config.getStringValue("Password");
          log("changed password");
        }

      //save the number of versions to map
      cmla[nv] = config.getStringValue("NumVersions");

      //only change watch directory if it has not already been set
      if(strcmp(cmla[wdir].c_str(),"") == 0)
        {
          cmla[wdir] = config.getStringValue("WatchDir");
	  log("changing watch directory.");
        }

      if(strcmp(cmla[v].c_str(),"true") == 0)
        {
	  stringstream hold;
	  hold << "Map values: " << "daemon: " << cmla[d].c_str() << " , " << "configfile: " << cmla[c].c_str() << " , " << "verbose: " << cmla[v].c_str()
	       << " , " << "logfile: " << cmla[lf].c_str() << " , " << "password: " << cmla[p].c_str() << " , " << "version number: " << cmla[nv].c_str()
	       << " , " << "watch directory: " << cmla[wdir].c_str();
	  log(hold.str());
        }
    }
}

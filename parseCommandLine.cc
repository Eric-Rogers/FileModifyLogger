//name:Eric Rogers
//email:ejr140230@utdallas.edu
//course number:CS3376.001

#include"hw5.h"

void parseCommandLine(int n, char *v[])
{
  try
    {
      //First argument is program description and is printed at bottom of help
      //Second argument is delimiter
      //Third is version number
      TCLAP::CmdLine cmd("CS3376.001 Homework 2: Reads input text file and, based on command line arguments given, changes the text upon writing to an output file.",' ',"2.1");

      //Switch arguments
      //First argument is the short name of flag("u" means -u on command line)
      //Second argument is longname flag("upper" means --upper on command line)
      //Third argument is description of what the argument does
      //Fourth argument is name of CmdLine object that is going to parse the command line
      //Fifth argument is the default value of flag
      TCLAP::SwitchArg daemonSwitch("d", "daemon","Run the program in daemon mode.",cmd,false);

      //Unlabeled value arguments
      //First argument is the name of the parameter
      //Second argument is the description of the value
      //Third argument is a boolean that tells whether the argument is required
      //Fourth argument is the default value
      //Fifth argument is used in the <  > description in help
      //Sixth argument is the CmdLine object this arg is a part of
      //Seventh argument states whether you can ignore the parameter
      TCLAP::UnlabeledValueArg<string> configArg("configfile","The config file's name.",false,"cs3376dirmond.conf","config filename",cmd,false);

      cmd.parse(n,v); //parse the command line looking for arguments associated with cmd

      //bool value stored in daemon switch them to string so it can be stored in the map cmla
      if(daemonSwitch.getValue())
	cmla[d] = "true";
      else
	cmla[d] = "false";

      //store value from configArg into map cmla
      cmla[c] = configArg.getValue();

      if(strcmp(cmla[c].c_str(), "") == 0)
	{
	  string hold = "cs3376dirmond.conf";
	  cmla[c] = hold;
        }
    }
  catch(TCLAP::ArgException &e) //catches any exception
    {
      cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
    }
}

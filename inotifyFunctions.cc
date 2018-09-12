//name:Eric Rogers
//email:ejr140230@utdallas.edu
//course number:CS3376.001

#include"hw5.h"

void inotify()
{
  stringstream hold;

  size_t bufsiz = sizeof(struct inotify_event) + PATH_MAX + 1; //size of buffer
  int EVENT_SIZE = sizeof (struct inotify_event); //defining size of each event

  int length, i = 0; //length will hold read struct and i will be used to cycle through events returned
  int fd; //used to initialize inotify
  int wd; //used to add watch drectory
  char buffer[bufsiz]; //create buffer

  fd = inotify_init(); //initialize inotify and store return status

  //check if inotify initialized successfully 
  if (fd < 0)
    {
      perror( "inotify_init" ); //if initialized unsuccessfully print error
    }

  if(strcmp(cmla[v].c_str(),"true") == 0)
    {
      hold << "Setting watch directory: " << cmla[wdir].c_str();
      log(hold.str());
      hold.str("");
      hold.clear();
    }

  //add watch of directory contained in map whose value we obtained from the config file
  wd = inotify_add_watch( fd, cmla[wdir].c_str(), IN_MODIFY);

  if(strcmp(cmla[v].c_str(),"true") == 0)
    {
      log("Reading for IN_MODIFY.");
    }

  length = read(fd, buffer, bufsiz); //read using fd and store return in buffer, buffer's size is busiz 

  //cycle through events fetected
  while ( i < length )
    {
      //create structure that holds events
      struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
      
      //if there is an event found(length of name of file is more than 0)
      if (event->len)
	{
	  //if the event found is a modify event
	  if ( event->mask & IN_MODIFY )
	    {
	      //log that file was modified
	      hold <<  event->name << " was modified.";
	      log(hold.str());
	      hold.str("");
	      hold.clear();

	      //using stat check if .versions folder exists
	      struct stat buf;
	      string filename = cmla[wdir].c_str();
	      
	      //save the directory watching before we change it(just so we do not have to call .c_str() again)
	      //used as the from part of cp
	      string from = filename;

	      //append to filename the name of our file we are checking for/ copying file into
	      filename.append("/.versions");
	      
	      //save path of .versions folder/ this will be used for the to part of cp 
	      string to = filename;
	      
	      //check for existence of folder .versions/ if does not exist make it
	      if(stat(filename.c_str(), &buf) != 0)
		{
		  const int dir_err = mkdir(filename.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		  if (-1 == dir_err)
		    {
		      log("Error creating directory.\nexiting");
		      exit(1);
		    }
		}

	      //append the name of the file that was modified 
	      from.append("/");
	      from.append(event->name);

	      stringstream value; //used to temporarily hold ouput of popen running date
	      char buff[BUFSIZ]; //buffer for our stream(fp) used when reading from stream
	      
	      FILE *fp;
	      
	      fp = popen("date +.%y.%m.%d-%T", "r"); //run date on shell and store the output
	      while((fgets(buff, BUFSIZ, fp)) != NULL) //loop and get all of the lines from the output of our popen(command in shell) save in buff
		{
		  value << buff; //append each line onto the stringstream value
		}
	      
	      //append filename and date on the end of the to part of cp
	      to.append("/");
	      to.append(event->name);
	      to.append(value.str());
	      
	      string copy = "cp ";
	      copy.append(from).append(" ").append(to);
	      
	      if(strcmp(cmla[v].c_str(), "true") == 0)
		{
		  hold << "Executing on shell: " << copy;
		  log(hold.str());
		  hold.str("");
		  hold.clear();
        	}
	      //run our copy command
	      system(copy.c_str());

	      pclose(fp); //close the stream
	    }
	}
      //increment to next event
      i = EVENT_SIZE + event->len;      
    }

  //close everything
  ( void ) inotify_rm_watch( fd, wd );
  ( void ) close( fd );
}

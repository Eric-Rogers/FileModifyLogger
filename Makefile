#name:Eric Rogers
#email:ejr140230@utdallas.edu
#course number:CS3376.001
# Compiler Specific stuff

CXX = g++
CXXFLAGS = -Wall -O
CPPFLAGS = -I /home/012/e/ej/ejr140230/include -I /home/012/e/ej/ejr140230/HW5/include 

#
# Project Specific stuff
PROJECTNAME = HW5
# used for the backup target
EXECFILE = hw5			# the neme of the executable
OBJS = loggingFunctions.o inotifyFunctions.o parseCommandLine.o parseConfig.o signalHandling.o  hw5.o	# a list of all .o files needed

# Implicit Rule
%.o:%.cc
	$(CXX) $(CPPFLAGS) -M -MF $*.P $<
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@


# This is the first target so it is the default
all: $(EXECFILE)


# Link .o files to create an executable
$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) /home/012/e/ej/ejr140230/lib/librudeconfig.a


clean:
	make backup
	rm -f $(OBJS) *.P *~ \#* #$(EXECFILE)

#
# Note: tar errors will not be displayed.  Check your backups.
#
backup:
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcf $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

tarball:
	make backup
	make clean
	tar cfzv ../tarballs/ejr140230_HW5.tar.gz --exclude=include --exclude=test ../$(PROJECTNAME)

# Include all the header file dependencies
# created by the preprocessor.  The list
# is initially empty after a make clean.
#
# The first full build will create the .P
# files. After the .P files exist and will
# be included.
-include $(OBJS:%.o=%.P)

#!/usr/bin/make -f
#
# Filename Makefile
# Date 11/10/2020
# Author Junsik Seo
# Email jxs161930@utdallas.edu
# Version 1.0
# Copyright 2020, All Rights Reserved
# Description:
# This is makefile that take care of creating dependencies

CC= g++
CCFLAGS= -Wall
CPPFLAGS=-I /home/012/j/jx/jxs161930/include/

LDLIBS=-lrudeconfig 
LDFLAGS=-L /home/012/j/jx/jxs161930/lib


PROJECTNAME= assignment5

EXEC= assign5

SRCS= $(wildcard *.cc)
OBJS= $(patsubst %.cc,%.o,$(SRCS))

.PHONY = all clean backup

all: $(EXEC)

clean:
	rm -f $(OBJS) *.d *~ $(EXEC)

%.d:%.cc
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS)$< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ :,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(EXEC):$(OBJS)
	$(CXX) -static $(CPPFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS) $(LDLIBS)


backup:clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename 'pwd'))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:$S')tar.gz)
	@echo
	@echo Writing backup file to : $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!	


#Ronan Brennan   28/12/2017
#Wator Project

CC=g++
CFLAGS= -std=c++11 -pthread
CFILES= wator.cpp #.cpp files

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(CFILES)  #When changes made to CFILES this runs
	$(CC) -o wator wator.cpp $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -g 00
DEBUG: ALL


CLEAN:	rm *.o #Removes all previous .o files

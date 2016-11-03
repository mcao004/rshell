OBJS = Ampersand.o IndivCmd.o LineCmd.o Semicolon.o Sticks.o
CPP = rshell.cpp src/Ampersand.cpp src/IndivCmd.cpp src/LineCmd.cpp src/Semicolon.cpp src/Sticks.cpp  
CC = g++
FLAGS = -Wall -Werror -ansi -pedantic

all: rshell

rshell: $(CPP)
	@mkdir -p bin
	$(CC) $(FLAGS) $(CPP) -o bin/rshell
clean:
	/rm *.o *~ *.exe


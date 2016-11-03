OBJS = Ampersand.o IndivCmd.o LineCmd.o Semicolon.o Sticks.o
CPP = src/rshell.cpp src/Ampersand.cpp src/IndivCmd.cpp src/LineCmd.cpp src/Semicolon.cpp src/Sticks.cpp  
CC = g++
FLAGS = -Wall -Werror -ansi -pedantic

all: 
	$(CC) $(FLAGS) src/main.cpp $(CCP)
rshell: $(CPP)
	$(CC) $(FLAGS) $(CPP) -o rshell
clean:
	/rm *.o *~ *.exe


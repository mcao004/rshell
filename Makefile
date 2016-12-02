OBJS = Ampersand.o IndivCmd.o LineCmd.o Semicolon.o Sticks.o
<<<<<<< HEAD
<<<<<<< HEAD
CPP = rshell.cpp src/Ampersand.cpp src/IndivCmd.cpp src/LineCmd.cpp src/Semicolon.cpp src/Sticks.cpp src/Parentheses.cpp 
=======
>>>>>>> a8e854f0a0b4a191f89a0a0cec9957ae84002dc1
=======
>>>>>>> a8e854f0a0b4a191f89a0a0cec9957ae84002dc1
CC = g++
FLAGS = -Wall -Werror -ansi -pedantic

all: rshell

rshell: $(CPP)
	@mkdir -p bin
	$(CC) $(FLAGS) $(CPP) -o bin/rshell
clean:
	/rm *.o *~ *.exe


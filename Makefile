OBJS = 
CC = g++
FLAGS = -Wall -Werror -ansi -pedantic

all: 
	$(CC) $(FLAGS) src/main.cpp 
rshell: rshell.sh
	$(CC) $(FLAGS) rshell
clean:
	/rm *.o *~ *.exe


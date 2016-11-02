#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio.h>
#include <unistd.h>
#include <string>
#include <cstring>
//#include <boost/tokenizer.hpp>

//including our own files
#include "Semicolon.h"
#include "Sticks.h"
#include "Ampersand.h"
#include "LineCmd.h"
#include "IndivCmd.h"

// parse the line of input into a vector of the commands and their connectors in order of appearance
char** parse(string input) {
	string temp = input;
	string delim1 = ";";
	string delim2 = "&&";
	string delim3 = "||";

	char* argv[
	for(int i = 0; i < input.size(); i++) {
		
	}


}

void execute(char* argv[], int argc) { // passed in a single command in array form with the num of elements where argv[argc] = '\0'
	pid_t pid;
	pid_t tpid;

	pid = fork(); #child's pid
	if (pid < 0) { // negative or failed
		perror("Error: fork failed\n" );
		exit(1);
	}	
	else if (pid == 0) { //child process
		if (execvp(*argv, argv) < 0) {
			perror("Error: execvp failed\n");
			exit(1);
		}
	}
	else { // parent
		while(1){
			tpid = waitpid(pid, NULL, 0);
			if (tpid == -1) { //then #perror check
				perror("Error: Waitpid failed" );
				exit(1);
			}
			else if (tpid == 0) {//# child running
				; // do nothing and wait for child
			}
			else #child done
				break; // to execute parent
		}
	}
	object.execute();
}

unsigned findHash(string input) {
	return input.find_first_of('#');
}

int main( )
{
	unsigned i = 0;
	string comment = "";
	while (1) {
		// prompt and take in input 
		read -p "$" input
		
		//check for comments and separate
		if ((i = input.find("#")) != string::npos) { // there exists a #
			comment = input.substr(i, string::npos);
			input = input.substr(0, i);
		}
		// split up remaining commands
		parse(input);
		
		// execute those commands
		
		execute(argv);
		
	}
}

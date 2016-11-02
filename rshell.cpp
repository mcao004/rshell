#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <cstring>
//#include <boost/tokenizer.hpp>

//including our own files
#include "Semicolon.h"
#include "Sticks.h"
#include "Ampersand.h"
//#include "LineCmd.h"
#include "IndivCmd.h"

// parse the line of input into a vector of the commands and their connectors in order of appearance
char** parse(string input) {
	string inputcopy = input;
	string delim1 = ";";
	string delim2 = "&&";
	string delim3 = "||";
	string b = "";

	char* semicolon = const_cast<char*>(delim1.c_str());
	char* ampersand = const_cast<char*>(delim2.c_str());
	char* stick = const_cast<char*>(delim3.c_str());
	char* blank = const_cast<char*>(b.c_str());

	char* argv[256];
	char* ctemp = blank;
	int currarg = 0;
	for(int i = 0; i < input.length(); i++) {
		if (inputcopy.at(i) == ';'){ // full connector
			argv[currarg] = ctemp;
			ctemp = blank;
			currarg++;
			// add ';' into argv
			argv[currarg] = semicolon;
			currarg++;
		}else if (inputcopy.at(i) == '&'){
			if (i+1 != inputcopy.length() && inputcopy.at(i+1) == '&') {
				// end the prev command
				argv[currarg] = ctemp;
				ctemp = blank;
				currarg++;
				// add another for the "&&"
				argv[currarg] = ampersand;
				currarg++;
				// iterate i since we are using 2 characters
				i++;
			} else { // only single '&' present => still works in bash, so it'll work here too
				// add last ctemp to argv
				argv[currarg] = ctemp;
				ctemp = blank;
				currarg++;
				// add another to represent the split
				argv[currarg] = ampersand;
				currarg++;
			}
		}else if (inputcopy.at(i) == '|'){
			if (i + 1 < copyinput.length() && copyinput.at(i+1) == '&') { // this means "&&"
				argv[currarg] = ctemp;
				ctemp = blank;
				currarg++;
				// add "||" into argv
				argv[currarg] = sticks;
				currarg++;
				// iterate i, so we continue normally
				i++;
			} else { // only single | present but still works in bash, so it'll work here too since the directions were somewhat vague
				argv[currarg] = ctemp;
				ctemp = blank;
				currarg++;
				// add '|' into argv
				argv[currarg] = sticks;
				currarg++;
			}
		}else if (inputcopy.at(i) == ' ') { // separate by spaces to parse each argument
			argv[currarg] = ctemp;
			ctemp = blank;
			currarg++;
		}else {// none of the possible connectors
			strcat(ctemp, inputcopy.at(i)); // => ctemp += inputcopy.at(i);
		}

		if (currarg == 63)
			cout << "Too many arguments" << endl;
	}
	// when we reach the end the last string is likely still in ctemp
	if (ctemp == blank) {
		argv[currarg] = ctemp;
		ctemp = blank;
		currarg++;
	}
	// add the NULL at the end of argv
	argv[currarg] = NULL;

	return argv;
}

void execute(char* argv[], int argc) { // passed in a single command in array form with the num of elements where argv[argc] = '\0'
	pid_t pid;
	pid_t tpid;

	pid = fork();// #child's pid
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
	//object.execute();
}

/*unsigned findHash(string input) {
	return input.find_first_of('#');
}*/

int main( )
{
	unsigned i = 0;
	string comment = "";
	char** args[256];
	while (1) {
		// prompt and take in input 
		read -p "$" input
		
		//check for comments and separate
		if ((i = input.find("#")) != string::npos) { // there exists a #
			comment = input.substr(i, string::npos);
			input = input.substr(0, i);
		}
		// parse remaining commands/argumets
		args = parse(input);
		
		// split args into command and argument sections and build structure to hold them
		
		// if command is exit, exit


		// execute those commands
		
		execute(argv);
		
	}
}

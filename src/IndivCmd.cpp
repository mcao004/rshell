
#include "IndivCmd.h"

IndivCmd::IndivCmd(char** argv) 
:argv(argv)
{}

void IndivCmd::test(char** args) { 
	// args is assumed to have "test" or "[" followed by arguments
	int end;
	// 0 is location of "test" or "["
	// find end of args, so we don't seg fault
	for (end = 0; strcmp(args[end],"]") != 0 && strcmp(args[end],"\0") != 0; end++) {}
	// now end is the index after the last argument
	// actual test of arguments
	if (end == 1) { // no arguments
		cout << "(FALSE)" << endl;
		executed = false;
	} else if (end == 2) { // 1 argument true if not NULL
		if (strcmp(args[end-1],"\0") == 0){
			cout << "(FALSE)" << endl;
			executed = false;
		} else {
			cout << "(TRUE)" << endl;
			executed = true;
		}
	} else if (end == 3){ // 2 arugments
		if (strcmp(args[1],"!") == 0){ // true if second arg is null
			if (strcmp(args[2], "\0") == 0){
				cout << "(TRUE)" << endl;
				executed = true;
			} else {
				cout << "(FALSE)" << endl;
				executed = false;
			}
		} else if (false) { // if valid unary conditional operator under syntax rules, true
			cout << "(TRUE)" << endl;
			executed = true;
		} else { // not a valid unary conditional operator, false
			cout << "(FALSE)" << endl;
			executed = false;
		}
	} else if (end == 4) { // 3 arguments
		if (true) { // if binary condtionala operator, resutl fo binary test using the 1st and 3rd as args
			cout << "Binary combination" << endl;
		} else if (true) { // if first if "!", negation of two argument test
			cout << "Negation of two args" << endl;
		} else if (true) { // if first ( and third ), result is one-arg test of second
			cout << "Args in parentheses" << endl;
		} else { // else false
			cout << "(FALSE)" << endl;
		}
	} else if (end == 5) { // 4 arguments
		cout << "4 args" << endl; 
	} else { // 5+ arguments -> parsed and evaluated according to precedence
		cout << "No" << endl;
	}
}

// has the ability to execute the command that it stores in argv
void IndivCmd::execute() {
	if (prev && !(prev->executed)){ // if prev didn't execute
		return;
	}
	if (strcmp(argv[0],"exit")== 0) {
		exit(0);
	}
	if (strcmp(argv[0],"test") == 0 || strcmp(argv[0], "[") == 0) {
		test(argv);
	}

	pid_t pid;
	pid_t tpid;
	executed = false;

	pid = fork();
	if(pid < 0) { // fail
		perror("Error: fork failed\n" );
		exit(1);
	} else if (pid == 0) { // child
		if (execvp(argv[0], argv) < 0) {
			executed = false;
			//cout << "Arg 1 = " << argv[0] << endl;
			perror("Error: execvp failed\n");
		} executed = true;
	} else {// parent process
		while(1) {
			tpid = waitpid(pid,NULL, 0);
			if(tpid == -1) {
				perror("Error: waitpid failed\n");
				exit(1);
			} else if (tpid == 0) { // child running
				;
			} else {// child done
				break;
			}
		}
	}
	// if parent reaches this point, then
	//executed = true; 
}

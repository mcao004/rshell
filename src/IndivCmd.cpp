
#include "IndivCmd.h"

IndivCmd::IndivCmd(char** argv) 
:argv(argv)
{}

IndivCmd::~IndivCmd() {
	cout << "IndivCmd destructor" << endl;
	delete argv;
}

// more of a file test than anything else
// honestly could have better organized this such as returning a bool and cout/setting executed based on that outside of the test class
void IndivCmd::test(char** args) { 
	// args is assumed to have "test" or "[" followed by arguments
	int end;
	// 0 is location of "test" or "["
	
	// find end of args, so we don't seg fault
	for (end = 0; strcmp(args[end],"]") != 0 && strcmp(args[end],"\0") != 0; end++) {}
	// now end is the index after the last argument
	
	// actual test of arguments
	if (end == 1) { // no arguments otherwise known as only "test"
		cout << "(FALSE)" << endl;
		executed = false;
	} else if (end == 2) { // 1 argument true if not NULL, if regular test, but in this case we default to -e and check path
		struct stat bf; // stat buffer
		
		// now check if file exists
		if (stat(args[1], &bf) != -1) {
			cout << "(TRUE)" << endl;
			executed = true;
		} else {
			cout << "(FALSE)" << endl;
			executed = false;
		}
	} else if (end == 3){ // 2 arugments, so all unary operators or !
		if (strcmp(args[1],"!") == 0){ // true if second arg is null
			struct stat bf;

			if (stat(args[1], &bf) == -1){ // negation of file existing
				cout << "(TRUE)" << endl;
				executed = true;
			} else {
				cout << "(FALSE)" << endl;
				executed = false;
			}
		} else if (strcmp(args[1],"-e") == 0 || strcmp(args[1], "-f") == 0 || strcmp(args[1],"-d") == 0) { // if -e, -f, or -d, perform the operation on following operator
			struct stat bf;

			if (stat(args[1], &bf) == -1) { // if doesn't exist, cannot fulfill any of the three flag conditions
				cout << "(FALSE)" << endl;
				executed = false;
			} else {
				if (strcmp(args[1],"-d") == 0) {
					if (S_ISDIR(bf.st_mode)) { // checks if directory
						cout << "(TRUE)" << endl;
						executed = true;
					} else {
						cout << "(FALSE)" << endl;
						executed = false;
					}
				} else if (strcmp(args[1],"-f") == 0) {
					if (S_ISREG(bf.st_mode)) {
						cout << "(TRUE)" << endl;
						executed = true;
					} else {
						cout << "(FALSE)" << endl;
						executed = false;
					}
				} else { // -e
					cout << "(TRUE)" << endl;
					execute = true;
				}
			}
		} else { // not a valid unary conditional operator, false
			cout << "(FALSE)" << endl;
			executed = false;
		}
	} else if (end == 4) { // 3 argument -> our case: ( filepath ) and -e -f filepath does not work, but ! -e vim seems to work with its respective order
		if (strcmp(args[1],"!") == 0) { // checks if this number of arguments could work
			if (strcmp(args[2],"-e") == 0 || strcmp(args[2],"-d") == 0 || strcmp(args[2],"-f") == 0) {
				struct stat bf;
				
				// test if file actually exists
				if (stat(arg[3],bf) == -1) {
					cout << "(FALSE)" << endl;
					executed = false;
				} else {
					if (strcmp(args[2],"-d") == 0) {
						if (S_ISDIR(bf.st_mode)) { // if directory
							cout << "(TRUE)" << endl;
							executed = true;
						} else {
							cout << "(FALSE)" << endl;
							executed = false;
						}
					} else if (strcmp(args[2], "-f") == 0) {
						if (S_ISREG(bf.st_mode)) { // if regular file
							cout << "(TRUE)" << endl;
							executed = true;
						} else {
							cout << "(FALSE)" << endl;
							executed = false;
						}
					} else { // if file exists
						cout << "(TRUE)" << endl;
						executed = true;
					}
				}
			} else { // not a combination of arguments that will work
				cout << "(FALSE)" << endl;
				executed = false;
			}
		} else { // else false since 
			cout << "(FALSE)" << endl;
			executed = false;
		}
	} else { // test does not seem to handle parentheses in its arguments, so we cannot go larger in terms of argument number
		cout << "(FALSE)" << endl;
		executed = false;
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

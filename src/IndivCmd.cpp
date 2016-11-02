
#include "IndivCmd.h"

IndivCmd::IndivCmd(char** argv) 
:argv(argv)
{}

// has the ability to execute the command that it stores in argv
void IndivCmd::execute() {
	if (strcmp(argv[0],"exit")== 0)
		exit(0);

	pid_t pid;
	pid_t tpid;
	executed = false;

	pid = fork();
	if(pid < 0) { // fail
		perror("Error: fork failed\n" );
		exit(1);
	} else if (pid == 0) { // child
		if (execvp(argv[0], argv) < 0) {
			perror("Error: execvp failed\n");
			exit(1);
		}
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
	executed = true; 
	//cout << "Hello world" << endl;
}


#include "IndivCmd.h"

IndivCmd::IndivCmd(char** argv) 
:argv(argv)
{}

void IndivCmd::execute() {
	pid_t pid;
	pid_t tpid;

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
			} else // child done
				break;
		}
	}
	//cout << "Hello world" << endl;
}

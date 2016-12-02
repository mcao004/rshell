
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
	for (end = 0; args[end] &&  strcmp(args[end],"]") != 0 && strcmp(args[end],"\0") != 0; end++) {}
	// now end is the index after the last argument
	
	// actual test of arguments
	if (end == 1) { // no arguments otherwise known as only "test"
		cout << "(False)" << endl;
		executed = false;
	} else if (end == 2) { // 1 argument true if not NULL, if regular test, but in this case we default to -e and check path
		struct stat bf; // stat buffer
		
		// now check if file exists
		if (stat(args[1], &bf) != -1) {
			cout << "(True)" << endl;
			executed = true;
		} else {
			cout << "(False)" << endl;
			executed = false;
		}
	} else if (end == 3){ // 2 arugments, so all unary operators or !
		if (strcmp(args[1],"!") == 0){ // true if second arg is null
			struct stat bf;

			if (stat(args[1], &bf) == -1){ // negation of file existing
				cout << "(True)" << endl;
				executed = true;
			} else {
				cout << "(False)" << endl;
				executed = false;
			}
		} else if (strcmp(args[1],"-e") == 0 || strcmp(args[1], "-f") == 0 || strcmp(args[1],"-d") == 0) { // if -e, -f, or -d, perform the operation on following operator
			struct stat bf;

			if (stat(args[2], &bf) != -1) { // if exists
				if (strcmp(args[1],"-d") == 0) {
					if (S_ISDIR(bf.st_mode)) { // checks if directory
						cout << "(True)" << endl;
						executed = true;
					} else {
						cout << "(False)" << endl;
						executed = false;
					}
				} else if (strcmp(args[1],"-f") == 0) {
					if (S_ISREG(bf.st_mode)) {
						cout << "(True)" << endl;
						executed = true;
					} else {
						cout << "(False)" << endl;
						executed = false;
					}
				} else { // -e
					cout << "(True)" << endl;
					executed = true;
				}
			} else {
				cout << "(False)" << endl;
				executed = false;
			}
		} else { // not a valid unary conditional operator, false
			cout << "(False)" << endl;
			executed = false;
		}
	} else if (end == 4) { // 3 argument -> our case: ( filepath ) and -e -f filepath does not work, but ! -e vim seems to work with its respective order
		if (strcmp(args[1],"!") == 0) { // checks if this number of arguments could work
			if (strcmp(args[2],"-e") == 0 || strcmp(args[2],"-d") == 0 || strcmp(args[2],"-f") == 0) {
				struct stat bf;
				
				// test if file actually exists
				if (stat(args[3],&bf) == -1) {
					cout << "(True)" << endl;
					executed = true;
				} else {
					if (strcmp(args[2],"-d") == 0) {
						if (!S_ISDIR(bf.st_mode)) { // if directory
							cout << "(True)" << endl;
							executed = true;
						} else {
							cout << "(False)" << endl;
							executed = false;
						}
					} else if (strcmp(args[2], "-f") == 0) {
						if (!S_ISREG(bf.st_mode)) { // if regular file
							cout << "(True)" << endl;
							executed = true;
						} else {
							cout << "(False)" << endl;
							executed = false;
						}
					} else { // if file exists
						cout << "(False)" << endl;
						executed = false;
					}
				}
			} else { // not a combination of arguments that will work
				cout << "(False)" << endl;
				executed = false;
			}
		} else { // else false since 
			cout << "(False)" << endl;
			executed = false;
		}
	} else { // test does not seem to handle parentheses in its arguments, so we cannot go larger in terms of argument number
		cout << "(False)" << endl;
		executed = false;
	} 
}


// performs the change of directory using PWD, OLDPWD, setenv, getenv
void IndivCmd::cd(char** args) {
    //cout << "Start cd" << endl;
    // case where there is no second argument => change to home directory 
    if (!args[1] || args[1] == NULL || args[1] == '\0') {
        char* pwd = getenv("HOME");
	char curr[4096];
        if (curr == NULL) {
        	perror("getenv HOME");
		return;	
	}
	strcpy(curr,pwd);
	char old[4096];
	strcpy(old,curr);
        if (chdir(curr) != 0) {
		perror("chdir HOME");
		return;
	} else if (-1 == setenv("PWD", curr, 1))
        	perror("setenv HOME");
	else if (-1 == setenv("OLDPWD", old,1))
		perror("setenv old");
	else {  // set pwd pointer's data to what we are working with
		strcpy(pwd,curr);
		executed = true;
	}
    } else if (strncmp(args[1], "../", 2) == 0) { // case where the second argument is ".."
        // this problem needs to be perfomed recursively for ../../../etc.
	char copy[4096];
	strcpy(copy,args[1]);
	char* currarg = copy;
	//cout << ".. case: " << currarg << endl;
	
	char* pwd = getenv("PWD");
	// keep separate a  pointer to our actual pwd and what we are modifing til the end
	char curr[4096];
	if (curr == NULL ) {
		perror("getenv PWD");
		return;
	}
	strcpy(curr,pwd);
	// keep track of the old path to store into oldpwd
	char old[4096];
	strcpy(old,pwd);


	char* temp;
	unsigned lastslash = 0; // index of last slash
	

	// iterative changes to curr until we are out of "../"'s in args[1]
	// In other words, for every "../" in currarg, we go back a directory
	while (strncmp(currarg, "../miscellaneous", 3) == 0) {
		//cout << "we have ../" << endl;
		if (strlen(curr) <= 1) { // current path is only "/"
			//cout << "current path length <= 1" << endl;
		} else { 
			// find the last forward slash to environment
			temp = strrchr(curr,'/'); // last occurrence of slash
			if (temp == NULL) {
	//			cout << "somehow did not find '/'" << endl;
				return;
			}

			// if our current directory ends with '/'
			
			
			lastslash = temp-curr+1; // store index of lastslash
			curr[lastslash-1] = '\0';

			// checking the flow of our navigation
			//cout << "arg: " << currarg+3 << endl;
			//cout << "dir: " << curr << endl;
		}
		// get rid of first three chars of currarg
		currarg += 3;
	}
	// after all of the "../"'s there may be a .. or some other directory left.
	if (strcmp(currarg,"..") == 0) {
		if (strlen(curr) == 1) {
	//		cout << "current path length == 1" << endl;
		} else {
			temp = strrchr(curr,'/');
			if (temp == NULL) {
	//			cout << "somehow did not find '/'" << endl;
				return;
			}
			lastslash = temp-curr+1;
			curr[lastslash-1] = '\0';

	//		cout << "arg: " << currarg+3 << endl;
	//		cout << "dir: " << curr << endl;
		}
		currarg += 3;
	} else { // some other directory navigation => same as general case
		unsigned numtoappend = strlen(currarg);
		if (currarg[numtoappend-1] == '/')
			numtoappend--;
		
		strcat(curr,"/");
		strncat(curr,currarg,numtoappend);
		curr[strlen(curr)] = '\0';	
	}

	// set newpath as the current directory
	if (chdir(curr) != 0) {
		perror("chdir PWD to ..");
		return;
	} else if (-1 == setenv("PWD", curr, 1))
		perror("setenv PWD to ..");
	else if (-1 == setenv("OLDPWD", old, 1))
		perror("setenv OLDPWD from ..");
	else {
		strcpy(pwd,curr);
		executed = true;
	}
    }else if (strcmp(args[1],"-") == 0) {// case where there is '-' => change to PWD
        char* pwd = getenv("PWD");
	char curr[4096];
        if (curr == NULL) {
            perror("getenv PWD");
	    return;
	}
	strcpy(curr,pwd);
        char* old = getenv("OLDPWD");
        if (old == NULL)
            perror("getenv PWD");
        else if (chdir(old) != 0) {
	    perror("chdir to OLDPWD");
	    return;
	} else if (-1 == setenv("PWD", old, 1))
            perror("setenv PWD to last dir");
        else if (-1 == setenv("OLDPWD", curr, 1))
            perror("setenv OLDPWD to current dir");
	else { // if all works, then assign the path to pwd
	    strcpy(pwd,curr);
	    executed = true;
	}
    } else {// default/general case
        // NOTE: the second argument may work with or without a '/' char at the end
	unsigned numtoappend = strlen(args[1]); // all of the chars in argument
	if (args[1][numtoappend-1] == '/') {// if last part of args is '/'
		numtoappend--;
	} // got rid of any excess / at end of new path

	char* pwd = getenv("PWD"); // actual pointer
	char curr[4096]; // copy of the path
	if (curr == NULL) {
		perror("getenv PWD");
		return;
	}
	strcpy(curr,pwd);
	char old[4096];
	strcpy(old,curr);
	
	// append the / to end of current path
	strcat(curr,"/");
	// append the argument to our current environment
	strncat(curr,args[1],numtoappend);
	curr[strlen(curr)] = '\0';
	//cout << "This is the new path: " << curr << endl;
	if (chdir(curr) != 0) {
		perror("chdir to new path");
		return;
	} else if ( -1 == setenv("PWD", curr, 1))
		perror("setenv on new path");
	else if (-1 == setenv("OLDPWD", old, 1))
		perror("setenv of old path");
	else {// final assignment of path to actual pointer
		strcpy(pwd,curr);
		executed = true;
	}
    }//cout << "End cd" << endl;
}

// has the ability to execute the command that it stores in argv
void IndivCmd::execute() {
	//cout << "Indiv execute" << endl;
		
	if (prev && !(prev->executed)){ // if prev didn't execute
		return;
	}

	if (argv[0] && strcmp(argv[0],"exit")== 0) {
		exit(0);
	}	

	if (strcmp(argv[0],"test") == 0 || strcmp(argv[0], "[") == 0) {
		test(argv);
		return;
	}
	
	if (strcmp(argv[0], "cd") == 0 ) {
		cd(argv);
		return;
	}
	
	pid_t pid;
	pid_t tpid;
	executed = false;
	int share_id;
	bool *sharedExecuted = 0;

	// create shared memory
	share_id = shmget(IPC_PRIVATE,sizeof(sharedExecuted),S_IRUSR|S_IWUSR);
	sharedExecuted = (bool *)shmat(share_id,NULL,0);

	pid = fork();
	if(pid < 0) { // fail
		perror("Error: fork failed\n" );
		exit(1);
	} else if (pid == 0) { // child
		*sharedExecuted = true;
		if (execvp(argv[0], argv) < 0) {
			*sharedExecuted = false;
			//cout << "Arg 1 = " << argv[0] << endl;
			perror("Error: execvp failed\n");
			kill(getpid(),SIGTERM);
		} else {
			*sharedExecuted = true;
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
				executed = *sharedExecuted;
				/*if (executed)
					cout << "true" << endl;
				else
					cout << "false" << endl;*/
				shmdt(sharedExecuted);
				shmctl(share_id,IPC_RMID,NULL);
				break;
			}
		}
	}
	/*if (executed)
		cout << "true" << endl;
	else
		cout << "false" << endl;*/
	// if parent reaches this point, then
	//executed = true; 
}

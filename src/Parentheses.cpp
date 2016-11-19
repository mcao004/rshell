
#include "Parentheses.h"

// input: the args that make up the test
Parentheses::Parentheses(char** args) 
: lastexecuted(0), innerLineCmd(0)
{
	innerLineCmd = new LineCmd("");
	init(args);
//	cout << "End init" << endl;
}

// adds a single command to our vector
void Parentheses::add(Cmd* c) {
	// init innerLineCmd

	innerLineCmd->add(c);	
}

void Parentheses::execute() {
	// similar to LineCmd
	innerLineCmd->execute();
	/*for (int i = 0; i < v.size(); i++) { // go through all the commands while also keeping track of the last actually executed
		if (i%2 == 1 && v.at(i)->executed) // every two is a IndivCmd, so if operand executes true
			lastexecuted = v.at(i+1);
	}*/
	executed = innerLineCmd->executed;
}

void Parentheses::init(char** args) {
	char** cmdArgs = new char*[1024];
	int cmdsize = 0;
	int curr = 0;
	vector<Cmd*> v;
	
	while (args[curr]) {
			//cout << "args[" << curr << "]: " << args[curr] << endl;
			/*if (strcmp(args[curr],"test") == 0) {
				cmdArgs[cmdsize] = NULL;
				v.push_back(new testCmd(
				
			} else*/ // will use when finished fixing the problem
			if (strcmp(args[curr], "") == 0) {
				;// do nothing since the cmd is nonexistent
			} else if (strcmp(args[curr], ";") == 0) { // for each delimiter, push_back the Cmd, and add the delimiter
				// null terminate the char*
				if (cmdsize != 0) {
					cmdArgs[cmdsize] = NULL;
					// push back the previous cmd and then the operator
					v.push_back(new IndivCmd(cmdArgs));
					cmdArgs = new char*[1024];
				}
				v.push_back(new Semicolon());
				// reset cmdsize (the size of cmdArgs)
				cmdsize = 0;
			} else if (strcmp(args[curr], "||") == 0) { // same as before
				if (cmdsize != 0) {
					cmdArgs[cmdsize] = NULL;
					v.push_back(new IndivCmd(cmdArgs));
					cmdArgs = new char*[1024];
				}
				v.push_back(new Sticks());
				cmdsize = 0;
			} else if (strcmp(args[curr], "&&") == 0) {
				if (cmdsize != 0) {
					cmdArgs[cmdsize] = NULL;
					v.push_back(new IndivCmd(cmdArgs));
					cmdArgs = new char*[1024];
				}
				v.push_back(new Ampersand());
				cmdsize = 0;
			} else if (strcmp(args[curr], "(") == 0) { // parentheses case
				if (cmdsize != 0) { // some case handler where there is a cmd directly before the '('
					cmdArgs[cmdsize] = NULL;
					v.push_back(new IndivCmd(cmdArgs));
					cmdArgs = new char*[1024];
					cmdsize = 0;
				}
				// find the closing parenthesis and pass in the cmds in between
				curr++; // go to cmd after ')'
//				cout << "What are we passing into Parentheses: " << endl;
				// using cmdArgs to pass into the Parentheses
				for (unsigned l = 0; strcmp(args[curr], ")") != 0 && args[curr] != '\0'; l++) { // probably should be while loop
					if (strcmp(args[curr], "") != 0) {
						cmdArgs[cmdsize] = new char[128];

//						cout << "args[" << cmdsize << "]: " << args[curr] << endl;

						strcpy(cmdArgs[cmdsize], args[curr]);
						cmdsize++;
						curr++;
						}
				}
				if (args[curr] == '\0') {
					perror("Did not end '('  with ')");
					return;
				}
				cmdArgs[cmdsize] = NULL;
				
				// create Parentheses where they implement the LineCmd similarly
				v.push_back(new Parentheses(cmdArgs));
				
				cmdArgs = new char*[1024];
				cmdsize = 0;
				// set the next curr as after ')'
			} else if (strcmp(args[curr], "[") == 0) { // brackets case
				// if starts with "test" will be treated as regular cmd but with special functionality in IndivCmd
				
				// if has something in the cmdArgs before '['
				if (cmdsize != 0) {
					cmdArgs[cmdsize] = NULL;
					v.push_back(new IndivCmd(cmdArgs));
					cmdArgs = new char*[1024];
					cmdsize = 0;
				}
				// set [ as first arg and includes up to and including ]
				cmdArgs[cmdsize] = new char[128];
				strcpy(cmdArgs[0], "[");
				cmdsize++;
				curr++;

				// set all the args leading to "]" into test
				while(args[curr] != '\0' && strcmp(args[curr],"]") != 0 ) {
					cmdArgs[cmdsize] = new char[128];
					strcpy(cmdArgs[cmdsize],args[curr]);
					cmdsize++;
					curr++;
				}
				if (args[curr] == '\0') {
					perror("Error: did not end test with ']'.");
					return;
				}

				// set last arg as "]" and then null
				cmdArgs[cmdsize] = new char[128];
				strcpy(cmdArgs[cmdsize],args[curr]);
				cmdsize++;
				curr++;

				// push back the cmd
				//cmdArgs[cmdsize] = NULL;
				//v.push_back(new IndivCmd(cmdArgs));
				//cmdArgs = new char*[1024];
				//cmdsize = 0;
						
			} else { // otherwise, either a cmd or an argument 
				cmdArgs[cmdsize] = new char[128];
				strcpy(cmdArgs[cmdsize],args[curr]);
				cmdsize++;
			}
			curr++;
	} 
	// end with the last cmd not yet pushed in
	if (strcmp(cmdArgs[0], "") != 0) {
		v.push_back(new IndivCmd(cmdArgs));
	}

//	cout << "parentheses vector size: " << v.size() << endl;
		
	// init innerLineCmd
	for (unsigned i = 0; i < v.size(); i++) {
		this->add(v.at(i));
	}
}

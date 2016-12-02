#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <cstring>
#include <boost/tokenizer.hpp>
#include <vector>

//including our own files
#include "src/Semicolon.h"
#include "src/Sticks.h"
#include "src/Ampersand.h"
#include "src/LineCmd.h"
#include "src/IndivCmd.h"
#include "src/Parentheses.h"

using namespace std;

char* noSpaces(char* string) {
	int j = 0; unsigned i = 0;
	char* result = string;
	for (;i<strlen(string); i++){
		if(string[i]!=' ')
			result[j] = string[i];
		else
			j--;
		j++;
	}
	result[j] = 0;
	return result;
}

// parse the line of input into a vector of the commands and their connectors in order of appearance
char** parse(string input) {
	string inputcopy(input);
	
	string delim1 = ";";
	string delim2 = "&&";
	string delim3 = "||";
	string delim4 = "(";
	string delim5 = ")";
	string delim6 = "[";
	string delim7 = "]";
	string b = "\0";

	/*boost::char_separator<char> sep(";&|");
	boost::tokenizer< boost::char_separator<char> > token (input, sep);
	char** argv = new char* [1024];
	
	for(boost::tokenizer< boost::char_separator<char> >::iterator it = token.begin(); it!=token.end(); ++it) {
		if (
	}*/

	/*char* rand = new char[128];
	rand[0] = 'a';
	rand[1] = 'b';
	rand[2] = '\0';
	cout << rand << endl;
	rand[0] = '\0';
	cout << rand << endl;
	cout << strlen(rand) << endl;
	*/	
	char* semicolon = const_cast<char*>(delim1.c_str());
	char* ampersand = const_cast<char*>(delim2.c_str());
	char* stick = const_cast<char*>(delim3.c_str());
	char* startparenthesis = const_cast<char*>(delim4.c_str());
	char* endparenthesis = const_cast<char*>(delim5.c_str());
	char* startbracket = const_cast<char*>(delim6.c_str());
	char* endbracket = const_cast<char*>(delim7.c_str());

	char** argv = new char *[1024];
	char* ctemp = new char [128];
	memset(ctemp, '\0', 128);
	int currarg = 0;
	//for(string::iterator it = inputcopy.begin(); it != inputcopy.end(); it++) {
	for(unsigned i = 0; i < input.length() && inputcopy.at(i) != 0; i++) {
		if (inputcopy.at(i) == '[') {
			if (strlen(ctemp) != 0){ // if ctemp is not empty add to argv** and clear
				argv[currarg] = new char[128];
				strcpy(argv[currarg], ctemp);
				memset(ctemp, '\0', 128);
				currarg++;
			}
			// handling of starting parenthesis
			argv[currarg] = new char[128];
			strcpy(argv[currarg], startbracket);
			currarg++;
			// start parentheses now added to argv**
		} else if (inputcopy.at(i) == ']') {
			// if ctemp isnt empty
			if (strlen(ctemp) != 0) {
				argv[currarg] = new char[128];
				strcpy(argv[currarg], ctemp);
				memset(ctemp, '\0', 128);
				currarg++;
			}
			// handling of closing parenthesis
			argv[currarg] = new char[128];
			strcpy(argv[currarg], endbracket);
			currarg++;
			// end parentheses now added to argv**
		} else	if (inputcopy.at(i) == '(') {
			if (strlen(ctemp) != 0){ // if ctemp is not empty add to argv** and clear
				argv[currarg] = new char[128];
				strcpy(argv[currarg], ctemp);
				memset(ctemp, '\0', 128);
				currarg++;
			}
			// handling of starting parenthesis
			argv[currarg] = new char[128];
			strcpy(argv[currarg], startparenthesis);
			currarg++;
			// start parentheses now added to argv**
		} else if (inputcopy.at(i) == ')') {
			// if ctemp isnt empty
			if (strlen(ctemp) != 0) {
				argv[currarg] = new char[128];
				strcpy(argv[currarg], ctemp);
				memset(ctemp, '\0', 128);
				currarg++;
			}
			// handling of closing parenthesis
			argv[currarg] = new char[128];
			strcpy(argv[currarg], endparenthesis);
			currarg++;
			// end parentheses now added to argv**
		} else if(strcmp(ctemp, "exit") == 0) {
			argv[currarg] = new char[128];
			strcpy(argv[currarg], ctemp);
			memset(ctemp,'\0',128);
			currarg++;
			// special case for "exit" to either fail to reach cmd exit or execute exit, so other cmds after are insignificant
			break;
		}else if (inputcopy.at(i) == ';'){ // full connector
			if (strlen(ctemp) != 0){
				argv[currarg] = new char[128];
				strcpy(argv[currarg], ctemp);
				memset(ctemp, '\0', 128);
				ctemp[0] = '\0';
				currarg++;
			}// add ';' into argv
			argv[currarg] = new char[128];
			strcpy(argv[currarg], semicolon);
			currarg++;
		}else if (inputcopy.at(i) =='&'){
			if (i+1 < inputcopy.length() && inputcopy.at(i+1) == '&') {
				// end the prev command
				if (strlen(ctemp) > 0) {// not a blank string
					argv[currarg] = new char[128];
					strcpy(argv[currarg],ctemp);
					memset(ctemp, '\0', 128);
					ctemp[0] = '\0';
					currarg++;
				}
				// add another for the "&&"
				argv[currarg] = new char[128];
				strcpy(argv[currarg], ampersand);
				currarg++;
				// iterate i since we are using 2 characters
				i++;
			} else { // only single '&' present => still works in bash, so it'll work here too
				// add last ctemp to argv
				if (strlen(ctemp) > 0) {
					argv[currarg] = new char[128];
					strcpy(argv[currarg], ctemp);
					memset(ctemp, '\0', 128);
					ctemp[0] = '\0';
					currarg++;
				}// add another to represent the split
				argv[currarg] = new char[128];
				strcpy(argv[currarg], ampersand);
				currarg++;
			}
		}else if (inputcopy.at(i) =='|'){
			if (i + 1 < inputcopy.length() && inputcopy.at(i+1) == '|') { // this means "&&"
				if (strlen(ctemp) > 0) {
					argv[currarg] = new char[128];
					strcpy(argv[currarg], ctemp);
					ctemp[0] = '\0';
					memset(ctemp, '\0', 128);
					currarg++;
				}// add "||" into argv
				argv[currarg] = new char[128];
				strcpy(argv[currarg], stick);
				currarg++;
				// iterate i, so we continue normally
				i++;
			} else { // onlym single | present but still works in bash, so it'll work here too since the directions were somewhat vague
				if (strlen(ctemp) > 0) {
					argv[currarg] = new char[128];
					strcpy(argv[currarg], ctemp);
					ctemp[0] = '\0';
					memset(ctemp, '\0', 128);
					currarg++;
				}// add '|' into argv
				argv[currarg] = new char[128];
				strcpy(argv[currarg], stick);
				currarg++;
			}
		}else if (inputcopy.at(i) == ' ' && strlen(ctemp) != 0) { // separate by spaces to parse each argument
			argv[currarg] = new char[128];
			strcpy(argv[currarg], ctemp);
			ctemp[0] = '\0';
			memset(ctemp,'\0', 128);
			currarg++;	
		}else { // none of the possible connectors, so just add the current char to ctemp
			ctemp[strlen(ctemp)] = inputcopy.at(i);
		}

	}
	
	// when we reach the end, the last string is likely still in ctemp
	if (strlen(ctemp) > 0) {
		argv[currarg] = new char[128];
		strcpy(argv[currarg],ctemp);
		ctemp[0] = '\0';
		memset(ctemp,'\0',128);
		currarg++;
	}
	
	
	// add the NULL at the end of argv
	int i = 0;
	while(argv[i] != '\0') {
		argv[i] = noSpaces(argv[i]);
		i++;
	}
	
	/*for (unsigned i = 0; argv[i] != '\0'; i++)
		cout << argv[i] << endl;*/
	
	return argv;
}


/*unsigned findHash(string input) {
	return input.find_first_of('#');
}*/



int main( )
{
	unsigned i = 0;
	string input = "";
	char** args;
	string comment = "";
	while(1) {
		// prompt
		char* currentdir = getenv("PWD");
		if (currentdir == NULL)
			perror("Error: env prompt");
		cout << currentdir << endl;
		cout << "$";

		getline(cin, input);
	
		//check for comments and separate
		i = input.find('#');
		if (i < input.length()) { // there exists a #
			comment = input.substr(i);
			input = input.substr(0, i);
		}
		// parse remaining commands/argumets
		args = parse(input);
		
		i = 0;

		LineCmd* l = new LineCmd(comment);
		int curr = 0;
		int cmdsize = 0;
		char** cmdArgs = new char*[1024];
		// construct the lineCmd from the arguments provided
		/*while (args[curr] != NULL) {
			cout << "$$: " << args[curr] << endl;
			curr++;
		}*/
		vector<Cmd*> v;

		// if restructured, would be recursive for intuitive parentheses within parentheses handling
		while (args[curr] != 0) {
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
					memset(cmdArgs,0,1024);
					cmdsize = 0;
				}
				v.push_back(new Semicolon());
				// reset cmdsize (the size of cmdArgs)
			} else if (strcmp(args[curr], "||") == 0) { // same as before
				if (cmdsize != 0) {
					cmdArgs[cmdsize] = NULL;	
					v.push_back(new IndivCmd(cmdArgs));
					cmdArgs = new char*[1024];
					memset(cmdArgs,0,1024);
					cmdsize = 0;
				}
				v.push_back(new Sticks());
			} else if (strcmp(args[curr], "&&") == 0) {
				if (cmdsize != 0) {
					cmdArgs[cmdsize] = NULL;
					v.push_back(new IndivCmd(cmdArgs));
					cmdArgs = new char*[1024];
					memset(cmdArgs,0,1024);
					cmdsize = 0;
				}
				v.push_back(new Ampersand());
			} else if (strcmp(args[curr], "(") == 0) { // parentheses case
				if (cmdsize != 0) { // some case handler where there is a cmd directly before the '('
					cmdArgs[cmdsize] = NULL;
					v.push_back(new IndivCmd(cmdArgs));
					cmdArgs = new char*[1024];
					memset(cmdArgs,0,1024);
					cmdsize = 0;
				}
				cmdArgs = new char*[1024];
				memset(cmdArgs,0,1024);
				cmdsize = 0;
				// find the closing parenthesis and pass in the cmds in between
				curr++; // go to cmd after ')'
				//cout << "What are we passing into Parentheses: "<< args[curr] << endl;
				// using cmdArgs to pass into the Parentheses
				for (unsigned l = 0; strcmp(args[curr], ")") != 0 && args[curr] != '\0'; l++) { // probably should be while loop
					if (strcmp(args[curr], "") != 0) {
						cmdArgs[cmdsize] = new char[128];
						memset(cmdArgs[cmdsize],'\0',128);
				//		cout << "args[" << cmdsize << "]: " << args[curr] << endl;

						strcpy(cmdArgs[cmdsize], args[curr]);
						cmdsize++;
						curr++;
					}
				}
				if (args[curr] == '\0') {
					perror("Did not end '('  with ')");
					return 1;
				}
				curr++;
				cmdArgs[cmdsize] = NULL;
				
			//	cout << endl;
				/*for (unsigned i = 0 ; cmdArgs[i] != NULL; i++){
					cout<<"'(' pushing back: " << args[i] << endl;
				}*/

				//cout << "pushing parentheses" << endl;
				// create Parentheses where they implement the LineCmd similarly
				v.push_back(new Parentheses(cmdArgs));
				
				cmdArgs = new char*[1024];
				memset(cmdArgs,0,1024);
				cmdsize = 0;
				// set the next curr as after ')'
			} else if (strcmp(args[curr], "[") == 0) { // brackets case
				// if starts with "test" will be treated as regular cmd but with special functionality in IndivCmd
				
				// if has something in the cmdArgs before '['
				if (cmdsize != 0) {
					cmdArgs[cmdsize] = NULL;
					v.push_back(new IndivCmd(cmdArgs));
					cmdArgs = new char*[1024];
					memset(cmdArgs,0,1024);
					cmdsize = 0;
				}
				// set [ as first arg and includes up to and including ]
				cmdArgs[cmdsize] = new char[128];
				memset(cmdArgs[cmdsize],'\0',128);
				strcpy(cmdArgs[0], "[");
				cmdsize++;
				curr++;

				// set all the args leading to "]" into test
				while(args[curr] != '\0' && strcmp(args[curr],"]") != 0 ) {
					cmdArgs[cmdsize] = new char[128];
					memset(cmdArgs[cmdsize],'\0',128);
					strcpy(cmdArgs[cmdsize],args[curr]);
					cmdsize++;
					curr++;
				}
				if (args[curr] == '\0') {
					perror("Error: did not end test with ']'.");
					return 1;
				}

				// set last arg as "]" and then null
				cmdArgs[cmdsize] = new char[128];
				memset(cmdArgs[cmdsize],'\0',128);
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
				memset(cmdArgs[cmdsize],'\0',128);
				strcpy(cmdArgs[cmdsize],args[curr]);
				cmdsize++;
			}
			curr++;
		}
		 // end with the last cmd not yet pushed in
		//cout << "End of second parsing" << endl;
		if (cmdArgs != NULL && cmdArgs[0] != NULL && strcmp(cmdArgs[0],"") != 0) {
			v.push_back(new IndivCmd(cmdArgs));
		}
		// reinit the cmdArgs for next loop
		cmdArgs = 0;
		args = 0;
	//	cout << "v.size(): " << v.size() << endl;
		for (unsigned m = 0; m < v.size(); m++) {
			if (v.at(m))
				l->add(v.at(m));
			//cout <<"iteration: " <<  m << endl;
		}
		l->execute();
	}

	/* first try
	unsigned i = 0;
	int n = 0;
	int startcmdi = 0;
	char* currarg = "";
	string comment = "";
	string input = "";
	char** args;
	LineCmd* l = 0;
	while (1) {
		// prompt and take in input 
		cout << "$";
		getline(cin,input);
		
		//check for comments and separate
		i = input.find('#');
		if (i < input.length()) { // there exists a #
			comment = input.substr(i);
			input = input.substr(0, i);
		}
		// parse remaining commands/argumets
		args = parse(input);
		
		// split args into command and argument sections and build structure to hold them
		l = new LineCmd(comment);
		n = 0;
		startcmdi = 0; // start of the command's index
		currarg = args[n];
		while(currarg) {
			if (strcmp(currarg,";") == 0) {
				l->add(new IndivCmd(args[startcmdi, n]));
				l->add(new Semicolon());
				startcmdi = n+1;
			} else if (strcmp(currarg,"&&") == 0) {
				l->add(new IndivCmd(args[startcmdi, n]));
				l->add(new Ampersand());
				startcmdi = n+1;
			} else if (strcmp(currarg, "||") == 0) {
				l->add(new IndivCmd(args[startcmdi, n]));
				l->add(new Sticks());
				startcmdi = n+1;
			}
				
			n++;
			currarg = args[n];
		}

		// execute those commands
		cout << "Executing" << endl;	
		execute(args);
		
	}
	delete [] args;
	*/
}

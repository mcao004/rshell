#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
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

using namespace std;

// parse the line of input into a vector of the commands and their connectors in order of appearance
char** parse(string input) {
	string inputcopy = input;
	string delim1 = ";";
	string delim2 = "&&";
	string delim3 = "||";
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

	char** argv = new char *[1024];
	char* ctemp = new char [128];
	int currarg = 0;
	for(unsigned i = 0; i < input.length() && inputcopy.at(i) != 0; i++) {
		//cout << inputcopy.at(i) << endl;
		/*if (strcmp(ctemp, "test ") == 0 || strcmp(ctemp, "[ ") == 0) {
			// if starts with [
			if (strcmp(ctemp, "[ ") == 0) { // we need to find ]
				
				ctemp[strlen(ctemp)] = inputcopy.at(i);
			} else { // starts with "test "
				
			}
		} else*/ if(strcmp(ctemp, "exit") == 0) {
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
		}else if (inputcopy.at(i)=='&'){
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
		}else { // none of the possible connectors
			//strcat(ctemp, inputcopy.at(i)); // => ctemp += inputcopy.at(i);
			ctemp[strlen(ctemp)] = inputcopy.at(i);
			//strcat(ctemp,&inputcopy.at(i));
			/*othertemp = malloc(strlen(ctemp) + 1);
			strcpy(othertemp, ctemp);
			strcat(othertemp, inputcopy.at(i));
			ctemp = othertemp;
			othertemp = blank;*/
		}

	}
	// when we reach the end the last string is likely still in ctemp
	if (strlen(ctemp) > 0) {
		argv[currarg] = new char[128];
		strcpy(argv[currarg],ctemp);
		ctemp[0] = '\0';
		memset(ctemp,'\0',128);
		currarg++;
	}
	// add the NULL at the end of argv
	argv[currarg] = new char[128];
	strcpy(argv[currarg], ctemp);
	currarg++;
	return argv;
}


/*unsigned findHash(string input) {
	return input.find_first_of('#');
}*/

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

int main( )
{
	unsigned i = 0;
	string input = "";
	char** args;
	string comment = "";
	while(1) {
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
		while (args[curr] != 0) {
			args[curr] = noSpaces(args[curr]);
			/*if (strcmp(args[curr],"test") == 0) {
				cmdArgs[cmdsize] = NULL;
				v.push_back(new testCmd(
				
			} else*/ // will use when finished fixing the problem
			if (strcmp(args[curr], ";") == 0) {
				cmdArgs[cmdsize] = NULL;
				v.push_back(new IndivCmd(cmdArgs));
				cmdArgs = new char*[1024];
				v.push_back(new Semicolon());
				cmdsize = 0;
			} else if (strcmp(args[curr], "||") == 0) {
				cmdArgs[cmdsize] = NULL;
				v.push_back(new IndivCmd(cmdArgs));
				cmdArgs = new char*[1024];
				v.push_back(new Sticks());
				cmdsize = 0;
			} else if (strcmp(args[curr], "&&") == 0) {
				cmdArgs[cmdsize] = NULL;
				v.push_back(new IndivCmd(cmdArgs));
				cmdArgs = new char*[1024];
				v.push_back(new Ampersand());
				cmdsize = 0;
			} else {
				cmdArgs[cmdsize] = new char[128];
				strcpy(cmdArgs[cmdsize],args[curr]);
				cmdsize++;
			}
			curr++;
		}
		v.push_back(new IndivCmd(cmdArgs));

		for (unsigned m = 0; m < v.size(); m++) {
			l->add(v.at(m));
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

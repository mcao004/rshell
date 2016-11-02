
#include "IndivCmd.h"
#include "LineCmd.h"
#include "Ampersand.h"
#include "Sticks.h"
#include "Semicolon.h"

#include <string>
#include <iostream>

using namespace std;

int main() {
	char line[1024];
	char *argv[64];

	//IndivCmd* test = new IndivCmd(argv);
	string ls = "ls";
	string l = "-l";
	
	argv[0] = const_cast<char*>(ls.c_str());
	argv[1] = const_cast<char*>(l.c_str());
	argv[2] = NULL;

//	cout << argv[0] << endl;
//	cout << argv[1] << endl;
//	execvp(argv[0], argv);

	// test for ls -l
	IndivCmd* lsl = new IndivCmd(argv);
	cout << "Cmd 1: ";
	lsl->execute();
	cout << endl;

	// first linecmd test with empty linecmd
	LineCmd* line1 = new LineCmd();
	cout << "Test 1: no cmds";
	line1->execute();
	cout << endl;

	// with one cmd
	line1->add(lsl);
	cout << "Test 2: one cmd";
	line1->execute();
	cout << endl;

	// with two cmds, no connector
	line1->add(lsl);
	cout << "Test3: ls -l ls -l = No such file or directory";
	line1->execute();
	cout << endl;

	// with two cmds, one semicolon btw
	LineCmd* line2 = new LineCmd();
	line2->add(lsl);
	Semicolon* s = new Semicolon();
	line2->add(s);
	line2->add(lsl);
	cout << "Test4: ls -l;ls -l: ";
	line2->execute();
	cout << endl;
	

	//IndivCmd* test2 = new IndivCmd(argv);
//	cout << "Hello Butts" << endl;

	return 0;
}


#include "IndivCmd.cpp"
#include "LineCmd.cpp"
#include "Ampersand.cpp"
#include "Sticks.cpp"
#include "Semicolon.cpp"

#include <string>
#include <iostream>

using namespace std;

int main() {
	char line[1024];
	char *argv[64];
	char *argv1[64];
	char *argv2[64];
	char* argv3[64];

	//IndivCmd* test = new IndivCmd(argv);
	string ls = "ls";
	string l = "-l";
	string echo = "echo";
	string hello = "Hello world";
	string mkdir = "mkdir";
	string file = "file.txt";
	string git = "git";
	string status = "status";
	
	argv[0] = const_cast<char*>(ls.c_str());
	argv[1] = const_cast<char*>(l.c_str());
	argv[2] = NULL;// always need to null terminate argv

	argv1[0] = const_cast<char*>(echo.c_str());
	argv1[1] = const_cast<char*>(hello.c_str());
	argv1[2] = NULL;

	argv2[0] = const_cast<char*>(mkdir.c_str());
	argv2[1] = const_cast<char*>(file.c_str());
	argv2[2] = NULL;

	argv3[0] = const_cast<char*>(git.c_str());
	argv3[1] = const_cast<char*>(status.c_str());
	argv3[2] = NULL;

//	cout << argv[0] << endl;
//	cout << argv[1] << endl;
//	execvp(argv[0], argv);

	// test for IndivCmds
	IndivCmd* lsl = new IndivCmd(argv);
	//cout << "Cmd 1: ";
	//lsl->execute();
	//cout << endl;
	
	IndivCmd* ech = new IndivCmd(argv1);
	//cout << "Cmd echo: ";
	//ech->execute();
	//cout << endl;

	IndivCmd* mk = new IndivCmd(argv2);
	//cout << "Cmd Mkdir: ";
	//mk->execute();
	//cout << endl;

	IndivCmd* gitstatus = new IndivCmd(argv3);
	cout << "Cmd gitstatus: ";
	gitstatus->execute();
	cout << endl;

	// first linecmd test with empty linecmd
	LineCmd* line1 = new LineCmd("");
	cout << "Test 1: no cmds";
	line1->execute();
	cout << endl;

	// with one cmd
	line1->add(lsl);
	cout << "Test 2: one cmd";
	line1->execute();
	cout << endl;

	// with two cmds, no connector (this shouldn't occur if parser works)
	line1->add(ech);
	cout << "Test3: ls -l echo Hello world";
	line1->execute();
	cout << endl;

	// with two cmds, one semicolon btw
	delete line1;	
	//IndivCmd* i1 = IndivCmd(argv);
	LineCmd* line2 = new LineCmd("");
	line2->add(lsl);
	Semicolon* s = new Semicolon();
	line2->add(s);
	line2->add(mk);
	cout << "Test4: ls -l;mkdir file.txt ";
	line2->execute();
	cout << endl;	

	//IndivCmd* test2 = new IndivCmd(argv);
//	cout << "Hello Butts" << endl;

	return 0;
}

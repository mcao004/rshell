
#include "IndivCmd.cpp"
#include <string>
#include <iostream>

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

	IndivCmd* test = new IndivCmd(argv);
	test->execute();
	IndivCmd* test2 = new IndivCmd(argv);
	LineCmd* line1 = new LineCmd(arg
//	cout << "Hello Butts" << endl;

	return 0;
}

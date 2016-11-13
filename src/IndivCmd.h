#ifndef __INDIVCMD_HH__
#define __INDIVCMD_HH__

#include <sys/wait.h>

using namespace std;

#include "Cmd.h"

class IndivCmd : public Cmd {
	private:
		void test(char** args);
	protected:
		char** argv;
	public:
		IndivCmd(char** argv);
		void execute();
};

#endif

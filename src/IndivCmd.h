#ifndef __INDIVCMD_HH__
#define __INDIVCMD_HH__

#include <linux/limits.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>

using namespace std;

#include "Cmd.h"

class IndivCmd : public Cmd {
	private:
		void test(char** args);
		void cd(char** args);
	protected:
		char** argv;
	public:
		IndivCmd(char** argv);
		void execute();
};

#endif

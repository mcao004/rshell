#ifndef __CMD_HH__
#define __CMD_HH__

#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

class Cmd {
	protected:
		Cmd* prev;
		Cmd* next;

		virtual void execute() = 0;
};
#endif

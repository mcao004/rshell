#ifndef __CMD_HH__
#define __CMD_HH__

#include <cstdlib>

using namespace std;

class Cmd {
	protected:
		Cmd* prev;
		Cmd* next;

		virtual void execute() = 0;
}
#endif

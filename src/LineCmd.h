#ifndef __LINECMD_HH__
#define __LINECMD_HH__

#include "Cmd.h"

class LineCmd: public Cmd {
	protected:
		// will contain a linked list of commands
		Cmd* first;
		Cmd* last;
	public:	
		LineCmd();
		void add(Cmd* c); // adds a command to the linked list
		void execute();
};
#endif

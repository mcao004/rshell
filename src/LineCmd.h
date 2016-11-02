#ifndef __LINECMD_HH__
#define __LINECMD_HH__

#include "Cmd.h"

class LineCmd: public Cmd {
	protected:
		// will contain a linked list of commands
		Cmd* first;
		Cmd* last;
		
		void execute();
};
#endif

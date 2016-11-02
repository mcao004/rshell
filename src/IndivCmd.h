#ifndef __INDIVCMD_HH__
#define __INDIVCMD_HH__

#include "Cmd.h"

class IndivCmd : public Cmd {
	protected:
		char** argv;
	public:
		IndivCmd(char** argv);
		void execute();
};

#endif

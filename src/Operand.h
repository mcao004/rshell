
#ifndef __OPERAND_HH__
#define __OPERAND_HH__

#include "Cmd.h"

class Operand: public Cmd {
	public:
		virtual void execute()= 0;
};
#endif

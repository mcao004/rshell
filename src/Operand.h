
#ifndef __OPERAND_HH__
#define __OPERAND_HH__

#include "Cmd.h"

class Operand: public Cmd {
	protected:
		virtual void execute()= 0;
};
#endif

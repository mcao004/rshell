#ifndef __STICKS_HH__
#define __STICKS_HH__

#include "Operand.h"

class Sticks : public Operand {
	protected:
		void execute() {
			if (prev->fail())
				next->execute();
			else
				exit();
		}
}
#endif

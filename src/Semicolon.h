#ifndef __SEMICOLON_HH__
#define __SEMICOLON_HH__

#include "Operand.h"

class Semicolon : public Operand {
	protected:
		void execute() {
			next->execute();
		}
}
#endif

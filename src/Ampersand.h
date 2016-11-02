#ifndef __AMPERSAND_HH__
#define __AMPERSAND_HH__

#include "Operand.h"
class Ampersand : public Operand {
	protected:
		void execute() {
			if (prev->fail())
				exit(0);
			else
				next->execute();
		}
};
#endif

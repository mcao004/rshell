#ifndef __PARENTHESES_HH__
#define __PARENTHESES_HH__

#include "Cmd.h"

class Parentheses : public Cmd {
	protected:
		Cmd* lastexecuted;
		vector<Cmd*> v;
	public:
		Parenthese();
		void add(Cmd* c);
		void execute();
}
#endif

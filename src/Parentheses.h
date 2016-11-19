#ifndef __PARENTHESES_HH__
#define __PARENTHESES_HH__

#include <vector>

using namespace std;

#include "IndivCmd.h"
#include "Ampersand.h"
#include "LineCmd.h"
#include "Semicolon.h"
#include "Sticks.h"
#include "Cmd.h"

class Parentheses : public Cmd {
	private:
		void init(char**);
	protected:
		Cmd* lastexecuted;
		LineCmd* innerLineCmd;	
		vector<Cmd*> v;
	public:
		Parentheses(char**);
		void add(Cmd* c);
		void execute();
};
#endif


#include "Parenthese.h"

// input: the args that make up the test
Parentheses::Parentheses() 
: lastexecuted(0)
{
}

// adds a single command to our vector
void Parentheses::add(Cmd* c) {
	incomplete
}

void Parentheses::execute() {
	// similar to LineCmd
	for (int i = 0; i < v.size(); i++) { // go through all the commands while also keeping track of the last actually executed
		v.at(i)->execute();
		if (i%2 == 1 && v.at(i)->executed) // every two is a IndivCmd, so if operand executes true
			lastexecuted = v.at(i+1);
	}
}

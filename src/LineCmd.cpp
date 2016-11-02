
#include "LineCmd.h"

LineCmd::LineCmd() 
:first(0), last(0)
{}

void LineCmd::add(Cmd* c) {
	incomplete, so I'll need to finish this later...	
}

void LineCmd::execute() {
	// execute through the linked list
	Cmd* currCmd = first;
	while(currCmd) {
		currCmd->execute();
	}
}

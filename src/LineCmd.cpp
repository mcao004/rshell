
#include "LineCmd.h"

LineCmd::LineCmd() 
:first(0), last(0)
{}

void LineCmd::add(Cmd* c) {
	if (first == 0) { // initially empty list
		first = c;
		last = c;
	} else {
		last->next = c;
		c->prev = last;
		last = c;
	}
}

void LineCmd::execute() {
	// execute through the linked list
	//executed = false;
	Cmd* currCmd = first;
	bool lastcmdexecuted = true;
	while(currCmd && lastcmdexecuted) { // while currCmd exists and last Cmd hasn't failed
		currCmd->execute();
		lastcmdexecuted = currCmd->executed;
		currCmd = currCmd->next;
	}
	//executed = true;
	//if (next) // if there is another line after this one for some reason
	//	next->execute();

	cout << "LineCmd executed" << endl;
		
}

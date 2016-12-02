
#include "LineCmd.h"

LineCmd::LineCmd(string comment) 
:first(0), last(0), comment(comment)
{}

void LineCmd::add(Cmd* c) {
	//if (c != NULL || !c)
	//	return;
	if (first == 0) { // initially empty list
		first = c;
		last = c;
		c->prev = 0;
		c->next = 0;
	} else {
		last->next = c;
		c->prev = last;
		last = c;
		c->next = 0;
	}
}

void LineCmd::execute() {
	// execute through the linked list
	executed = true;
	Cmd* currCmd = first;
	//Cmd* lastexecuted = currCmd;
	//bool succeed = true;
	int i = 0;
	//cout << "Start working on line" << endl;
	
	

	while(currCmd) {
		currCmd->execute();
		// the last cmd to executed is true, then true
		// last cmd executed is false, then false
		//if (currCmd->next) {
			// if i is odd => operator
		if (i == 0 || currCmd->next == 0){ // if first or last, match their executed variable
			//cout << "first/last: ";
			//if ( currCmd->executed)
			//	cout << "true" << endl;
			//else
			//	cout << "false" << endl;
			executed = currCmd->executed;
		} else if (i%2 == 1 && currCmd->prev &&  !currCmd->executed ) {
			executed = currCmd->prev->executed;
			break;
		}
		currCmd=currCmd->next;
		i++;
		/*} else { 
			break;
		}*/
		// //cout << "iteration: " << i <<  endl;
	}
	/*if (executed)
		cout << "Line: true" << endl;
	else
		cout << "Line: false" << endl;*/
	/*while(currCmd && lastcmdexecuted) { // while currCmd exists and last Cmd hasn't failed
		currCmd->execute();
		lastcmdexecuted = currCmd->executed;
		currCmd = currCmd->next;
	}*/
	//executed = true;
	//if (next) // if there is another line after this one for some reason
	//	next->execute();

		
}

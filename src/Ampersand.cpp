
#include "Ampersand.h"

Ampersand::Ampersand() {}

void Ampersand::execute() {
	if(prev->executed) { // if the prev one did not succeed in executing
		executed = true;
	} else { // succeeded in executing, so next one can
		executed = false;
		//next->execute();
	}
}

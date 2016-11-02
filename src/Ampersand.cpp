
#include "Ampersand.h"

void Ampersand::execute() {
	if(!prev->executed) { // if the prev one did not succeed in executing
		executed = false;
		exit(0);
	} else { // succeeded in executing, so next one can
		executed = true;
		next->execute();
	}
}

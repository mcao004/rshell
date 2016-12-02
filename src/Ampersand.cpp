
#include "Ampersand.h"

Ampersand::Ampersand() {}

void Ampersand::execute() {
<<<<<<< HEAD
	if(!prev) {
		perror("No Command before ||");
		return;
	}

	if(prev->executed) { // if the prev one did not succeed in executing
		executed = true;
	} else { // succeeded in executing, so next one can
		executed = false;
		//next->execute();
=======
>>>>>>> a8e854f0a0b4a191f89a0a0cec9957ae84002dc1
	}
}

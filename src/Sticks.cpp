
#include "Sticks.h"

Sticks::Sticks() {}

void Sticks::execute() {
	if (!prev) {
		perror("No Command before ||");
		return;
	}
	if (!prev->executed){
		executed = true;
		//next->execute();
	}else{
		executed = false;
	}
}

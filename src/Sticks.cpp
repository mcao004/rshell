
#include "Sticks.h"

void Sticks::execute() {
	if (!prev->executed){
		executed = true;
		next->execute();
	}else{
		executed = false;
		exit(0);
	}
}

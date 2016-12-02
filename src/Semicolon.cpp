
#include "Semicolon.h"

Semicolon::Semicolon() 
{}

void Semicolon::execute() {
	if (!prev) {// if there isnt a command before
		perror("Error: no preceding command");
<<<<<<< HEAD
	}else if (!next) {
		perror("Error: no following command");
	}
	executed = true;
	//next->execute();
=======
>>>>>>> a8e854f0a0b4a191f89a0a0cec9957ae84002dc1
}

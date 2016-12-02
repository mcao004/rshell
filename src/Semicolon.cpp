
#include "Semicolon.h"

Semicolon::Semicolon() 
{}

void Semicolon::execute() {
	if (!prev) {// if there isnt a command before
		perror("Error: no preceding command");
	}else if (!next) {
		perror("Error: no following command");
	}
	executed = true;
	//next->execute();
}

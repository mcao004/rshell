
#include "Semicolon.h"

Semicolon::Semicolon() 
{}

void Semicolon::execute() {
	cout << "Executing Semicolon" << endl;
	if (!prev) {// if there isnt a command before
		perror("Error: no preceding command");
		exit(1);
	}else if (!next) {
		perror("Error: no following command");
		exit(1);
	}
	executed = true;
	next->execute();
}


#include "Semicolon.h"

Semicolon::Semicolon() 
{}

void Semicolon::execute() {
	executed = true;
	next->execute();
}

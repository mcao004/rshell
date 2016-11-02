
#include "Semicolon.h"

void Semicolon::execute() {
	executed = true;
	next->execute();
}

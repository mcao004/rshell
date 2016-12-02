#ifndef __INDIVCMD_HH__
#define __INDIVCMD_HH__

<<<<<<< HEAD
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>

using namespace std;

#include "Cmd.h"

class IndivCmd : public Cmd {
	private:
		void test(char** args);
=======
>>>>>>> a8e854f0a0b4a191f89a0a0cec9957ae84002dc1
	protected:
		char** argv;
	public:
		IndivCmd(char** argv);
<<<<<<< HEAD
=======
>>>>>>> a8e854f0a0b4a191f89a0a0cec9957ae84002dc1
		void execute();
};

#endif

#RSHELL


##Licensing Information:

COPYING.txt

##Github Repository

https://github.com/mcao004/rshell


##Authors

Marvin Cao

Tamir Habari


```
##File List

Makefile

License

README.md

Copying.txt

rshell.cpp

./src

./tests
```

```
/src

Ampersand.cpp

Ampersand.h

Cmd.h

IndivCmd.cpp

IndivCmd.h

LineCmd.cpp

LineCmd.h

Operand.h

Parentheses.cpp

Parentheses.h

Semicolon.cpp

Semicolon.h

Sticks.cpp

Sticks.h

main.cpp


```
```
/tests

single_command.sh

commented_command.sh

multi_command.sh

exit.sh

cd-test.sh

cd-test.txt

test_test.sh

precedence_test.sh
```

##Instructions to run on your machine after you clone it

1. `cd` into `rshell`

2. Call `make`

3. Call `./bin/rshell`


##BUGS

1. Sometimes executes a command twice.

2. Too long of input causes seg fault.

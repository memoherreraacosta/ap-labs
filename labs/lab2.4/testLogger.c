#include "logger.h"

//Implementation made by https://github.com/razonixx

int main(int argc, char const *argv[])
{	
	//initLogger("syslog");
	initLogger("");
	int myInt = 10;
    double myDouble = 15.2;
    float myFloat = 12.4f;
    char myChar = 'H';
    char *myString = "Hello World";

	infof("%cello, this is general information\n", myChar);	
	warnf("%cello, this is a warning with code: %f\n", myChar, myDouble);
	errorf("%cello, this is an error with code: %d\n", myChar, myInt);
	panicf("%s, this is a panic with code: %f\n", myString, myFloat);
	return 0;
}

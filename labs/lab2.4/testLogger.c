#include <stdio.h>
#include <string.h>

#define INFO "INFO"
#define WARN "WARN"
#define ERROR "ERROR"
#define PANIC "PANIC"

int pLogger(const char *format, const char *message);
int initLogger(const char* logType);

int main(int argc, char **argv){
	
	//Default 
	
	pLogger(INFO,"This is an INFO message");
	// INFO message
	pLogger(WARN,"This is a WARN message");
	// WARN message
	pLogger(ERROR,"This is an ERROR message");
	// ERROR message
	pLogger(PANIC,"This is a PANIC");
	// PANIC message

	
	//stdout 
	initLogger("stdout");

	pLogger(INFO,"This is an INFO message");
	// INFO message
	pLogger(WARN,"This is a WARN message");
	// WARN message
	pLogger(ERROR,"This is an ERROR message");
	// ERROR message
	pLogger(PANIC,"This is a PANIC");
	// PANIC message
	

	//syslog
	initLogger("syslog");

	pLogger(INFO,"This is an INFO message");
	// INFO message
	pLogger(WARN,"This is a WARN message");
	// WARN message
	pLogger(ERROR,"This is an ERROR message");
	// ERROR message
	pLogger(PANIC,"This is a PANIC");
	// PANIC message

	return 0;
}

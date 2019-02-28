#include <stdio.h>
#include <string.h>

#define INFO "INFO"
#define WARN "WARN"
#define ERROR "ERROR"
#define PANIC "PANIC"

int textcolor(int attr, int fg, int bg);
int infof(const char *message);
int warnf(const char *message);
int errorf(const char *message);
int panicf(const char *message);
int printLogger(const char *format, const char *message);

int main(int argc, char **argv){
	
	printLogger(INFO,"This is an INFO message");
	printLogger(WARN,"This is a WARN message");
	printLogger(ERROR,"This is an ERROR message");
	printLogger(PANIC,"This is a PANIC");
	
	return 0;
}

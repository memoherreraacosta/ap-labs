#include <stdio.h>
#include <string.h>

#define RESET		0
#define BRIGHT 		1

#define BLACK 		0
#define RED		1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define	WHITE		7

int textcolor(int attr, int fg, int bg);
int infof(const char *message);
int warnf(const char *message);
int errorf(const char *message);
int panicf(const char *message);
int printLogger(const char *format, const char *message);

int textcolor(int attr, int fg, int bg){	
	char command[13];

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
	return 0;
}

int printLogger(const char *format, const char *message ){
	
	if(strcmp(format,"INFO")==0)
		return infof(message);
	
	if(strcmp(format,"WARN")==0)
		return warnf(message);

	if(strcmp(format,"ERROR")==0)
		return errorf(message);

	if(strcmp(format,"PANIC")==0)
		return panicf(message);

	return -1;
}	

int infof(const char *message){
// Info General information.
// Green
	textcolor(BRIGHT, GREEN, BLACK);
	printf("%s\n",message);
	textcolor(RESET, WHITE, BLACK);
	return 0;
}

int warnf(const char *message){
// WARN Warnings.
// RED
	textcolor(BRIGHT, RED, BLACK);
	printf("%s\n",message);
	textcolor(RESET, WHITE, BLACK);
	return 0;
}

int errorf(const char *message){
// ERROR Errors.
// Yellow
	textcolor(BRIGHT, YELLOW, BLACK);
	printf("%s\n",message);
	textcolor(RESET, WHITE, BLACK);
	return 0;
}

int panicf(const char *message){
// PANIC Panics. Non recoverable issues with core dump.
// BLUE
	textcolor(BRIGHT, YELLOW, BLACK);
	printf("%s\n",message);
	textcolor(RESET, WHITE, BLACK);
	return 0;
}



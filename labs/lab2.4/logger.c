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
int initLogger(const char logType[]);
int printLogger(const char *format, const char *message);

char lType[] = "default";


int initLogger(const char logType[]){

	if (strcmp("syslog",logType) == 0 ){
		strcpy(lType,logType);
		return 0;
	}
	if (strcmp("stdout",logType) == 0){
		strcpy(lType,logType);
		return 0;
	}
	if (strcmp("",logType) == 0){
		strcpy(lType,logType);
		return 0;
	}
	return -1;
}

int textcolor(int attr, int fg, int bg){	
	char command[13];

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
	return 0;
}

int defaultf(const char *message){
	printf("The following has no readible format : %s\n",message);
	return 0;
}

int pLogger(const char *format, const char *message ){
	
	if(strcmp(format,"INFO")==0){
		return infof(message);
	}
	if(strcmp(format,"WARN")==0){
		return warnf(message);
	}
	if(strcmp(format,"ERROR")==0){
		return errorf(message);
	}
	if(strcmp(format,"PANIC")==0){
		return panicf(message);
	}
	return defaultf(message);
}	

int infof(const char *message){
// Info General information.
// Green
	textcolor(BRIGHT, GREEN, BLACK);
	
	if(strcmp(lType,"stdout") == 0){
		printf("stdout log : [%s]\n",message);
	}else if(strcmp(lType,"syslog") == 0){
		printf("syslog log : [%s]\n",message);
	}else{
		printf("%s\n",message);
	}
	textcolor(RESET, WHITE, BLACK);
	return 0;
}

int warnf(const char *message){
// WARN Warnings.
// RED
	textcolor(BRIGHT, RED, BLACK);

	if(strcmp(lType,"stdout") == 0){
		printf("stdout log : [%s]\n",message);
	}else if(strcmp(lType,"syslog") == 0){
		printf("syslog log : [%s]\n",message);
	}else{
		printf("%s\n",message);
	}
	textcolor(RESET, WHITE, BLACK);
	return 0;
}

int errorf(const char *message){
// ERROR Errors.
// Yellow
	textcolor(BRIGHT, YELLOW, BLACK);
	
	if(strcmp(lType,"stdout") == 0){
		printf("stdout log : [%s]\n",message);
	}else if(strcmp(lType,"syslog") == 0){
		printf("syslog log : [%s]\n",message);
	}else{
		printf("%s\n",message);
	}
	textcolor(RESET, WHITE, BLACK);
	return 0;
}

int panicf(const char *message){
// PANIC Panics. Non recoverable issues with core dump.
// BLUE
	textcolor(BRIGHT, BLUE, BLACK);
	
	if(strcmp(lType,"stdout") == 0){
		printf("stdout log : [%s]\n",message);
	}else if(strcmp(lType,"syslog") == 0){
		printf("syslog log : [%s]\n",message);
	}else{
		printf("%s\n",message);
	}
	textcolor(RESET, WHITE, BLACK);
	return 0;
}



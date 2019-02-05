#include <stdio.h>

int strlen(char *str);

char* stradd(char *origin, char *addition);

int strfind(char *origin, char *substr);


int main(int argc, char **argv){

	if(argc == 4){
	//1
		printf("Initial length : %d\n",strlen(argv[1]));

	//2
		char *ns = stradd(argv[1],argv[2]);	
		printf("New String : %s\n",ns);
	
	//3
		if(strfind(ns, argv[3]) == 0){
			printf("The substring was found : YES\n");
		}else {
			printf("The substring was found : NO\n");
		}
	}else {
		printf("Invalid number of arguments");
	}
}

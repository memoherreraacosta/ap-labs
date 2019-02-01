#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

	if(argc == 4){
	//1
		printf("Initial length : %d\n",strlen(argv[1]));

	//2
		char *ns = stradd(argv[1],argv[2]);	
		printf("New String : %s\n",ns);
	
	//3
		char awr = 'no';
		if(strfind(ns, argv[3]) == 0){
			awr = 'yes';
		}
		printf("Substring was found : %c",awr);

	}else {
		printf("Invalid number of arguments");
	}
}

#include <stdio.h>

int main(int argc, char **argv);{
	printf("Initial length : %d\n",strlen(argv[1]));
	char* ns = stradd(argv[1],argv[2]);
	
	printf("New String : %s\n",ns);
	
	char awr = 'no';
	if(strfind(ns, argv[3]) == 0){
		awr = 'yes';
	}
	printf("Substring was found : %c",awr);
	
}

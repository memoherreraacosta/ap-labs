#include <stdio.h>

int main(void){
	int c;
	while((c = getchar()) != EOF){
		if( c != '\n' && c != '\t' && c != ' '){
			putchar(c);
		}else{
			printf("\n");
		}
	}
}

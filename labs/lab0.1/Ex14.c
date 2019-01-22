#include <stdio.h>

int main(void){
	int c;
	int character[128];
	for (int i = 0;i < 128; i++){
		character[i] = 0;
	}
	while((c =  getchar()) != EOF){
		character[c]++;
	}
	for(int i = 0; i < 128; i++){
		putchar(i);
		for(int j = 0; j< character[i]; j++){
			putchar('*');
		}
		putchar('\n');
	}
}

#include <stdio.h>

/* print Celsius-Fahrenheit table for celsius = 0, 20, ..., 300*/

int main(){
	int fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	celsius = lower;
	
	printf("print Celsius-Fahrenheit table for celsius = 0, 20, ..., 300\n");
	while(celsius <= upper){
		fahr = 32 + (9/5.0)*celsius;
		printf("%d\t%d\n", celsius, fahr);
		celsius = celsius + step;
	}
	return 0;
}

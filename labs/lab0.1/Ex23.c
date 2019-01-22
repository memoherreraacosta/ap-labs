#include <stdio.h>

int main(int argc, char *argv[]){
	FILE *fleer, *fescribir;

	char c,d;

	if(argc < 3 ){
		printf("No se introdujeron los datos necesarios");
	}
	fleer = fopen(argv[1],"r");
	fescribir = fopen(argv[2],"w");

	if ( fleer == NULL){
		printf("Error al abrir el archivo");
		return 0;
	}
	if ( fescribir == NULL){
		printf("Error al leer el archivo");
		return 0;
	}
	d = fgetc(fleer);
	while( d != EOF){
		c = d;
		d = fgetc(fleer);
			
		if( (c == '/') && (d == '/')){
			c = d;
                        d = fgetc(fleer);
                        while (d != '\n'){
                                c = d;
                                d = fgetc(fleer);
                        }
                        c = d;
			d = fgetc(fleer);
		} 
		if( (c == '/') && (d == '*')){
			c = fgetc(fleer);
			d = fgetc(fleer);
                        while ((d != EOF) || (c == '*' && d == '/')){
                                c = d;
                                d = fgetc(fleer);
                        }
			if(d == EOF)
				c = '\n';
		}
		putc(c,fescribir);
	}
	fclose(fleer);
	fclose(fescribir);
	return 0;
}	

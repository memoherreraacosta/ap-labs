#include <stdio.h>

int main(int argc, char **argv){
	
	if (argc != 2){
		printf("Numero invalido de argumentos\n");
		return 1;
	}

	FILE* archivito;
	
	if((archivito = fopen(argv[1], "r")) != NULL){
		int c, index = 0;
		char textito[2048];

   		while ((c = getc(archivito)) != EOF)
       			textito[index++] = c;
		
		printf("%s",textito);
	}else{
		printf("Error al leer el archivo\n");
		return 2;
	}
	fclose(archivito);
}

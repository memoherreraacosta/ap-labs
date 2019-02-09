#include <stdio.h>

int main(int argc, char **argv){
	
	if (argc != 2){
		printf("Numero invalido de argumentos\n");
		return 1;
	}

	FILE* archivito;
	
	if((archivito = fopen(argv[1], "r")) != NULL){
		int c, index = -1, sizeS = 2048;
		char textito[sizeS];

   		while ((c = getc(archivito)) != EOF)
       			textito[index++] = c;

		textito[index++] = '\0';
		fclose(archivito);
		printf("%s",textito);
	}else{
		printf("Error al leer el archivo\n");
		return 2;
	}
	
}

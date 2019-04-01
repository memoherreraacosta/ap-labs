#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define CODED_FILE_NAME "encoded.txt"
#define DECODED_FILE_NAME "decoded.txt"
#define SSOF 128 // Standard Size Of File

// Declaration of methods of b64.c
char *base64_encode(const unsigned char *data, 		// Min 0, Max 255
                    size_t input_length,
                    size_t *output_length);

unsigned char *base64_decode(const char *data,
                             size_t input_length,
                             size_t *output_length);

void build_decoding_table();
void base64_cleanup();
// Declaration of methods base64.c

int main(int argc, char ** argv);
int code(const char *archivito);
int decode(const char *archivito);
int sizeFile(char *fName);

int main(int argc, char ** argv){
    if(argc != 3){
		printf("Error in arguments [ %s %s ]\n", argv[1],argv[2]);
        return -1;
	}	
    if(strcmp(argv[1],"--encode") == 0){
        return code(argv[2]);
	}
    if(strcmp(argv[1],"--decode") ==0 ){
        return decode(argv[2]);
	}
    printf("Error in arguments [ %s %s ]\n", argv[1],argv[2]);
    return -2;
}

int code(const char *archivito){
	
	int sArch = sizeFile(archivito);
	int iter1;
	int iter2;

	unsigned char *textito[SSOF+1];

	// Crear archivo donde se guardara 
	// la codificacion
	FILE *fileR = fopen(archivito,"r");
	if (fileR == NULL){
    	printf("Error opening file! %s\n",archivito);
		fclose(fileR);
    	exit(1);
	}

	FILE *fileW = fopen(CODED_FILE_NAME,"w");
	if (fileW == NULL){
    	printf("Error opening file! %s\n",archivito);
		fclose(fileW);
    	exit(1);
	}

	if(sArch < SSOF){
		iter1 = 1;
		iter2 = 0;
	}else{
		iter1 = sArch/SSOF; 
		iter2 = sArch%SSOF;
	}

	// Obtener num de veces que se hara la
	// funcion de meter un string a un archivo
	// fputs() 127 char per buffer 
	int i;
	int j;

	for(i = 0 ; i < iter1 ; i++){
		// Asignar la concatenacion con el resultado de la funcion 
		for(j = 0 ; j < SSOF ; j++){
			textito[j] = fgetc(fileR);
		}
		fputs(base64_encode(textito,iter1,iter1),fileW);
		free(textito);
	}

	if(iter2 != 0){
		for(i = 0 ; i < iter2 ; i++){
			// Asignar la concatenacion con el resultado de la funcion 
			textito[j] = fgetc(fileR);
		}
		fputs(base64_encode(textito,iter2,iter2),fileW);
		free(textito);
	}
	fputc(EOF,fileW);
	fclose(fileR);
	fclose(fileW);
	base64_cleanup();
	return 0;
}

int decode(const char *archivito){
	int sArch = sizeFile(archivito);
	int iter1;
	int iter2;

	unsigned char textito[SSOF+1];

	// Crear archivo donde se guardara 
	// la codificacion
	FILE *fileR = fopen(archivito,"r");
	if (fileR == NULL){
    	printf("Error opening file! %s\n",archivito);
		fclose(fileR);
    	exit(1);
	}

	FILE *fileW = fopen(DECODED_FILE_NAME,"w");
	if (fileW == NULL){
    	printf("Error opening file! %s\n",archivito);
		fclose(fileW);
    	exit(1);
	}

	if(sArch < SSOF){
		iter1 = 1;
		iter2 = 0;
	}else{
		iter1 = sArch/SSOF; 
		iter2 = sArch%SSOF;
	}

	// Obtener num de veces que se hara la
	// funcion de meter un string a un archivo
	// fputs() 127 char per buffer 
	int i;
	int j;

	for(i = 0 ; i < iter1 ; i++){
		// Asignar la concatenacion con el resultado de la funcion 
		for(j = 0 ; j < SSOF ; j++){
			textito[j] = fgetc(fileR);
		}
		fputs(base64_decode(textito,iter1,iter1),fileW);
		free(textito);
	}

	if(iter2 != 0){
		for(i = 0 ; i < iter2 ; i++){
			// Asignar la concatenacion con el resultado de la funcion 
			textito[j] = fgetc(fileR);
		}
		fputs(base64_decode(textito,iter2,iter2),fileW);
		free(textito);
	}
	fputc(EOF,fileW);
	fclose(fileR);
	fclose(fileW);
	base64_cleanup();
	return 0;
}
int sizeFile(char *fName){

	FILE *arch = fopen(fName, "r");
	if (arch == NULL){
    	printf("Error opening file! %s\n",fName);
		fclose(arch);
		return -1;
	}
	int size = 0;
	while((fgetc(arch) != EOF))
		size++;
	
	fclose(arch);
	return size;
}
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define REPORT_LIST "list.txt"
#define REPORT_FILE "newFile.txt"

int createReport(char *fRead, char *fList); 
int omitir(char* test);
int omitChar(char c);
char* toArray(int number);

int main(int argc, char **argv) {

    if (argc != 2) {
	printf("Error in number of arguments\n");
	return 1;
    }
    
    return createReport(argv[1], REPORT_FILE);
}

int createReport(char *fRead, char *fWrite) {
	FILE *fp1;
	char ch;
	int pos;
 
	if ((fp1 = fopen(fRead,"r")) == NULL){    
		printf("File cannot be opened FP1\n");
        	return -1;
    	}

	int lineC = 1;
	char cLow;
	char palabra[45];
	char palabraTest[45];
	int sizeW = 200;
	int sizeL = 100;
	char *pValidas[sizeW][sizeL];

	for(int i = 0 ; i < sizeW ;i++ ){
		for(int j = 0; j < sizeL ; j++){
			pValidas[i][j] = "-";
		}
	}

	while ((ch = fgetc(fp1)) != EOF){
        	// copying file character by character
		if(omitChar(ch) == 0){
			//Char that wont be a word
			putchar(ch);

		}else if(ch == '\n'){
			//New line 
			putchar(ch);
			lineC ++;

		}else if(ch != '\n'){
			//Is a word
					
			for(int i = 0 ; ch != '\n' && omitChar(ch) == -1 && ch != EOF ; i++){
				palabra[i] = ch;
				cLow = tolower(ch);
				palabraTest[i] = cLow;

				ch = fgetc(fp1);	
			
		}
			//Test palabra to put it into the file
			//Crear referencia char* de palabra en minusculas para poder testearla con palabras invalidas
			strcat(palabra,"\0");

			if(omitir(palabraTest) == -1){
				//Palabra valida
				//Guardar palabra
				printf("%s",palabra);

				int flag = 0;
				for(int i = 0; flag == 0 && i < sizeW; i++ ){
					
					if(strcmp(pValidas[i][0],"-") == 0){
						
						pValidas[i][0] = palabra;
						pValidas[i][1] = toArray(lineC);
						flag = 1;

					}else if(strcmp(pValidas[i][0],palabra) == 0){
						int j;
						for(j = 1; strcmp(pValidas[i][j],"-") != 0 && j < sizeL; j++ ){}
								
						pValidas[i][j] = toArray(lineC);
						flag = 1;
					}

				}	
			}
			//Palabra invalida
			
			memset(palabra,'\0',sizeof(palabra));
			memset(palabraTest,'\0',sizeof(palabraTest));
			
			//Guardar ultimo caracter leido
			if(ch != EOF){
				putchar(ch);
				if(ch == '\n')
					lineC ++;
			}
		
		}else{
			printf("wtf : %c\n",cLow);
		}
    	}
    	fclose(fp1);	

	printf("\nList of the words and where they were found :\n");
	
	for( int i = 0; strcmp(pValidas[i][0],"-") != 0 ; i++ ){
		printf("\n");
		for( int j = 0 ; strcmp(pValidas[i][j],"-") != 0 ; j++ ){
			printf("%s, ",pValidas[i][j]);
		}
	}
	return 0;
}
int omitChar(char c){
	switch(c){
	case '.':	return 0;	case ' ':	return 0;
	case ',':	return 0;	case ';':	return 0;
	case ':':	return 0;	case '?':	return 0;
	case '-':	return 0;	case '_':	return 0;
	case '=':	return 0;	case '(':	return 0;
	case ')':	return 0;	case '"':	return 0;	
	case '!':	return 0;	case '%':	return 0;
	case '+':	return 0;	case '[':	return 0;
	case ']':	return 0;	case '{':	return 0;
	case '}':	return 0;	

	default:	return -1;}
}

int omitir(char* test){
	
	if(strcmp("and",test) == 0	||	strcmp("the",test) == 0  ||
	   strcmp("a",test) == 0	||	strcmp("to",test) == 0   ||
	   strcmp("an",test) == 0	||	strcmp("of",test) == 0   ||
           strcmp("for",test) == 0	||	strcmp("at",test) == 0   ||
	   strcmp("from",test) == 0	||	strcmp("also",test) == 0 ||
	   strcmp("in",test) == 0	||	strcmp("that",test) == 0)
	{	
		return 0;
	}else{
		return -1;
	}
}

char* toArray(int number){
     	char* char_arr;
	sprintf(char_arr, "%d", number); 
	return char_arr;
}

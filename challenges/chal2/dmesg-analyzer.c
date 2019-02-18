#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define REPORT_FILE "report.txt"

void analizeLog(char *logFile, char *report);

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage:./dmesg-analizer.o logfile.txt\n");
        return 1;
    }
    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void analizeLog(char *logFile, char *report){

        printf("Generating Report from: [%s] log file\n", logFile);

        FILE *fleer = fopen(logFile,"r");
        FILE *fescribir = fopen(report,"w");

        if (fleer == NULL){
                printf("Error al abrir el archivo: %s\n",logFile);
                return;
        }
        if (fescribir == NULL){
                printf("Error al abrir el archivo: %s\n",report);
        }

        int d;

        char num[16];
        char title[300];
        char fondo[300];
        char numFondo[316];
        char *textoF[1000][1000];

        for(int i = 0; i < 1000 ; i++){
                for(int j = 0 ; j < 1000 ; j++){
                        textoF[i][j] = ".";
                }
        }

        textoF[0][0] = "General";
        int sizeGen = 1;
        while((d = fgetc(fleer)) != EOF){
                // Leer cada characiter


                //Leer numero
                for(int i = 0; i < 15 ;i++ ){
                        num[i] = d;
                        d = fgetc(fleer);
                }

                int flag = 1;
                //Bandera que me indica si hay titulo o no
                // Busqueda del titulo
                for(int j = 0 ; d != '\n' && d != '\0' && flag == 1 ; j++){

                        if(d == ':'){
                                flag = 0;
                        }
                        title[j] = d;
                        d = fgetc(fleer);
                }

                if (flag == 1){
                        for(int i = 0 ; i < sizeof(title) ; i++){
                                fondo[i] = title[i];
                        }
                        strcpy(title,"General :\n");
                // Title es General
                }else{
                        strcat(title,"\n");
                        for(int i = 0; d != '\0' && d != '\n'; i++){
                                fondo[i] = d;
                                d = fgetc(fleer);

                        }

                }

                //Asignar a arreglo bidimensional

                strcpy(numFondo, num);
                strcat(numFondo,strcat(fondo,"\n\0"));

                if(flag == 1){
                        //Default
                        textoF[0][sizeGen] = numFondo;
                        sizeGen++;
                }else{
                        // Titulo asignado
                        int i;
                        for(i = 0 ; strcmp(textoF[i][0], ".") != 0 && strcmp(textoF[i][0], title) != 0 ; i++){}


                        if(strcmp(textoF[i][0], ".") == 0){
                                textoF[i][0] = strcat(title,"\n\0");
                                textoF[i][1] = numFondo;

                                printf("Titulo : %s",title);
                                printf("Numfondo : %s",numFondo);

                        }else if(textoF[i+1][0] == title){
                                int j;
                                for(j = 1 ; strcmp(textoF[i][j], ".") != 0 ; j++){}
                                textoF[i][j] = numFondo;

                        }
                }

                printf("%s%s",title,numFondo);
                memset(num, '\0', sizeof(num));
                memset(title, '\0', sizeof(title));
                memset(fondo, '\0', sizeof(fondo));
                memset(numFondo,'\0',sizeof(numFondo));
        }

        char *buff;
        for (int k = 0; strcmp(textoF[k][0],".") != 0 ; k++){
                for (int p = 0 ;strcmp(textoF[k][p],".") != 0; p++){
                        buff = textoF[k][p];
                        fputs(buff,fescribir);
                }
        }
        fclose(fleer);
        fclose(fescribir);
        printf("Report is generated at :[%s]\n", report);
}

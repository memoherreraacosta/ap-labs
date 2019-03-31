#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>

#define SLEEP_TIME 3
#define PROCESSES_TO_READ 1000

struct process {
	char name[20],
	     state[25],
	     pid[5],
	     ppid[5],
	     memory[25],
	     threads[25];

	int nFiles;
};
struct pid{
  int value;
};

struct process processes[PROCESSES_TO_READ];

static void saveProcesses(int signo);
int printTop();
int getTotalProcNum();
int main(int argc, char ** argv);
void getTable();
void clear();

static void saveProcesses(int signo) {
	FILE *fp;
  char filename[150];
  strcpy(filename, "mytop-status-");
    
  time_t rawtime;
  struct tm *timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  strcat(filename, strcat(asctime(timeinfo),".txt"));

	fp = fopen(filename, "w");
	fprintf(fp, "|%-7s | %-7s | %-35s | %-15s | %-10s | %-5s | %-10s|\n", 
              "PID", "Parent", "Name", "State", "Memory", "Threads", "Open Files");

	fprintf(fp, "%s\n", 
  "|-------|-------|-----------------------------------|---------------|----------|-----|----------|\n");
  int i;
	for(i = 0; processes[i].name[0] != '\0'; i++) {
		fprintf(fp, "| %-7s | %-7s | %-35s | %-15s | %-10fM | %-5s | %-10d|\n", 
    processes[i].pid, processes[i].ppid, processes[i].name, processes[i].state, 
    atof(processes[i].memory) / 1000, processes[i].threads, processes[i].nFiles);

	}
	printf("\nSaved as: %s\n", filename);
	fclose(fp);
	sleep(SLEEP_TIME);
}

int printTop() {
	int i = 0;
	printf("|%-7s | %-7s | %-35s | %-15s | %-10s | %-5s | %-10s|\n",
           "PID", "Parent", "Name", "State", "Memory","Threads", "Open Files");

	printf("%s\n", "|-------|-------|-----------------------------------|---------------|----------|-----|----------|\n");

	while(processes[i].name[0] != '\0') {
		printf("| %-7s | %-7s | %-35s | %-15s | %-10fM | %-5s | %-10d|\n", 
           processes[i].pid, processes[i].ppid, processes[i].name, 
           processes[i].state, atof(processes[i].memory) / 1000, 
           processes[i].threads, processes[i].nFiles);

		i++;
	}
	return 0;
}

int getTotalProcNum(){
    int num = 0;
    DIR *dir = opendir("/proc/");
    struct dirent *d;  
    
    if (dir != NULL){
        while ((d = readdir (dir))){
            if(isdigit(d->d_name[0])){
                num+=1;
            }
        }
        (void)closedir(dir);
    }else{
        printf("\nerror\n");
        return -1;
    }
    return num;
}

void getTable(){

  int nProc = getTotalProcNum();
  struct dirent *currDir; 
  struct pid pids[nProc]; 
  int pos=0;
  int files=0;
  int k=0;
  char path[30];
  char fdpath[30];

  DIR *d = opendir("/proc/");
  FILE *fp;

  strcpy(path, "/proc/");
  strcpy(fdpath, "/proc/"); 
    
  if (d != NULL){
    while ((currDir = readdir (d))){
      if(isdigit(currDir->d_name[0])){
        files = 0;

        pids[pos].value=atoi(currDir->d_name);
        pos+=1;

        strcat(path, currDir->d_name);
        strcat(path, "/status");

        strcat(fdpath, currDir->d_name);
		    strcat(fdpath, "/fd");

        fp = fopen(path, "r");
        char buffer[255];

            // Read file to get values 

        while(fgets(buffer, 255, (FILE*) fp)) {

                // Read file 
          if(buffer[0]=='N'){
            if(buffer[1]=='a' && buffer[2]=='m' && buffer[3]=='e'){
              int i;
              char nombre[20];
              int posN=0; 
              int terminar=0;   
              for(i=5;i<255;i++){
                if(buffer[i]=='\n'){
                  break;
                }
                if(buffer[i]==' '){
                  if(terminar==1){
                    nombre[posN]='\0';
                      break;
                  }
                  continue;
                }

                nombre[posN]=buffer[i];
                posN+=1;
                terminar=1;
              }
              strcpy(processes[k].name,nombre);
              memset(nombre,0,20);
            }
          }else if(buffer[0]=='S'){
            if(buffer[1]=='t' && buffer[2]=='a' && buffer[3]=='t' && buffer[4]=='e'){
              int i;
              char estado[20];
              int posN=0;
              int terminar=0;

              for(i=6;i<255;i++){
                if(buffer[i]=='\n'){                   
                  break;
                }
                if(buffer[i]==' '){
                  if(terminar==1){
                    estado[posN]='\0';
                    break;
                  }
                  continue;
                }
                estado[posN]=buffer[i];
                posN+=1;
                terminar=1;
              }
              strcpy(processes[k].state,estado);
              memset(estado,0,20);

              }
            }else if(buffer[0]=='P'){
              if(buffer[1]=='i' && buffer[2]=='d'){
                int i;
                char dataPID[20];
                int posN=0;
                int terminar=0;
                for(i=4;i<255;i++){
                  if(buffer[i]=='\n'){                       
                    break;
                  }
                  if(buffer[i]==' '){
                    if(terminar==1){
                      dataPID[posN]='\0';
                      break;
                    }
                    continue;
                  }
                  dataPID[posN]=buffer[i];
                  posN+=1;
                  terminar=1;
                }
                strcpy(processes[k].pid,dataPID);
                memset(dataPID,0,20);

              }else if(buffer[1]=='P' && buffer[2]=='i' && buffer[3]=='d'){
                int i;
                char dataPPID[20];
                int posN=0;
                int terminar=0;
                for(i=5;i<255;i++){
                  if(buffer[i]=='\n'){
                    break;
                  }
                  if(buffer[i]==' '){
                    if(terminar==1){
                      dataPPID[posN]='\0';
                      break;
                    }
                    continue;
                  }
                  dataPPID[posN]=buffer[i];
                  posN+=1;
                  terminar=1;
                }
                strcpy(processes[k].ppid,dataPPID);
                memset(dataPPID,0,20);

               }
              }else if(buffer[0]=='V'){
                  //VmRSS
                if(buffer[1]=='m' && buffer[2]=='R' && buffer[3]=='S' && buffer[4]=='S'){

                  int i;
                  char memoria[20];
                  int posN=0;
                  int terminar=0;
                  for(i=6;i<255;i++){
                    if(buffer[i]=='\n'){
                      break;
                    }
                    if(buffer[i]==' '){            
                      continue;
                    }

                    memoria[posN]=buffer[i];
                    posN+=1;
                    terminar=1;
                  }
                  if(memoria[0] == '\0'){
                    strcpy(processes[k].memory," ");
                  }else{
                    strcpy(processes[k].memory,memoria);
                    memset(memoria,0,20);
                  }
                 }
              }else if(buffer[0]=='T'){
                  //Threads
                if(buffer[1]=='h' && buffer[2]=='r' && buffer[3]=='e' && buffer[4]=='a' && buffer[5]=='d' && buffer[6]=='s'){
                  int i;
                  char threads[20];
                  int posN=0;   
                  int terminar=0;                 
                  for(i=8;i<255;i++){
                    if(buffer[i]=='\n'){
                      break;
                    }
                    if(buffer[i]==' '){
                      if(terminar==1){
                        threads[posN]='\0';
                        break;
                      }
                      continue;
                    }
                    threads[posN]=buffer[i];
                    posN+=1;
                    terminar=1;
                   }
                  if(threads[0] == '\0'){
                    strcpy(processes[k].memory," ");
                  }else{
                    strcpy(processes[k].threads,threads);
                    memset(threads,0,20);
                  }
                }
               }
            }
            fclose(fp);

            DIR *d2 = opendir(fdpath);
            int l = 0; // 
            struct dirent *ep2;  

            if (d != NULL){
              while ((ep2 = readdir (d2))){
                l += 1;
              }
            }
            (void) closedir (d2);
            processes[k].nFiles = l - 2;
            k++;
	      	  strcpy(path, "/proc/");
            strcpy(fdpath, "/proc/");
          }
        }
        (void) closedir (d);
      }
      else{
        printf("error\n");
      }
}

void clear() {
  printf("\e[1;1H\e[2J"); 
}

int main(int argc, char ** argv){
    
    // Leer interrupcion ctrl + c
    if(signal(SIGINT, saveProcesses) == SIG_ERR) {
       printf("Error\n");
    }
    // Tablita
    for(;;) {
        getTable();
        printTop();

        sleep(SLEEP_TIME);
        clear();
      }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <dirent.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

#define WAIT_TIME 3
#define PROC_TO_CHECK 10000

int main(int argc, char **argv);
int magic();
void checkFile(char *logFile);
void clear();
void cOFiles();
void printTable();
void processLine(char *line);

struct process{             // Struct to handle each process
  char pid[10];
  char parent[10];
  char name[30];
  char state[20];
  char mem[20];
  char threads[30];
  int files_open;
};

struct process totalP[PROC_TO_CHECK]; // Total processes to check
int pPos = 0;

void clear() {
  printf("\e[1;1H\e[2J"); 
}

void printTop(){
	printf("|__________|__________|_______________|__________|__________|__________|______________________________|\n");
	printf("|PID       |PPID      |STATUS         |THREADS   | MEMORY   |OPEN FILES|NAME                          |\n");
	printf("|__________|__________|_______________|__________|__________|__________|______________________________|\n");
}

void printTable(){

	printTop();
  float mem;
	for(int i = 0; i < pPos; i++){
		if(totalP[i].pid == 0){
			continue;
		}
		mem = atof(totalP[i].mem) / 1000;
		
		printf("|%10s|%10s|%15s|%10s|%10f M|%10i|%30s|\n", 
            totalP[i].pid, totalP[i].parent, 
            totalP[i].state, totalP[i].threads, 
            mem, totalP[i].files_open, 
            totalP[i].name);	
	}
	printf("|__________|__________|_______________|__________|__________|__________|______________________________|\n");
	return;
}

void cOFiles(char *fpath){
	
  int openFiles;
	struct dirent *fd_dir;
  
  DIR *fdd = opendir(fpath);

	while((fd_dir = readdir(fdd)) != NULL)
		openFiles++;

	closedir(fdd);
	totalP[pPos].files_open = openFiles - 2;
	strcpy(fpath, "/proc/");
}

void checkFile(char *logFile) {
  int fp;
  int c;
  char *f = (char *)malloc(sizeof(char)*1);

  if((fp = open(logFile, O_RDONLY)) < 0){
	  printf("cannot open file");
  }

  char line[400]; 
  memset(line, 0, 400);

  while((c = read(fp, f, 1)) > 0){
	  *f = tolower(*f);

	  if( *f == '\n'){
	    strcat(line, "\n\0");
	    processLine(line);
	    memset(line, 0, 500);
	  }else{
	    strcat(line, f);
	  }
  }
  close(fp);
}

void processLine(char *line){
    
  char *buff = (char *)malloc(sizeof(char) * 4);
  char *data = (char *)malloc(sizeof(char) * 80);
  bool flag = true;
  int p = 0;
	int j = 0;

	for(int i = 0; line[i] != '\0'; i++){
	  if(line[i] == ':'){
	    flag = false;
	  }

	  if(flag){
	    if(p<4){
		    buff[i] = line[i];
		    p++;
	    }
	  }

	  if(flag == false){
      if (strcmp(buff, "pid") == 0 || strcmp(buff, "ppid") == 0 ||
          strcmp(buff, "name") == 0 || strcmp(buff, "stat") == 0 || 
          strcmp(buff, "thre") == 0){

	          if(line[i] != ' ' && 
               line[i] != ':' && 
               line[i] != '\t' && 
               line[i] != '\n'){
									data[j] = line[i];
			        		j++;
  	        }	
      }
	      if (strcmp(buff, "vmrs") == 0){
          if(line[i] != ' ' && line[i] != ':' && 
             line[i] != '\t' && line[i] != '\n' && 
             line[i] != 'k' && line[i] != 'b')
         {
	  	      data[j] = line[i];
		  	    j++;
	       }	
        }	
  	}
  	}
    if (strcmp(buff, "pid") == 0){ 					strcpy(totalP[pPos].pid, data);
    }else if (strcmp(buff, "ppid") == 0){		strcpy(totalP[pPos].parent, data);
    }else if (strcmp(buff, "name") == 0){		strcpy(totalP[pPos].name, data);
    }else if (strcmp(buff, "stat") == 0){		strcpy(totalP[pPos].state, data);
    }else if (strcmp(buff, "thre") == 0){		strcpy(totalP[pPos].threads, data);
    }else if (strcmp(buff, "vmrs") == 0){		strcpy(totalP[pPos].mem, data);
    }
}

int magic(){
	struct dirent *dir;
  DIR *d = opendir("/proc/");
	char path[30], fpath[30];
	int f = 1;
  int flag = 0;

  for(;;){
	  strcpy(path, "/proc/");
	  strcpy(fpath, "/proc/");
	  while((dir = readdir(d)) != NULL) {
		  if(isdigit(dir->d_name[0])){
			  strcat(path, dir->d_name);
			  strcat(path, "/status");
			  strcpy(totalP[pPos].mem, "0");
			  checkFile(path);
			  pPos++;
			  strcpy(path, "/proc/");
			  strcat(fpath, dir->d_name);
			  strcat(fpath, "/fd");
			  cOFiles(fpath);
			  flag++;
		  }
	  }
	  printTable();
	  sleep(WAIT_TIME);
	  clear();
	  f++;
  }
  clear();
  return 0;
}

int main(int argc, char **argv){
  return magic();
}

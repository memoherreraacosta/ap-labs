#include <stdio.h>
#define REPORT_FILE "list.txt"

int createReport(char *fRead, char *fList); 
int omitir(char *test);

int main(int argc, char **argv) {

    if (argc != 2) {
	printf("Error in number of arguments\n");
	return 1;
    }
    int res = createReport(argv[1], REPORT_FILE);
    return res;
}

int createReport(char *fRead, char *fList) {
	FILE *fp1, *fp2;
	char ch;
	int pos;
 
	if ((fp1 = fopen(fRead,"r")) == NULL){    
		printf("\nFile cannot be opened");
        	return -1;
    	}

    	fp2 = fopen(fList, "w");  
    	fseek(fp1, 0L, SEEK_END); // file pointer at end of file
    	pos = ftell(fp1);
    	fseek(fp1, 0L, SEEK_SET); // file pointer set at start

	int lineC = 1;
	
	while (pos--){
        	ch = fgetc(fp1);  // copying file character by character
        	
		
		lineC ++;
		fputc(ch, fp2);
    	}
    	fclose(fp1);
    	fclose(fp2);	
	return 0;
}
int omitir(char *test){
	switch(test):
	
	case "and":
		return -1;
	case "the":
		return -1;
	case "a":
		return -1;
	case "to":
		return -1;
	case "an":
		return -1;
	case "of":
		return -1;
	case "for":
		return -1;
	case "at":
		return -1;
	case "from":
		return -1;
	case "also":
		return -1;
	case "in":
		return -1;
	case "that":
		return -1;
	default:
		return 0;
}

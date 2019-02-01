int strlen(char *str){
	int x = 0;
	for(int i = 0; str[i] != '\0' ; i++){
		x += 1;
	}
	return x;
}

char* stradd(char *origin, char *addition){
	char *newS;

	newS = (char *)malloc(strlen(origin)+strlen(addition)+1);
	if(!newS){
		perror("Failed to allocate space because: ");
		exit(1);
	}

	for(int i = 0 ; i < len(origin) ; i++){
		newS[i] = origin[i];
	}
	int x = 0;
	for(int i = len(origin) ; i < len(newS) ; i++){
		newS[i] = addition[x];
		x += 1; 
	}
	newS[x] = "\0";
	return newS;
}

int strfind(char *origin, char *substr){
	int found = 1; //True = 0 , False = 1
	int flag;

	for(int i = 0; i < len(origin) ; i++){
		if(origin[i] == substr[0]){
			//Se entrara a un ciclo donde se buscara comprobar que la palabra substr esta dentro de origin
			flag = len(substr);
			for(int j = 0 ; j < len(substr) && (j+i) < len(origin) ; j ++){
				if (substr[j] == origin[j+i]){
					flag -= 1;
				}
				if(flag == 0){
					return 0;
				}
			}	
		}
	}	
	return found;
}

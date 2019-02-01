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
		return "-1";
	}
	int lenO = 0;
	for(int i = 0 ; origin[i] != '\0'  ; i++){
		newS[i] = origin[i];
		lenO = i;
	}
	int x = 0;
	for(int i = lenO  ; addition[i] != '\0' ; i++){
		newS[i] = addition[x];
		x += 1; 
	}
	newS[x] = '\0';
	return newS;
}

int strfind(char *origin, char *substr){
	int found = 1; //True = 0 , False = 1
	int flag;
	int lenSubstr;

	for(int i = 0  ; substr[i] != '\0' ; i++){
		lenSubstr = i;
	}

	for(int i = 0; i < origin[i] != '\0' ; i++){
		if(origin[i] == substr[0]){
			//Se entrara a un ciclo donde se buscara comprobar que la palabra substr esta dentro de origin
			flag = lenSubstr;
			for(int j = 0 ; j < lenSubstr  && origin[j+i] != '\0' ; j ++){
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

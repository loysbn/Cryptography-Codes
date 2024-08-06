#include<stdio.h>
#include<ctype.h>
#include<string.h>

void encrypt(char *str, char *newKey){
	int i;
	char result[255];
		for(i = 0; i < strlen(str); i++){
			if(!isalpha(str[i])){ // checks if the character is a number
				result[i] = str[i];
			} else {
				result[i] = (isupper(str[i])) ? ((str[i] + newKey[i]) % 26) + 65 : tolower(((toupper(str[i]) + toupper(newKey[i])) % 26) + 65);
				//result[i] = ((str[i] + newKey[i]) % 26) + 65;
			}
		}
		result[i] = '\0';
		printf("\nResult:\n%s", result);
}

void decrypt(char *str, char *newKey){
	int i;
	char result[255];
		for(i = 0; i < strlen(str); i++){
			if(!isalpha(str[i])){
				result[i] = str[i];
			} else {
				result[i] = (isupper(str[i])) ? ((str[i] - newKey[i]+26) % 26) + 65 : tolower(((toupper(str[i]) - toupper(newKey[i])+26) % 26) + 65);
				//result[i] = ((str[i] + newKey[i]) % 26) + 65;
			}
		}
		result[i] = '\0';
		printf("\nResult:\n%s", result);
	
}

int main(){
	
	int num, i, j;
	char str[255], key[50];
	
	printf("Do you want to encrypt or decrypt?\n[1]Encrypt\n[2]Decrypt\n");
	scanf("%d", &num);
	
	fflush(stdin);
	printf("\nEnter a text:\n");
	gets(str);
	
	fflush(stdin);
	printf("Enter keyword:\n");
	gets(key);

	int len = strlen(str);
	char newKey[len];
	for(i = 0, j = 0; i < len; i++){ // 
		if(key[j] == '\0'){ // checks if its the end of the string, if it is, it goes back to the first character of the string
			j = 0;
		}
		if(!isalpha(str[i])){ // checks if the character is not an alphabet
			newKey[i] = str[i];
		} else {
			if(!isalpha(key[j])){
				newKey[i] = toupper(key[j++]);
			} else {
				newKey[i] = toupper(key[j++]);
			}	
		}
	}
	newKey[i] = '\0';
	
	if(num == 1){
		encrypt(str, newKey);
	} else if(num == 2){
		decrypt(str, newKey);
	}
	
	return 0;
}

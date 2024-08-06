#include<stdio.h>
#include<ctype.h>
#include<string.h>

void encrypt(char *str, char *newKey){
	int i;
	char result[255];
	FILE *fp;
	
	if((fp = fopen("polyalpha_text.txt", "w")) == NULL){
		printf("File failed to open.");
	} else {
		for(i = 0; i < strlen(str); i++){
			if(!isalpha(str[i])){ // checks if the character is a number
				result[i] = str[i];
			} else {
				result[i] = (isupper(str[i])) ? ((str[i] + newKey[i]) % 26) + 65 : tolower(((toupper(str[i]) + toupper(newKey[i])) % 26) + 65);
			}
		}
		result[i] = '\0';
		fprintf(fp, "%s", result);
		fclose(fp);
	}
}

void decrypt(char *str, char *newKey){
	int i;
	char result[255];
	FILE *fp;
	
	if((fp = fopen("polyalpha_text.txt", "w")) == NULL){
		printf("File failed to open.");
	} else {
		for(i = 0; i < strlen(str); i++){
			if(!isalpha(str[i])){
				result[i] = str[i];
			} else {
				result[i] = (isupper(str[i])) ? ((str[i] - newKey[i]+26) % 26) + 65 : tolower(((toupper(str[i]) - toupper(newKey[i])+26) % 26) + 65);
			}
		}
		result[i] = '\0';
		fprintf(fp, "%s", result);
		fclose(fp);
	}
}

int main(){
	
	int num, i, j;
	char str[255], key[50];
	FILE *fptr;
	
	printf("Do you want to encrypt or decrypt?\n[1]Encrypt\n[2]Decrypt\n");
	scanf("%d", &num);
	
//	fflush(stdin);
//	printf("\nEnter a text:\n");
//	gets(str);
//	
	fflush(stdin);
	printf("Enter keyword:\n");
	gets(key);

	if((fptr = fopen("polyalpha_text.txt", "r")) == NULL){ // the file you want to encrypt or decrypt
		printf("File failed to open.");
	} else {
		fgets(str, 255, fptr);
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
		printf("New Key: %s\n", newKey);
		if(num == 1){
			encrypt(str, newKey);
		} else if(num == 2){
			decrypt(str, newKey);
		}
	}
	return 0;
}

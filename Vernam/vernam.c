#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int solveXOR(int strSize, int strArr[][strSize], int i){ // this function will solve for the XOR
	int xorResult;
	xorResult = strArr[0][i] ^ strArr[1][i];
	if(xorResult > 26){
		xorResult -= 26;
	}
	return xorResult;
}

int main(){
	char alphabets[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str[255], key[100];
	char result[255] = "", temp[100] = "";
	int num, i, j ,k = 0, x, alphNum, retVal;
	FILE *fptr;
	
//	printf("Do you want to encrypt or decrypt?\n[1]Encrypt\n[2]Decrypt\n");
//	scanf("%d", &num);
	
//	printf("Enter a text: ");
//	gets(str);
//	fflush(stdin);
	
	if((fptr = fopen("vernam_text.txt", "r")) == NULL){
		printf("File failed to open.");
		exit(0);
	}
	
	fgets(str, 255, fptr);
	printf("Enter key with %d letters: ", strlen(str));
	gets(key);
	
	if((fptr = fopen("vernam_text.txt", "w")) == NULL){
		printf("File failed to open.");
		exit(0);
	} else {
		int strSize = strlen(str);
		int strArr[2][strSize]; // 2d array
		
		if(strlen(str) != strlen(key)){ // if the length of the text and key is not equal, the program will be terminated
			printf("Key length should be equal to the length of the text.");
			exit(0);
		} 
		
		for(i = 0; str[i] != '\0'; i++){ // getting the assigned number of the string letters from the alphabets
			for(j = 0; j < 26; j++){
				if(tolower(str[i]) == tolower(alphabets[j])){
					strArr[0][k] = j;
					k++;
				}
			}
		}
		k = 0;
		for(i = 0; key[i] != '\0'; i++){ // getting the assigned number of the key letters from the alphabets
			for(j = 0; j < 26; j++){
				if(tolower(key[i]) == tolower(alphabets[j])){
					strArr[1][k] = j;
					k++;
				}
			}
		}
		
		for(i = 0, x = 0; i < strSize; i++){ // encryption
			retVal = solveXOR(strSize, strArr, i); // calling the function to solve for XOR
			result[i] = alphabets[retVal];
			if(islower(str[i])){
				result[i] = tolower(alphabets[retVal]);
			} else {
				result[i] = alphabets[retVal];
			}
			
		}
		fprintf(fptr, "%s", result);
		fclose(fptr);
	}
	
	
	return 0;
}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int solveXOR(int strSize, int strArr[][strSize], int i){
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
	int num, i, j ,k = 0, x, y, alphNum, retVal;
	FILE *fptr;
	
//	printf("Do you want to encrypt or decrypt?\n[1]Encrypt\n[2]Decrypt\n");
//	scanf("%d", &num);
	
	printf("Enter a text: ");
	gets(str);
	fflush(stdin);
	

	printf("Enter key with %d letters: ", strlen(str));
	gets(key);
	
	int strSize = strlen(str);
	int keySize = strlen(key);
		int strArr[2][strSize];
		if(strlen(str) != strlen(key)){ // if the length of the text and key is not equal, the program will be terminated
			printf("Key length should be equal to the length of the text.");
			exit(0);
		} 
		
		for(i = 0; str[i] != '\0'; i++){
			for(j = 0; j < 26; j++){
				if(tolower(str[i]) == tolower(alphabets[j])){
					strArr[0][k] = j;
					k++;
				}
			}
		}
		k = 0;
		for(i = 0; key[i] != '\0'; i++){
			for(j = 0; j < 26; j++){
				if(tolower(key[i]) == tolower(alphabets[j])){
					strArr[1][k] = j;
					k++;
				}
			}
		}
		
		for(i = 0, x = 0, y = 0; str[i] != '\0'; i++){
//			if(!isalpha(str[i])){
//				result[i] = str[i];
//			} 
			retVal = solveXOR(strSize, strArr, i);
//			result[i] = alphabets[retVal];
				if(islower(str[i])){
					result[i] = tolower(alphabets[retVal]);
				} else {
					result[i] = alphabets[retVal];
				}	
			
		}
		result[i] = '\0';
		printf("Result: %s\n", result);
	
	
	return 0;
}

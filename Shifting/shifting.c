#include<stdio.h>
#include<math.h>

void encrypt(char* alphabets, char* msg, int shift){
	char result[255] = "";
	int i, j, k = 0, x;
	FILE *fp;
	
	if((fp = fopen("shifting_text.txt", "w")) == NULL){
		printf("File failed to open.");
	} else {
		for(i = 0; msg[i] != '\0'; i++){
			if(!isalpha(msg[i])){
				result[k] = msg[i];
				k++;
			}
			for(j = 0; alphabets[j] != '\0'; j++){
				if(islower(msg[i])){ // checks if the letter is a lowercase, if yes then the result will also be set to lowercase
					if(msg[i] == tolower(alphabets[j])){
						x = (j + shift) % 26;
						result[k] = tolower(alphabets[x]);
						k++;
					}
				} else if(msg[i] == alphabets[j]){
					x = (j + shift) % 26;
					result[k] = alphabets[x];
					k++;
				}
			}
		}
		result[k] = '\0';
		fprintf(fp,"%s", result);
		fclose(fp);
	}
}

void decrypt(char* alphabets, char* msg, int shift){
	char result[255] = "";
	int i, j, k = 0, x, num;
	float flr;
	FILE *fp;
	
	if((fp = fopen("shifting_text.txt", "w")) == NULL){
		printf("File failed to open.");
	} else {
		for(i = 0; msg[i] != '\0'; i++){
			if(!isalpha(msg[i])){
				result[k] = msg[i];
				k++;
			}
			for(j = 0; alphabets[j] != '\0'; j++){
				if(islower(msg[i])){ // checks if the letter is a lowercase, if yes then the result will also be set to lowercase
					if(msg[i] == tolower(alphabets[j])){
						x = (j - shift + 26) % 26;
						result[k] = tolower(alphabets[x]);
						k++;
					}
				} else if(msg[i] == alphabets[j]){
					x = (j - shift + 26) % 26;
					result[k] = alphabets[x];
					k++;
				}
			}
		}
		result[k] = '\0';
		fprintf(fp,"%s", result);
		fclose(fp);
	}
}

int main(){
	
	char alphabets[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
	char str[255];
	int shift, num;
	FILE *fptr;
	
	if((fptr = fopen("shifting_text.txt", "r")) == NULL){ // the file you want to encrypt or decrypt
		printf("File failed to open.");
	} else {
		printf("Do you want to encrypt or decrypt?\n[1]Encrypt\n[2]Decrypt\n");
	    scanf("%d", &num);
	    
	    switch (num) {
	        case 1:
	            fflush(stdin);
//	            printf("\nEnter a text to encrypt:\n");
//	            gets(str);
				fgets(str, 255, fptr);
	            printf("\nShift value: ");
	            scanf("%d", &shift);
	            encrypt(alphabets, str, shift);
	            break;
	        case 2:
	        	fflush(stdin);
//	            printf("\nEnter a text to decrypt:\n");
//	            gets(str);
				fgets(str, 255, fptr);
	            printf("\nShift value: ");
	            scanf("%d", &shift);
	            decrypt(alphabets, str, shift);
	            break;
	        default:
	            printf("Invalid input");
	            break;
	    }
	    fclose(fptr);
	}
	return 0;
}

#include<stdio.h>
#include<ctype.h>

void atbash(char* plain, char* cipher, char* msg){ // can be use for both encrypt and decrypt
    char result[255] = "";
    int i, j, k = 0;
    FILE *fp;
    
    if((fp = fopen("atbash_text.txt", "w")) == NULL){
		printf("Error!");
	} else {
		for(i = 0; msg[i] != '\0'; i++){
			if(!isalpha(msg[i])){// checks if the character is not an alphabet
				result[k] = msg[i];
				k++;
			}
	        for(j = 0; plain[j] != '\0'; j++){
	        	if(islower(msg[i])){ // checks if the letter is a lowercase, if yes then the result will also be set to lowercase
	        		if(msg[i] == tolower(plain[j])){
						result[k] = tolower(cipher[j]);
						k++;
			        }
				} else if(msg[i] == plain[j]){
					result[k] = cipher[j];
					k++;
		        }
			}
	    }
	    result[i] = '\0';
		fprintf(fp, "%s", result);
		fclose(fp);	
	}
}

int main(){

    char plain[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char cipher[27];
    char str[255];
    int i, j = 0, k, num;
    FILE *fptr;
    
    if((fptr = fopen("atbash_text.txt", "r")) == NULL){ // the file you want to encrypt or decrypt
    	printf("Error!");
	} else {
		for(i = 25; i >= 0; i--) { // cipher gets the alphabet letters from plain but in reverse order
	        cipher[j] = plain[i];
	        j++;
	    }
	    cipher[27] = '\0';
	
	    printf("Do you want to encrypt or decrypt?\n[1]Encrypt\n[2]Decrypt\n");
	    scanf("%d", &num);
	    
	    switch (num) {
	        case 1:
	            fflush(stdin);
//           	printf("\nEnter a text to encrypt:\n");
//            	gets(str);
				fgets(str, 255, fptr);
	            atbash(plain, cipher, str);
	            break;
	        case 2:
	        	fflush(stdin);
//	            printf("\nEnter a text to decrypt:\n");
//	            gets(str);
	            fgets(str, 255, fptr);
	            atbash(plain, cipher, str);
	            break;
	        default:
	            printf("Invalid input");
	            break;
		}
		fclose(fptr);
	}
    return 0;
}

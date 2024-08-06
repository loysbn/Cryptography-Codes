#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

int alpha_to_num(char c){ // Function that converts letters to numbers
    int n = 1;
    static const char * const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *p = strchr(alphabet, toupper((unsigned char)c));

    if(p){
        n = p - alphabet;
    }
    return n+1;
}

char* atbash(char* plain, char* cipher, char* msg){
	char* result = (char*)malloc(sizeof(char) * strlen(msg)+1);
    int i, j, k = 0;
    
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
	return result;
}

char* shiftEncrypt(char* alphabets, char* msg, int shift){
	char* result = (char*)malloc(sizeof(char) * strlen(msg)+1);
	int i, j, k = 0, x;

		for(i = 0; msg[i] != '\0'; i++){
			if(!isalpha(msg[i])){// checks if the character is not an alphabet
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
	return result;
}

char* shiftDecrypt(char* alphabets, char* msg, int shift){
	char* result = (char*)malloc(sizeof(char) * strlen(msg)+1);
	int i, j, k = 0, x, num;
	
		for(i = 0; msg[i] != '\0'; i++){
			if(!isalpha(msg[i])){// checks if the character is not an alphabet
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
		return result;
}

void encryptRSA(char* msg, int n, int totient){
	int i, j = 0, k = 0, c, ctr = 0, e;
	char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char result[255] = "";
	int msgLen = strlen(msg);
	int arr[msgLen];
	char temp[msgLen];
	FILE *fptr;
	
	if((fptr = fopen("crypto_project.txt", "w")) == NULL){
		printf("File failed to open.");
		exit(0);
	}
	
	printf("\n========== ENCRYPTION KEY ==========\n");
	printf("Encryption key should be, 1 < (e) < %d\n", totient);
	printf("Encryption key should be co-prime with %d and %d\n", n, totient);
	printf("Enter a number for (e)encryption key: ");
	scanf("%d", &e);
	
	// converting letters to numbers
	for(i = 0; msg[i] != '\0'; i++){
		if(!isalpha(msg[i])){
			ctr++;
			continue;
		}
		arr[j] = alpha_to_num(msg[i]);
		j++;
	}

	// copying the text from msg to temp except for the non-alphabet characters
	for(i = 0, j = 0; msg[i] != '\0'; i++){
		if(!isalpha(msg[i])){
			continue;
		}
		temp[j] = msg[i];
		j++;
	}
	
	// printing the values of the letters
	printf("\n");
	for(i = 0; i < j; i++){
		printf("%d ", arr[i]);
	}
	
	// encrypting
	int x = msgLen - ctr;
	for(i = 0; i < x; i++){
		c = pow(arr[i], e);
		c = c % n;
		if(c <= 0){
			c = 1;
		}
		if(islower(temp[i])){
			result[k] = tolower(alphabets[c-1]);
		} else {
			result[k] = alphabets[c-1];
		}
		k++;
	}
	
	result[k] = '\0';
	fprintf(fptr, "%s", result);
	fclose(fptr);
}

char* decryptRSA(char* msg, int n, int totient){
	int i, j = 0, d, ans, flag = 0, ctr = 0, c = 0, m = 0, k = 0, e;
	char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* result = (char*)malloc(sizeof(char) * strlen(msg)+1);
	int msgLen = strlen(msg);
	int arr[msgLen];

	printf("Enter th encryption key: ");
	scanf("%d", &e);
	
	printf("\n============================\n");
	// printing possible values for the decryption key
	printf("Private key (d): \n");
	for(i = 1; i < 1000 && flag != 1; i++){ // computes for the decryption key
		ans = (e * i) % totient;
		if(ans == 1){
			printf("%d ", i);
			ctr++;
		}
		if(ctr == 1){
			flag = 1;
		}
	}
	printf("\n============================\n");
	printf("\nEnter (d)decryption key: ");
	scanf("%d", &d);
	
	// converting letters to numbers
	for(i = 0, ctr = 0; msg[i] != '\0'; i++){
		if(!isalpha(msg[i])){
			ctr++;
			continue;
		}
		arr[j] = alpha_to_num(msg[i]);
		j++;
	}
	
	// printing the values of the letters
	printf("\n");
	for(i = 0; i < j; i++){
		printf("%d ", arr[i]);
	}
	
	// decrypting Meefaffhdeebm (Mccfaffhbccdm)
	for(i = 0; i < msgLen; i++){
		m = pow(arr[i], d);
		m = m % n;
		if(m <= 0){
			m = 1;
		}
		if(islower(msg[i])){
			result[k] = tolower(alphabets[m-1]);
		} else {
			result[k] = alphabets[m-1];
		}
		k++;
	}
	
	result[k] = '\0';
	return result;
}

void decrypt(char* msg){
	FILE *fptr;
	
	if((fptr = fopen("crypto_project.txt", "w")) == NULL){
		printf("File failed to open.");
		exit(0);
	}
	fprintf(fptr, "%s", msg);
	fclose(fptr);
}

int main(){

    char plain[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char cipher[27];
    char str[255];
    char* atbashResult;
    char* shiftResult;
    char* rsaDecryptResult;
    int i, j = 0, k, num, shift, p, q, n, totient, e;
    FILE *fptr;
	
	if((fptr = fopen("crypto_project.txt", "r")) == NULL){ // the file you want to encrypt or decrypt
		printf("File failed to open.");
		exit(0);
	}
    
	for(i = 25; i >= 0; i--) { // cipher gets the alphabet letters from plain but in reverse order
	    cipher[j] = plain[i];
	    j++;
	}
	cipher[27] = '\0';
	
	printf("Do you want to encrypt or decrypt?\n[1]Encrypt\n[2]Decrypt\n");
	scanf("%d", &num);
	printf("============================\n");
	
	fflush(stdin);
	fgets(str, 255, fptr);
	    
	// input two prime numbers
	printf("\nEnter first prime number: ");
	scanf("%d", &p);
	printf("Enter second prime number: ");
	scanf("%d", &q);
		
	n = p * q; // n will become the modulo or remainder of the key
	totient = (p-1) * (q - 1); // gets the totient
	    
	switch (num) {
	    case 1:
	        fflush(stdin);
			fgets(str, 255, fptr);
			printf("\nShift value: ");
	        scanf("%d", &shift);
	        atbashResult = atbash(plain, cipher, str);
	        //printf("Atbash: %s\n", atbashResult);
	        shiftResult = shiftEncrypt(plain, atbashResult, shift);
	        //printf("Shift: %s\n", shiftResult);
	        encryptRSA(shiftResult, n, totient);
	        break;
	    case 2:
	        fflush(stdin);
	        fgets(str, 255, fptr);
	        printf("\nShift value: ");
	        scanf("%d", &shift);
	        rsaDecryptResult = decryptRSA(str, n, totient);
	        //printf("RSA: %s\n", rsaDecryptResult);
	        shiftResult = shiftDecrypt(plain, rsaDecryptResult, shift);
	        //printf("Shift: %s\n", shiftResult);
	        atbashResult = atbash(plain, cipher, shiftResult);
	        //printf("Atbash: %s\n", atbashResult);
	        decrypt(atbashResult);
	        break;
	    default:
	        printf("Invalid input");
	        break;
	}
	fclose(fptr);
    return 0;
}

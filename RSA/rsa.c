#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int alpha_to_num(char c){ // Function that converts letters to numbers
    int n = 1;
    static const char * const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *p = strchr(alphabet, toupper((unsigned char)c));

    if(p){
        n = p - alphabet;
    }
    return n+1;
}

void encrypt(char* msg, int n, int totient, int e){
	int i, j = 0, k = 0, c, ctr = 0;
	char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char result[255] = "";
	int msgLen = strlen(msg);
	int* arr = (int*)malloc(sizeof(int)*msgLen);
	char temp[msgLen];
	FILE *fptr;
	
	if((fptr = fopen("rsa_text.txt", "w")) == NULL){
		printf("File failed to open.");
		exit(0);
	}
	
	// converting letters to numbers
	for(i = 0; msg[i] != '\0'; i++){
		if(!isalpha(msg[i])){
			ctr++;
			continue;
		}
		arr[j] = alpha_to_num(msg[i]);
		j++;
	}
	int arr2[ctr];
	// copying the text from msg to temp except for the non-alphabet characters
	for(i = 0, j = 0; msg[i] != '\0'; i++){
		if(!isalpha(msg[i])){
			arr2[j] = i;
			temp[j] = msg[i];
			j++;
		}
//		temp[j] = msg[i];
//		j++;
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
		if(!isalpha(msg[i])){
			result[k] = msg[i];
			k++;
		}
		if(islower(msg[i])){
			result[k] = tolower(alphabets[c-1]);
		} else {
			result[k] = alphabets[c-1];
		}
		k++;
	}
	
	result[k] = '\0';
	printf("\nK: %d", k);
	printf("\nResult: %s", result);
	fprintf(fptr, "%s", result);
	fclose(fptr);
}

void decrypt(char* msg, int n, int totient, int e){
	int i, j = 0, d, ans, flag = 0, ctr = 0, c = 0, m = 0, k = 0;
	char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char result[255] = "";
	int msgLen = strlen(msg);
	int arr[msgLen];
	FILE *fptr;
	
	if((fptr = fopen("rsa_text.txt", "w")) == NULL){
		printf("File failed to open.");
		exit(0);
	}
	
	printf("\n============================\n");
	// printing possible values for the decryption key
	printf("Possible values for d: \n");
	for(i = 1; i < 1000 && flag != 1; i++){
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
	printf("\nEnter a number for (d)decryption key: ");
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
	
	// decrypting Meefaffhdeebm (Mccfaffhbccdm)
	for(i = 0; i < msgLen; i++){
		printf("A: %d ", arr[i]);
		m = pow(arr[i], d);
		m = m % n;
		printf("M: %d ", m);
		printf("\n");
		if(islower(msg[i])){
			result[k] = tolower(alphabets[m-1]);
		} else {
			result[k] = alphabets[m-1];
		}
		k++;
	}
	
	result[k] = '\0';
	fprintf(fptr, "%s", result);
	fclose(fptr);
}

int main(){
	int num, p, q, n, totient, e;
	char msg[255];
	FILE *fptr;
	
	if((fptr = fopen("rsa_text.txt", "r")) == NULL){ // the file you want to encrypt or decrypt
		printf("File failed to open.");
		exit(0);
	}
	
	printf("==============\n");
	printf("  RSA Cipher\n");
	printf("==============\n");
	printf("Do you want to encrypt or decrypt?\n[1]Encrypt\n[2]Decrypt\n");
	scanf("%d", &num);
	printf("============================\n");
	
	fflush(stdin);
	fgets(msg, 255, fptr);
	
	// input two prime numbers
	printf("\nEnter first prime number: ");
	scanf("%d", &p);
	printf("Enter second prime number: ");
	scanf("%d", &q);
	
	n = p * q; // n will become the modulo or remainder of the key
	totient = (p-1) * (q - 1); // gets the totient

	if(num == 1){
		printf("\n========== ENCRYPTION KEY ==========\n");
		printf("Encryption key should be, 1 < (e) < %d\n", totient);
		printf("Encryption key should be co-prime with %d and %d\n", n, totient);
		printf("Enter a number for (e)encryption key: ");
		scanf("%d", &e);
		encrypt(msg, n, totient, e);
	} else if(num == 2){
		printf("Enter the encryption key: ");
		scanf("%d", &e);
		decrypt(msg, n, totient, e);
	} else {
		printf("Input invalid!");
	}
	
	fclose(fptr);
	return 0;
}

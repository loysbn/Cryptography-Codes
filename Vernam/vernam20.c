#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

int solve(int a, int b);
void v_encrypt(char message[], char key[]);
void v_decrypt(char message[], char key[]);

// Vernam cipher
int main(){
    int i;
    char message[MAX], key[MAX],choice;
    FILE *fp;

    // Open a file
    fp = fopen("data.txt", "r+");
    // Check if file does not exist
    if(fp == NULL){
        printf("File does not exist, creating file 'data.txt'\n");
    	fp =fopen("data.txt","w");
        printf("Enter the plain text:");
        fflush(stdin);
	    gets(message);
        fprintf(fp,"%s",message);
        fclose(fp);
    }else{
		
    	if(fgets(message,MAX,fp) == NULL){ // Files is visible but has no content
	    	printf("File is empty please input text. \n");
	        printf("Enter the plain text:");
            fflush(stdin);
	        gets(message);
	        fprintf(fp,"%s",message);
	    }else{ // Files is visible but has content
	        for(i=0; i<MAX; i++){
	            fscanf(fp, "%c", &message[i]);
	        }
        }
    }	
	
    fclose(fp); // Close the file

    // printf("%d",strlen(message));
    puts(message);

    

    printf("Do you want to Encrypt or Decrypt? (E/D) : ");
    scanf("%c", &choice);
    // Switch case to encrypt or decrypt

    switch(choice){
        case 'E':
        case 'e':
            printf("Enter the key with %d letters:", strlen(message));
            fflush(stdin);
            gets(key);
            v_encrypt(message, key);
            break;
        case 'D':
        case 'd':
            printf("Enter the key with %d letters:", strlen(message));
            fflush(stdin);
            gets(key);
            v_decrypt(message, key);
            break;
        default:
            printf("Invalid choice");
            break;
    }


    return 0;
}
// solve XOR bitwise condition function
int solve(int a, int b){
    int c;
    c = a^b;

    return c;
}
// Vernam encryption
void v_encrypt(char message[], char key[]){  
    char final_encrypt[MAX],n_message[MAX];
    char alp[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int cipher[MAX],n_key[MAX],num_encrypt[MAX];
    int i,j,k=0, len,n_len, lenKey,ans;

    len = strlen(message);
    lenKey = strlen(key);

    for(i=0;i<len;i++){
        if(isspace(message[i])){
            i++;
        }
        n_message[k] = message[i];
        k++;
    }

    n_len = strlen(n_message);
   printf("n_len: %d", n_len);

    for(i=0;i<n_len;i++){
        for(j=0;j<26;j++){
            if(toupper(n_message[i]) == alp[j]){
                cipher[i] = j+1;
            }
        }
    }
    for(i=0;i<n_len;i++){
         for(j=0;j<26;j++){
            if(toupper(key[i]) == alp[j]){
                n_key[i] = j+1;
            }
        }
    }
    // numeric encrypt   
   for(i=0;i<n_len;i++){
        ans = solve(cipher[i],n_key[i]);
        if(ans %26 == 0){
            num_encrypt[i] = ans;
        }else{
            num_encrypt[i] = ans % 26;
        }
   }
//    for(i=0;i<n_len;i++){
//        printf("%d",num_encrypt[i]);
//        printf("\n");
//    }
   
    // convert num_encrypt to alphabet
    for(i=0;i<n_len;i++){
        for(j=0;j<26;j++){
            if(num_encrypt[i] == j+1){
                final_encrypt[i] = alp[j];
            }
        }
    }
    puts(final_encrypt);

}

// Vernam decryption
void v_decrypt(char message[], char key[]){
    char final_decrypt[MAX],n_message[MAX];
    char alp[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int cipher[MAX],n_key[MAX],num_decrypt[MAX];
    int i,j,k=0, len,n_len, lenKey,ans;

    len = strlen(message);
    lenKey = strlen(key);

    for(i=0;i<len;i++){
        if(isspace(message[i])){
            i++;
        }
        n_message[k] = message[i];
        k++;
    }

    n_len = strlen(n_message);
   
   
    for(i=0;i<n_len;i++){
        for(j=0;j<26;j++){
            if(toupper(n_message[i]) == alp[j]){
                cipher[i] = j+1;
            }
        }
    }
    for(i=0;i<n_len;i++){
         for(j=0;j<26;j++){
            if(toupper(key[i]) == alp[j]){
                n_key[i] = j+1;
            }
        }
    }
    // numeric encrypt   
   for(i=0;i<n_len;i++){
        ans = solve(cipher[i],n_key[i]);
        if(ans %26 == 0){
            num_decrypt[i] = ans;
        }else{
            num_decrypt[i] = ans % 26;
        }
   }
//    for(i=0;i<n_len;i++){
//        printf("%d",num_decrypt[i]);
//        printf("\n");
//    }
   
    // convert num_encrypt to alphabet
    for(i=0;i<n_len;i++){
        for(j=0;j<26;j++){
            if(num_decrypt[i] == j+1){
                final_decrypt[i] = alp[j];
            }
        }
    }
    puts(final_decrypt);
}


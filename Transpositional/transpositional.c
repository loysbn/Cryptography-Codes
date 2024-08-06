#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main(){
	
	int row, col, i, j, k = 0, x, temp = 1;
	char str[255];
	char key[100];
	char sortedKey[] = "", min, num = '1';
	char result[255] = "";
	
	printf("Enter a text to encrypt:\n");
	gets(str);
	fflush(stdin);
	printf("Enter keyword:\n");
	gets(key);
	
	col = strlen(key);
	row = strlen(str)/col;
	if(strlen(str) % col){
		row += 1;
	}
	char mArr[row][col];
	printf("\nKeyword:\n%s\n", key);
	printf("\n");
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			if(!isalpha(str[k])){
				mArr[i][j] = '_';
				k++;
			} else {
				mArr[i][j] = str[k];
				k++;
			}
			
		}
	}
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			printf("%c ", mArr[i][j]);
		}
		printf("\n");
	}
	printf("\nResult\n");
	for(i = 0; key[i] != '\0'; i++){
		min = i;
        for(j = i+1; key[j] != '\0'; j++){
            if(key[j] < key[min]){
                min = j;
            }
        }
		for(x = 0; x < row; x++){
			printf("%c ", mArr[x][min]);
		}
	}
//	printf("\nSorted Key: %s\n", key);
//	
//	for(i = 0; i < strlen(key); i++){
//		sortedKey[i] = num++;
//	}
//	sortedKey[i] = '\0';
//	printf("Sorted Key order: %s\n", sortedKey);
	return 0;
}

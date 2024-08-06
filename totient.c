#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
	double x = pow(13, 11);
	char str[100];
	char *ptr;
	char temp[100] = "";
	int i, j = 1, num;
	
	sprintf(str, "%f", x);
	
	for(i = 0; str[i] != '\0'; i++){
		
		if(str[i] == '.'){
			break;
		}
		temp[i] = str[i];
	}
	printf("String: %s\n", temp);
	num = strtol(str, &ptr, 30);
	printf("Int: %d", num);

    return 0;
}

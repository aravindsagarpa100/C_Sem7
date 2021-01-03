#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h> 

void hcipher(char str[], char key[]) 
{ 
	int keyMatrix[3][3], k = 0, i, j, x, messageVector[3][1], cipherMatrix[3][1]; 
	char CipherText[20]; 
	for (i = 0; i < 3; i++) 
	{ 
		for (j = 0; j < 3; j++) 
		{ 
			keyMatrix[i][j] = (key[k]) % 65; 
			k++; 
		} 
	}  

	for (i = 0; i < 3; i++) 
		messageVector[i][0] = (str[i]) % 65; 
	
	for (i = 0; i < 3; i++) 
	{ 
		for (j = 0; j < 1; j++) 
		{ 
			cipherMatrix[i][j] = 0; 
		
			for (x = 0; x < 3; x++) 
			{ 
				cipherMatrix[i][j] += 
					keyMatrix[i][x] * messageVector[x][j]; 
			} 
		
			cipherMatrix[i][j] = cipherMatrix[i][j] % 26; 
		} 
	}  
	for (i = 0; i < 3; i++) 
		CipherText[i] = cipherMatrix[i][0] + 65; 
	printf("Cipher text is %s\n", CipherText);
} 

void main() 
{ 
	char str[20], key[20]; 
	gets(key);
	printf("Key is %s\n",key); 
	gets(str);
	printf("Plain text is %s\n",str);  
	hcipher(str, key); 
} 


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h> 

void generateKeyTable(char key[], int ks, char keyT[5][5]) 
{ 
	int i, j, k, flag = 0, *dicty; 
	dicty = (int*)calloc(26, sizeof(int)); 
	for (i = 0; i < ks; i++) { 
		if (key[i] != 'j') 
			dicty[key[i] - 97] = 2; 
	} 

	dicty['j' - 97] = 1; 

	i = 0; 
	j = 0; 

	for (k = 0; k < ks; k++) { 
		if (dicty[key[k] - 97] == 2) { 
			dicty[key[k] - 97] -= 1; 
			keyT[i][j] = key[k]; 
			j++; 
			if (j == 5) { 
				i++; 
				j = 0; 
			} 
		} 
	} 

	for (k = 0; k < 26; k++) { 
		if (dicty[k] == 0) { 
			keyT[i][j] = (char)(k + 97); 
			j++; 
			if (j == 5) { 
				i++; 
				j = 0; 
			} 
		} 
	} 
} 

void search(char keyT[5][5], char a, char b, int arr[]) 
{ 
	int i, j; 

	if (a == 'j') 
		a = 'i'; 
	else if (b == 'j') 
		b = 'i'; 

	for (i = 0; i < 5; i++) { 

		for (j = 0; j < 5; j++) { 

			if (keyT[i][j] == a) { 
				arr[0] = i; 
				arr[1] = j; 
			} 
			else if (keyT[i][j] == b) { 
				arr[2] = i; 
				arr[3] = j; 
			} 
		} 
	} 
} 

int mod5(int a) 
{ 
	return (a % 5); 
} 

void encrypt(char str[], char keyT[5][5], int ps) 
{ 
	int i, a[4]; 

	for (i = 0; i < ps; i += 2) { 

		search(keyT, str[i], str[i + 1], a); 

		if (a[0] == a[2]) { 
			str[i] = keyT[a[0]][mod5(a[1] + 1)]; 
			str[i + 1] = keyT[a[0]][mod5(a[3] + 1)]; 
		} 
		else if (a[1] == a[3]) { 
			str[i] = keyT[mod5(a[0] + 1)][a[1]]; 
			str[i + 1] = keyT[mod5(a[2] + 1)][a[1]]; 
		} 
		else { 
			str[i] = keyT[a[0]][a[3]]; 
			str[i + 1] = keyT[a[2]][a[1]]; 
		} 
	} 
} 

void pcipher(char str[], char key[]) 
{ 
	char ps, ks, keyT[5][5]; 
	int i;
	ks = strlen(key); 
	for(i = 0;i < ks;i++)
		key[i] = tolower(key[i]); 
	ps = strlen(str); 
	for(i = 0;i < ps;i++)
		str[i] = tolower(str[i]); 
	if (ps % 2 != 0) { 
		str[ps] = 'z'; 
		ps++;
		str[ps] = '\0'; 
	}
	generateKeyTable(key, ks, keyT); 

	encrypt(str, keyT, ps); 
} 

void main() 
{ 
	char str[20], key[20]; 
	gets(key);
	printf("Key is %s\n",key); 
	gets(str);
	printf("Plain text is %s\n",str); 
	pcipher(str,key); 
	printf("Cipher text is %s\n",str);  
} 

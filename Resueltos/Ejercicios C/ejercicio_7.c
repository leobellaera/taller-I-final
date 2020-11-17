/*Escriba una función C que reciba 1 cadena (S) y 1 entero (N) y un caracter (C); y retorne
una nueva cadena cuyo contenido sea N veces la cadena S utilizando el caracter C como
separador*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* clone_string(char* S, int N, char C) {
	size_t len = (strlen(S) * N) + (N-1) + 1;  //(N-1) for separator characters; +1 for '\0'
	char* res = (char*)malloc(len);
	res[len - 1] = '\0';

	int i = 0;
	while (i < N) {
		int idx = i * (strlen(S) + 1);
		memcpy(&res[idx], S, strlen(S));

		if (i != N-1) {					//if i == N - 1 we dont want to put the separator character at the end of res
			res[idx + strlen(S)] = C;
		}

		i++;
	}

	return res;
		
}

int main() {
	char a[] = "leo";
	char c = 'N';

	char* result = clone_string(a, 3, c);
	printf("%s\n", result);
	return 0;
}
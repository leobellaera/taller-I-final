/* Escriba un programa C que tome 2 cadenas por línea de comandos: A y B; e imprima la
cadena A después de haber duplicado todas las ocurrencias de B.. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUF_SIZE 1024

void duplicate(char* a, char* b, char* printable) {

	size_t len_a = strlen(a);
	size_t len_b = strlen(b);

	int i = 0;
	int buff_idx = 0;

	while (i <= len_a - len_b) {
		bool found = strncmp(&a[i], b, len_b) == 0;

		if (found) {
			memcpy(&printable[buff_idx], &a[i], len_b);
			buff_idx += len_b;
			memcpy(&printable[buff_idx], &a[i], len_b);
			buff_idx += len_b;

			i += len_b;

		} else {
			
			printable[buff_idx] = a[i];
			buff_idx++; 
			i++;
		}
	}

	//me falta agregar el peadzo que no llego a completar en el while!
	for (int j = len_a - len_b + 1; j < len_a; j++) {
		printable[buff_idx] = a[j];
		buff_idx++;
	}

}

int main() {
	char a[] = "hola che como estas";
	char b[] = "che como";

	char printable[BUF_SIZE];
	memset(printable, 0, BUF_SIZE);

	duplicate(a,b, printable);
	printf("%s\n", printable);

	return 0;

}
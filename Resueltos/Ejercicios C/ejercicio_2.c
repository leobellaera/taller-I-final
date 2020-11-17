/*Implemente la función void ValorHex(char *hex, int *ent) que interprete la cadena hex (de
símbolos hexadecimales) y guarde el valor correspondiente en el entero indicado por ent.*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h> //atoi declaration

//Para compilar: gcc -std=c99 -ggdb -o ejercicio_2 ejercicio_2.c -lm   **(-lm: link math library)**


int getHexNumber(char hex) {

	if (hex >= '0' && hex <= '9') {
		char aux[] = "X";
		aux[0] = hex;
		return atoi(aux);

	} else if (hex == 'A' || hex == 'a') {
		return 10;
	} else if (hex == 'B' || hex == 'b') {
		return 11;
	} else if (hex == 'C' || hex == 'c') {
		return 12;
	} else if (hex == 'D' || hex == 'd') {
		return 13;
	} else if (hex == 'E' || hex == 'e') {
		return 14;
	} else {
		return 15;
	}
}

void ValorHex(char* hex, int* ent) {
	int exponent = 0;
	int sum = 0;
	for (int i = strlen(hex) - 1; i >= 0; i--) {
		sum += getHexNumber(hex[i]) * pow(16, exponent);
		exponent++;
	}
	*ent = sum;
}

int main() {
	int ent;
	char hexa[] = "ff13";
	ValorHex(hexa, &ent);
	printf("%d\n", ent);
	return 0;
}
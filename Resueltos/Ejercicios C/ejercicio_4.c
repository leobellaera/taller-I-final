/*Implemente la función void String_a_Int(char* bin, int* ent) que interprete la cadena bin (de 32 1s/0s) 
y guarde el valor correspondiente en el entero indicado por ent.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void String_a_Int(char* bin, int* ent) {
	int resul = 0;
	int exp = 0;
	for (int i = 31; i >= 0; i--) {
		
		if (bin[i] == '1') {
			resul += pow(2, exp);
		}

		exp++;
	}
	*ent = resul;
}

int main() {
	char string[] = "00000000000000000000000000010111";
	int resul;
	String_a_Int(string, &resul);

	printf("%d\n", resul);
	return 0;
}

/*Escriba una funcion de C llamada strncat_new que reciba tres parametros: dos punteros a caracter constante (S1 y S2)
y un entero sin signo (L). La funcion debe concatenar S1 con S2 y retornar una nueva cadena de caracteres considerando L
como tamaño maximo para cualquiera de los elementos (S1, S2 y la nueva cadena). La funcion debe detectar condiciones de error
respecto de la longitud y retornar NULL en cualquier caso.*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* strncat_new(const char* S1, const char* S2, unsigned int L) {
	size_t len_S1 = strlen(S1);
	size_t len_S2 = strlen(S2);
	size_t len_concat = len_S1 + len_S2;

	if (len_S1 > L || len_S2 > L || len_concat > L) {
		return NULL;
	}

	char* res = (char*)malloc(len_concat + 1);
	res[len_concat] = '\0';

	memcpy(res, S1, len_S1);
	memcpy(&res[len_S1], S2, len_S2);

	return res;

}


int main() {
	const char* a = "hola ";
	const char* b = "leo";

	char* result = strncat_new(a, b, 8);
	if (result) {
		printf("%s\n", result);
	} else {
		printf("LA FUNCION LANZO ERROR\n");
	}
	

	return 0;
}
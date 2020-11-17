/*Defina una función C llamada trim_all que reciba una lista de strings L y el tamaño de dicha lista
C. La función debe retornar una nueva lista de strings, que posea copias de los valores recibidos pero
sin carácteres de espacio (" ") en el inicio de cada string. Indique claramente el tipo elegido para las
variables L y C.*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char** trim_all(char** l, size_t c) {

	char** res = (char**)malloc(sizeof(char*) * c);

	for (int i = 0; i < c; i++) {

		int pos = 0;
		char* actual_string = l[i];

		while (actual_string[pos] == ' ') {
			pos++;
		}

		int len = strlen(actual_string) - pos;
		char* trimmed_string = (char*)malloc(len + 1);
		trimmed_string[len] = '\0';

		memcpy(trimmed_string, &actual_string[pos], len);
		res[i] = trimmed_string;
	}

	return res;

}


int main() {
	char* l[4] = {"  leo", " leo", "leito", "   marto"};
	char** resul = trim_all(l, 4);
	for (int i = 0; i < 4; i++) {
		printf("%s\n", resul[i]);
	}
	return 0;
}
/* Escriba una función ISO C llamada Replicar que reciba 1 cadena (S), dos índices (I1 e I2) y
una cantidad (Q). La función debe retornar una copia de S salvo los caracteres que se
encuentran entre los índices I1 e I2 que serán duplicados Q veces.
Ej. replicar(“Hola”, 1, 2, 3) retorna “Hololola”. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* Replicar(const char* string, size_t idx_a, size_t idx_b, size_t q) {
	if (q < 1 || idx_b < idx_a || idx_a >= strlen(string) || idx_b >= strlen(string)) {
		return NULL;
	}

	size_t original_len = strlen(string);
	size_t substr_len = idx_b - idx_a + 1;
	size_t result_len = original_len + substr_len*(q-1);

	char* res_string = (char*)malloc(sizeof(char) * result_len + 1); //+1 for '\0'
	memset(res_string, '\0', result_len + 1);

	size_t idx_result = 0;
	int i = 0;

	for (i = 0; i < original_len; i++) {
		if (i < idx_a || i > idx_b) {
			res_string[idx_result] = string[i];
			idx_result++;
		} else { //No importa cual sea i, solo se entrara una vez al while puesto que q queda en 0 luego de la primera vez de entrar al else
			while (q > 0) {
				for (int j = i; j <= idx_b; j++) {
					res_string[idx_result] = string[j];
					idx_result++;
				}
				q--;
			}
		}
	}

	return res_string;

}

int main() {

	const char* s = "Hola"; //esperado: "Holololola"
    char* new_s = Replicar(s, 1, 2, 4);
    printf("%s\n", new_s);
    free(new_s);

    return 0;

}
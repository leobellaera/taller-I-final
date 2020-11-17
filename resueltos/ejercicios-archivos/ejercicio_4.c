/*Escribir un programa ISO C que procese el archivo “valuesword.dat” sobre sí mismo,
eliminando los words (2 bytes) múltiplos de 16.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LEN_WORD 2

bool read_word(FILE* file, char* buffer, long int* read_seek) {
	fseek(file, *read_seek, SEEK_SET);

	if (!fgets(buffer, LEN_WORD + 1, file)) {
		return false;
	}

	*read_seek = ftell(file);

	return true;
}

void write_word(FILE* file, char* word, long int* write_seek) {
	fseek(file, *write_seek, SEEK_SET);
	fputs(word, file);
	*write_seek = ftell(file);
}

int main() {
	long int read_seek = 0;
	long int write_seek = 0;
	FILE* f = fopen("valuesword.dat", "r+");
	if (!f) {
		return 1;
	}

	char buffer[3];
	int bytes = 0;

	while (read_word(f, buffer, &read_seek)) {
		int value = atoi(buffer);
		if ((value % 16) != 0) {
			write_word(f, buffer, &write_seek);
			bytes += 2;
		}
	}

	fclose(f);
	truncate("valuesword.dat", bytes);

}
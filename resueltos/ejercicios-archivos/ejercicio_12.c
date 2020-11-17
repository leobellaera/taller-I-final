/* Escribir un programa C que reciba por argumento el nombre de un archivo, y lo procese sobre sí mismo
(sin crear archivos intermedios). El procesamiento consiste en eliminar todos los espacios duplicados
dejando solamente 1 espacio en su lugar */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool read_file(char* buffer, long int* seek, FILE* f) {
	fseek(f, *seek, SEEK_SET);
	bool res = (fread(buffer, 1, 1, f) == 1);
	*seek += 1;
	return res;
}

void write_file(char c, long int* seek, FILE* f) {
	fseek(f, *seek, SEEK_SET);
	fwrite(&c, 1, 1, f);
	*seek += 1;
}

int main(int argc, char* argv[]) {
	FILE* f = fopen(argv[1], "r+");
	if (!f) {
		return 1;
	}

	long int read_seek = 0;
	long int write_seek = 0;

	char actual;
	char previous = 'a';
	size_t bytes_written = 0;

	while (read_file(&actual, &read_seek, f)) {

		if ((actual == ' ' && previous != ' ') || actual != ' ') {
			bytes_written += 1;
			write_file(actual, &write_seek, f);
		}

		previous = actual;

	}

	truncate(argv[1], bytes_written);
	fclose(f);
	return 0;
}
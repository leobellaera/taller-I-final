/*Escribir un programa ISO C que reciba por argumento el nombre de un archivo de texto y lo
procese sobre sí mismo (sin crear archivos intermedios ni subiendo todo su contenido a
memoria). El procesamiento consiste en eliminar las líneas de 1 sola palabra.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 1024

char read_char(FILE* file, long int* read_seek) {
	fseek(file, *read_seek, SEEK_SET);
	int c = fgetc(file);
	*read_seek = ftell(file);
	return (char)c;
}

void write_file(FILE* file, char* line, long int* write_seek) {
	fseek(file, *write_seek, SEEK_SET);
	fputs(line, file);
	*write_seek = ftell(file);
}

bool must_be_supressed(char* line) {
	for (int i = 0; i < strlen(line); i++) {
		if (line[i] == ' ') {
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[]) {

	FILE* file = fopen(argv[1], "r+");
	if (!file) {
		return 1;
	}

	long int read_seek = 0;
	long int write_seek = 0;

	char line[MAX_LINE];
	memset(line, '\0', MAX_LINE);
	size_t line_idx = 0;

	char c = '\0';
	size_t bytes_written = 0;

	while ((c = read_char(file, &read_seek)) != EOF) {
		
		if (c == '\n') {

			if (!must_be_supressed(line)) {
				line[line_idx] = c;
				write_file(file, line, &write_seek);
				bytes_written += strlen(line);
			}

			memset(line, '\0', MAX_LINE);
			line_idx = 0;

		} else {
			line[line_idx] = c;
			line_idx++;
		}
	}

	truncate(argv[1], bytes_written);
	fclose(file);

	return 0;

}
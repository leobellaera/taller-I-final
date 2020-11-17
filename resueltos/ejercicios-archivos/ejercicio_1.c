/*Escribir un programa ISO C que procese el archivo de texto cuyo nombre es recibido como
parámetro. El procesamiento consiste en leer oraciones y suprimir aquellas que tengan
más de 3 palabras. Asuma que el archivo no puede cargarse en memoria, pero una oración
sí puede.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 1024

/*The  fseek()  function  sets the file position indicator for the stream
       pointed to by stream.  The new position, measured in bytes, is obtained
       by  adding offset bytes to the position specified by whence.  If whence
       is set to SEEK_SET, SEEK_CUR, or SEEK_END, the offset  is  relative  to
       the  start of the file, the current position indicator, or end-of-file,
       respectively.*/

//Compilar con la siguiente línea: gcc -std=gnu99 -ggdb -o ejercicio_1 ejercicio_1.c

void read_character(FILE* file, long int* read_seek, char* buffer) {
	fseek(file, *read_seek, SEEK_SET);
    *buffer = (char)fgetc(file);
    *read_seek = ftell(file);
}

void write_line(FILE* file, const char* line, long int* write_seek) {
    fseek(file, *write_seek, SEEK_SET);
    fputs(line, file);
    *write_seek = ftell(file);
}

bool line_must_be_supressed(const char* line) {
	int line_spaces = 0;
	for (int i = 0; i < strlen(line); i++) {
		if (line[i] == ' ') {
			line_spaces++;
		}
	}
	return (line_spaces > 3);
}

int main(int argc, char* argv[]) {
	FILE* file = fopen(argv[1], "r+"); //r+ para lectura y escritura, empieza al ppio.
	long int read_seek = 0;
	long int write_seek = 0;
	int line_idx = 0;
	long int bytes_written = 0;

	char character = '\0';
	char line[MAX_LINE];
	memset(line, '\0', MAX_LINE); //llenar el buffer con el caracter '\0' o 0 es lo mismo.

	while (true) {
		read_character(file, &read_seek, &character);
		if (character == EOF) {
			if (!line_must_be_supressed(line)) {
				write_line(file, line, &write_seek);
				bytes_written += strlen(line);
			}
			break;
		}

		if (character != '.') {
			line[line_idx] = character;
			line_idx++;
		} else {
			line[line_idx] = character;
			if (!line_must_be_supressed(line)) {
				write_line(file, line, &write_seek);
				bytes_written += strlen(line);
			}
			memset(line, '\0', MAX_LINE);
			line_idx = 0;
		}
	}

	truncate(argv[1], bytes_written);
	fclose(file);

	return 0;
}
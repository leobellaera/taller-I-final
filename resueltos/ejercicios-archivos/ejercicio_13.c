/*Escribir un programa C que reciba por argumento el nombre de un archivo, y lo procese
sobre sí mismo (sin crear archivos intermedios). El procesamiento consiste en eliminar todos las
ocurrencias de la cadena “ABCD”.
ej.: la cadena “01 23 AABCDD 45” debe ser reemplazada por “01 23 AD 45”*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool read_char(char* c, long int* seek, FILE* f) {
	fseek(f, *seek, SEEK_SET);
	*seek += 1;
	return (fread(c, sizeof(char), 1, f) == 1);
}

void write_char(char* c, long int* seek, FILE* f) {
	fseek(f, *seek, SEEK_SET);
	*seek += 1;
	fwrite(c, sizeof(char), 1, f);
}

int main(int argc, char* argv[]) {
	FILE* f = fopen(argv[1], "r+");
	if (!f) {
		return 1;
	}

	long int read_seek = 0;
	long int write_seek = 0;
	char c;

	char replacement = 'C';
	int stage = 0;
	char buffer[4];
	size_t bytes_written = 0;

	while (read_char(&c, &read_seek, f)) {
		if ((c == 'A' && stage == 0) || (c == 'B' && stage == 1) || (c == 'C' && stage == 2)) {
			buffer[stage] = c;
			stage++;
		} else if (c == 'D' && stage == 3) {
			bytes_written++;
			write_char(&replacement, &write_seek, f);
			stage = 0;
		} else {  //Si nos llega un caracter que rompe la secuencia ABCD, escribimos el contenido buffer y luego
			//tenemos 2 casos: si el caracter que llego es una 'A' o si es otro.


			//escribimos el buffer
			for (int i = 0; i < stage; i++) {
				bytes_written++;
				write_char(&buffer[i], &write_seek, f);
			}

			stage = 0;

			if (c == 'A') {

				buffer[stage] = c;
				stage++;

			} else {

				write_char(&c, &write_seek, f);
				bytes_written++;

			}
		}
	}

	//Si tenemos en el buffer ABC y llegamos al eof nunca escribimos ABC en el archivo.
	for (int i = 0; i < stage; i++) {
		bytes_written++;
		write_char(&buffer[i], &write_seek, f);
	}

	truncate(argv[1], bytes_written);
	fclose(f);
	return 0;

}

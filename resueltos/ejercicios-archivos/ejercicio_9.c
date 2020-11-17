/*9) Escriba una función ISO C que permita procesar un archivo texto que contenga frases (1
por línea) sobre sí mismo, sin generar archivos intermedios ni cargar el archivo completo a
memoria. El procesamiento consiste en eliminar las palabras de más de 3 letras de cada línea.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_CHARACTERS 30

bool read_file(char* buff, long int* read_seek, FILE* f) {
	fseek(f, *read_seek, SEEK_SET);
	size_t read = fread(buff, sizeof(char), 1, f);
	*read_seek += 1;
	return (read == 1);
}

void write_file(char* buff, long int* write_seek, FILE* f) {
	fseek(f, *write_seek, SEEK_SET);
	fwrite(buff, sizeof(char), strlen(buff), f);
	*write_seek += strlen(buff);
}

int main(int argc, char* argv[]) {
	FILE* f = fopen(argv[1], "r+");

	long int read_seek = 0;
	long int write_seek = 0;

	char word[MAX_WORD_CHARACTERS];
	memset(word, '\0', MAX_WORD_CHARACTERS);
	int word_idx = 0;

	int bytes_written = 0;
	int letters_counter = 0;

	char buff;

	while (1) {
		if (!read_file(&buff, &read_seek, f)) {
			break;
		}

		if (buff != ' ' && buff != '\n') {
			letters_counter++;
			word[word_idx] = buff;
			word_idx++;
			
		} else if (buff == ' ' || buff == '\n') {

			if (letters_counter <= 3) {
				word[word_idx] = buff;
				write_file(word, &write_seek, f);
				bytes_written += strlen(word);
			}
			memset(word, '\0', MAX_WORD_CHARACTERS);
			letters_counter = 0;
			word_idx = 0;
		}

	}

	truncate(argv[1], bytes_written);
	fclose(f);

	return 0;

}
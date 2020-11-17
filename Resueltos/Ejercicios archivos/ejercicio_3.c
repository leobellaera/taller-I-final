/* Escriba una función ISO C que permita procesar un archivo texto sobre sí mismo, que
contenga una palabra por línea. El procesamiento consiste en ordenar las palabras (líneas)
alfabéticamente considerando que el archivo no entra en memoria. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD 256

//https://www.youtube.com/watch?v=EQMGabLO_M0 es unbubblesort retocado -> corto ejecucion si no encontre ningun desorden

bool read_word(FILE* file, char* word_buffer, long int* seek) {
	fseek(file, *seek, SEEK_SET);
	char* ret = fgets(word_buffer, MAX_WORD, file); //fgets devuelve buffer o NULL 
	//en caso de error o alcanzar eof sin haber guardado al menos un caracter en buffer.
	*seek = ftell(file);
	return (ret != NULL);
}

void write_word(FILE* file, char* word, long int* seek) {
	fseek(file, *seek, SEEK_SET);
	fputs(word, file);
	*seek = ftell(file);
}

size_t min_characters(char* word_a, char* word_b) {
	size_t len_a = strlen(word_a);
	size_t len_b = strlen(word_b);
	if (len_a > len_b) {
		return len_b;
	} else {
		return len_a;
	}
}

int main(int argc, char* argv[]) {
	FILE* file = fopen(argv[1], "r+");
	if (!file) {
		return 1;
	}

	bool sorted = false;
	bool eof = false;

	char word_a[MAX_WORD];
	char word_b[MAX_WORD];

	long int read_seek = 0;
	long int write_seek = 0;

	while (!sorted) {

		sorted = true;
		eof = false;

		read_seek = 0; //https:www.youtube.com/watch?v=EQMGabLO_M0
		write_seek = 0;

		while (!eof) {

			if (!read_word(file, word_a, &read_seek) || !read_word(file, word_b, &read_seek)) { //si llegue al eof ya no habrá que switchear
				eof = true;
				continue;
			}

			if (strncmp(word_a, word_b, min_characters(word_a, word_b)) > 0) {
				sorted = false;
				//switch
				write_seek = read_seek - strlen(word_b) - strlen(word_a);
				write_word(file, word_b, &write_seek);
				write_word(file, word_a, &write_seek);
			}

			//En esta seccion retrocedemos el cursor de lectura hasta el inicio de la nueva palabra.

			if (strncmp(word_a, word_b, min_characters(word_a, word_b)) > 0) {
				read_seek -= strlen(word_a);
			} else {
				read_seek -= strlen(word_b);
			}	
			
		}
	}

	fclose(file);
	return 0 ;

}

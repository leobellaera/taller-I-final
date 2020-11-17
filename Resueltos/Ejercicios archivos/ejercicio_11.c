/*Escribir un programa C que procese el archivo “numeros.txt” sobre sí mismo (sin crear
archivos intermedios y sin subir el archivo a memoria). El procesamiento consiste en leer
grupos de 5 dígitos y reemplazarlos por 4 caracteres hexadecimales que representen el mismo
número leído pero en Hexadecimal.*/

#include <stdint.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool read_number(char* numb, long int* seek, FILE* f) {
	fseek(f, *seek, SEEK_SET);
	size_t membs_readen = fread(numb, sizeof(char), 5, f);
	*seek += 5;
	return (membs_readen == 5);
}

void write_number(char* numb, long int* seek, FILE* f) {
	fseek(f, *seek, SEEK_SET);
	int value = atoi(numb);

	char write_buff[5];
	memset(write_buff, '\0', 5);

	snprintf(write_buff, 5, "%x", value); //max to write in write_buff is 5 - 1 = 4 bytes.

	char zero = '0';

	for (int i = 0; i < 4 - strlen(write_buff); i++) {
		fwrite(&zero, sizeof(char), 1, f);
	}
	
	fwrite(write_buff, sizeof(char), strlen(write_buff), f);

	*seek += 4;
}


int main() {

	FILE* f = fopen("numeros2.txt", "r+");
	if (!f) {
		return 1;
	}

	char numb[6];
	numb[5] = '\0';

	long int read_seek = 0;
	long int write_seek = 0;
	size_t bytes_written = 0;

	while (read_number(numb, &read_seek, f)) {
		write_number(numb, &write_seek, f);
		bytes_written += 4;
	}

	truncate("numeros2.txt", bytes_written);
	fclose(f);
	return 0;
}

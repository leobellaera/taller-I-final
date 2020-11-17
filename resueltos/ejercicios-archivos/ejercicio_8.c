/*Escribir un programa C que procese el archivo “numeros.txt” sobre sí mismo (sin crear
archivos intermedios y sin subir el archivo a memoria). El procesamiento consiste en leer
grupos de 4 caracteres hexadecimales y reemplazarlos por los correspondientes dígitos
decimales (que representen el mismo número leído pero en decimal).*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//Para compilar: gcc -std=c99 -ggdb -o ejercicio_8 ejercicio_8.c -lm

int getHexNumber(char hex) {

	if (hex >= '0' && hex <= '9') {
		char aux[] = "X";
		aux[0] = hex;
		return atoi(aux);

	} else if (hex == 'A' || hex == 'a') {
		return 10;
	} else if (hex == 'B' || hex == 'b') {
		return 11;
	} else if (hex == 'C' || hex == 'c') {
		return 12;
	} else if (hex == 'D' || hex == 'd') {
		return 13;
	} else if (hex == 'E' || hex == 'e') {
		return 14;
	} else {
		return 15;
	}
}

void ValorHex(char* hex, int* ent) {
	int exponent = 0;
	int sum = 0;
	for (int i = strlen(hex) - 1; i >= 0; i--) {
		sum += getHexNumber(hex[i]) * pow(16, exponent);
		exponent++;
	}
	*ent = sum;
}

int get_number_len(int num) {
	int counter = 1;
	while(num / 10 > 0) {
        num = num / 10;
        counter++;
    }
    return counter;
}

void read_in_reverse(FILE* f, long int* read_seek, char* buffer) {
	fseek(f, *read_seek, SEEK_SET);
	fread(buffer, sizeof(char), 4, f);
	*read_seek -= 4;
}

void write_in_reverse(FILE* f, long int* write_seek, int numb) {
	fseek(f, *write_seek, SEEK_SET);

	char zero = '0';
	int number_len = get_number_len(numb);
	for (int i = 0; i <  5 - number_len ; i++) {
		fwrite(&zero, sizeof(char), 1, f);
	}

	char buff[6];
	memset(buff, '\0', 6);
	snprintf(buff, 6, "%d", numb);
	
	fwrite(buff, sizeof(char), number_len, f);

	*write_seek -= 5;
}

int main() {
	FILE* f = fopen("numeros.txt", "r+");

	if (!f) {
		return 1;
	}

	char buffer[5];
	buffer[4] = '\0';

	size_t len = 0;
	size_t final_len = 0;

	while (fread(buffer, sizeof(char), 4, f) == 4) {
		len += 4;
		final_len += 5;
	}

	long int read_seek = len - 4;
	long int write_seek = final_len - 5;

	int bytes_written = 0;
	int number = 0;
	while (bytes_written < final_len) {
		read_in_reverse(f, &read_seek, buffer);
		ValorHex(buffer, &number);
		write_in_reverse(f, &write_seek, number);
		bytes_written += 5;
	}

	fclose(f);
	return 0;
	
}
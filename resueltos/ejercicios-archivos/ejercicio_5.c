/*Escriba un programa C que reciba por argumento el nombre de un archivo de numeros binarios de 16 bits y lo procese sobre si mismo.
El procesamiento consiste en repetir los numeros que sean "multiplos de 5 + 1" (6, 11, 16...)*/

#include <stdio.h>
#include<stdint.h>
#include <stdbool.h>

void gen_file(const char* filename) {
    FILE* file = fopen(filename, "wb");
    int16_t numbers[10] = {1,5,6,9,11,14,16,12,21,13};
    fwrite(numbers, sizeof(int16_t), 10, file);
    fclose(file);
}

bool read_file(FILE* file, long int* read_seek, int16_t* numb_buff) {
	fseek(file, *read_seek, SEEK_SET);
	if (fread(numb_buff, sizeof(int16_t), 1, file) != 1) {
		return false;
	}
	*read_seek = ftell(file);
	return true;
}

void write_file_inverted(FILE* file, long int* write_seek, int16_t numb) {
	fseek(file, *write_seek, SEEK_SET);
	fwrite(&numb, sizeof(int16_t), 1, file);
	*write_seek -= sizeof(int16_t);
}

void read_file_inverted(FILE* file, long int* read_seek, int16_t* numb_buff) {
	fseek(file, *read_seek, SEEK_SET);
	fread(numb_buff, sizeof(int16_t), 1, file);
	*read_seek -= sizeof(int16_t);
}

void read_answer(FILE* file) {
    long int seek = 0; int16_t number;
    while (read_file(file, &seek, &number)) {
        printf("%i ", number);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {

	gen_file(argv[1]);

	FILE* f = fopen(argv[1], "r+b");
	if (!f) {
		return 1;
	}

	long int read_seek = 0;
	long int write_seek = 0;

	size_t file_len = 0; //in bytes
	size_t new_file_len = 0; //in bytes

	int16_t numb = 0;

	while (read_file(f, &read_seek ,&numb)) {
		file_len += sizeof(int16_t); //number size is 2 bytes
		if ((numb - 1) % 5 == 0) new_file_len += 2*sizeof(int16_t);
		else new_file_len += sizeof(int16_t);
	}

	read_seek = file_len - sizeof(int16_t);
	write_seek = new_file_len - sizeof(int16_t);

	size_t bytes_written = 0;

	while (bytes_written < new_file_len) {
		read_file_inverted(f, &read_seek, &numb);
		if ((numb - 1) % 5 == 0) {
			write_file_inverted(f, &write_seek, numb);
			write_file_inverted(f, &write_seek, numb);
			bytes_written += 2 * sizeof(int16_t);
		} else {
			write_file_inverted(f, &write_seek, numb);
			bytes_written += sizeof(int16_t);
		}

	}

	read_answer(f);
	fclose(f);
	return 0;

}
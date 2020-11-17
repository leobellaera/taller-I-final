/*Escribir un programa ISO C que procese el archivo “nros_2bytes_bigendian.dat” sobre sí
mismo, eliminando los número múltiplos de 7.*/

#include <stdint.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void gen_file(const char* filename) {
    FILE* file = fopen(filename, "wb");
    int16_t numbers[6] = {2, 1, 7, 8, 14, 10};
    for (int i = 0; i < 6; i++) {
    	numbers[i] = htons(numbers[i]);
    	fwrite(&numbers[i], sizeof(int16_t), 1, file);
    }
    fclose(file);
}

void read_answer(FILE* file) {
	fseek(file, 0, SEEK_SET);
    int16_t number;
    while (fread(&number, sizeof(int16_t), 1, file) == 1) {
    	number = ntohs(number);
        printf("%d ", number);
    }
    printf("\n");
}

bool read_file(FILE* f, int16_t* num_buff, long int* read_seek) {
	fseek(f, *read_seek, SEEK_SET);
	size_t membs_readen =  fread(num_buff, sizeof(int16_t), 1, f);
	*read_seek += sizeof(int16_t);
	*num_buff = ntohs(*num_buff);
	return (membs_readen == 1);
}

void write_file(FILE* f, int16_t num, long int* write_seek) {
	fseek(f, *write_seek, SEEK_SET);
	int16_t num_big_endian = htons(num);
	fwrite(&num_big_endian, sizeof(int16_t), 1, f);
	*write_seek += sizeof(int16_t);
}

int main() {

	gen_file("nros.dat"); //to debug


	FILE* f = fopen("nros.dat", "r+b");
	if (!f) {
		return 1;
	}

	size_t bytes_written = 0;
	long int read_seek = 0;
	long int write_seek = 0;

	int16_t num;

	while(read_file(f, &num, &read_seek)) {
		if ((num % 7) != 0) {
			write_file(f, num, &write_seek);
			bytes_written += 2;
		}
	}

	truncate("nros.dat", bytes_written);
	read_answer(f);
	fclose(f); //to debug

	return 0;
}
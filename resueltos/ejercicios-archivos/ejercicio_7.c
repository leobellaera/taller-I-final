/*Escribir un programa que procese un archivo binario de enteros sin signo sobre si mismo.
El procesamiento consiste en leer pares de enteros de 1 byte cada uno y reemplazarlos
por 3 enteros (el archivo se agranda): su suma, su resta y el OR logico entre ambos.*/


#include <stdint.h>
#include <stdio.h>

void gen_file(const char* filename) {
    FILE* file = fopen(filename, "wb");
    uint8_t numbers[4] = {4, 3, 2, 1};
    for (int i = 0; i < 4; i++) {
    	fwrite(&numbers[i], sizeof(uint8_t), 1, file);
    }
    fclose(file);
}

void read_in_reverse(FILE* file, long int* read_seek, uint8_t* a, uint8_t* b) {
	fseek(file, *read_seek, SEEK_SET);
	fread(a, sizeof(uint8_t), 1, file);
	fread(b, sizeof(uint8_t), 1, file);
	*read_seek -= 2 * sizeof(uint8_t);
}

void write_in_reverse(FILE* file, long int* write_seek, uint8_t numb) {
	fseek(file, *write_seek, SEEK_SET);
	fwrite(&numb, sizeof(uint8_t), 1, file);
	*write_seek -=  sizeof(uint8_t);
}

void read_answer(FILE* file) {
	fseek(file, 0, SEEK_SET);
    uint8_t number;
    while (fread(&number, sizeof(uint8_t), 1, file) == 1) {
        printf("%d ", number);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {

	gen_file(argv[1]);

	FILE* f = fopen(argv[1], "r+b");
	if (!f) {
		return 1;
	}

	uint8_t a;
	uint8_t b;

	//primer pasada; calculamos largo del archivo y largo del archivo final.

	size_t len = 0;
	size_t final_len = 0;

	while (1) {
		if (fread(&a, sizeof(uint8_t), 1, f) == 1 && fread(&a, sizeof(uint8_t), 1, f) == 1) {
			len += 2;
			final_len += 3;
		} else {
			break;
		}
	}

	//segunda pasada; leemos y escribimos en reversa.
	long int read_seek = len - 2;
	long int write_seek = final_len - 1;

	size_t bytes_written = 0;
	while (bytes_written < final_len) {
		read_in_reverse(f, &read_seek, &a, &b);

		uint8_t sum = a + b;
		uint8_t sub = a - b;
		uint8_t or = a || b;

		write_in_reverse(f, &write_seek, or);
		write_in_reverse(f, &write_seek, sub);
		write_in_reverse(f, &write_seek, sum);
		

		bytes_written += 3;
	}

	read_answer(f); //to debugging
	fclose(f);

	return 0;
}
/*Escriba una rutina que procese un archivo binario indicado por parametro sobre si mismo sumarizando los listados de numeros que posee almacenado.
La sumarizacion consiste en recorrer los valores enteros de 32 bits con signo grabados en formato big-endian y acumular sus valores hasta encontrar
el valor 0xffffffff que se considera un separador entre listados.
Todos los valores enteros detectados son reemplazados por su sumatoria (en el mismo formato) manteniendo luego el elemento separador. 
Considere archivos bien formados.*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <inttypes.h>
#include <arpa/inet.h>

void gen_file(const char* filename) {
    FILE* file = fopen(filename, "wb");
    uint32_t numbers[11] = {1,1,1,1,1, 0xffffffff, 2,2,2,2, 0xffffffff};
    for (int i = 0; i < 11; i++) {
    	uint32_t numb = htonl(numbers[i]);
    	fwrite(&numb, sizeof(uint32_t), 1, file);
    }
    
    fclose(file);
}

bool read_file(FILE* file, long int* read_seek, uint32_t* numb_buff) {
	fseek(file, *read_seek, SEEK_SET);
	if (fread(numb_buff, sizeof(uint32_t), 1, file) != 1) {
		return false;
	}

	*numb_buff = ntohl(*numb_buff);
	*read_seek = ftell(file);
	return true;
}

void write_file(FILE* file, long int* write_seek, uint32_t numb) {
	fseek(file, *write_seek, SEEK_SET);
	uint32_t number_be = htonl(numb);
	fwrite(&numb, sizeof(uint32_t), 1, file);
	*write_seek = ftell(file);
}

void read_answer(FILE* file) {
    long int seek = 0; uint32_t number;
    while (read_file(file, &seek, &number)) {
    	number = ntohl(number);
        printf("%" PRIu32 "\n", number);
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

	uint32_t actual_number = 0;
	uint32_t sum = 0;

	size_t bytes_written = 0;

	while (read_file(f, &read_seek, &actual_number)) {
		if (actual_number != 0xffffffff) {
			sum += actual_number;
		} else {
			write_file(f, &write_seek, sum);
			write_file(f, &write_seek, 0xffffffff);
			bytes_written += 2 * sizeof(uint32_t);
			sum = 0;
		}
	}

	truncate(argv[1], bytes_written);

	read_answer(f); //to debugging

	fclose(f);
	return 0;

}

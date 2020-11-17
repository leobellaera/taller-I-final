/*Defina una rutina en C que se conecte a la IP 8.8.8.8, al puerto 8192 y reciba un archivo binario.
El archivo recibido debe ser descargado a un archivo llamado recibido.bin cuidando el uso de recursos de memoria.
El archivo finaliza al detectar conexion cerrada.*/

#define _POSIX_C_SOURCE 200112L

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main() {
	FILE* f = fopen("recibido.bin", "wb");
	if (!f) {
		return 1;
	}

	struct addrinfo hints;
	struct addrinfo *res, *ptr;
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;

	int skt = -1;

	getaddrinfo("localhost", "7777", &hints, &res);

	for (ptr = res; ptr != NULL; ptr->ai_next) {
		skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (skt != -1 && connect(skt, ptr->ai_addr, ptr->ai_addrlen) == 0) break;
	}

	freeaddrinfo(res);

	char buffer;

	while (1) {
		int s = recv(skt, &buffer, 1, MSG_NOSIGNAL);
		if (s == 0 || s == -1) {
			break;
		}

		fwrite(&buffer, sizeof(char), 1, f);

	}

	fclose(f);
	return 0;

}
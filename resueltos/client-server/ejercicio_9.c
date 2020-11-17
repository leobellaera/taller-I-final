/*Implemente un servidor que escuche en el puerto 5000. El servidor debe aceptar conexiones
(de 1 a la vez) escribiendo el contenido recibido en un archivo (001.txt, 002.txt, etc.) y sin
responder nada. Cada conexión debe ser cerrada por el servidor al recibir la palabra “FIN”.
Luego de una conexión sin contenido (se recibe sólo la palabra “FIN”), el servidor debe
cerrarse ordenadamente.*/

#define _POSIX_C_SOURCE 200112L

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BACKLOG 10

bool attend_client(int peerskt, int counter) {
	char file_name[8];
	snprintf(file_name, 8, "00%d.txt", counter);

	FILE* f = fopen(file_name, "w");

	char buffer[2];
	char c;
	int stage = 0;
	bool continue_attending = false;

	while (1) {
		recv(peerskt, &c, 1, MSG_NOSIGNAL);

		if (c == 'F' && stage == 0) {
			buffer[stage] = 'F';
			stage = 1;
		} else if (c == 'I' && stage == 1) {
			buffer[stage] = 'I';
			stage = 2;
		} else if (c == 'N' && stage == 2) {
			break;
		} else {

			fwrite(buffer, sizeof(char), stage, f); //escribimos el contenido del buffer en el archivo (si stage == 0 no se escribe nada)
			stage = 0;
			continue_attending = true;

			if (c == 'F') {  //si nos llega FI y luego F entramos al else pero nunca agregamos la F al buffer.
				buffer[0] = 'F';
				stage = 1;
			} else {
				fwrite(&c, sizeof(char), 1, f); //escribimos el ultimo caracter que llego
			}

			continue_attending = true;
		}

	}

	shutdown(peerskt, SHUT_RDWR);
	close(peerskt);
	fclose(f);
	return continue_attending;
}

int main() {
	struct addrinfo hints, *res, *ptr;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, "5000", &hints, &res);

	int skt = -1;
	for (ptr = res; ptr != NULL; ptr->ai_next) {
		skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (skt != -1) {
			break;
		}
	}

	bind(skt, ptr->ai_addr, ptr->ai_addrlen);
	listen(skt, BACKLOG);

	freeaddrinfo(res);

	int counter = 0;

	while (1) {
		int peerskt = accept(skt, NULL, NULL);
		if (!attend_client(peerskt, counter)) {
			break;
		}
		counter++;
	}

	shutdown(skt, SHUT_RDWR);
	close(skt);
	return 0;
}
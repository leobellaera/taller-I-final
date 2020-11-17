/*Escriba un programa que reciba paquetes de 10 bytes por el puerto TCP 815 y los imprima por pantalla.
Al recibir el byte 0xff debe cerrarse ordenadamente. No considere errores.*/

#define _POSIX_C_SOURCE 200112L

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main() {
	struct addrinfo hints, *ptr, *res;
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, "7777", &hints, &res);

	int skt = -1;
	for (ptr = res; ptr != NULL; ptr->ai_next) {
		skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (skt != -1) break;
	}

	bind(skt, ptr->ai_addr, ptr->ai_addrlen);
	listen(skt, 1); //solo 1 puede ponerse en la cola de espera, el proximo es rechazado

	freeaddrinfo(res);

	int8_t numb;

	int peerskt = accept(skt, NULL, NULL);

	int counter = 0;

	while (1) {
		recv(peerskt, &numb, 1, MSG_NOSIGNAL);
		if (numb == 0xff) {
			break;
		}

		printf("%d ", numb);
		counter++;

		if (counter == 10) {
			printf("\n");
			counter = 0;
		}
	}

	shutdown(peerskt, SHUT_RDWR);
	shutdown(skt, SHUT_RDWR);
	close(peerskt);
	close(skt);

	return 0;
}
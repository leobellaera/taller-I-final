/*Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa debe
aceptar una unica conexión e imprimir en stdout todo lo recibido. Al recibir el texto ‘FIN’ debe
finalizar el programa sin imprimir dicho texto.*/

#define _POSIX_C_SOURCE 200112L

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	struct addrinfo hints, *res, *ptr;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, argv[1], &hints, &res);

	int skt = -1;
	for (ptr = res; ptr != NULL; ptr->ai_next) {
		skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (skt != -1) {
			break;
		}
	}

	bind(skt, ptr->ai_addr, ptr->ai_addrlen);
	listen(skt, 1);
	freeaddrinfo(res);

	int peerskt = accept(skt, NULL, NULL);


	char buffer[4];
	memset(buffer, '\0', 4);

	char character;
	int stage = 0;

	while (1) {
		recv(peerskt, &character, 1, MSG_NOSIGNAL);

		if (character == 'F' && stage == 0) {

			buffer[stage] = character;
			stage++;

		} else if (character == 'I' && stage == 1) {

			buffer[stage] = character;
			stage++;

		} else if (character == 'N' && stage == 2) {

			break;

		} else {

			for (int i = 0; i < stage; i++) {
				printf("%c", buffer[i]);
			}

			memset(buffer, '\0', 4);
			printf("%c", character);
			stage = 0;

		}
	}

	shutdown(skt, SHUT_RDWR);
	shutdown(peerskt, SHUT_RDWR);
	close(skt);
	close(peerskt);

}


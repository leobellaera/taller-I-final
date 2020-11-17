/*Escriba un programa (desde la inicialización hasta la liberación de los recursos) que reciba
paquetes de texto delimitados por corchetes angulares (“<...>”) y los imprima completos por
pantalla. Al recibir un paquete vacío (“<>”) debe cerrarse ordenadamente. No considere
errores.*/

#define _POSIX_C_SOURCE 200112L
#define MAX_PACKAGE 1024

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include <stdbool.h>

int main(int argc, char* argv[]) {
	struct addrinfo hints;
	struct addrinfo* ptr;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	getaddrinfo(NULL, argv[1], &hints, &ptr);

	int skt = -1;
	for (; ptr != NULL; ptr->ai_next) {
		skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (skt != -1) {
			break;
		}
	}


	bind(skt, ptr->ai_addr, ptr->ai_addrlen);
	listen(skt, 1);

	int peerskt = accept(skt, NULL, NULL);

	char buffer[MAX_PACKAGE];
	memset(buffer, '\0', MAX_PACKAGE);

	char character;
	int buffer_pos = 0;

	while (true) {
		recv(peerskt, &character, 1, 0);

		//netcat
		if (character == '\n') {
			continue;
		}

		if (character == '<' && buffer_pos == 0) {
			continue;
		} else if (character == '>') {
			if (buffer_pos == 0) {
				break;
			}
			printf("%s\n", buffer);
			memset(buffer, '\0', MAX_PACKAGE);
			buffer_pos = 0;
		} else {
			buffer[buffer_pos] = character;
			buffer_pos++;
		}
	}

	shutdown(peerskt, SHUT_RDWR);
	shutdown(skt, SHUT_RDWR);
	close(skt);
	close(peerskt);
	freeaddrinfo(ptr);
	return 0;

}
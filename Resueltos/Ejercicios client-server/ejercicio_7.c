/*Escriba un programa (desde la inicialización hasta la liberación de los recursos) que reciba
paquetes de la forma [nnn+nn+....+nnnn] (numeros separados por +, encerrados entre
corchetes) e imprima el resultado de la suma de cada paquete por pantalla. Al recibir un
paquete vacío (“[]”) debe cerrarse ordenadamente. No considere errores.*/

#define _POSIX_C_SOURCE 200112L

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUMB_DIGITS 10

int main() {
	struct addrinfo hints, *res, *ptr;
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, "7777", &hints, &res);


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

	char buffer;

	char number_buffer[MAX_NUMB_DIGITS];
	memset(number_buffer, '\0', MAX_NUMB_DIGITS);
	int numb_index = 0;

	int package_counter = 0;
	int sum = 0;

	while (1) {
		recv(peerskt, &buffer, 1, MSG_NOSIGNAL);

		if (buffer == '[' || buffer == '\n') { //el '\n' lo ponemos para probar con netcat
			continue;
		}

		if (buffer == ']') {

			if (package_counter == 0) {
				break;

			} else {

				sum += atoi(number_buffer);
				printf("%d\n", sum);

				sum = 0;
				memset(number_buffer, '\0', MAX_NUMB_DIGITS);
				package_counter = 0;
				numb_index = 0;
			}

		} else if (buffer == '+') {

			sum += atoi(number_buffer);
			memset(number_buffer, '\0', MAX_NUMB_DIGITS);
			numb_index = 0;
			

		} else {
			package_counter++; //llego al menos un numero en el paquete
			number_buffer[numb_index] = buffer;
			numb_index++;
		}
	}

	shutdown(skt, SHUT_RDWR);
	shutdown(peerskt, SHUT_RDWR);
	close(skt);
	close(peerskt);

	return 0;
}
/*Defina un rutina en C que se conecte a la IP 10.9.8.7, puerto 7777 y procese
la informacion recibida. El proceso consiste en recibir textos numericos
utilizando '\n' como caracter delimitador.
Para cada entero recibido se debe enviar su valor convertido en 32 bits
big-endian en modo binario sin delimitadores. El proceso finaliza al recibir
el valor 0.*/

/*Defina  una  rutina  en  C  que  se  conecte  a  la  IP  10.9.8.7,
puerto  7777  y  procese  la  informacion recibida.  El proceso consiste
en recibir textos numericos utilizando el como \n caracter delimitador.
Para cada entero recibido se debe enviar su valor convertido en 32bits
big-endian en modo binario sin delimitadores. El proceso finaliza al recibir el valor 0 */


#define _POSIX_C_SOURCE 200112L

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 1024

void send_number(char* number_as_str, int socket) {
	int32_t number = atoi(number_as_str);
	number = htonl(number);
	send(socket, &number, 4, MSG_NOSIGNAL);
}

int main() {
	struct addrinfo hints;
	struct addrinfo *res;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;

	struct addrinfo *ptr;

	int skt = -1;

	getaddrinfo("localhost", "7777", &hints, &res);
	for (ptr = res; ptr != NULL; ptr->ai_next) {
		skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (skt != -1 && connect(skt, ptr->ai_addr, ptr->ai_addrlen) == 0) break;
	}

	freeaddrinfo(res);

	
	char buffer[BUF_SIZE];
	memset(buffer, '\0', BUF_SIZE);
	int buffer_pos = 0;

	char character;
	//loop
	while (1) {
		recv(skt, &character, 1, 0);
		if (character != '\n') {
			buffer[buffer_pos] = character;
			buffer_pos++;
		} else {
			if (atoi(buffer) == 0) {
				break;
			} else {
				send_number(buffer, skt);
				memset(buffer, '\0', BUF_SIZE);
				buffer_pos = 0;
			}
		}
	}

	shutdown(skt, SHUT_RDWR);
	close(skt);

	return 0;

}
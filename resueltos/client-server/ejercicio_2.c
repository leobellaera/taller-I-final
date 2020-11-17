/*Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa
debe aceptar una única conexión e imprimir en stdout la sumatoria de los enteros recibidos
en cada paquete. Un paquete está definido como una sucesión de números recibidos como
texto, en decimal, separados por comas y terminado con un signo igual (ej: “27,12,32=”). Al
recibir el texto ‘FIN’ debe finalizar el programa ordenadamente liberando los recursos.*/

#define _POSIX_C_SOURCE 200112L

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NUMB_DIGITS 20

int main(int argc, char* argv[]) {
	struct addrinfo hints;
	struct addrinfo* ptr;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int skt = -1;
    getaddrinfo(NULL, argv[1], &hints, &ptr);
    for (; ptr != NULL; ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt != -1)
            break;
    }

    bind(skt, ptr->ai_addr, ptr->ai_addrlen);
    listen(skt, 1);

    int peer_skt = accept(skt, NULL, NULL);

    char received = '\0';
    char buffer[MAX_NUMB_DIGITS];
    memset(buffer, '\0', MAX_NUMB_DIGITS);

    int sum = 0;
    int buffer_idx = 0;

    while (true) {

    	recv(peer_skt, &received, 1, 0);

    	/*netcat*/
    	if (received == '\n') {
    		continue;
    	}

    	if (received == 'F') {
    		recv(peer_skt, &received, 1, 0); //receive 'I'
    		recv(peer_skt, &received, 1, 0); //receive 'N'
    		break;
    	} else if (received == '=' || received == ',') {
    		sum += atoi(buffer);
    		memset(buffer, '\0', MAX_NUMB_DIGITS);
    		buffer_idx = 0;	
    	} else {
    		buffer[buffer_idx] = received;
    		buffer_idx++;
    	}

    	if (received == '=') {
    		printf("%d\n", sum);
    		sum = 0;
    	}

    }

    shutdown(skt, SHUT_RDWR);
    shutdown(peer_skt, SHUT_RDWR);
    close(skt);
    close(peer_skt);
    freeaddrinfo(ptr);

    return 0;

}
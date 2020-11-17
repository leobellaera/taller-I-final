/*Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa debe
aceptar una unica conexión y recibir paquetes (cada paquete inicia con ‘[‘ y finaliza con ‘]’). Para
cada paquete recibido debe imprimir el checksum (sumatoria de bytes del paquete) del mismo,
excepto que el paquete esté vacío (‘[]’), en cuyo caso debe finalizar.*/

#define _POSIX_C_SOURCE 200112L

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include <stdbool.h>

int main(int argc, char* argv[]) {
	char* port = argv[1];

	struct addrinfo hints;
    struct addrinfo *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int skt = -1;
    getaddrinfo(NULL, port, &hints, &ptr);
    for (; ptr != NULL; ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt != -1) {
        	break;
        }
    }

    bind(skt, ptr->ai_addr, ptr->ai_addrlen);
    listen(skt, 1);

    int peer_skt = accept(skt, NULL, NULL);

    int checksum = 0;
    bool continue_recv = true;
    char actual_value = '\0';

    while (continue_recv) {
    	recv(peer_skt, &actual_value, 1, 0);

        //Las proximas 3 lineas son para usarlo con netcat
        if (actual_value == '\n') {  
            continue;
        }

    	if (actual_value == '[' && checksum == 0) {
    		continue;
    	} else if (actual_value == ']') {
    		if (checksum == 0) {
    			continue_recv = false;
    		} else {
    			printf("%d\n", checksum);
    			checksum = 0;
			}
    	} else {
    		checksum += 1;
    	}
        if (actual_value == '\n') {
            printf("mal\n");
        }
    }

  	shutdown(peer_skt, SHUT_RDWR);
	shutdown(skt, SHUT_RDWR);
	close(skt);
	close(peer_skt);
	freeaddrinfo(ptr);
	return 0;

}
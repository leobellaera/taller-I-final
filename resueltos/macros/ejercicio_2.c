/*Defina una macro llamada LOG que reciba una cadena como parámetro y la imprima
utilizando printf. La macro debe ejecutar el comando printf solamente cuando detecta que la
macro LOG_ENABLED se encuentra definida.*/

#include <stdio.h>

#define LOG_ENABLED //si dejamos comentada esta linea no imprimira nada, en caso contrario sí.

#ifdef LOG_ENABLED

#define LOG(x) {\
	printf("%s\n", (x));\
}\

#else 
#define LOG(x) {}

#endif

int main() {
	LOG("Hola");
	return 0;
}
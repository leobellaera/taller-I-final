/*Escriba una macro llamada ASSERT. La macro debe recibir como parámetro una condición de código
a validar y un mensaje de error a imprimir por la salida estándar en caso que la condición no se cumpla.
Al imprimir el mensaje, se debe incluir el nombre del archivo C. Ejemplo de uso: ASSERT(div > 0,
“Imposible dividir por 0”)*/

#include <stdio.h>

#define ASSERT(condition, message) {\
	if (!(condition)) {\
		printf("%s\n", (message));\
		printf("Error en archivo %s\n", __FILE__);\
	}\
}\

#define CUBE(A) ((A)*(A)*(A))

int main() {
	ASSERT(1 == 0, "1 no es igual a 0");
	printf("%d\n", CUBE(3));
	return 0;
}

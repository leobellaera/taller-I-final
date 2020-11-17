#include <stdio.h>

int cuadrado(int a) {
	return a*a;
}

int main() {
	int (*f)(int);

	f = cuadrado;
	printf("%d\n", f(3));

	return 0;
}
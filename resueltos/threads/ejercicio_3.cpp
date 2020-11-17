/*Dado un vector de enteros en C++, escriba un procedimiento que retorne el promedio de
todos sus números en punto flotante. Debido a la longitud del vector, se pide que el
procesamiento sea en paralelo con 2 hilos de ejecución ¿Es necesario realizar un control de
concurrencia entre los 2 hilos? ¿Por qué?*/

#include <vector>
#include <thread>
#include <iostream>

/*Este ejercicio es tramposo; no usen ningun contorl de concurrencia... simplemente recorran con cada hilo una parte del vector y devuelvan la sumatoria.
esto es mas eficiente y veloz que estar usando mutex y conditions variables*/

void suma_vector(int inicio, int fin, std::vector<float>& numeros, float& resul) {
	for (int i = inicio; i < fin; i++) {
		resul += numeros[i];
	}
}

float promedio(std::vector<float>& numeros) {
	float resul_a = 0;
	float resul_b = 0;
	std::thread t1(suma_vector, 0, numeros.size()/2, std::ref(numeros), std::ref(resul_a));
	std::thread t2(suma_vector, numeros.size()/2, numeros.size(), std::ref(numeros), std::ref(resul_b));
	t1.join();
	t2.join();

	return (resul_a + resul_b) / float(numeros.size());
}

int main() {
	std::vector<float> numeros = {1.0, 1.0, 1.0, 2.0, 2.0, 2.0, 2.0};
	float prom = promedio(numeros);
	std::cout << prom << std::endl;
	return 0;
}

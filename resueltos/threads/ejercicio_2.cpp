/*Dado un vector de enteros en C++, escriba un procedimiento que reciba el vector, lo recorra
y genere un nuevo vector con las potencias de 2 de cada uno de los items del vector original.
Para optimizar los recursos de computación, se pide que se utilicen al menos 2 hilos para
realizar el procesamiento. ¿Es necesario realizar un control de concurrencia entre dichos hilos?*/

#include <mutex>
#include <cmath>
#include <thread>
#include <vector>
#include <iostream>

/*Ojo con este ejercicio! Es medio tramposo... no te están pidiendo que el vector resultante quede en el mismo orden que el original
por lo cual tranquilamente nosotros podriamos procesar con un hilo de la mitad para adelante y con el otro de la mitad para atras
entonces ahi aceleramos bastante la cosa porque no es necesario sincronizar nada; por como lo resolvimos (suponiendo que se debe
conservar un orden, si o si es necesario el lock, pues usamos el cursor idx como recurso compartido entre los threads*/

class MonitorTransform {
private:
	int idx;
	std::vector<int>& vector;
	std::mutex m;
public:

	MonitorTransform(std::vector<int>& vector) :
		vector(vector), idx(0) {}

	bool transform() {
		std::unique_lock<std::mutex> lock(m);

		if (idx == vector.size()) {
			return false;
		}

		vector[idx] = pow(2, vector[idx]);
		idx++;
		return true;

	}

};

void transformVector(MonitorTransform& monitor) {
	while(monitor.transform()) {
		continue;
	}
}

int main() {
	std::vector<int> arr = {1, 2, 3, 4, 5};
	MonitorTransform monitor(arr);

	std::thread t1(transformVector, std::ref(monitor));
	std::thread t2(transformVector, std::ref(monitor));

	t1.join();
	t2.join();

	//imprimimos el estado final del array
	for (int i = 0; i < arr.size(); i++)  {
		std::cout 
		<< arr[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
/*
Escriba un programa que imprima por salida estándar los números entre 1 y 100, en orden ascendente.
Se pide que los números sean contabilizados por una variable global única y que los pares sean escritos
por un hilo mientras que los impares por otro. Contemple la correcta sincronización entre hilos y la
liberación de los recursos utilizados.*/

/* 

Wait causes the current thread to block until the condition variable is notified or a spurious wakeup occurs,
optionally looping until some predicate is satisfied.

Atomically unlocks lock, blocks the current executing thread, and adds it to the list of threads waiting on *this.
The thread will be unblocked when notify_all() or notify_one() is executed. It may also be unblocked spuriously.
When unblocked, regardless of the reason, lock is reacquired and wait exits. If this function exits via exception, 
lock is also reacquired.

*/

//Compilar con: g++ -std=c++11 -ggdb -o ejercicio_1 ejercicio_1.cpp -pthread

// https://sergworks.wordpress.com/2010/08/28/understanding-threads-atomic-operations-and-memory-ordering/

#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

class MonitorContador {

private:

	std::mutex m;
	int& contador;
	int max;
	std::condition_variable cv_par, cv_impar;

public:

	MonitorContador(int& numeroInicial, int max) : contador(numeroInicial), max(max) {}

	bool imprimirImpar() {
		std::unique_lock<std::mutex> lock(m);
		while ((contador % 2) == 0)  {
			cv_impar.wait(lock); //cede el lock y bloquea el hilo que ejecuta esto hasta que sea notificado
			//para evitar spuriously "wakeups" se pone el "while (!es_impar)" porque a veces se notifican sin que
			//ningun otro hilo notifique a esta condition variable.
		}

		if (contador > max) {
			contador++;
			cv_par.notify_all();
			return false;
		}

		std::cout << contador << std::endl;
		contador++;
		cv_par.notify_all();
		return true;
	}

	bool imprimirPar() {
		std::unique_lock<std::mutex> lock(m);
		while ((contador % 2) != 0) {
			cv_par.wait(lock);
		}

		if (contador > max) {
			contador++;
			cv_impar.notify_all();
			return false; 
		}

		std::cout << contador << std::endl;
		contador++;
		cv_impar.notify_all();
		return true;
	}
};

/* Cuando se imprime el 100, el hilo q imprime impares esta en wait, se incrementa el contador a 101 y se notifica al hilo q imprime impares;
ahora el hilo que imprime impares despierta, no entra en el while->wait se da cuenta que se paso del maximo entonces incrementa el contador
a 102, notifica al hilo que imprime pares y retorna false por lo que este hilo ya no se ejecutará mas; despierta el hilo que imprime pares,
no entra en el while->wait y se da cuenta que ya se pasó del maximo por lo que retorna false y ambos hilos se joinean correctamente.*/


int x = 1;

int main() {
	MonitorContador contador(x, 100);
	std::thread thread_pares([&]() {
		while (contador.imprimirPar()) {
			continue;
		}
	});
	std::thread thread_impares([&]() {
		while (contador.imprimirImpar()) {
			continue;
		}
	});

	thread_pares.join();
	thread_impares.join();

	return 0;
}


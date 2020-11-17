/*Escriba una clase template llamada Sumador que reciba por constructor un vector de elementos genéri-
cos. La clase Sumador debe incluir un metodo llamado sumar que acumule los valores del tipo recibido
y retorne un nuevo objeto del tipo genérico. ¿Qué restricciones se le piden al tipo genérico en la
definición de Sumador?*/

#include <vector>
#include <iostream>

template <class T>
class Sumador {
private:
	std::vector<T> elements;
public:
	Sumador(std::vector<T> elements) :
		elements(elements) {}
	T sumar() {
		
		T acum;
		int i = 0;

		for (T& elem: elements) {
			if (i == 0) {
				acum = elem;
			} else {
				acum += elem;
			}
			i++;
		}

		return acum;
	}
};

int main() {
	std::vector<int> elements = {1,1,1,1};
	Sumador<int> sumador(elements);
	std::cout << sumador.sumar() << std::endl;
	return 0;
}
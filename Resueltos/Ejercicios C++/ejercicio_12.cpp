/*Defina un operador global == que toma un vector STL de tipo genérico T y un arreglo de
elementos T. El operador debe retornar un bool indicando si las colecciones son iguales, es
decir si todos los elementos T coinciden en ambas colecciones.*/

#include <iostream>
#include <vector>
#include <array>

template<class T, size_t N>
bool std::operator==(const std::vector<T>& v1, const std::array<T, N>& v2) {
	if (v1.size() != v2.size()) {
		return false;
	} 

	for (int i = 0; i < v1.size(); i++) {
		if (v1[i] != v2[i]) {
			return false;
		}
	}

	return true;
}

int main() {
	std::vector<int> a = {1, 2, 3, 4};
	std::array<int, 4> b = {1, 2, 3, 4};

	if (a == b) {
		std::cout << "SON IGUALES" << std::endl;
	}

	return 0;
}
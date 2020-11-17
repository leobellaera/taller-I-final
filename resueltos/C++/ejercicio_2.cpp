/*Implemente una función C++ denominada Intersección que reciba dos listas de elementos y devuelva
una nueva lista con los elementos que se encuentran en ambas listas std::list<T> Interseccion(std::list <T> a, std::list<T> b)*/

//Compilado con g++ -std=c++11 your_file.cpp -o your_program

#include <list>
#include <iostream> 

template <class T>
std::list<T> Interseccion(std::list<T>& a, std::list<T>& b) {
	std::list<T> result;
	for (T& elem_a: a) {
		for (T& elem_b : b) {
			if (elem_a == elem_b) {
				result.push_back(elem_a);
			}
		}
	}
	return std::move(result);
}

int main() {
	std::list<int> list_a = {1,2,4,5};
	std::list<int> list_b = {1,4,6,8};

	std::list<int> intersection = Interseccion(list_a, list_b);
	for (int& elem: intersection) {
		std::cout << elem << std::endl;
	}
}
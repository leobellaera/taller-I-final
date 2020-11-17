/*Implemente una función C++ denominada DobleSegunda que reciba dos listas de elementos
y devuelva una nueva lista duplicando los elementos de la primera si están en la segunda:
std::list<T> DobleSegunda(std::list<T> a,std::list<T> b);*/

#include <list>
#include <iostream>

template <class T>
std::list<T> DobleSegunda(std::list<T> a, std::list<T> b) {
	std::list<T> res;
	for (T& elem_a: a) {
		bool found = false;
		for (T& elem_b : b) {
			if (elem_a == elem_b) {
				res.push_back(elem_a);
				res.push_back(elem_a);
				found = true;
			}
		}

		if (!found) {
			res.push_back(elem_a);
		}

	}

	return res;

}

int main() {

	std::list<int> a = {1,4,2,3};
	std::list<int> b = {1,2};

	std::list<int> res = DobleSegunda(a, b);

	for (int& elem: res) {
		std::cout << elem << " ";
	}

	std::cout << std::endl;

	return 0;
}
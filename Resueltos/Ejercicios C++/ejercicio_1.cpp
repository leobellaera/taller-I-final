/*Implemente una función C++ denominada Suprimir que reciba dos listas de elementos y devuelva una
nueva lista con los elementos de la primera que no están en la segunda*/

//Compilado con g++ -std=c++11 your_file.cpp -o your_program

#include <list>
#include <iostream> 

template<class T>
std::list<T> Suprimir(std::list<T> list_a, std::list<T> list_b) {
	bool elem_is_in_other_list = false;
	std::list<T> result;
	for (T& elem_a: list_a) {
		for (T& elem_b: list_b) {
			if (elem_a == elem_b) {
				elem_is_in_other_list = true;
			}
		}
		if (!elem_is_in_other_list) {
			result.push_back(elem_a);
		}

		elem_is_in_other_list = false;
	} 

	return result;

}

int main() {
	std::list<int> l1{1,2,3,4,6,7,8,8,2,4};
    std::list<int> l2{3,4,5};

    std::list<int> l = Suprimir<int>(l1, l2);
    for (auto& elem : l)
        std::cout << elem << std::endl;

    return 0;
}
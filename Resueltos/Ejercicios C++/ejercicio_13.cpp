/*Defina una clase template llamada Concatenador que posea un método llamado agregar que
recibe un elemento que será almacenado internamente y en orden. Dada una instancia llamada
concatenador, se debe permitir la impresión de todos los elementos agregados mediante:
std::cerr << concatenador << std::endl;*/

#include <vector>
#include <iostream>

template <class T> 
class Concatenador {
private:
	std::vector<T> elements;
public:
	void add(T element) {
		elements.push_back(element);
	}

	std::vector<T> getElements() const {
		return elements;
	}

	friend std::ostream& operator<<(std::ostream& out, const Concatenador& concatenador) {
		std::vector<T> elements = concatenador.getElements();
		for (int i = 0; i < elements.size(); i++) {
			out << elements[i] << " ";
		}
		return out ;
	}

};

int main() {
	Concatenador<int> c;
	c.add(1);
	c.add(2);
	c.add(3);
	std::cerr << c << std::endl;
	return 0;
}
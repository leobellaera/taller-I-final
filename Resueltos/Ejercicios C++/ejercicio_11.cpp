/*Declare la clase ‘Pagina’ capaz de almacenar una acumulación de líneas de texto (strings) en
cierto orden. Incluya las operaciones de agregación y eliminación de líneas.
La clase debe poseer los operadores usuales de copia, asignación, salida a flujo (<<),
comparación (==), agregación (+), eliminación (-). Implemente este último operador.*/

#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <algorithm>

class Pagina {

private:

	std::vector<std::string> lines;

public:

	Pagina() {}

	Pagina(const Pagina& other) {
		this->lines = other.lines;
	}

	Pagina& operator=(const Pagina& other) {

		if (this != &other) {
			this->lines = other.lines;
		}

		return *this;
	}

	void addLine(std::string line) {
		lines.push_back(line);
	}

	bool operator==(const Pagina& other) const {
		if (this->lines.size() != other.lines.size()) {
			return false;
		}

		for (int i = 0; i < this->lines.size(); i++) {
			if (this->lines[i] != other.lines[i]) {
				return false;
			}
		}
		return true;
	}

	std::vector<std::string> getLines() const {
		return this->lines;
	}

	friend std::ostream& operator<<(std::ostream& out, const Pagina& pagina) {
		for (int i = 0; i < pagina.getLines().size(); i++) {
			out << pagina.getLines()[i] << " ";
		}

		out << std::endl;

		return out;
	}

	Pagina operator-(std::string line) {
		Pagina pag;
		for (int i = 0; i < this->lines.size(); i++) {
			if (this->lines[i] != line) {
				pag.addLine(lines[i]);
			}
		}
		return pag;
	}

};

int main() {
	Pagina pag_a;

	std::string a = "hola";
	std::string b = "chau";
	std::string c = "leo";
	pag_a.addLine(a);
	pag_a.addLine(b);
	pag_a.addLine(c);

	std::cout << pag_a;

	std::cout << "________________________" << std::endl;

	Pagina pag_b = pag_a - a;
	std::cout << pag_b;

	return 0;
}
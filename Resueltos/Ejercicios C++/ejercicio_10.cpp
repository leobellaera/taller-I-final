/*Declare la clase TELEFONO para encapsular una cadena numérica correspondiente a un
teléfono. Incluya al menos: Constructor(area, numero), Constructor move y Constructor de
Copia; Operador <<, ==, =, long y >>. Implemente el operador >>.*/

#include <string>
#include <iostream>
#include <istream>
#include <ostream>

class Telefono {
private:
	std::string area;
	std::string numero;
public:

	Telefono(std::string area, std::string numero) :
		area(area), numero(numero) {}

	Telefono(const Telefono& other) {
		this->area = other.area;
		this->numero = other.numero;
	}

	Telefono(Telefono&& other) {
		this->area = other.area;
		other.area = "";

		this->numero = other.numero;
		other.numero = "";
	}

	std::string getArea() const {
		return area;
	}

	std::string getNumero() const {
		return numero;
	}

	void setComponents(std::string area, std::string numero) {
		this->area = area;
		this->numero = numero;
	}

	Telefono& operator=(const Telefono& other) {
		if (this != &other) {
			this->area = other.area;
			this->numero = other.numero;
		}
		return *this;
	}

	bool operator==(const Telefono& other) const {
		return ((this->area == other.area) && (this->numero == other.numero));
	}

	friend std::ostream& operator<<(std::ostream& out, const Telefono& telefono) {
		out << "Area: " << telefono.getArea() << ", Numero: " << telefono.getNumero();
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Telefono& tel) {
		std::string area;
		std::string numero;
		in >> area >> numero;
		tel.setComponents(area, numero);
		return in;
	}


};

int main() {

	std::string numero_a = "42003702";
	std::string numero_b = "42503451";

	std::string area_a = "0800";
	std::string area_b = "0801";

	Telefono a(numero_a, area_a);
	Telefono b(numero_b, area_b);

	if (a == b){
		std::cout << "SON IGUALES!" << std::endl;
	} else {
		std::cout << "SON DISTINTOS!" << std::endl;
	}

	std::cin >> a;
	std::cout << a << std::endl;

	a = b;
	std::cout << a << std::endl;


	return 0;
}
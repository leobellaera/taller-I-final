/*La clase Oracion utiliza un char *a para almacenar un string terminado en \0. Escriba la declaracion de esta clase no olvidando:
constructor por default, constructor por copia, operadores +, -, =, >> y <<.
Implemente el operador = y el operador -. Este ultimo debe eliminar de la primer cadena todas las ocurrencias de la segunda.*/

#include <ostream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

class Oracion {
private:
	char* string;
public:
	Oracion(const char* str) {

		size_t len = strlen(str);

		this->string = new char[len + 1];
		string[len] = '\0';
		memcpy(string, str, len);
	}

	Oracion(const Oracion& other) {
		size_t len = strlen(other.string);

		this->string = new char[len + 1];
		this->string[len] = '\0';
		memcpy(this->string, other.string, len);
	}

	Oracion& operator=(const Oracion& other) {
		if (this != &other) {
			delete [] this->string;

			size_t len = strlen(other.string);
			this->string = new char[len + 1];
			this->string[len] = '\0';
			memcpy(this->string, other.string, len);
		}

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, const Oracion& other) {
		out << other.string << std::endl;
		return out;
	}

	//friend std::istream& operator>>(std::istream& in, Oracion& other);

	Oracion operator-(const Oracion& other) const {
		std::string aux_a(this->string);
		std::string aux_b(other.string);

		size_t pos;
		while (1) {
			pos = aux_a.find(aux_b);
			if (pos == std::string::npos) {
				break;
			}
			aux_a.erase(pos, aux_b.length());
		}

		Oracion resul(aux_a.c_str());
		return resul;
	}

	~Oracion() {
		delete [] this->string;
	}	

};

int main() {
	char oracion_a[] = "hola leo como estas hola leo todo bien?";
	char oracion_b[] = "hola leo";
	Oracion a(oracion_a);
	Oracion b(oracion_b);

	Oracion c = a - b;

	std::cout << c << std::endl;

	return 0;
}
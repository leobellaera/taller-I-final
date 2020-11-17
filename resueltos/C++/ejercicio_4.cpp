/*
Declare la clase Oraciones que almacena una acumulacion de lineas de texto (strings)
en cierto orden e incluye las operaciones de agregacion y eliminacion de lineas.
La clase debe poseer los operadores usuales de copia, asignacion,
salida a flujo (<<) comparacion (==), agregacion (+), substraccion (-).
Los 2 ultimos operadores deben admitir argumentos del tipo string en
formato C (char*) y C++ (std::string).
*/

#include <list>
#include <iostream>
#include <ostream>
#include <string>

class Oraciones {
private:
	std::list<std::string> lines;
public:
	Oraciones() {}

	Oraciones(const Oraciones& other) { //constructor por copia
		this->lines = other.lines;
	}

	Oraciones& operator=(const Oraciones& other) { //asignacion por copia
		if (this != &other) {
			this->lines = lines;
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, const Oraciones& oracion) { //salida a flujo
		for (auto& line: oracion.lines) {
			out << line << std::endl;
		}
		return out;
	}

	void add(std::string added) {
		lines.push_back(added);
	};

	void remove(std::string removed) {
		lines.remove(removed);
	}

	bool operator==(const Oraciones& other) const {
		return (this->lines == other.lines);
	}

	Oraciones operator+(std::string added) const {
		Oraciones oraciones = *this;
		oraciones.add(added);	
		return oraciones;
	}

	Oraciones operator+(char* new_line) const {
		Oraciones oraciones = *this;
		std::string added(new_line);
		oraciones.add(added);	
		return oraciones;
	}

	Oraciones operator-(std::string removed) const {
		Oraciones oraciones = *this;
		oraciones.remove(removed);
		return oraciones;
	}

	Oraciones operator-(char* removed) const {
		Oraciones oraciones = *this;
		std::string aux(removed);
		oraciones.remove(aux);
		return oraciones;
	}

};

int main() {
	Oraciones oraciones;

	oraciones.add(std::string("Perro"));
	oraciones.add(std::string("Casa"));

	std::string str = "celular";

	Oraciones prueba_a = oraciones + str;

	char str_c[] = "Optimo";
	Oraciones prueba_b = oraciones + str_c;

	std::cout << prueba_a << std::endl;
	std::cout << prueba_b << std::endl;

	return 0;
}
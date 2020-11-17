/*Declare la clase Número para encapsular una cadena numérica larga. Incluya al menos:
Constructor(unsigned long), Constructor default y Constructor move; Operador <<, (), =, long y
++(int). Implemente el operador >>.*/

#include <iostream>
#include <ostream>
#include <istream>

class Numero {
private:
	unsigned long n;
public:
	Numero(unsigned long number) :
		n(number) {}

	Numero(Numero&& other) {
		n = std::move(other.n);
	}

	Numero(const Numero& other) {
		this->n = other.n;
	}

	void setNumber(unsigned long newNumb) {
		n = newNumb;
	}

	friend std::ostream& operator<<(std::ostream& out, const Numero& num) {
		out << num.n;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Numero& num) {
		std::string number;
		in >> number;
		num.setNumber(std::stoul(number));
		return in;
	}

	Numero& operator=(const Numero& other) {
		if (this != &other) {
			n = other.n;
		}
		return *this;
	}

	//Post-incremento ---> la instancia queda como esta y se devuelve otro con el valor incrementado (++a)
	//Pre-incremento --> la instancia se modifica y se devuelve una referencia a la misma

	Numero operator++(int) {
		Numero num = *this;
		num.n++;
		return num;
	}

	void operator()() {
		std::cout << this->n << std::endl;
	}
};

int main() {
	Numero num_a(10);
	Numero num_b = num_a++;

	std::cout<< num_a << std::endl;
	std::cout<< num_b << std::endl;
	std::cout<< num_a << std::endl;

	Numero num_c(5);

	std::cin >> num_c ;

	std::cout << num_c << std::endl;

	num_a();

	return 0;
}
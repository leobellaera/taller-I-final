/*Declare una clase a elección considerando:
 Atributos que son necesarios
 Accesibilidad a la Clase
 Incluir los operadores +, ++ (post-incremento), --(pre-incremento), >> (impresión),
<< (carga desde consola), long*/

#include <iostream>
#include <ostream>
#include <istream>

class Complex {

private:
	int re;
	int im;

public:
	Complex(int re, int im) :
		re(re), im(im) {}

	int getRe() const { //se agregan los const despues del nombre de la funcion para indicar que el objeto no cambia de estado.
		return re;
	}

	int getIm() const {  //se agregan los const despues del nombre de la funcion para indicar que el objeto no cambia de estado.
		return im;
	}

	void setComponents(int re, int im) {
		this->re = re;
		this->im = im;
	}

	Complex& operator=(const Complex& other) {
		if (this != &other) {
			re = other.re;
			im = other.im;
		}

		return *this;

	}

	Complex operator+(const Complex& other) {
		Complex resul(this->re + other.re, this->im + other.im);
		return resul;
	}

	Complex& operator--() {
		re--;
		im--;
		return *this;
	}

	Complex operator++(int) {
		Complex copy(re + 1, im + 1);
		return copy;
	}

	friend std::ostream& operator<<(std::ostream& out, const Complex& n) {
		out << "Re(x) = " << n.getRe() << " Im(x) = " << n.getIm();
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Complex& num) {
		std::string re;
		std::string im;
		in >> re >> im;
		num.setComponents(std::stoul(re), std::stoul(im));
		return in;
	}

};


int main() {
	Complex a(1,2);
	std::cin >> a;
	std::cout << a << std::endl;

	--a;

	std::cout << a << std::endl;

	Complex b(1,0);

	Complex c = a + b;

	std::cout << c << std::endl;

	Complex d(a + b);

	std::cout << d << std::endl;

	return 0;
}
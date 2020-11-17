#include <iostream>
#include <string>
#include <ostream>

class Cadena {

public:

	std::string str;

	Cadena(const char* str) :
		str(str) {}

	Cadena(const Cadena& other) {
		this->str = other.str;
	}

	Cadena& operator=(const Cadena& other) {
		this->str = other.str;
		return *this;
	}

	Cadena& operator=(const char* str) {
		this->str = str;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, const Cadena& cadena) {
		out << cadena.str;
		return out;
	}

	Cadena operator+(const Cadena& other) {
		std::string res = this->str + other.str;
		Cadena cadena(res.c_str());
		return cadena;
	}
};

int main() {
	Cadena c1("abc");
	Cadena c2("def");
	Cadena c4(c2);
	Cadena c3 = c1 + c2;
	c1 = c2 = "ghi";
	std::cout << c4 << std::endl;
	return 0;
}

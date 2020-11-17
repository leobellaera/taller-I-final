/*Defina la clase URL para permitir almacenar las siguientes propiedades:
protocolo (http), host (fi.uba.ar), port (80), y file (index.php o resources/img/logo.png)
A su vez se pide que implemente los siguientes operadores: operator<<, operator==
y operator=.*/

#include <iostream>
#include <string>
#include <ostream>

class URL {
private:
	std::string protocol;
	std::string host;
	std::string port;
	std::string file;

public:
        URL(std::string host, std::string port, std::string file ,std::string protocol):
            file(file), host(host), port(port), protocol(protocol) {}

        URL& operator=(const URL& other) {
            if (this != &other) {
            	this->protocol = other.protocol;
            	this->host = other.host;
            	this->port = other.port;
            	this->file = other.file;
            }

            return *this;
        }

        bool operator==(const URL& other) {
         	return (this->protocol == other.protocol && this->host == other.host && this->port == other.port && this->file == other.file);
        }

        friend std::ostream& operator<<(std::ostream& out, const URL& url) {
            out << "Host: " <<  url.host << std::endl;
            out << "Port: " << url.port << std::endl;
            out << "File: " << url.file << std::endl;
            return out;
        }
};

int main() {
	URL url_a("fi.uba.ar", "80", "index.php", "http");
	URL url_b("fi.uba.ar", "75", "index.php", "https");
	URL url_c("gov.ar", "77", "index.php", "http");

	if (!(url_a == url_b)) {
		std::cout << "url_a y url_b son distintos!" << std::endl;
	}

	url_a = url_b;

	if (url_a == url_b) {
		std::cout << "url_a y url_b son ahora iguales!" << std::endl;
	}

	std::cout << url_a << std::endl;


    return 0;
}
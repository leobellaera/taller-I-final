 #include <iostream>
    class Clase {
    public:
        static int numero;
        Clase() {}
    };

    int Clase::numero = 0;
        
    int main() {
        std::cout << Clase::numero << std::endl;
        return 0;
    }
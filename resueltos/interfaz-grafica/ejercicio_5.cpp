/* Escriba un pequeño programa de interfaz gráfica que lance una aplicación de ventana simple, con un
único botón. El botón debe tener el texto ‘Cerrar’ que al ser presionado oculta la ventana y cierra el
sistema. */

#include <QLabel>
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

class Window : public QWidget {
private:
	QVBoxLayout layout;
	QPushButton button;

	void onClick() {
		this->close();
	}

public:

	Window(QWidget* parent = 0) :
		QWidget(parent), 
		button("Cerrar") {

			layout.addWidget(&button);
			this->setLayout(&layout);
			QObject::connect(&button, &QPushButton::clicked, this, &Window::onClick);
			this->resize(500, 500);
		}
};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	Window w;
	w.show();
	return app.exec();
}
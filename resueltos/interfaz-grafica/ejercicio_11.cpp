/* Escriba una función que cargue un listbox (combo o dropdown) con 10 strings de la forma “opción xx”,
siendo xx una cadena de 2 dígitos con la forma 01, 02, ..., 10. */

#include <QLabel>
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <iostream>
#include <QPushButton>
#include <QComboBox>


class Window : public QWidget {
private:
	QVBoxLayout layout;
	QComboBox comboBox;
	QPushButton button;

	void displayCurrentText() {
		std::cout << comboBox.currentText().toStdString() << std::endl;
	}

public:
	Window(QWidget* parent = 0) :
		QWidget(parent),
		button("Seleccionar item") {

			for (int i = 1; i <= 9; i++) {
				std::string item = "opción 0" + std::to_string(i);
				comboBox.addItem(item.c_str());
			}

			comboBox.addItem("opción 10");

			layout.addWidget(&comboBox);
			layout.addWidget(&button);
			this->setLayout(&layout);

			QObject::connect(&button, &QPushButton::clicked, this, &Window::displayCurrentText);
	}

};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	Window w;
	w.show();
	return app.exec();
}
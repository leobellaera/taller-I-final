/* Escriba una rutina para ambientes gráficos que exponga una ventana con un cuadro de texto y un
botón. Al realizar click sobre el botón, el sistema debe tomar la información ingresada en el cuadro de
texto e imprimirla por consola. */

#include <QLabel>
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <iostream>
#include <QPushButton>

#include <iostream>

class PrintTextBox : public QWidget {
private:
	QPushButton button;
	QVBoxLayout layout;
	QLineEdit lineEdit;

	void setOnClick() {
		std::string text = lineEdit.text().toStdString();
		std::cout << text << std::endl;
	}

public:

	PrintTextBox(QWidget* parent = 0) :
		button("Imprimir texto"),
		lineEdit("") {

			layout.addWidget(&button);
			layout.addWidget(&lineEdit);
			this->setLayout(&layout);
			QObject::connect(&button, &QPushButton::clicked, this, &PrintTextBox::setOnClick);

		}

};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	PrintTextBox p;
	p.show();
	return app.exec();
}

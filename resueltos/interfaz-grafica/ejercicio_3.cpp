/*Escriba una rutina que muestre un botón y un cuadro de texto en una ventana. Al hacer click
en el botón debe desaparecer el cuadro de texto, dejando el resto de la ventana intácta.*/

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
	QVBoxLayout layout; // vertical box layout
	QPushButton button;
	QLineEdit text_box;

	void onClick() {
		text_box.hide();
	}

public:

	Window(QWidget* parent = 0) :
		QWidget(parent),
		button("Quitar el cuadro de texto"), 
		text_box("") {
			layout.addWidget(&button);
			layout.addWidget(&text_box);
			this->setLayout(&layout);

			//Esto es para que no se muevan los widgets agregados en el layout
			QSizePolicy sp_retain = text_box.sizePolicy();
            sp_retain.setRetainSizeWhenHidden(true);
            text_box.setSizePolicy(sp_retain);

			QObject::connect(&button, &QPushButton::clicked, this, &Window::onClick);
			this->resize(300, 300);
	}

};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	Window w;
	w.show();
	return app.exec();
}
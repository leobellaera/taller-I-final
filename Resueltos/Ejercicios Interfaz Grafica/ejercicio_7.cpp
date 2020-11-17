/* Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje la siguiente imagen en su área
de dibujo (un circulo azul en un rectangulo negro que lo contiene). */

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QRect>

class BlueCircle : public QWidget {
	void paintEvent(QPaintEvent* event) override {
		QPainter painter(this);
		QRect rectangle(0, 0, 300, 300);   //QRect rect(x, y, width, height) ---> rectangulo con origen en x, y.
		painter.setBrush(Qt::blue);
		painter.drawEllipse(rectangle);

		this->setStyleSheet("background-color:back;");
		this->resize(300, 300);
	}
};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	BlueCircle bc;
	bc.show();
	return app.exec();
}
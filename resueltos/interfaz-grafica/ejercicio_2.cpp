/*Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje un círculo verde
del tamaño de la ventana.*/

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QRect>


class GreenCircleDraw : public QWidget {

	void paintEvent(QPaintEvent* event) override {

		QPainter painter(this);
		QRect rectangle(0, 0, 500, 500);

		/*es importante notar que el pen (lapicera) solo sirve para dibujar puntos y lineas.
		Los brushes (pinceles) sirven para colorear cosas con relleno*/

		QBrush brush(Qt::green); //Cuando inicializas el QBrush sin parametros te setea el pattern a Qt::NoBrush --> no rellena figuras.
		//Si inicializamos el Qbrush sin parametros podemos realizar lo siguiente y llegamos a lo mismo.

		/*QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(Qt::green);*/

		painter.setBrush(brush);
		painter.drawEllipse(rectangle);

		QPen pen; //inicializa un pen con width default de 1 pixel.
		pen.setWidth(10);
		pen.setColor(Qt::black);
		painter.setPen(pen);

		painter.drawPoint(rectangle.width() / 2, rectangle.height() / 2);

		this->resize(rectangle.width(), rectangle.height());
		this->setStyleSheet("background-color:blue;"); //cambiamos el color del fondo azul (para probar)

	}
};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	GreenCircleDraw draw;
	draw.show();
	return app.exec();
}
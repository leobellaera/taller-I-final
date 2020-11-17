/* Escriba una rutina que dibuje un circulo arriba de un rectangulo. El circulo de
color naranja y el rectangulo de color azul. El circulo debe estar centrado sobre
el rectangulo. De fondo se debe dibujar una X rojo.*/

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QRect>
#include <QPen>


class Draw : public QWidget {
	void paintEvent(QPaintEvent* event) {
            QPainter painter(this);

            QPen pen;
            pen.setColor(Qt::red);
            pen.setWidth(20);

            painter.setPen(pen);
            painter.drawLine(0, 0, 1000, 1000);
            painter.drawLine(0, 1000, 1000, 0);

            QRect rectangle(250, 250, 500, 500);  //rectangulo centrado en el medio de la ventana (500,500)
            //recordar que (250, 500) es el borde sup izquierdo del rectangulo

            painter.setPen(Qt::NoPen); //Le sacamos la lapicera al painter para q no nos remarque los contornos del circulo y el rectangulo

            painter.setBrush(Qt::blue);
            painter.drawConvexPolygon(rectangle);

            painter.setBrush(Qt::yellow); //no tenemos el color Qt::orange, reemplazamos con amarillo
            painter.drawEllipse(rectangle);

            this->resize(1000,1000);
        }
};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	Draw d;
	d.show();
	return app.exec();
}
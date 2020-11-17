/*Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje un triángulo
amarillo del tamaño de la ventana.*/

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QRect>

class TriangleDraw : public QWidget {

public:
	void paintEvent(QPaintEvent* event) override {
		QPainter painter(this);
		QBrush brush(Qt::yellow);
		painter.setBrush(brush);

		QPointF points[3] = {
			QPointF(0, 300),
			QPointF(150, 0),
			QPointF(300, 300) 
		};

		painter.drawConvexPolygon(points, 3);
		this->resize(300, 300);
	}
};


int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	TriangleDraw t;
	t.show();
	return app.exec();
}

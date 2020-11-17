/*
Escriba una rutina para ambiente gráfico que dibuje un rombo rojo, centrado que ocupe todo el espacio
de ventana.
*/
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QRect>

class DiamondDraw : public QWidget {
	void paintEvent(QPaintEvent* event) override {
		QPainter painter(this);
		QBrush brush(Qt::red);
		painter.setBrush(brush);

		QPointF points[4] = {
			QPointF(500, 0),
			QPointF(1000, 500),
			QPointF(500, 1000),
			QPointF(0, 500)
		};

		painter.drawConvexPolygon(points, 4);
		this->resize(1000, 1000);

	}
};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	DiamondDraw d;
	d.show();
	return app.exec();
}
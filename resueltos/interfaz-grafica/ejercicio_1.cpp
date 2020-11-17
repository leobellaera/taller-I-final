/*Escriba una rutina que dibuje las dos diagonales de la pantalla en color rojo.*/

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QRect>

class DiagonalsDraw : public QWidget {

    public:
        void paintEvent(QPaintEvent* event) override {
            QPainter painter(this);
            QPen pen;
            pen.setWidth(10);
            pen.setColor(Qt::red);

            painter.setPen(pen);
            painter.drawLine(0, 0, 500, 500);
            painter.drawLine(500, 0, 0, 500);
            this->resize(500, 500);
        }

};

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	DiagonalsDraw diagonalsDraw;
	diagonalsDraw.show();
	return app.exec();
}


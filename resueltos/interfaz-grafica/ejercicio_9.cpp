/*
Implemente una rutina (en Windows o Linux) que dibuje un óvalo que ocupe toda la ventana.
*/

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QRect>

class EllipseDraw : public QWidget {

    public:
        void paintEvent(QPaintEvent* event) override {
            QPainter painter(this);
            painter.setBrush(Qt::blue);
            /*QRect screenRectangle = QApplication::desktop()->screenGeometry(); //QApplication::desktop() devuelve una instancia de la clase QDesktopWidget
            painter.drawEllipse(screenRectangle);
            this->resize(screenRectangle.width(), screenRectangle.height());*/

            //El codigo comentado arriba es para q la elipse sea en pantalla completa. Ahora hacemos uno en un tamaño prefijado.

            QRect rect(0, 0, 500, 300);
            painter.drawEllipse(rect);
            this->setStyleSheet("background-color:black"); //le ponemos fondo negro a la ventana
            this->resize(500, 300);

        }
};

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	EllipseDraw ellipse;
	ellipse.show();
	return app.exec();
}

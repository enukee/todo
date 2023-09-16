#include "imgwidget.h"
#include <iostream>

ImgWidget::ImgWidget(QString imgPath) {
    widget = new QWidget();
    layout = new QBoxLayout(QBoxLayout::LeftToRight, widget);
    layout->setContentsMargins(500, 500, 500, 500);
    image = new Image(imgPath, widget);
    widget->setGeometry(0, 0, 5120, 2880);
    layout->addWidget(image, Qt::AlignCenter);
	setWidget(widget);

    cursorTarget = QCursor(Qt::CrossCursor);
    setCursor(cursorTarget);

    setMouseTracking(true);
}

void ImgWidget::wheelEvent(QWheelEvent* event) {
    QPoint numDegrees = event->angleDelta() / 8;

    QPoint p = event->pos();
    std::cout << p.x() << "  " << p.y() << std::endl;

    //adjusting_widget();

    if (numDegrees.y() > 0) {
        scaleImage(1.25);
    }
    else {
        scaleImage(0.8);
    }

    QPoint position = event->pos();

    int maxVertical = verticalScrollBar()->maximum();
    int maxHorizontal = horizontalScrollBar()->maximum();

    //int valueScrolHorizontal = (y * maxHorizontal) / 2880;
    //int valueScrolVertical = (x * maxVertical) / 5120;

    //verticalScrollBar()->setValue(valueScrolVertical);
    //horizontalScrollBar()->setValue(valueScrolHorizontal);

}

void ImgWidget::scaleImage(double factor) {
    image->setScaleFactor(image->getScaleFactor() * factor);

    double newScaleFactor = image->getScaleFactor();
    image->resize(newScaleFactor * (image->pixmap()->size()));

    int x = newScaleFactor * image->pixmap()->size().width();
    int y = newScaleFactor * image->pixmap()->size().height();

    widget->setGeometry(0, 0, x + 1000, y + 1000);

    /*adjustScrollBar(horizontalScrollBar(), factor);
    adjustScrollBar(verticalScrollBar(), factor);*/
}

void ImgWidget::adjustScrollBar(QScrollBar* scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
        + ((factor - 1) * scrollBar->pageStep() / 2)));
}
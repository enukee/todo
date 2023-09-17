#include "imgwidget.h"
#include <iostream>

ImgWidget::ImgWidget(QString imgPath) {
    widget = new QWidget();
    layout = new QBoxLayout(QBoxLayout::LeftToRight, widget);
    layout->setContentsMargins(500, 500, 500, 500);
    image = new Image(imgPath, widget);
    widget->setGeometry(0, 0, image->pixmap()->size().width(), image->pixmap()->size().height());
    layout->addWidget(image, Qt::AlignCenter);
	setWidget(widget);

    cursorTarget = QCursor(Qt::CrossCursor);
    setCursor(cursorTarget);

    setMouseTracking(true);
}

//void ImgWidget::mouseMoveEvent(QMouseEvent* event) {
//    QPoint position = event->pos();
//    //std::cout << "позиция на изображении: " << xPos << "  " << yPos << "  " << scaleFactor << std::endl;
//}

void ImgWidget::wheelEvent(QWheelEvent* event) {
    QPoint numDegrees = event->angleDelta() / 8;

    // получение координат на widget
    double newScaleFactor_1 = image->getScaleFactor();
    QPoint pos = widget->mapFromGlobal(QCursor::pos());
    int x1 = pos.x();
    int y1 = pos.y();
    
    // получение координат с учётом newScaleFactor
    int posX = x1 / newScaleFactor_1;
    int posY = y1 / newScaleFactor_1;
    //std::cout << posX << "  " << posY << std::endl;

    // получение значения valueScrolBar
    int valueScrolHorizontal_1 = horizontalScrollBar()->value();
    int valueScrolVertical_1 = verticalScrollBar()->value();

    // масштабирование 
    // изменение scrollFactor
    if (numDegrees.y() > 0) {
        scaleImage(1.25);
    }
    else {
        scaleImage(0.8);
    }

    // новые координаты изначальной точки
    double newScaleFactor_2 = image->getScaleFactor();
    int x2 = posX * newScaleFactor_2;
    int y2 = posY * newScaleFactor_2;

    int maxHorizontal = horizontalScrollBar()->maximum();
    int maxVertical = verticalScrollBar()->maximum();

    int widgetSizeX = widget->size().width();
    int widgetSizeY = widget->size().height();

    // изменение значения valueScrolBar
    int valueScrolHorizontal_2 = (maxHorizontal * x2) / widgetSizeX;
    int valueScrolVertical_2 = (maxVertical * y2) / widgetSizeY;

    horizontalScrollBar()->setValue(valueScrolHorizontal_2);
    verticalScrollBar()->setValue(valueScrolVertical_2);

    //QPoint position = event->pos();

    //int maxVertical = verticalScrollBar()->maximum();
    //int maxHorizontal = horizontalScrollBar()->maximum();

    //std::cout << "                         " << maxVertical << "  " << maxHorizontal << std::endl;
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

    int borderX = image->pixmap()->size().width() * newScaleFactor;
    int borderY = image->pixmap()->size().height() * newScaleFactor;
    layout->setContentsMargins(borderX, borderY, borderX, borderY);
    widget->setGeometry(0, 0, x + 2 * borderX, y + 2 * borderY);

    /*adjustScrollBar(horizontalScrollBar(), factor);
    adjustScrollBar(verticalScrollBar(), factor);*/
}

void ImgWidget::adjustScrollBar(QScrollBar* scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
        + ((factor - 1) * scrollBar->pageStep() / 2)));
}
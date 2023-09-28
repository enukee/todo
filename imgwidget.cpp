#include "imgwidget.h"
#include <iostream>

ImgWidget::ImgWidget(QString imgPath) {
    scroll = new QScrollArea;
    scroll->setAlignment(Qt::AlignCenter);
    // disable wheel event for scroll
    scroll->viewport()->installEventFilter(this);

    this->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
    this->layout()->addWidget(scroll);

    image = new QLabel();
    image->setPixmap(QPixmap(imgPath));
    image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    image->setScaledContents(true);

    paintWidget = new QWidget(image);
    painter = new QPainter(paintWidget);

    scroll->setWidget(image);

    cursorTarget = QCursor(Qt::CrossCursor);
    image->setCursor(cursorTarget);
}

void ImgWidget::paintEvent(QPaintEvent* e) {
    painter->setPen(QPen{ Qt::black, 33, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin });

    painter->drawLine(0, 0, 1000, 1000);
}

void ImgWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        paintWidget->update();
    }
}

void ImgWidget::wheelEvent(QWheelEvent* event) {
    // функция для перехода от системы координат(СК) ImgWidget в пиксельную СК изображения
    auto widgetToImageCS = [this] (const QPoint& p) {
        const QPoint labelPos = image->mapFrom(this, p);
        return labelPos / scaleFactor;
    };

    const QPoint imageFocusOld = widgetToImageCS(event->pos());
    const int dy = event->angleDelta().y();

    if (dy > 0) {
        scaleImage(2);
    } else if (dy < 0) {
        scaleImage(0.5);
    }
    const QPoint imageFocusNew = widgetToImageCS(event->pos());
    const QPoint offset = (imageFocusOld - imageFocusNew) * scaleFactor;

    auto updateScroll = [] (QScrollBar* s, int offset) {
        s->setValue(s->value() + offset);
    };
    updateScroll(scroll->horizontalScrollBar(), offset.x());
    updateScroll(scroll->verticalScrollBar(), offset.y());
}

void ImgWidget::scaleImage(double factor) {
    scaleFactor *= factor;
    image->resize(scaleFactor * image->pixmap()->size());
}

bool ImgWidget::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::Wheel && watched == scroll->viewport()) {
        return true;
    }
    return QObject::eventFilter(watched, event);
}

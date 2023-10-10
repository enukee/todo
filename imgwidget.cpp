#include "imgwidget.h"

ImgWidget::ImgWidget(QString imgPath) {
    scroll = new QScrollArea;
    scroll->setAlignment(Qt::AlignCenter);
    // disable wheel event for scroll
    scroll->viewport()->installEventFilter(this);

    this->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
    this->layout()->addWidget(scroll);

    image = new ImageView(QPixmap(imgPath));
    scroll->setWidget(image);

    cursorTarget = QCursor(Qt::CrossCursor);
    image->setCursor(cursorTarget);
}

void ImgWidget::wheelEvent(QWheelEvent* event) {
    // функция для перехода от системы координат(СК) ImgWidget в пиксельную СК изображения
    auto widgetToImageCS = [this] (const QPoint& p) {
        const QPoint labelPos = image->mapFrom(this, p);
        return labelPos * image->getScale();
    };

    const QPoint imageFocusOld = widgetToImageCS(event->pos());
    const int dy = event->angleDelta().y();

    if ((dy > 0) && (image->getScale() > 0.125)) {
        image->scaleImage(0.5);
    } else if ((dy < 0) && (image->getScale() < 8)) {
        image->scaleImage(2);
    }

    const QPoint imageFocusNew = widgetToImageCS(event->pos());
    const QPoint offset = (imageFocusOld - imageFocusNew) / image->getScale();

    auto updateScroll = [] (QScrollBar* s, int offset) {
        s->setValue(s->value() + offset);
    };

    updateScroll(scroll->horizontalScrollBar(), offset.x());
    updateScroll(scroll->verticalScrollBar(), offset.y());
}

bool ImgWidget::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::Wheel && watched == scroll->viewport()) {
        return true;
    }
    return QObject::eventFilter(watched, event);
}
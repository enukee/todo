#include "ImageView.h"
#include <iostream>

ImageView::ImageView(QPixmap image)
    :image{ image } {
    setGeometry(0, 0, image.width(), image.height());
    this->setMouseTracking(true);
}

void ImageView::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    auto vp = painter.viewport();
    const auto topLeftImagePoint = viewToImage(vp.topLeft());
    const auto bottomRightImagePoint = viewToImage(vp.bottomRight());
    painter.drawPixmap(vp, image, QRectF(topLeftImagePoint, bottomRightImagePoint));

    auto ImageToPainter = [this](QPoint& p) {
        return p * scale;
        };

    qreal lineThickness = 4 / scale;
    lineThickness = std::clamp(lineThickness, (qreal)2, (qreal)6);

    painter.setPen(QPen(Qt::red, lineThickness, Qt::DotLine));

    QRect rectangle;
    rectangle.setTopLeft(ImageToPainter(rect.topLeft()));
    rectangle.setBottomRight(ImageToPainter(rect.bottomRight()));
    painter.drawRect(rectangle);
    QWidget::paintEvent(event);

    // sending a signal about a change in the selection
    emit PointRectChanged(rect.x(), rect.y(), rect.width(), rect.height());
}

void ImageView::mousePressEvent(QMouseEvent* event) {
    QPoint position = event->pos();
    position /= scale;

    if (event->button() == Qt::LeftButton) {
        rect.setTopLeft(QPoint(position.x(), position.y()));
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent* event) {
    QPoint position = event->pos();
    position /= scale;

    if (event->button() == Qt::LeftButton) {
        // normalization of coordinates
        qreal x1 = position.x();
        qreal y1 = position.y();
        qreal x2 = rect.topLeft().x();
        qreal y2 = rect.topLeft().y();

        std::pair<qreal, qreal> x = std::minmax(x1, x2);
        std::pair<qreal, qreal> y = std::minmax(y1, y2);

        rect.setBottomRight(QPoint(x.second, y.second));
        rect.setTopLeft(QPoint(x.first, y.first));

        setRectW(x.second - x.first);
        setRectH(y.second - y.first);
        setRectX(x.first);
        setRectY(y.first);

        // sending a signal about a change in the selection
        //emit PointRectChanged(rect.x(), rect.y(), rect.width(), rect.height());
        update();
    }
}


QPointF ImageView::viewToImage(const QPointF& view) const {
    return view / scale;
}

QSize ImageView::getImageSize() {
    return image.size();
}

double ImageView::getScale() {
    return scale;
}

void ImageView::setRectX(int x) {
    x = std::max(x, 0);
    rect.setX(x);
    update();
}
void ImageView::setRectY(int y) {
    y = std::max(y, 0);
    rect.setY(y);
    update();
}
void ImageView::setRectW(int width) {
    width = std::min(image.width() - rect.x(), width);
    rect.setWidth(width);
    update();
}
void ImageView::setRectH(int height) {
    height = std::min(image.height() - rect.y(), height);
    rect.setHeight(height);
    update();
}

QRect ImageView::getRect() {
    return rect;
}

void ImageView::scaleImage(double factor) {
    scale *= factor;
    // image.width() - the real width of the image
    // image.width() / scale - width on widget
    setGeometry(0, 0, image.width() * scale, image.height() * scale);
    update();
}
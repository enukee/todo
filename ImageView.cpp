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
        return p / scale;
    };

    qreal lineThickness = 4 * scale;
    if (lineThickness > 6)
        lineThickness = 6;
    else if (lineThickness < 2)
        lineThickness = 2;

    painter.setPen(QPen(Qt::red, lineThickness, Qt::DotLine));

    QRect rectangle;
    rectangle.setTopLeft(ImageToPainter(rect.topLeft()));
    rectangle.setBottomRight(ImageToPainter(rect.bottomRight()));
    painter.drawRect(rectangle);
    QWidget::paintEvent(event);
}

void ImageView::mousePressEvent(QMouseEvent* event) {
    QPoint position = event->pos();
    position *= scale;

    if (event->button() == Qt::LeftButton) {
        rect.setTopLeft(QPoint(position.x(), position.y()));
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent* event) {
    QPoint position = event->pos();
    position *= scale;

    if (event->button() == Qt::LeftButton) {
        // normalization of coordinates
        auto swapByValue = [](qreal& a, qreal& b) {
            if (a < b) {
                int c = a;
                a = b;
                b = c;
            }
        };

        qreal x1 = position.x();
        qreal y1 = position.y();
        qreal x2 = rect.topLeft().x();
        qreal y2 = rect.topLeft().y();

        swapByValue(x1, x2);
        swapByValue(y1, y2);

        rect.setBottomRight(QPoint(x1, y1));
        rect.setTopLeft(QPoint(x2, y2));

        update();
    }
    std::cout << rect.topLeft().x() << "    " << rect.topLeft().y() << std::endl;
    std::cout << rect.bottomRight().x() << "    " << rect.bottomRight().y() << std::endl << std::endl;
}

QPointF ImageView::viewToImage(const QPointF& view) const {
    return view * scale;
}

QSize ImageView::getImageSize() {
    return image.size();
}

double ImageView::getScale() {
    return scale;
}

void ImageView::setOffset(QPointF offset) {
    this->offset = offset;
}

void ImageView::scaleImage(double factor) {
    scale *= factor;
    // image.width() - the real width of the image
    // image.width() / scale - width on widget
    setGeometry(0, 0, image.width() / scale, image.height() / scale);
    update();
}
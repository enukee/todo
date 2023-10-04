#include "ImageView.h"

ImageView::ImageView(QPixmap image)
    :image{ image } {
    setGeometry(0, 0, image.width(), image.height());
}

void ImageView::paintEvent(QPaintEvent* event) {

    QPainter painter(this);
    auto vp = painter.viewport();
    const auto topLeftImagePoint = viewToImage(vp.topLeft());
    const auto bottomRightImagePoint = viewToImage(vp.bottomRight());
    painter.drawPixmap(vp, image, QRectF(topLeftImagePoint, bottomRightImagePoint));
    QWidget::paintEvent(event);
}

QPointF ImageView::viewToImage(const QPointF& view) const {
    return view * scale + offset;
}

QSize ImageView::getImageSize() {
    return image.size();
}

double ImageView::getScale() {
    return scale;
}

void ImageView::scaleImage(double factor) {
    scale *= factor;
    update();
    setGeometry(0, 0, image.width() / scale, image.height() / scale);
}
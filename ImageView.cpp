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
    //emit PointRectChanged(rect.x(), rect.y(), rect.width(), rect.height());
}

std::pair<qreal, qreal> ImageView::searchMinMax(qreal x1, qreal x2, qreal max) {
    std::pair<qreal, qreal> result = std::minmax(x1, x2);

    auto coordinateRestriction = [](qreal& value, qreal max) {
        value = std::clamp(value, (qreal)0, max);
        };

    coordinateRestriction(result.second, max);
    coordinateRestriction(result.first, max);
    return result;
}

void ImageView::mousePressEvent(QMouseEvent* event) {
    QPoint position = event->pos();
    position /= scale;

    if (event->button() == Qt::LeftButton) {
        rect.setTopLeft(QPoint(position.x(), position.y()));
    }
}

void ImageView::mouseMoveEvent(QMouseEvent* event) {
    QPoint position = event->pos();
    position /= scale;

    if (event->buttons().testFlag(Qt::LeftButton)) {
        // normalization of coordinates
        qreal x1 = position.x();
        qreal y1 = position.y();
        qreal x2 = rect.topLeft().x();
        qreal y2 = rect.topLeft().y();

        std::pair<qreal, qreal> x = searchMinMax(x1, x2, image.width());
        std::pair<qreal, qreal> y = searchMinMax(y1, y2, image.height());

        rect.setBottomRight(QPoint(x1, y1));

        update();
        QRect rectangle;
        rectangle.setBottomRight(QPoint(x.second - 1, y.second - 1));
        rectangle.setTopLeft(QPoint(x.first, y.first));

        emit PointRectChanged(rectangle);
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

        std::pair<qreal, qreal> x = searchMinMax(x1, x2, image.width());
        std::pair<qreal, qreal> y = searchMinMax(y1, y2, image.height());

        rect.setBottomRight(QPoint(x.second - 1, y.second - 1));
        rect.setTopLeft(QPoint(x.first, y.first));

        update();
        emit PointRectChanged(rect);
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
    int width = rect.width();
    int max = image.width() - width;
    if ((x < 0) || (x > max)) {
        rect.setX(max);
        emit IncorrectSelectionSize(0, max);
    }
    else
        rect.setX(x);
    
    rect.setWidth(width);
    update();
    emit PointRectChangedX(rect.x());
}

void ImageView::setRectY(int y) {
    int height = rect.height();
    int max = image.height() - height;
    if ((y < 0) || (y > max)) {
        rect.setY(max);
        emit IncorrectSelectionSize(0, max);
    }
    else
        rect.setY(y);

    rect.setHeight(height);
    update();
    emit PointRectChangedY(rect.y());
}

void ImageView::setRectW(int width) {
    int max = image.width() - rect.x();
    if ((width < 0) || (width > max)) {
        rect.setWidth(max);
        emit IncorrectSelectionSize(0, max);
    }
    else
        rect.setWidth(width);
    
    update();
    emit PointRectChangedW(rect.width());
}

void ImageView::setRectH(int height) {
    int max = image.height() - rect.y();
    if ((height < 0) || (height > max)) {
        rect.setHeight(max);
        emit IncorrectSelectionSize(0, max);
    }
    else
        rect.setHeight(height);
    
    update();
    emit PointRectChangedH(rect.height());
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
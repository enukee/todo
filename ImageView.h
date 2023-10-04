#pragma once
#include <QWidget>
#include <QLabel>
#include <QPainter>

class ImageView : public QWidget {
public:
    ImageView(QPixmap image);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPointF viewToImage(const QPointF& view) const;

private:
    QPixmap image;
    QPointF offset;
    double scale{ 1. };

public:
    QSize getImageSize();
    double getScale();

    void scaleImage(double factor);
};
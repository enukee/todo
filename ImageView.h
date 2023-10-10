#pragma once
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>

#include <stdio.h>

class ImageView : public QWidget {
public:
    ImageView(QPixmap image);

protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF viewToImage(const QPointF& view) const;

private:
    QPixmap image;
    QPointF offset;
    double scale{ 1. };

    QRect rect;

public:
    QSize getImageSize();
    double getScale();
    void setOffset(QPointF offset);

    void scaleImage(double factor);
};
#pragma once
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>

#include <stdio.h>

class ImageView : public QWidget {
    Q_OBJECT

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
    double scale{ 1. };
    QRect rect;

public:
    QSize getImageSize();

    double getScale();

    QRect getRect();

    void scaleImage(double factor);

signals:
    void PointRectChanged(int x, int y, int width, int height);

public slots:
    void setRectX(int x);
    void setRectY(int y);
    void setRectW(int width);
    void setRectH(int height);
};
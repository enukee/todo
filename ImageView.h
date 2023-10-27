#pragma once
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>

#include <stdio.h>
#include <algorithm>

class ImageView : public QWidget {
    Q_OBJECT

public:
    ImageView(QPixmap image);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF viewToImage(const QPointF& view) const;

    std::pair<qreal, qreal> searchMinMax(qreal value1, qreal value2, qreal max);

private:
    QPixmap image;
    double scale{ 1. };
    QRect rect;

public:
    QSize getImageSize();

    double getScale();

    QRect getRect();

    void scaleImage(double factor);

private:


signals:
    // изменение коррдинаты x
    void PointRectChangedX(int x);
    // изменение коррдинаты y
    void PointRectChangedY(int y);
    // изменение коррдинаты ширины выделения
    void PointRectChangedW(int w);
    // изменение коррдинаты высоты выделения
    void PointRectChangedH(int h);

    void PointRectChanged(QRect);

    // сигнал о некоректном значении
    void IncorrectSelectionSize(int min, int max);

public slots:
    void setRectX(int x);
    void setRectY(int y);
    void setRectW(int width);
    void setRectH(int height);
};
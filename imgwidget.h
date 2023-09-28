#pragma once 
#include <QObject>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QWheelEvent>
#include <QMoveEvent>
#include <QScrollArea>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>

#include <iostream>

class ImgWidget : public QWidget{

	Q_OBJECT

private:
    QLabel* image;
	QPainter* painter;

	QWidget* paintWidget;

	//widget ��� ������������ �����������
	QWidget* widget;
	//layout ��� ������������� ����������
	QScrollArea* scroll;

	QCursor cursorTarget;
	double scaleFactor = 1;

public:
	explicit ImgWidget(QString imgPath);

	void wheelEvent(QWheelEvent* event) override;

private:
	void drawArea(QWheelEvent* event);

    void scaleImage(double factor);
	
	bool eventFilter(QObject *watched, QEvent *event) override;

protected:
	void mousePressEvent(QMouseEvent* e) override;

	void paintEvent(QPaintEvent* e) override;

};
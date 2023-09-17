#pragma once 
#include <QObject>
#include <QHBoxLayout >
#include <QScrollBar>
#include <QWheelEvent>
#include <QMoveEvent>
#include <QScrollArea>
#include <QLabel>
#include <QMouseEvent>

#include <iostream>

#include "image.h"

class ImgWidget : public QScrollArea {

	Q_OBJECT

private:
	Image* image;

	//widget для расположения изображения
	QWidget* widget;
	//layout для центрирования зображения
	QBoxLayout* layout;

	QCursor cursorTarget;
	double scaleFactor = 1;

public:
	explicit ImgWidget(QString imgPath);

	virtual void wheelEvent(QWheelEvent* event);
	//void mouseMoveEvent(QMouseEvent* event);

	void adjustScrollBar(QScrollBar* scrollBar, double factor);

	void scaleImage(double factor);
};
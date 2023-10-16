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

#include "ImageView.h"

class ImgWidget : public QWidget{

	Q_OBJECT

public:
	ImageView* image;

private:
	QWidget* widget;

	QScrollArea* scroll;

	QCursor cursorTarget;

public:
	explicit ImgWidget(QString imgPath);

protected:
	void wheelEvent(QWheelEvent* event) override;

private:
	void drawArea(QWheelEvent* event);
	
	bool eventFilter(QObject *watched, QEvent *event) override;
};
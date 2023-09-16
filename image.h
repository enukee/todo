#pragma once
#include <QLabel>
#include <QMouseEvent>

#include <iostream>

class Image : public QLabel {

	Q_OBJECT

private:
	QPixmap* image;
	double scaleFactor = 1;	

public:
	int xPos;
	int yPos;

	Image(QString imgPath, QWidget* parent);

	double getScaleFactor();
	void setScaleFactor(double value);

protected:
	virtual void mouseMoveEvent(QMouseEvent* event);
};
#include "image.h"

Image::Image(QString imgPath, QWidget* parent) : QLabel(parent){
	image = new QPixmap(imgPath);
	setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	setScaledContents(true);
	setPixmap(*image);
	setMouseTracking(true);
}

void Image::mouseMoveEvent(QMouseEvent* event) {
	QPoint position = event->pos();
	xPos = position.x() / scaleFactor;
	yPos = position.y() / scaleFactor;
	//std::cout << "позиция на изображении: " << xPos << "  " << yPos << "  " << scaleFactor << std::endl;
}

double Image::getScaleFactor() {
	return scaleFactor;
}

void Image::setScaleFactor(double value) {
	scaleFactor = value;
}
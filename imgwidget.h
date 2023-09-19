#pragma once 
#include <QObject>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QWheelEvent>
#include <QMoveEvent>
#include <QScrollArea>
#include <QLabel>
#include <QMouseEvent>

#include <iostream>

class ImgWidget : public QWidget{

	Q_OBJECT

private:
    QLabel* image;

	//widget ��� ������������ �����������
	QWidget* widget;
	//layout ��� ������������� ����������
	QScrollArea* scroll;

	QCursor cursorTarget;
	double scaleFactor = 1;

public:
	explicit ImgWidget(QString imgPath);
	void wheelEvent(QWheelEvent* event) override;

public:
    void scaleImage(double factor);

    bool eventFilter(QObject *watched, QEvent *event) override;
};
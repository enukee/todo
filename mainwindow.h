#pragma once 

#include <iostream>

#include <QMainWindow>
#include <QMenuBar>
#include <QObject>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QErrorMessage>
#include <QSizePolicy>

#include "imgwidget.h"
#include "processingWidget.h"
#include "ñoordinateInputPanel.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QTabWidget* tabWidget;
	ImgWidget* currentWidget;

	CoordinateInputPanel* panelInput;

	ProcessingWidget* processingWindow;

public:
	MainWindow();

private:
	void connectingGraphicWidget(ImgWidget* currentWidget);
	void disablingGraphicalWidget(ImgWidget* currentWidget);

protected:
	void closeEvent(QCloseEvent* event);

public slots:
	void changingFields(QRect rect);

	void creatingTab(QPixmap pixmap);

	void sizeErrorWindowOutput(int min, int max);

	void openFileDialog();

	void selectTab(int x);

	void slotCloseTab(int index);

	void recipientOfImageData(int index, QRect* rect);
};

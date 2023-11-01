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
#include "InputField.h"
#include "processingWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QTabWidget* tabWidget;
	ImgWidget* currentWidget;

	InputField* inputFieldX;
	InputField* inputFieldY;
	InputField* inputFieldW;
	InputField* inputFieldH;

	ProcessingWidget* window;

public:
	MainWindow();

private:
	void connectingGraphicWidget(ImgWidget* currentWidget);
	void disablingGraphicalWidget(ImgWidget* currentWidget);

protected:
	void closeEvent(QCloseEvent* event);

public slots:
	void changingFields(QRect rect);

	void sizeErrorWindowOutput(int min, int max);

	void openFileDialog();

	void openWindowCombining();

	void selectTab(int x);
};

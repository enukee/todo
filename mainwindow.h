#pragma once 

#include <iostream>

#include <QMainWindow>
#include <QMenuBar>
#include <QObject>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include "imgwidget.h"
#include "InputField.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QTabWidget* tabWidget;

	InputField* inputFieldX;
	InputField* inputFieldY;
	InputField* inputFieldW;
	InputField* inputFieldH;

public:
	MainWindow();

public slots:
	void changingFields(int x, int y, int width, int height);

	void openFileDialog();

	void selectTab(int x);
};

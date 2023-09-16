#pragma once 

#include <iostream>

#include <QMainWindow>
#include <QMenuBar>
#include <QObject>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include "imgwidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QTabWidget* tabWidget;
	QLabel* panle_coord;

public:
	MainWindow();

public slots:
	void openFileDialog();

};

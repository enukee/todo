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
#include "coordinateInputPanel.h"

#include "bmp/matrixProcessing.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	QTabWidget* tabWidget;
	ImgWidget* currentWidget;

	CoordinateInputPanel* panelInput;

	ProgressBarValue* progress;
	std::thread* thread;

	ProcessingWidget* processingWindow;

public:
	MainWindow();

private:
	void connectingGraphicWidget(ImgWidget* currentWidget);
	void disablingGraphicalWidget(ImgWidget* currentWidget);

	void combiningImage(std::string w1, std::string w2, QRect rect_1, QRect rect_2);

protected:
	void closeEvent(QCloseEvent* event);

signals:
	void creatingNewTab(QPixmap pixmap);

	void callingMessageBox(QString strTitle, QString strText);

public slots:
	void changingFields(QRect rect);

	void creatingTab(QPixmap pixmap);

	void sizeErrorWindowOutput(int min, int max);

	void openFileDialog();

	void selectTab(int x);

	void startProcessing();

	void slotCloseTab(int index);

	void recipientOfImageData(int index, QRect* rect);

	void createMessageBox(QString strTitle, QString strText);
};

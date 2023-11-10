#pragma once 

#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

// a widget that will receive information about the location of files and process them
class ProcessingWidget : public QWidget {
	Q_OBJECT

private:
	QComboBox* list1;
	QComboBox* list2;
	QPushButton* processingButton;

public:
	ProcessingWidget();

	void addFile(QString fileName);

	void deleteItem(int index);

public slots:
	void imageProcessing();

signals:
	void getterDataForProcessing(int index, QRect* rect);

	void creatingNewTab(QPixmap pixmap);
};
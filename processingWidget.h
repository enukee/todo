#pragma once 

#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>

// a widget that will receive information about the location of files and process them
class ProcessingWidget : public QWidget {
	Q_OBJECT

private:
	QVBoxLayout* layout;
	QComboBox* list1;
	QComboBox* list2;
	QPushButton* processingButton;

public:
	ProcessingWidget();

	void addFile(QString fileName);
};
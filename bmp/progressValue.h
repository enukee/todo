#pragma once 

#include <QObject>

class ProgressBarValue : public QObject {
	Q_OBJECT

private:
	int value = 0;

public:
	ProgressBarValue();
	void setValue(int value);

	void increaseValue(int value);

signals:
	void valueChange(int value);
};
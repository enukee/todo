#pragma once 

#include <QObject>

class ProgressBarValue : public QObject {
	Q_OBJECT

private:
	int value = 0;

	bool stop = 0;

public:
	ProgressBarValue();
	void setValue(int value);

	int getValue();

	void increaseValue(int value);

	bool isProcessStopped();

signals:
	void valueChange(int value);

public slots:
	void stopProcess();
};
#pragma once 

#include <QObject>
#include <atomic>

class ProgressBarValue : public QObject {
	Q_OBJECT

private:
	std::atomic_int value = 0;

	std::atomic_bool stop = 0;

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
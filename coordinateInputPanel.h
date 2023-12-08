#pragma once 

#include <QHBoxLayout>
#include <QProgressBar>

#include "InputField.h"

class CoordinateInputPanel : public QWidget {
	Q_OBJECT

public:
	InputField* inputFieldX;
	InputField* inputFieldY;
	InputField* inputFieldW;
	InputField* inputFieldH;

	QProgressBar* progressBar;

	CoordinateInputPanel();

	void isEnabled(bool enable);

public slots:
	void progressChange(int value);
};
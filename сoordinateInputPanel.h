#pragma once 

#include <QHBoxLayout>

#include "InputField.h"

class CoordinateInputPanel : public QWidget {
	//Q_OBJECT

public:
	InputField* inputFieldX;
	InputField* inputFieldY;
	InputField* inputFieldW;
	InputField* inputFieldH;

	CoordinateInputPanel();

	void isEnabled(bool enable);
};
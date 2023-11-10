#include "ñoordinateInputPanel.h"

CoordinateInputPanel::CoordinateInputPanel() {
	QGridLayout* layoutField = new QGridLayout();

	// ïîëå ââîäà êîîðäèíàòû
	inputFieldX = new InputField("coordinate X : ");
	layoutField->addWidget(inputFieldX, 0, 0);
	inputFieldY = new InputField("coordinate Y : ");
	layoutField->addWidget(inputFieldY, 0, 1);
	inputFieldW = new InputField("width : ");
	layoutField->addWidget(inputFieldW, 1, 0);
	inputFieldH = new InputField("height : ");
	layoutField->addWidget(inputFieldH, 1, 1);
	setLayout(layoutField);
	setMaximumSize(300, inputFieldX->sizeHint().height() * 2);

	isEnabled(false);
}

void CoordinateInputPanel::isEnabled(bool enable) {
	enable = !enable;

	for (auto el : { inputFieldX, inputFieldY, inputFieldW, inputFieldH }) {
		el->inputDialog->setReadOnly(enable);
		el->inputDialog->setText("");
	}
}

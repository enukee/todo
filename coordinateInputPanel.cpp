#include "coordinateInputPanel.h"

CoordinateInputPanel::CoordinateInputPanel() {
	QVBoxLayout* toolLauout = new QVBoxLayout();

	QLabel* progressLabel = new QLabel("Process:");
	progressBar = new QProgressBar();
	toolLauout->addWidget(progressLabel);
	toolLauout->addWidget(progressBar);

	QWidget* widgetField = new QWidget();
	QGridLayout* layoutField = new QGridLayout();
	widgetField->setLayout(layoutField);
	toolLauout->addWidget(widgetField);

	// поле ввода координаты
	inputFieldX = new InputField("coordinate X : ");
	layoutField->addWidget(inputFieldX, 0, 0);
	inputFieldY = new InputField("coordinate Y : ");
	layoutField->addWidget(inputFieldY, 0, 1);
	inputFieldW = new InputField("width : ");
	layoutField->addWidget(inputFieldW, 1, 0);
	inputFieldH = new InputField("height : ");
	layoutField->addWidget(inputFieldH, 1, 1);
	setMaximumSize(300, inputFieldX->sizeHint().height() * 2 
		+ progressBar->sizeHint().height() + 30 + progressLabel->sizeHint().height());

	isEnabled(false);

	setLayout(toolLauout);
}

void CoordinateInputPanel::isEnabled(bool enable) {
	enable = !enable;

	for (auto el : { inputFieldX, inputFieldY, inputFieldW, inputFieldH }) {
		el->inputDialog->setReadOnly(enable);
		el->inputDialog->setText("");
	}
}

void CoordinateInputPanel::progressChange(int value) {
	progressBar->setValue(value);
}

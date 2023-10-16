#pragma once

#include "InputField.h"

InputField::InputField(QString str): numeric_validator(QRegExp("^[0-9]+$")) {
	QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	labelInput = new QLabel(str);
	inputDialog = new QLineEdit();
	inputDialog->setValidator(&numeric_validator);
	layout->addWidget(labelInput);
	layout->addWidget(inputDialog);

	connect(inputDialog, SIGNAL(textEdited(const QString&)),
		this, SLOT(validator(const QString&)));
}

void InputField::setField(QString str) {
	inputDialog->setText(str);
}

void InputField::validator(const QString& str) {
	int value = str.toInt();

	emit changingField(value);
}

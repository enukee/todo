#pragma once

#include "InputField.h"

InputField::InputField(QString str): numeric_validator(QRegExp("^[0-9]+$")) {
	QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	labelInput = new QLabel(str);
	inputDialog = new QLineEdit();
	inputDialog->setValidator(&numeric_validator);
	layout->addWidget(labelInput);
	layout->addWidget(inputDialog);

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(sizeHint());
	setMaximumSize(sizeHint());

	connect(inputDialog, SIGNAL(textEdited(const QString&)),
		this, SLOT(validator(const QString&)));
}

void InputField::setField(int value) {
	inputDialog->setText(QString::number(value));
}

void InputField::validator(const QString& str) {
	int value = str.toInt();

	emit changingField(value);
}

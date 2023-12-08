#include "progressValue.h"

ProgressBarValue::ProgressBarValue() {}

void ProgressBarValue::setValue(int value) {
		this->value = value;

		emit valueChange(value);
}

void ProgressBarValue::increaseValue(int value) {
	this->value += value;

	emit valueChange(this->value);
}
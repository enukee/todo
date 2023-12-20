#include "progressValue.h"

ProgressBarValue::ProgressBarValue() {}

int ProgressBarValue::getValue() {
	return this->value;
}

void ProgressBarValue::setValue(int value) {
	this->value = value;

	emit valueChange(value);
}

void ProgressBarValue::increaseValue(int value) {
	this->value += value;

	emit valueChange(this->value);
}

void ProgressBarValue::stopProcess() {
	stop = 1;
}

bool ProgressBarValue::isProcessStopped() {
	return stop;
}
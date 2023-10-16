#pragma once

#include <QLineEdit>
#include <QBoxLayout>
#include <QRegExpValidator>
#include <QLabel>

class InputField : public QWidget {
	Q_OBJECT

private:
	QLabel* labelInput;
	QRegExpValidator numeric_validator;

public:
	QLineEdit* inputDialog;

public:
	InputField(QString str);

	void setField(QString str);

signals:
	void changingField(int);

public slots:
	void validator(const QString& str);
};
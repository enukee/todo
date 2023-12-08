#include "processingWidget.h"
#include "bmp/BmpFile.h"

ProcessingWidget::ProcessingWidget() {
	setWindowTitle("Combining an image");
	QVBoxLayout* layout = new QVBoxLayout();

	QLabel* label1 = new QLabel("Path to the first file");
	list1 = new QComboBox();
	layout->addWidget(label1);
	layout->addWidget(list1);
	list1->setMinimumSize(120, 30);

	QLabel* label2 = new QLabel("Path to the second file");
	list2 = new QComboBox();
	layout->addWidget(label2);
	layout->addWidget(list2);
	list2->setMinimumSize(120, 30);

	processingButton = new QPushButton("merge images");
	layout->addWidget(processingButton,5, Qt::AlignCenter);
	processingButton->setFixedSize(100, 30);

	layout->setContentsMargins(70, 70, 70, 70);
	setLayout(layout);

	setFixedSize(list1->sizeHint() * 2 + label1->sizeHint() * 2 +
		processingButton->sizeHint() + (QSize(200, 200)));
	//setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// connecting the handler when the button is clicked
}

void ProcessingWidget::deleteItem(int index) {
	list1->removeItem(index);
	list2->removeItem(index);
}

void ProcessingWidget::addFile(QString fileName) {
	list1->addItem(fileName);
	list2->addItem(fileName);
}
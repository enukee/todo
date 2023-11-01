#include "processingWidget.h"

ProcessingWidget::ProcessingWidget() {
	setWindowTitle("Combining an image");

	layout = new QVBoxLayout();

	list1 = new QComboBox();
	layout->addWidget(list1);
	list1->setMinimumSize(120, 30);

	list2 = new QComboBox();
	layout->addWidget(list2);
	list2->setMinimumSize(120, 30);

	processingButton = new QPushButton("merge images");
	layout->addWidget(processingButton,3, Qt::AlignCenter);
	processingButton->setFixedSize(100, 30);

	layout->setContentsMargins(70, 70, 70, 70);
	setLayout(layout);

	setFixedSize(list1->sizeHint() + list2->sizeHint() +
		processingButton->sizeHint() + (QSize(200, 200)));
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void ProcessingWidget::addFile(QString fileName) {
	list1->addItem(fileName);
	list2->addItem(fileName);
}

#include "mainwindow.h"

void MainWindow::openFileDialog() {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("����� �����������"), "C:/", tr("Image Files (*.bmp)"));
	ImgWidget* img = new ImgWidget(fileName);
	tabWidget->addTab(img, fileName);

	/*int id = tabWidget->addTab(img, fileName);
	QWidget* w = tabWidget->widget(id);
	ImgWidget* orig = dynamic_cast<ImgWidget*>(w);*/
}

void MainWindow::selectTab(int id) {
	QWidget* w = tabWidget->widget(id);
	ImgWidget* image = dynamic_cast<ImgWidget*>(w);

	QRect rect = image->image->getRect();
	changingFields(rect.x(), rect.y(), rect.width(), rect.height());
}

void MainWindow::changingFields(int x, int y, int width, int height) {
	inputFieldX->setField(QString::number(x));
	inputFieldY->setField(QString::number(y));
	inputFieldW->setField(QString::number(width));
	inputFieldH->setField(QString::number(height));
}

MainWindow::MainWindow() {
	setWindowTitle("Main Window");
	resize(1200, 700);
	QWidget* centralWidget = new QWidget;
	QHBoxLayout* lauout = new QHBoxLayout();

	QWidget* widget1 = new QWidget;
	widget1->setMaximumSize(300,1000);

	tabWidget = new QTabWidget();
	lauout->addWidget(tabWidget);

	QGridLayout* layoutField = new QGridLayout();
	// ���� ����� ����������
	inputFieldX = new InputField("coordinate X : ");
	layoutField->addWidget(inputFieldX, 0, 0);
	inputFieldY = new InputField("coordinate Y : ");
	layoutField->addWidget(inputFieldY, 0, 1);
	inputFieldW = new InputField("width : ");
	layoutField->addWidget(inputFieldW, 1, 0);
	inputFieldH = new InputField("height : ");
	layoutField->addWidget(inputFieldH, 1, 1);
	layoutField->addWidget(new QLabel(), 2, 0);
	layoutField->addWidget(new QLabel(), 3, 0);
	layoutField->addWidget(new QLabel(), 4, 0);
	layoutField->addWidget(new QLabel(), 5, 0);
	widget1->setLayout(layoutField);
	lauout->addWidget(widget1);

	// ���������� ������� ��� �������
	ImgWidget* img = new ImgWidget("C:/Users/vi/Pictures/Saved Pictures/5120x2880-UHD.bmp");
	tabWidget->addTab(img, "fileName");

	// ����
	QMenuBar* menubar = new QMenuBar();

	// �������� ����� .bmp
	QAction* actionOpen = new QAction("Open");
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(openFileDialog()));

	// ���������� ����� .bmp
	QAction* actionSave = new QAction("Save");
	connect(actionSave, SIGNAL(triggered()), this, SLOT(openFileDialog()));

	// ��������� �������� ��������� ��� ������������� �������
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(selectTab(int)));

	// ������� ������
	ImgWidget* currentWidget = dynamic_cast<ImgWidget*>(tabWidget->currentWidget());

	// ��������� �������� ����� ��� ���������� ���������
	connect(currentWidget->image, SIGNAL(PointRectChanged(int, int, int, int)),
		this, SLOT(changingFields(int, int, int, int)));

	// ���������� ��������� ��� ��������� �������� ����
	connect(inputFieldX, SIGNAL(changingField(int)),
		currentWidget->image, SLOT(setRectX(int)));

	// ���������� ��������� ��� ��������� �������� ����
	connect(inputFieldY, SIGNAL(changingField(int)),
		currentWidget->image, SLOT(setRectY(int)));

	// ���������� ��������� ��� ��������� �������� ����
	connect(inputFieldW, SIGNAL(changingField(int)),
		currentWidget->image, SLOT(setRectW(int)));

	// ���������� ��������� ��� ��������� �������� ����
	connect(inputFieldH, SIGNAL(changingField(int)),
		currentWidget->image, SLOT(setRectH(int)));

	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(actionOpen);
	fileMenu->addAction(actionSave);
	QMenu* helpMenu = menuBar()->addMenu("Help");

	centralWidget->setLayout(lauout);
	setCentralWidget(centralWidget);
}

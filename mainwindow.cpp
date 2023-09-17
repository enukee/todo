#include "mainwindow.h"

void MainWindow::openFileDialog() {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Выбор изображения"), "C:/", tr("Image Files (*.bmp)"));
	ImgWidget* img = new ImgWidget(fileName);
	tabWidget->addTab(img, fileName);

	/*int id = tabWidget->addTab(img, fileName);
	QWidget* w = tabWidget->widget(id);
	ImgWidget* orig = dynamic_cast<ImgWidget*>(w);*/
}

MainWindow::MainWindow()
{
	setWindowTitle("Main Window");
	resize(1200, 700);
	QWidget* widget = new QWidget;
	QHBoxLayout* lauout = new QHBoxLayout();

	QWidget* widget1 = new QWidget;
	QVBoxLayout* toolbar = new QVBoxLayout();
	widget1->setLayout(toolbar);

	panle_coord = new QLabel();
	QPushButton* but1 = new QPushButton("+");
	QPushButton* but2 = new QPushButton("-");
	toolbar->addWidget(panle_coord);
	toolbar->addWidget(but1);
	toolbar->addWidget(but2);

	tabWidget = new QTabWidget();
	lauout->addWidget(tabWidget);

	lauout->addWidget(widget1);

	// добавления виджета для отладки
	ImgWidget* img = new ImgWidget("C:/Users/vi/Pictures/Saved Pictures/5120x2880-UHD.bmp");
	tabWidget->addTab(img, "fileName");

	// Меню
	QMenuBar* menubar = new QMenuBar();

	// Открытие файла .bmp
	QAction* actionOpen = new QAction("Open");
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(openFileDialog()));

	// Сохранение файла .bmp
	QAction* actionSave = new QAction("Save");
	connect(actionSave, SIGNAL(triggered()), this, SLOT(openFileDialog()));

	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(actionOpen);
	fileMenu->addAction(actionSave);
	QMenu* helpMenu = menuBar()->addMenu("Help");

	widget->setLayout(lauout);
	setCentralWidget(widget);
}

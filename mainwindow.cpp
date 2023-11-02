#include "mainwindow.h"

void MainWindow::openFileDialog() {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Image Selection"), "C:/", tr("Image Files (*.bmp)"));
	if (fileName == nullptr) return;

	ImgWidget* img = new ImgWidget(fileName);
	tabWidget->addTab(img, fileName);
	tabWidget->setCurrentWidget(img);

	processingWindow->addFile(fileName);
}

void MainWindow::connectingGraphicWidget(ImgWidget* widget) {
	// изменение значения полей при изменениии выделения
	connect(widget->image, SIGNAL(PointRectChanged(QRect)),
		this, SLOT(changingFields(QRect)));

	// изменение значения поля x при некорректно введёном значении
	connect(widget->image, SIGNAL(PointRectChangedX(int)),
		panelInput->inputFieldX, SLOT(setField(int)));

	// изменение значения поля y при некорректно введёном значении
	connect(widget->image, SIGNAL(PointRectChangedY(int)),
		panelInput->inputFieldY, SLOT(setField(int)));

	// изменение значения поля ширина при некорректно введёном значении
	connect(widget->image, SIGNAL(PointRectChangedW(int)),
		panelInput->inputFieldW, SLOT(setField(int)));

	// изменение значения поля высота при некорректно введёном значении
	connect(widget->image, SIGNAL(PointRectChangedH(int)),
		panelInput->inputFieldH, SLOT(setField(int)));

	// изменениии выделения при изменении значения поля
	connect(panelInput->inputFieldX, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectX(int)));

	// изменениии выделения при изменении значения поля
	connect(panelInput->inputFieldY, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectY(int)));

	// изменениии выделения при изменении значения поля
	connect(panelInput->inputFieldW, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectW(int)));

	// изменениии выделения при изменении значения поля
	connect(panelInput->inputFieldH, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectH(int)));

	// отркрытие окна с информацией об ошибке
	connect(widget->image, SIGNAL(IncorrectSelectionSize(int, int)),
		this, SLOT(sizeErrorWindowOutput(int, int)));
}

void MainWindow::disablingGraphicalWidget(ImgWidget* widget) {
	// изменение значения полей при изменениии выделения
	disconnect(widget->image, SIGNAL(PointRectChanged(QRect)),
		this, SLOT(changingFields(QRect)));

	// изменение значения поля x при некорректно введёном значении
	disconnect(widget->image, SIGNAL(PointRectChangedX(int)),
		panelInput->inputFieldX, SLOT(setField(int)));

	// изменение значения поля y при некорректно введёном значении
	disconnect(widget->image, SIGNAL(PointRectChangedY(int)),
		panelInput->inputFieldY, SLOT(setField(int)));

	// изменение значения поля ширина при некорректно введёном значении
	disconnect(widget->image, SIGNAL(PointRectChangedW(int)),
		panelInput->inputFieldW, SLOT(setField(int)));

	// изменение значения поля высота при некорректно введёном значении
	disconnect(widget->image, SIGNAL(PointRectChangedH(int)),
		panelInput->inputFieldH, SLOT(setField(int)));

	// изменениии выделения при изменении значения поля
	disconnect(panelInput->inputFieldX, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectX(int)));

	// изменениии выделения при изменении значения поля
	disconnect(panelInput->inputFieldY, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectY(int)));

	// изменениии выделения при изменении значения поля
	disconnect(panelInput->inputFieldW, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectW(int)));

	// изменениии выделения при изменении значения поля
	disconnect(panelInput->inputFieldH, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectH(int)));

	// отркрытие окна с информацией об ошибке
	disconnect(widget->image, SIGNAL(IncorrectSelectionSize(int, int)),
		this, SLOT(sizeErrorWindowOutput(int, int)));
}

void MainWindow::selectTab(int id) {
	if (id == -1) return;

	if (currentWidget != NULL)
		disablingGraphicalWidget(currentWidget);
	else
		panelInput->isEnabled(true);


	QWidget* w = tabWidget->widget(id);
	currentWidget = dynamic_cast<ImgWidget*>(w);

	QRect rect = currentWidget->image->getRect();
	changingFields(rect);

	connectingGraphicWidget(currentWidget);
}

void MainWindow::changingFields(QRect rect) {
	panelInput->inputFieldX->setField(rect.x());
	panelInput->inputFieldY->setField(rect.y());
	panelInput->inputFieldW->setField(rect.width());
	panelInput->inputFieldH->setField(rect.height());
}

void MainWindow::sizeErrorWindowOutput(int min, int max) {
	QErrorMessage errorMessage;
	errorMessage.showMessage("The value must be in the range from " 
		+ QString::number(min) + tr(" to ") + QString::number(max));
	setEnabled(false);
	errorMessage.exec();
	setEnabled(true);
}


MainWindow::MainWindow() {
	setWindowTitle("Merging Images");
	resize(1200, 700);
	QWidget* centralWidget = new QWidget();
	QHBoxLayout* lauout = new QHBoxLayout();

	processingWindow = new ProcessingWidget();

	tabWidget = new QTabWidget();
	tabWidget->setMovable(true);
	tabWidget->setTabsClosable(true);
	//tabWidget->setUsersScrollButtons(true);
	lauout->addWidget(tabWidget);
	currentWidget = NULL;

	QWidget* toolWidget = new QWidget();
	toolWidget->setMaximumSize(300, 1000);
	QHBoxLayout* toolLayout = new QHBoxLayout();
	toolLayout->setAlignment(Qt::AlignTop);
	lauout->addWidget(toolWidget);

	panelInput = new CoordinateInputPanel();
	toolLayout->addWidget(panelInput);
	toolWidget->setLayout(toolLayout);

	// добавления виджета для отладки
	/*ImgWidget* img = new ImgWidget("C:/Users/vi/Pictures/Saved Pictures/5120x2880-UHD.bmp");
	tabWidget->addTab(img, "fileName");
	processingWindow->addFile("fileName");*/

	// Открытие файла .bmp
	QAction* actionOpen = new QAction("Open");
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(openFileDialog()));

	// Сохранение файла .bmp
	QAction* actionSave = new QAction("Save");
	connect(actionSave, SIGNAL(triggered()), this, SLOT(openFileDialog()));

	// Сохранение файла .bmp
	QAction* combining = new QAction("Combining");
	connect(combining, SIGNAL(triggered()), this->processingWindow, SLOT(show()));

	// изменение значений выделения при переключениии вкладки
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(selectTab(int)));

	//
	connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(slotCloseTab(int)));

	// подключение текущего виджета
	//selectTab(0);

	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(actionOpen);
	fileMenu->addAction(actionSave);
	QMenu* image = menuBar()->addMenu(tr("&Image"));
	image->addAction(combining);

	QMenu* helpMenu = menuBar()->addMenu("Help");

	centralWidget->setLayout(lauout);
	setCentralWidget(centralWidget);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	/*QMessageBox::StandardButton resBtn = QMessageBox::question(this, APP_NAME,
		tr("Are you sure?\n"),
		QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
		QMessageBox::Yes);
	if (resBtn != QMessageBox::Yes) {
		event->ignore();
	}
	else {
		event->accept();
	}*/

	event->accept();
}

void MainWindow::slotCloseTab(int index) {
	QWidget* widget = tabWidget->widget(index);
	ImgWidget* widgetToDeleted = dynamic_cast<ImgWidget*>(widget);
	disablingGraphicalWidget(widgetToDeleted);
	tabWidget->removeTab(index);
	delete widgetToDeleted;

	if (tabWidget->currentIndex() == -1){
		currentWidget = NULL;
		panelInput->isEnabled(false);
	}
}

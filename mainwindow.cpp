#include "mainwindow.h"

void MainWindow::openFileDialog() {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Выбор изображения"), "C:/", tr("Image Files (*.bmp)"));
	ImgWidget* img = new ImgWidget(fileName);
	tabWidget->addTab(img, fileName);

	window->addFile(fileName);
}

void MainWindow::openWindowCombining() {
	setEnabled(false);
	window->show();
	setEnabled(true);
}

void MainWindow::connectingGraphicWidget(ImgWidget* widget) {
	// изменение значения полей при изменениии выделения
	connect(widget->image, SIGNAL(PointRectChanged(QRect)),
		this, SLOT(changingFields(QRect)));

	// изменение значения поля x при некорректно введёном значении
	connect(widget->image, SIGNAL(PointRectChangedX(int)),
		inputFieldX, SLOT(setField(int)));

	// изменение значения поля y при некорректно введёном значении
	connect(widget->image, SIGNAL(PointRectChangedY(int)),
		inputFieldY, SLOT(setField(int)));

	// изменение значения поля ширина при некорректно введёном значении
	connect(widget->image, SIGNAL(PointRectChangedW(int)),
		inputFieldW, SLOT(setField(int)));

	// изменение значения поля высота при некорректно введёном значении
	connect(widget->image, SIGNAL(PointRectChangedH(int)),
		inputFieldH, SLOT(setField(int)));

	// изменениии выделения при изменении значения поля
	connect(inputFieldX, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectX(int)));

	// изменениии выделения при изменении значения поля
	connect(inputFieldY, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectY(int)));

	// изменениии выделения при изменении значения поля
	connect(inputFieldW, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectW(int)));

	// изменениии выделения при изменении значения поля
	connect(inputFieldH, SIGNAL(changingField(int)),
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
		inputFieldX, SLOT(setField(int)));

	// изменение значения поля y при некорректно введёном значении
	disconnect(widget->image, SIGNAL(PointRectChangedY(int)),
		inputFieldY, SLOT(setField(int)));

	// изменение значения поля ширина при некорректно введёном значении
	disconnect(widget->image, SIGNAL(PointRectChangedW(int)),
		inputFieldW, SLOT(setField(int)));

	// изменение значения поля высота при некорректно введёном значении
	disconnect(widget->image, SIGNAL(PointRectChangedH(int)),
		inputFieldH, SLOT(setField(int)));

	// изменениии выделения при изменении значения поля
	disconnect(inputFieldX, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectX(int)));

	// изменениии выделения при изменении значения поля
	disconnect(inputFieldY, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectY(int)));

	// изменениии выделения при изменении значения поля
	disconnect(inputFieldW, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectW(int)));

	// изменениии выделения при изменении значения поля
	disconnect(inputFieldH, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectH(int)));

	// отркрытие окна с информацией об ошибке
	disconnect(widget->image, SIGNAL(IncorrectSelectionSize(int, int)),
		this, SLOT(sizeErrorWindowOutput(int, int)));
}

void MainWindow::selectTab(int id) {
	if (currentWidget != NULL) {
		disablingGraphicalWidget(currentWidget);
	}
	QWidget* w = tabWidget->widget(id);
	currentWidget = dynamic_cast<ImgWidget*>(w);

	QRect rect = currentWidget->image->getRect();
	changingFields(rect);

	connectingGraphicWidget(currentWidget);
}

void MainWindow::changingFields(QRect rect) {
	inputFieldX->setField(rect.x());
	inputFieldY->setField(rect.y());
	inputFieldW->setField(rect.width());
	inputFieldH->setField(rect.height());
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

	window = new ProcessingWidget();

	tabWidget = new QTabWidget();
	lauout->addWidget(tabWidget);
	currentWidget = NULL;

	QWidget* w1 = new QWidget();
	w1->setMaximumSize(300, 1000);
	QHBoxLayout* l1 = new QHBoxLayout();
	w1->setLayout(l1);
	l1->setAlignment(Qt::AlignTop);
	lauout->addWidget(w1);

	QWidget* gridWidget = new QWidget();
	QGridLayout* layoutField = new QGridLayout();
	// поле ввода координаты
	inputFieldX = new InputField("coordinate X : ");
	layoutField->addWidget(inputFieldX, 0, 0);
	inputFieldY = new InputField("coordinate Y : ");
	layoutField->addWidget(inputFieldY, 0, 1);
	inputFieldW = new InputField("width : ");
	layoutField->addWidget(inputFieldW, 1, 0);
	inputFieldH = new InputField("height : ");
	layoutField->addWidget(inputFieldH, 1, 1);
	gridWidget->setLayout(layoutField);
	l1->addWidget(gridWidget);
	gridWidget->setMaximumSize(300, inputFieldX->sizeHint().height() * 2);

	// добавления виджета для отладки
	ImgWidget* img = new ImgWidget("C:/Users/vi/Pictures/Saved Pictures/5120x2880-UHD.bmp");
	tabWidget->addTab(img, "fileName");
	window->addFile("fileName");

	// Открытие файла .bmp
	QAction* actionOpen = new QAction("Open");
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(openFileDialog()));

	// Сохранение файла .bmp
	QAction* actionSave = new QAction("Save");
	connect(actionSave, SIGNAL(triggered()), this, SLOT(openFileDialog()));

	// Сохранение файла .bmp
	QAction* combining = new QAction("Combining");
	connect(combining, SIGNAL(triggered()), this, SLOT(openWindowCombining()));

	// изменение значений выделения при переключениии вкладки
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(selectTab(int)));

	// подключение текущего виджета
	selectTab(0);

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

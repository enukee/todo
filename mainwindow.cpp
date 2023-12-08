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

void MainWindow::creatingTab(QPixmap pixmap) {
	ImgWidget* img = new ImgWidget(pixmap);
	tabWidget->addTab(img, "new file*");
	tabWidget->setCurrentWidget(img);
}

void MainWindow::connectingGraphicWidget(ImgWidget* widget) {
	connect(widget->image, SIGNAL(PointRectChanged(QRect)),
		this, SLOT(changingFields(QRect)));

	connect(widget->image, SIGNAL(PointRectChangedX(int)),
		panelInput->inputFieldX, SLOT(setField(int)));

	connect(widget->image, SIGNAL(PointRectChangedY(int)),
		panelInput->inputFieldY, SLOT(setField(int)));

	connect(widget->image, SIGNAL(PointRectChangedW(int)),
		panelInput->inputFieldW, SLOT(setField(int)));

	connect(widget->image, SIGNAL(PointRectChangedH(int)),
		panelInput->inputFieldH, SLOT(setField(int)));

	connect(panelInput->inputFieldX, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectX(int)));

	connect(panelInput->inputFieldY, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectY(int)));

	connect(panelInput->inputFieldW, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectW(int)));

	connect(panelInput->inputFieldH, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectH(int)));

	connect(widget->image, SIGNAL(IncorrectSelectionSize(int, int)),
		this, SLOT(sizeErrorWindowOutput(int, int)));
}

void MainWindow::disablingGraphicalWidget(ImgWidget* widget) {
	disconnect(widget->image, SIGNAL(PointRectChanged(QRect)),
		this, SLOT(changingFields(QRect)));

	disconnect(widget->image, SIGNAL(PointRectChangedX(int)),
		panelInput->inputFieldX, SLOT(setField(int)));

	disconnect(widget->image, SIGNAL(PointRectChangedY(int)),
		panelInput->inputFieldY, SLOT(setField(int)));

	disconnect(widget->image, SIGNAL(PointRectChangedW(int)),
		panelInput->inputFieldW, SLOT(setField(int)));

	disconnect(widget->image, SIGNAL(PointRectChangedH(int)),
		panelInput->inputFieldH, SLOT(setField(int)));

	disconnect(panelInput->inputFieldX, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectX(int)));

	disconnect(panelInput->inputFieldY, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectY(int)));

	disconnect(panelInput->inputFieldW, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectW(int)));

	disconnect(panelInput->inputFieldH, SIGNAL(changingField(int)),
		widget->image, SLOT(setRectH(int)));

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

void MainWindow::startProcessing() {
	processingWindow->hide();
	QByteArray ba_1 = processingWindow->list1->currentText().toLocal8Bit();
	QByteArray ba_2 = processingWindow->list2->currentText().toLocal8Bit();

	char* way_1 = ba_1.data();
	char* way_2 = ba_2.data();

	QRect rect_1;
	recipientOfImageData(processingWindow->list1->currentIndex(), &rect_1);

	QRect rect_2;
	recipientOfImageData(processingWindow->list2->currentIndex(), &rect_2);

	std::string w1(way_1);
	std::string w2(way_2);

	thread = new std::thread(&MainWindow::combiningImage, this, w1, w2, rect_1, rect_2);
	thread->detach();
	/*QMessageBox msgBox;
	msgBox.setWindowTitle("The merger was successful");
	msgBox.setText("Intersection coordinates\n x:" + QString::number(coord.x) +
		tr("   \n y:") + QString::number(coord.y));
	msgBox.exec();*/
}

void MainWindow::combiningImage(std::string w1, std::string w2, QRect rect_1, QRect rect_2) {

	const char* way_1 = w1.c_str();
	const char* way_2 = w2.c_str();

	auto qrectToCoord = [](QRect rect) {
		coordinates coord;
		coord.x = rect.x();
		coord.y = rect.y();
		coord.width = rect.width();
		coord.height = rect.height();
		return coord;
		};

	ImageMatrix* combinedMatrix = matr::combiningImage(progress, way_1, way_2, qrectToCoord(rect_1), qrectToCoord(rect_2));

	QImage temp(combinedMatrix->get_width(), combinedMatrix->get_height(), QImage::Format_RGB888);

	QColor color;
	for (int y = 0; y < temp.height(); y++) {
		for (int x = 0; x < temp.width(); x++) {
			Pixel<BYTE> rgb = combinedMatrix->get_pixel(y, x);
			color.setRgb(rgb.canal_R, rgb.canal_G, rgb.canal_B);
			temp.setPixelColor(x, y, color);
		}
	}

	creatingNewTab(QPixmap::fromImage(temp));
}

MainWindow::MainWindow() {
	setWindowTitle("Merging Images");
	resize(1200, 700);
	QWidget* centralWidget = new QWidget();
	QHBoxLayout* lauout = new QHBoxLayout();

	processingWindow = new ProcessingWidget();
	progress = new ProgressBarValue();

	tabWidget = new QTabWidget();
	//tabWidget->setMovable(true);
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

	// äîáàâëåíèÿ âèäæåòà äëÿ îòëàäêè
	/*ImgWidget* img = new ImgWidget("C:/Users/vi/Pictures/Saved Pictures/5120x2880-UHD.bmp");
	tabWidget->addTab(img, "fileName");
	processingWindow->addFile("fileName");*/

	// Îòêðûòèå ôàéëà .bmp
	QAction* actionOpen = new QAction("Open");
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(openFileDialog()));

	// Ñîõðàíåíèå ôàéëà .bmp
	QAction* actionSave = new QAction("Save");
	connect(actionSave, SIGNAL(triggered()), this, SLOT(openFileDialog()));

	// Ñîõðàíåíèå ôàéëà .bmp
	QAction* combining = new QAction("Combining");
	connect(combining, SIGNAL(triggered()), processingWindow, SLOT(show()));

	// èçìåíåíèå çíà÷åíèé âûäåëåíèÿ ïðè ïåðåêëþ÷åíèèè âêëàäêè
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(selectTab(int)));

	//
	connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(slotCloseTab(int)));

	connect(processingWindow->processingButton, SIGNAL(clicked()), this, SLOT(startProcessing()));

	connect(this, SIGNAL(creatingNewTab(QPixmap)), this, SLOT(creatingTab(QPixmap)));

	connect(progress, SIGNAL(valueChange(int)), panelInput, SLOT(progressChange(int)));

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

void MainWindow::recipientOfImageData(int index, QRect* rect) {
	QWidget* widget = tabWidget->widget(index);
	ImgWidget* currentWidget = dynamic_cast<ImgWidget*>(widget);

	*rect = currentWidget->image->getRect();
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
	delete widget;

	processingWindow->deleteItem(index);

	if (tabWidget->currentIndex() == -1) {
		currentWidget = NULL;
		panelInput->isEnabled(false);
	}
}

#include "processingWidget.h"
#include "BmpFile.h"

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
	connect(processingButton, SIGNAL(clicked()), this, SLOT(imageProcessing()));
}

void ProcessingWidget::imageProcessing() {
	QByteArray ba_1 = list1->currentText().toLocal8Bit();
	QByteArray ba_2 = list2->currentText().toLocal8Bit();

	char* way_1 = ba_1.data();
	char* way_2 = ba_2.data();
	BmpFile img_1(way_1);
	BmpFile img_2(way_2);

	auto qrectToCoord = [](QRect rect) {
		coordinates coord;
		coord.x = rect.x();
		coord.y = rect.y();
		coord.width = rect.width();
		coord.height = rect.height();
		return coord;
		};

	QRect rect_1;
	emit getterDataForProcessing(list1->currentIndex(), &rect_1);

	QRect rect_2;
	emit getterDataForProcessing(list2->currentIndex(), &rect_2);

	// Создаём матрицу части изображения img_1
	ImageMatrix Bitmap_1(rect_1.height(), rect_1.width());
	// Записываем в неё нужный фрагмент
	Bitmap_1.cut_out(&img_1, rect_1.y(), rect_1.x());

	// Создаём матрицу части изображения img_2
	ImageMatrix Bitmap_2(rect_2.height(), rect_2.width());
	// Записываем в неё нужный фрагмент
	Bitmap_2.cut_out(&img_2, rect_2.y(), rect_2.x());

	unsigned int Height = Bitmap_2.get_height();
	unsigned int search_area_h = Bitmap_1.get_height() - Height + 1;

	coordinates coord;
	bool similar = 0;
	Bitmap_1.search_inside_img(&Bitmap_2, 0, search_area_h, &similar, &coord);

	coord.x += rect_1.x();
	coord.y += rect_1.y();

	QMessageBox msgBox;
	msgBox.setWindowTitle("The merger was successful");
	msgBox.setText("Intersection coordinates\n x:" + QString::number(coord.x) + 
		tr("   \n y:") + QString::number(coord.y));
	msgBox.exec();

	ImageMatrix* combinedMatrix = new ImageMatrix(&img_1, &img_2, coord, qrectToCoord(rect_2));

	QImage temp(combinedMatrix->get_width(), combinedMatrix->get_height(), QImage::Format_RGB888);

	QColor color;
	for (int y = 0; y < temp.height(); y++) {
		for (int x = 0; x < temp.width(); x++) {
			Pixel<BYTE> rgb = combinedMatrix->get_pixel(y, x);
			color.setRgb(rgb.canal_R, rgb.canal_G, rgb.canal_B);
			temp.setPixelColor(x, y, color);
		}
	}
	
	emit creatingNewTab(QPixmap::fromImage(temp));
}

void ProcessingWidget::deleteItem(int index) {
	list1->removeItem(index);
	list2->removeItem(index);
}

void ProcessingWidget::addFile(QString fileName) {
	list1->addItem(fileName);
	list2->addItem(fileName);
}
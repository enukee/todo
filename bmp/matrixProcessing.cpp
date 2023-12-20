#include "matrixProcessing.h"

ImageMatrix* matr::combiningImage(ProgressBarValue* progress, const char* w1, const char* w2, coordinates rect_1, coordinates rect_2) {
	BmpFile img_1(w1);
	BmpFile img_2(w2);

	ImageMatrix Bitmap_1(rect_1.height, rect_1.width);
	// Записываем в неё нужный фрагмент
	Bitmap_1.cut_out(&img_1, rect_1.y, rect_1.x);

	// Создаём матрицу части изображения img_2
	ImageMatrix Bitmap_2(rect_2.height, rect_2.width);
	// Записываем в неё нужный фрагмент
	Bitmap_2.cut_out(&img_2, rect_2.y, rect_2.x);

	// начльно значение  progressBar
	progress->setValue(0);

	unsigned int Height = Bitmap_2.get_height();
	unsigned int search_area_h = Bitmap_1.get_height() - Height + 1;

	coordinates coord;
	bool similar = 0;
	search_inside_img(progress, &Bitmap_1, &Bitmap_2, 0, search_area_h, &similar, &coord);

	// максимальное значение progressBar для этого этапа вычислений
	progress->setValue(80);

	if (similar) {
		coord.x += rect_1.x;
		coord.y += rect_1.y;
		coord.width = rect_2.width;
		coord.height = rect_2.height;

		brightness_correction(progress, &img_1, &img_2, coord, rect_2);

		ImageMatrix* combinedMatrix = matr::combiningMatrices(progress, &img_1, &img_2, coord, rect_2);

		// конечное значение  progressBar
		progress->setValue(100);
		return combinedMatrix;
	}
	return nullptr;
}

ImageMatrix* matr::combiningMatrices(ProgressBarValue* progress, ImageMatrix* img_1, ImageMatrix* img_2, coordinates coord_1, coordinates coord_2) {
	coordinates coord_general_image_1;
	coordinates coord_general_image_2;

	unsigned int Height;
	unsigned int Width;

	if (coord_1.x < coord_2.x) {
		coord_general_image_1.x = coord_2.x - coord_1.x;
		Width = img_1->get_width() + coord_general_image_1.x;
	}
	else {
		coord_general_image_2.x = coord_1.x - coord_2.x;
		Width = img_2->get_width() + coord_general_image_2.x;
	}

	if (coord_1.y < coord_2.y) {
		coord_general_image_1.y = coord_2.y - coord_1.y;
		Height = img_1->get_height() + coord_general_image_1.y;
	}
	else {
		coord_general_image_2.y = coord_1.y - coord_2.y;
		Height = img_2->get_height() + coord_general_image_2.y;
	}

	ImageMatrix* Bitmap = new ImageMatrix(Height, Width);

	Bitmap->recording(img_2, coord_general_image_2.y, coord_general_image_2.x);

	Bitmap->recording(img_1, coord_general_image_1.y, coord_general_image_1.x);

	return Bitmap;
}

void matr::search_inside_img(ProgressBarValue* progress, ImageMatrix* Bitmap1, ImageMatrix* Bitmap2, unsigned int a, unsigned int b, bool* similar, coordinates* coord) {
	unsigned int Height = Bitmap2->get_height();
	unsigned int Width = Bitmap2->get_width();

	unsigned int search_area_w = Bitmap1->get_width() - Width + 1;
	unsigned int search_area_h = Bitmap1->get_height() - Height + 1;

	// координаты пересечения
	coordinates coord_img;

	// флаг(было найдено хотя бы одно значение корреляции больше максимального)
	bool flag = 0;

	// структура хранения значений коэффициента корреляции для каждого канала
	Pixel<double> coef_cor;
	Pixel<double> max_coef_cor;
	max_coef_cor.canal_R = 0.7;
	max_coef_cor.canal_G = 0.7;
	max_coef_cor.canal_B = 0.7;

	// inc - Шаг увеличения progressBar (80 максимальное увеличение progressBar) 
	double inc = 80.0 / ((double)search_area_w * (double)search_area_h);
	// начальное значение progressBar
	double progValue = progress->getValue();

	for (unsigned int i = a; i < b; i++) {
		for (unsigned int j = 0; j < search_area_w; j++) {
			coef_cor = Bitmap1->finding_cor(i, j, *Bitmap2);

			progValue += inc;
			progress->setValue(progValue);

			if (*similar) return;

			if (coef_cor > max_coef_cor) {
				max_coef_cor = coef_cor;
				coord_img.x = j;
				coord_img.y = i;
				flag = 1;
			}

			if (coef_cor > 0.8) {
				*similar = 1;
				*coord = coord_img;
				return;
			}
		}

		if (progress->isProcessStopped()) return;
	}


	*similar = flag;
	*coord = coord_img;
	return;
}

// метод корректирования яркости
void matr::brightness_correction(ProgressBarValue* progress, BmpFile* img_1, BmpFile* img_2, coordinates coord_img_1, coordinates coord_img_2) {

	// создание матрицы части пересечения первого изображения
	ImageMatrix Bitmap_1(coord_img_1.height, coord_img_1.width);

	// заполнения первой матрицы 
	Bitmap_1.cut_out(img_1, coord_img_1.y, coord_img_1.x);

	// создание матрицы части пересечения второго изображения
	ImageMatrix Bitmap_2(coord_img_2.height, coord_img_2.width);

	// заполнения второй матрицы 
	Bitmap_2.cut_out(img_2, coord_img_2.y, coord_img_2.x);

	Pixel<double> sco_1 = Bitmap_1.finding_sd();
	Pixel<double> sco_2 = Bitmap_2.finding_sd();
	Pixel<double> mo_1 = Bitmap_1.finding_avg();
	Pixel<double> mo_2 = Bitmap_2.finding_avg();


	Pixel<double> sco;
	Pixel<double> mo;

	if (((sco_1.canal_R > -0.5) && (sco_1.canal_R < 0.5)) || ((sco_2.canal_R > -0.5) && (sco_2.canal_R < 0.5))) {
		sco.canal_R = 1;
	}
	else {
		sco.canal_R = sco_1.canal_R / sco_2.canal_R;
	}

	if (((sco_1.canal_G > -0.5) && (sco_1.canal_G < 0.5)) || ((sco_2.canal_G > -0.5) && (sco_2.canal_G < 0.5))) {
		sco.canal_G = 1;
	}
	else {
		sco.canal_G = sco_1.canal_G / sco_2.canal_G;
	}

	if (((sco_1.canal_B > -0.5) && (sco_1.canal_B < 0.5)) || ((sco_2.canal_B > -0.5) && (sco_2.canal_B < 0.5))) {
		sco.canal_B = 1;
	}
	else {
		sco.canal_B = sco_1.canal_B / sco_2.canal_B;
	}

	mo = mo_1 - (mo_2 * sco);

	Pixel<BYTE> byte;
	unsigned int height = img_2->get_height();
	unsigned int width = img_2->get_width();

	// inc - Шаг увеличения progressBar (20 максимальное увеличение progressBar) 
	double inc = (double)20 / ((double)height * (double)width);
	// начально значение rogressBar 
	double progValue = progress->getValue();
	auto color_correction = [](Pixel<double> pixel, Pixel<double>sco, Pixel<double>mo) {
		Pixel<double> value;
		value = pixel * sco + mo;

		Pixel<BYTE> pixel_1;
		pixel_1 = value.to_BYTE();

		return pixel_1;
	};

	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			byte = img_2->get_pixel(i, j);
			byte = color_correction(byte.to_double(), sco, mo);
			img_2->set_pixel(byte, i, j);

			progValue += inc;
			progress->setValue(progValue);
		}

		if (progress->isProcessStopped()) return;
	}
}
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
	progress->setValue(10);

	unsigned int Height = Bitmap_2.get_height();
	unsigned int search_area_h = Bitmap_1.get_height() - Height + 1;

	coordinates coord;
	bool similar = 0;
	search_inside_img(progress, &Bitmap_1, &Bitmap_2, 0, search_area_h, &similar, &coord);

	coord.x += rect_1.x;
	coord.y += rect_1.y;

	ImageMatrix* combinedMatrix = matr::combiningMatrices(progress, &img_1, &img_2, coord, rect_2);

	return combinedMatrix;
}

ImageMatrix* matr::combiningMatrices(ProgressBarValue* progress, ImageMatrix* img_1, ImageMatrix* img_2, coordinates coord_1, coordinates coord_2) {
	coordinates coord_general_image_1;
	coordinates coord_general_image_2;

	unsigned int Height;
	unsigned int Width;

	progress->setValue(95);

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

	progress->setValue(100);
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
	max_coef_cor.canal_R = 0.5;
	max_coef_cor.canal_G = 0.5;
	max_coef_cor.canal_B = 0.5;

	double inc = (double)60 / ((double)search_area_w * (double)search_area_h);
	double progValue = 10;

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
	}
	progress->setValue(60);

	*similar = flag;
	*coord = coord_img;
	return;
}
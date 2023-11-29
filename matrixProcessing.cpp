#include "matrixProcessing.h"

ImageMatrix* matr::combiningMatrices(ImageMatrix* img_1, ImageMatrix* img_2, coordinates coord_1, coordinates coord_2) {
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

ImageMatrix* matr::combiningImage(const char* w1, const char* w2, coordinates rect_1, coordinates rect_2) {

	BmpFile img_1(w1);
	BmpFile img_2(w2);

	ImageMatrix Bitmap_1(rect_1.height, rect_1.width);
	// Записываем в неё нужный фрагмент
	Bitmap_1.cut_out(&img_1, rect_1.y, rect_1.x);

	// Создаём матрицу части изображения img_2
	ImageMatrix Bitmap_2(rect_2.height, rect_2.width);
	// Записываем в неё нужный фрагмент
	Bitmap_2.cut_out(&img_2, rect_2.y, rect_2.x);

	unsigned int Height = Bitmap_2.get_height();
	unsigned int search_area_h = Bitmap_1.get_height() - Height + 1;

	coordinates coord;
	bool similar = 0;
	Bitmap_1.search_inside_img(&Bitmap_2, 0, search_area_h, &similar, &coord);

	coord.x += rect_1.x;
	coord.y += rect_1.y;

	ImageMatrix* combinedMatrix = matr::combiningMatrices(&img_1, &img_2, coord, rect_2);

	return combinedMatrix;
}
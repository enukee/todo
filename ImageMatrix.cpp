#pragma once

#include "ImageMatrix.h"
#define ALING4(x) ((((x)-1)/4+1)*4)

ImageMatrix::ImageMatrix() {
}

ImageMatrix::ImageMatrix(unsigned int height, unsigned int width) {
	img_Height = height;
	img_Width = width;

	matrix = new Pixel<BYTE> *[img_Height];
	for (unsigned int i = 0; i < img_Height; i++) {
		matrix[i] = new Pixel<BYTE>[img_Width];
	}
}

ImageMatrix::ImageMatrix(ImageMatrix* img_1, ImageMatrix* img_2, coordinates coord_1, coordinates coord_2) {
	unsigned int Height;
	unsigned int Width;

	coordinates coord_general_image_1;
	coordinates coord_general_image_2;

	if (coord_1.x < coord_2.x) {
		coord_general_image_1.x = coord_2.x - coord_1.x;
		coord_general_image_2.x = 0;
		Width = img_1->get_width() + coord_general_image_1.x;
	}

	if (coord_1.x > coord_2.x) {
		coord_general_image_1.x = 0;
		coord_general_image_2.x = coord_1.x - coord_2.x;
		Width = img_2->get_width() + coord_general_image_2.x;
	}

	if (coord_1.y < coord_2.y) {
		coord_general_image_1.y = coord_2.y - coord_1.y;
		coord_general_image_2.y = 0;
		Height = img_1->get_height() + coord_general_image_1.y;
	}

	if (coord_1.y > coord_2.y) {
		coord_general_image_1.y = 0;
		coord_general_image_2.y = coord_1.y - coord_2.y;
		Height = img_2->get_height() + coord_general_image_2.y;
	}

	img_Height = Height;
	img_Width = Width;

	matrix = new Pixel<BYTE> *[img_Height];
	for (unsigned int i = 0; i < img_Height; i++) {
		matrix[i] = new Pixel<BYTE>[img_Width];
	}

	recording(img_2, coord_general_image_2.y, coord_general_image_2.x);

	recording(img_1, coord_general_image_1.y, coord_general_image_1.x);
}

ImageMatrix::~ImageMatrix() {
	for (unsigned int i = 0; i < img_Height; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

// pixel setter
void ImageMatrix::set_pixel(Pixel<BYTE> value, unsigned int i, unsigned int j) {
	matrix[i][j] = value;
}

// pixel setter (separately by channels)
void ImageMatrix::set_pixel(BYTE canal_R, BYTE canal_G, BYTE canal_B, unsigned int i, unsigned int j) {
	matrix[i][j].canal_R = canal_R;
	matrix[i][j].canal_G = canal_G;
	matrix[i][j].canal_B = canal_B;
}

// pixel getter
Pixel<BYTE> ImageMatrix::get_pixel(unsigned int i, unsigned int j) {
	return matrix[i][j];
}

// matrix row getter
void ImageMatrix::get_row_matrix(Pixel<BYTE>* matr, unsigned int i) {
	for (unsigned int j = 0; j < img_Width; j++) {
		matr[j] = matrix[i][j];
	}
}

// getter of the matrix string 
// (with a slice starting from s_1 character of the string s_2 character of the string)
void ImageMatrix::get_row_matrix(Pixel<BYTE>* matr, unsigned int i, unsigned int s_1, unsigned int s_2) {
	for (unsigned int j = 0; j < s_2; j++) {
		matr[j] = matrix[i][s_1 + j];
	}
  }

// image height getter
unsigned int ImageMatrix::get_height() {
	return img_Height;
}

// image width getter
unsigned int ImageMatrix::get_width() {
	return img_Width;
}

// zeroing the matrix
void ImageMatrix::zeroing() {
	for (unsigned int i = 0; i < img_Height; i++) {
		for (unsigned int j = 0; j < img_Width; j++) {
			matrix[i][j].zeroing();
		}
	}
}

// writes the Bitmap matrix to the matrix (starting from the matrix[x][y] position)
void ImageMatrix::recording(ImageMatrix* Bitmap, unsigned int y, unsigned int x) {
	for (unsigned int i = 0; i < Bitmap->get_height(); i++) {
		for (unsigned int j = 0; j < Bitmap->get_width(); j++) {
			matrix[i + y][j + x] = Bitmap->matrix[i][j];
		}
	}
}

// filling the matrix with the values 
// of the Bitmap matrix (starting from the position Bitmap[x][y])
void ImageMatrix::cut_out(ImageMatrix* Bitmap, unsigned int y, unsigned int x) {
	for (unsigned int i = 0; i < img_Height; i++) {
		for (unsigned int j = 0; j < img_Width; j++) {
			matrix[i][j] = (*Bitmap).matrix[i + y][j + x];
		}
	}
}

// Search function for the average value of the array 
Pixel<double> ImageMatrix::finding_avg() { 
	Pixel<double> avg;

	for (unsigned int i = 0; i < img_Height; i++) {
		for (unsigned int j = 0; j < img_Width; j++) {
			avg += matrix[i][j].to_double();
		}
	}
	avg /= img_Height;
	avg /= img_Width;

	return avg;
}

// the function of searching for the standard deviation of the array
Pixel<double> ImageMatrix::finding_sd() {
	Pixel<double> sd;
	Pixel<double> _avg = finding_avg();

	for (unsigned int i = 0; i < img_Height; i++) {
		for (unsigned int j = 0; j < img_Width; j++) {
			sd += ((matrix[i][j].to_double() - _avg) * (matrix[i][j].to_double() - _avg));
		}
	}
	sd /= img_Height;
	sd /= img_Width;
	sd = pixel_sqrt(sd);

	return sd;
}

// The function of searching for the average value of array 
// elements in an area of size w * h, starting from the coordinates x, y
Pixel<double> ImageMatrix::finding_avg(unsigned int x, unsigned int y, unsigned int w, unsigned int h) { 
	Pixel<double> avg;

	for (unsigned int i = y; i < y + h; i++) {
		for (unsigned int j = x; j < x + w; j++) {
			avg += matrix[i][j].to_double();
		}
	}
	avg /= h;
	avg /= w;

	return avg;
}

// the search function is the standard deviation 
// of the array elements into an area of size w * h, starting from the x, y coordinates
Pixel<double> ImageMatrix::finding_sd(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	Pixel<double> sd;
	Pixel<double> _avg = finding_avg(x, y, w, h);

	for (unsigned int i = y; i < y + h; i++) {
		for (unsigned int j = x; j < x + w; j++) {
			sd += ((matrix[i][j].to_double() - _avg) * (matrix[i][j].to_double() - _avg));
		}
	}
	sd /= h;
	sd /= w;
	sd = pixel_sqrt(sd);

	return sd;
}

// image correlation coefficient search
Pixel<double> ImageMatrix::finding_cor(unsigned int y, unsigned int x, ImageMatrix& matr) {
	unsigned int Height = matr.get_height();
	unsigned int Width = matr.get_width();

	Pixel<double> avg_1 = finding_avg(x, y, Width, Height);
	Pixel<double> avg_2 = matr.finding_avg();

	Pixel<double> avg_1_2;
	for (unsigned int i = 0; i < Height; i++) {
		for (unsigned int j = 0; j < Width; j++) {
			avg_1_2 += matrix[i + y][j + x].to_double() * matr.matrix[i][j].to_double();
		}
	}
	avg_1_2 /= Height * Width;

	Pixel<double> sd_1 = finding_sd(x, y, Width, Height);
	Pixel<double> sd_2 = matr.finding_sd();

	Pixel<double> kof_kor;
	kof_kor = (avg_1_2 - avg_1 * avg_2) / (sd_1 * sd_2);

	return kof_kor;
}

//поиск коэффициента коррел€ции с матрицей matr (x и y позици€ matr внутри данной матрицы)
//boolean ImageMatrix::finding_correlation(Pixel<double>& coef_cor, unsigned int x, unsigned int y, ImageMatrix& matr) {
//	unsigned int Height = matr.get_height();
//	unsigned int Width = matr.get_width();
//
//	// коэффициент коррел€ции строк матриц
//	Pixel<double> coef_cor_str;
//
//	class RowOfPixels {
//	public:
//		Pixel<BYTE>* Bitmap;
//
//		RowOfPixels(unsigned int Width);
//		~RowOfPixels();
//	};
//
//	ImageString Bitmap_im_1(Width);
//	ImageString Bitmap_im_2(Width);
//
//	for (unsigned int t = 0; t < Height; t++) {
//		get_row_matrix(Bitmap_im_1.mass, x + t, y, Width);
//		matr.get_row_matrix(Bitmap_im_2.mass, t);
//		coef_cor_str = Bitmap_im_2.kcor(Bitmap_im_1.mass, Bitmap_im_2.mass, Width);
//		coef_cor += coef_cor_str;
//		if (((coef_cor_str.canal_R < 0.6) ||
//			(coef_cor_str.canal_G < 0.6) ||
//			(coef_cor_str.canal_B < 0.6))) {
//			return 0;
//		}
//	}
//	coef_cor /= Height;
//
//	return 1;
//}

// search inside the matrix of coordinates of the location of the Bitmap matrix
void ImageMatrix::search_inside_img(ImageMatrix* Bitmap, unsigned int a, unsigned int b, bool* similar, coordinates* coord) {
	unsigned int Height = Bitmap->get_height();
	unsigned int Width = Bitmap->get_width();

	unsigned int search_area_w = get_width() - Width + 1;

	// координаты пересечени€
	coordinates coord_img;

	// флаг(было найдено хот€ бы одно значение коррел€ции больше максимального)
	bool flag = 0;

	// структура хранени€ значений коэффициента коррел€ции дл€ каждого канала
	Pixel<double> coef_cor;
	Pixel<double> max_coef_cor;
	max_coef_cor.canal_R = 0.5;
	max_coef_cor.canal_G = 0.5;
	max_coef_cor.canal_B = 0.5;
	
	for (unsigned int i = a; i < b; i++) {
		for (unsigned int j = 0; j < search_area_w; j++) {
			coef_cor = finding_cor(i, j, *Bitmap);

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

	*similar = flag;
	*coord = coord_img;
	return;
}
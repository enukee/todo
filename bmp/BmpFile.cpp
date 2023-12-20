#include "BmpFile.h" 

using namespace std;
#define ALING4(x) ((((x)-1)/4+1)*4) //Макрос - дополнение величины до ближайшей кратной 4

BmpFile::BmpFile(const char* way) : ImageMatrix() {
	//std::fstream
	hFile = _lopen(way, OF_READ);
	if (hFile != HFILE_ERROR) //Если файл открылся нормально
	{
		_lread(hFile, (char*)&File, sizeof(File));
		_lread(hFile, (char*)&Head, sizeof(Head));

		img_Height = Head.biHeight;
		img_Width = Head.biWidth; 

		matrix = new Pixel<BYTE> *[img_Height];
		for (unsigned int i = 0; i < img_Height; i++) {
			matrix[i] = new Pixel<BYTE>[img_Width];
		}

		char empty_bytes[4] = { 0 };
		int w = ALING4(img_Width * 3) - img_Width * 3;
		BYTE* srok =new BYTE[img_Width*3];
		for (int i = img_Height - 1; i >= 0; i--) {
			_lread(hFile, (char*)srok, img_Width * 3);

			bmp_into_pixel_matrix(i, srok);

			_lread(hFile, (char*)&empty_bytes, w);
		}
	}
}

BmpFile::BmpFile(ImageMatrix* Bitmap) : ImageMatrix(Bitmap->get_height(),Bitmap->get_width()) {
	for (unsigned int i = 0; i < img_Height; i++) {
		for (unsigned int j = 0; j < img_Width; j++) {
			matrix[i][j].canal_R = Bitmap->get_pixel(i, j).canal_R;
			matrix[i][j].canal_G = Bitmap->get_pixel(i, j).canal_G;
			matrix[i][j].canal_B = Bitmap->get_pixel(i, j).canal_B;
		}
	}

	//Заполнение структуры нулевыми значениями
	ZeroMemory(&Head, sizeof(Head));

	//Заполнение необходимых полей параметров растра
	Head.biSize = 40;
	Head.biHeight = img_Height;
	Head.biWidth = img_Width;
	Head.biSizeImage = img_Height + img_Width * 3;
	Head.biPlanes = 1;
	Head.biBitCount = 24;

	//Заполнение структуры заголовка файла
	File.bfOffBits = sizeof(Head) + sizeof(File);
	File.bfSize = sizeof(File) + sizeof(Head) + img_Height * img_Width * 3;
	File.bfType = 'B' + (int)'M' * 256;
}

void BmpFile::bmp_writer(char* way) {
	char empty_bytes[4] = { 0 };
	int w = ALING4(img_Width * 3) - img_Width * 3;
	BYTE* srok = new BYTE[img_Width * 3];

	hFile = _lcreat(way, 0);
	if (hFile != HFILE_ERROR)
	{
		Pixel<BYTE> pixel;
		_lwrite(hFile, (const char*)&File, sizeof(File));
		_lwrite(hFile, (const char*)&Head, sizeof(Head));
		for (int i = img_Height - 1; i >= 0; i--) {
			pixel_matrix_in_bmp(i, srok);

			_lwrite(hFile, (const char*)srok, img_Width * 3);

			_lwrite(hFile, empty_bytes, w);
		}

		_lclose(hFile);

	}
}

void BmpFile::pixel_matrix_in_bmp(unsigned int i, BYTE* strok) {
	for (unsigned int j = 0; j < img_Width; j++) {
		strok[j * 3] = matrix[i][j].canal_B;
		strok[j * 3 + 1] = matrix[i][j].canal_G;
		strok[j * 3 + 2] = matrix[i][j].canal_R;
	}
}

void BmpFile::bmp_into_pixel_matrix(unsigned int i, BYTE* strok) {
	for (unsigned int j = 0; j < img_Width ; j++) {
		matrix[i][j].canal_B = strok[j * 3];
		matrix[i][j].canal_G = strok[j * 3 + 1];
		matrix[i][j].canal_R = strok[j * 3 + 2];
	}
}

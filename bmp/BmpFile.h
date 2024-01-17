#pragma once

#include "ImageMatrix.h"

class BmpFile : public ImageMatrix{
private:
	BITMAPFILEHEADER  File;       //��������� ���������� �����
	BITMAPINFOHEADER  Head;       //��������� ���������� ������
	HFILE hFile;

	void pixel_matrix_in_bmp(unsigned int i, BYTE* strok);
	void bmp_into_pixel_matrix(unsigned int i, BYTE* strok);

	// ���������� value �� ���������� �������� ����� �������� 4
	int aling4(int value);

public:

	BmpFile(const char* way);
	BmpFile(ImageMatrix* Bitmap);

	void bmp_writer(char* way);	
};

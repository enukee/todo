#include "BmpFile.h"

namespace matr {
	// constructor of a matrix consisting of 2 matrices img_1 and img_2, 
	// where coord_1 and coord_2 are the coordinates of a single point
	ImageMatrix* combiningMatrices(ImageMatrix* img_1, ImageMatrix* img_2, coordinates coord_1, coordinates coord_2);

	ImageMatrix* combiningImage(const char* w1, const char* w2, coordinates rect_1, coordinates rect_2);
}
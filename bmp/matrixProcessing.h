#include "BmpFile.h"
#include "progressValue.h"

namespace matr {
	// constructor of a matrix consisting of 2 matrices img_1 and img_2, 
	// where coord_1 and coord_2 are the coordinates of a single point
	ImageMatrix* combiningMatrices(ProgressBarValue* progress, ImageMatrix* img_1, ImageMatrix* img_2, coordinates coord_1, coordinates coord_2);

	ImageMatrix* combiningImage(ProgressBarValue* progress, const char* w1, const char* w2, coordinates rect_1, coordinates rect_2);

	void search_inside_img(ProgressBarValue* progress, ImageMatrix* Bitmap1, ImageMatrix* Bitmap2, unsigned int a, unsigned int b, bool* similar, coordinates* coord);

	void brightness_correction(ProgressBarValue* progress, BmpFile* img_1, BmpFile* img_2, coordinates coord_img_1, coordinates coord_img_2);

}
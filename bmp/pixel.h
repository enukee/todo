#pragma once 
#include <cmath>  
#include "windows.h"

struct coordinates {
	int x = 0;
	int y = 0;

	int width = 0;
	int height = 0;

	coordinates operator = (coordinates value) {
		x = value.x;
		y = value.y;

		return value;
	}

	void set_coord(int coord_x, int coord_y) {
		x = coord_x;
		y = coord_y;

	}
};

template<typename Type>
struct Pixel {
	Type canal_R = 0;
	Type canal_G = 0;
	Type canal_B = 0;

	Pixel<Type> operator = (Pixel<Type> value) {
		canal_R = value.canal_R;
		canal_G = value.canal_G;
		canal_B = value.canal_B;

		return value;
	}

	Pixel<Type> operator + (Pixel<Type> oper_2) {
		Pixel<Type> value;
		value.canal_R = canal_R + oper_2.canal_R;
		value.canal_G = canal_G + oper_2.canal_G;
		value.canal_B = canal_B + oper_2.canal_B;

		return value;
	}

	Pixel<Type> operator - (Pixel<Type> oper_2) {
		Pixel<Type> value;
		value.canal_R = canal_R - oper_2.canal_R;
		value.canal_G = canal_G - oper_2.canal_G;
		value.canal_B = canal_B - oper_2.canal_B;

		return value;
	}

	Pixel<Type> operator * (Pixel<Type> oper_2) {
		Pixel<Type> value;
		value.canal_R = canal_R * oper_2.canal_R;
		value.canal_G = canal_G * oper_2.canal_G;
		value.canal_B = canal_B * oper_2.canal_B;

		return value;
	}

	Pixel<Type> operator / (Pixel<Type> oper_2) {
		Pixel<Type> value;
		value.canal_R = canal_R / oper_2.canal_R;
		value.canal_G = canal_G / oper_2.canal_G;
		value.canal_B = canal_B / oper_2.canal_B;

		return value;
	}

	bool operator > (Pixel<Type> oper_2) {
		return ((canal_R > oper_2.canal_R) &&
			(canal_G > oper_2.canal_G) &&
			(canal_B > oper_2.canal_B));
	}

	bool operator > (Type value) {
		return ((canal_R > value) &&
			(canal_G > value) &&
			(canal_B > value));
	}

	bool operator < (Pixel<Type> oper_2) {
		return ((canal_R < oper_2.canal_R) &&
			(canal_G < oper_2.canal_G) &&
			(canal_B < oper_2.canal_B));
	}

	bool operator < (Type value) {
		return ((canal_R < value) &&
			(canal_G < value) &&
			(canal_B < value));
	}

	void operator += (Pixel<Type> value) {
		canal_R += value.canal_R;
		canal_G += value.canal_G;
		canal_B += value.canal_B;
	}

	void operator -= (Pixel<Type> value) {
		canal_R -= value.canal_R;
		canal_G -= value.canal_G;
		canal_B -= value.canal_B;
	}

	void operator *= (Pixel<Type> value) {
		canal_R *= value.canal_R;
		canal_G *= value.canal_G;
		canal_B *= value.canal_B;
	}

	void operator /= (Pixel<Type> value) {
		canal_R /= value.canal_R;
		canal_G /= value.canal_G;
		canal_B /= value.canal_B;
	}

	void operator += (Type value) {
		canal_R += value;
		canal_G += value;
		canal_B += value;
	}

	void operator -= (Type value) {
		canal_R -= value;
		canal_G -= value;
		canal_B -= value;
	}

	void operator *= (Type value) {
		canal_R *= value;
		canal_G *= value;
		canal_B *= value;
	}

	void operator /= (Type value) {
		canal_R /= value;
		canal_G /= value;
		canal_B /= value;
	}

	Pixel<double> to_double() {
		Pixel<double> res;
		res.canal_R = (double)canal_R;
		res.canal_G = (double)canal_G;
		res.canal_B = (double)canal_B;

		return res;
	}

	Pixel<BYTE> to_BYTE() {
		if (canal_R > 255) {
			canal_R = 255;
		}
		else if (canal_R < 0) {
			canal_R = 0;
		}

		if (canal_G > 255) {
			canal_G = 255;
		}
		else if (canal_G < 0) {
			canal_G = 0;
		}

		if (canal_B > 255) {
			canal_B = 255;
		}
		else if (canal_B < 0) {
			canal_B = 0;
		}

		Pixel<BYTE> res;
		res.canal_R = (BYTE)canal_R;
		res.canal_G = (BYTE)canal_G;
		res.canal_B = (BYTE)canal_B;

		return res;
	}

	void zeroing() {
		canal_R = 0;
		canal_G = 0;
		canal_B = 0;
	}
};

// возведение в степень Pixel
template<typename Type>
Pixel<Type> pixel_pow(Pixel<Type> value, int d) {
	Pixel<Type> res;
	res.canal_R = pow(value.canal_R, d);
	res.canal_G = pow(value.canal_G, d);
	res.canal_B = pow(value.canal_B, d);

	return res;
}

// кореень квадратный от Pixel
template<typename Type>
Pixel<Type> pixel_sqrt(Pixel<Type> value) {
	Pixel<Type> res;
	res.canal_R = sqrt(value.canal_R);
	res.canal_G = sqrt(value.canal_G);
	res.canal_B = sqrt(value.canal_B);

	return res;
}

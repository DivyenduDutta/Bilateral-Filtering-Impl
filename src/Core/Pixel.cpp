#include "Pixel.h"
#include <cmath>

Pixel::Pixel() : X(0), Y(0) {}

Pixel::Pixel(int x, int y) : X(x), Y(y){}

int Pixel::getX() const {
	return X;
}

int Pixel::getY() const {
	return Y;
}

float Pixel::l2_norm(Pixel dest) const {
	return sqrt(
				pow((X - dest.getX()),2) 
								+ 
				   pow((Y - dest.getY()),2)
	       );
}
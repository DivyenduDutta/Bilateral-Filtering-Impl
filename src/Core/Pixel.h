#pragma once

class Pixel {
private:
	int X;
	int Y;

public:
	Pixel();
	Pixel(int, int);
	int getX() const;
	int getY() const;
	float l2_norm(Pixel) const;
};

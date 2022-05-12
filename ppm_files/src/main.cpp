#include <iostream>
#include "image.h"
#include "image_manipulation.h"

int main() {
	Image image;
	if (imgman::loadImage(&image, "in.ppm")) {
		imgman::invert(&image);
		image.save("out.ppm");
	};

	return 0;
}

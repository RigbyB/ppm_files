#pragma once

#include "image.h"

namespace imgman {
	void genColoredImage(Image* image, int width, int height, Pixel color);
	bool loadImage(Image* image, const char* path);
	void invert(Image* image);
}

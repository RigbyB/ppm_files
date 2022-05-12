#include "image.h"
#include "image_manipulation.h"
#include <fstream>

Image::Image(): width_(100), height_(100) {
	imgman::genColoredImage(this, getSize().width, getSize().height, {0, 0, 0});
}

Image::Image(int width, int height, Pixel*** pixels) : width_(width), height_(height), pixels_(pixels) {}

Image::~Image() {
	for (int y = 0; y < getSize().height; y++) {
		for (int x = 0; x < getSize().width; x++) {
			delete pixels_[y][x];
		}
		delete[] pixels_[y];
	}
	delete[] pixels_;
}

Pixel Image::getPixel(int x, int y) {
	if (x < 0 || y < 0 || x > getSize().width || y > getSize().height)
		return {-1, -1, -1};

	return *pixels_[y][x];
}

ImageSize Image::getSize() {
	return {width_, height_};
}

void Image::setPixel(int x, int y, Pixel color) {
	if (x < 0 || y < 0 || x > getSize().width || y > getSize().height)
		return;

	*pixels_[y][x] = color;
}

void Image::setPixelData(Pixel ***pixels) {
	delete pixels_;
	pixels_ = pixels;
}

void Image::overrideSize(int width, int height) {
	width_ = width;
	height_ = height;
}

bool Image::save(const char* path) {
	std::ofstream stream;
	stream.open(path);
	if (!stream.is_open())
		return false;

	// Write header
	stream << "P3" << '\n';
	stream << getSize().width << ' ' << getSize().height << '\n';
	stream << 255 << '\n';

	for (int y = 0; y < getSize().height; y++) {
		for (int x = 0; x < getSize().width; x++) {
			Pixel curPixel = getPixel(x, y);
			stream << curPixel.r << ' ' << curPixel.g << ' ' << curPixel.b << '\n';
		}
	}

	stream.close();
	return true;
}


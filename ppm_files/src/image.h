#pragma once

struct Pixel {
	int r, g, b;
};

struct ImageSize {
	int width; int height;
};

class Image {
	int width_, height_;
	Pixel*** pixels_;

public:
	Image();
	Image(int width, int height, Pixel*** pixels);
	~Image();

	Pixel getPixel(int x, int y);
	ImageSize getSize();

	void setPixel(int x, int y, Pixel color);
	void setPixelData(Pixel*** pixels);

	void overrideSize(int width, int height);

	bool save(const char* path);
};
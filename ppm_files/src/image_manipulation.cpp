#include "image_manipulation.h"
#include "util.h"
#include <fstream>
#include <string>

Pixel*** genSolidPixelArr(int width, int height, Pixel color) {
	Pixel*** pixels = new Pixel * *[height];

	for (int y = 0; y < height; y++) {
		pixels[y] = new Pixel * [width];

		for (int x = 0; x < width; x++) {
			pixels[y][x] = new Pixel{ color };
		}
	}

	return pixels;
}

void imgman::genColoredImage(Image* image, int width, int height, Pixel color) {
	image->overrideSize(width, height);
	image->setPixelData(genSolidPixelArr(width, height, color));
}

bool imgman::loadImage(Image* image, const char* path) {
	std::ifstream stream;
	stream.open(path);
	if (!stream.is_open())
		return false;

	int width = 0, height = 0;
	Pixel*** pixels{ 0 };

	std::string line;
	int lineNo = 0;
	while (std::getline(stream, line)) {
		switch (lineNo) {
			// File type
			case 0:
			{
				// Not a P3 ppm file
				if (line != "P3")
					return false;
				break;
			}
			// Width and height
			case 1:
			{
				std::vector<std::string> splSize = util::splitString(line);
				// Two args, w & h
				if (splSize.size() < 2)
					return false;

				width = std::stoi(splSize.at(0));
				height = std::stoi(splSize.at(1));

				// Init pixel 2d array
				pixels = genSolidPixelArr(width, height, { 0, 0, 0 });

				break;
			}
			// TODO
			case 2:
			{
				break;
			}
			// Pixel data
			default:
			{
				if (line.empty()) continue;

				std::vector<std::string> splColor = util::splitString(line);
				// Three args, r, g, b
				if (splColor.size() < 3)
					return false;

				// Copy values into pixel array.
				int y = (int)(lineNo - 3) / width;
				int x = (int)lineNo - 3 - width * y;
				pixels[y][x] = new Pixel{ std::stoi(splColor.at(0)), std::stoi(
						splColor.at(1)), std::stoi(splColor.at(2)) };

				break;
			}
		}
		lineNo++;
	}

	image->overrideSize(width, height);
	image->setPixelData(pixels);
	return true;
}

void imgman::invert(Image* image) {
	for (int y = 0; y < image->getSize().height; y++) {
		for (int x = 0; x < image->getSize().width; x++) {
			Pixel oldColor = image->getPixel(x, y);

			Pixel newColor = {
				255 - oldColor.r,
				255 - oldColor.g,
				255 - oldColor.b,
			};

			image->setPixel(x, y, newColor);
		}
	}
}
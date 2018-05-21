/*
* Bruce Zitelli wrote this May 19th, 2018.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using uchar = unsigned char;

struct Pixel {
	uchar red, green, blue, alpha;
	
	int getColorDiff(const Pixel& other) const {
		// Returns: the summed RGB component color difference between two pixels
		return abs(red - other.red) + abs(green - other.green) + abs(blue - other.blue);
	}
};

map<string, Pixel>* buildColorMap() {
	// Returns: A pointer to a map of color names and their associated pixel values

	map<string, Pixel>* colorMap = new map<string, Pixel>;

	// Color file should be layed line by line like this:
	// *color name* *red* *green* *blue*
	// the color name cannot have spaces
	// the color components must be integers [0, 255]
	ifstream colorFile = ifstream("colors.txt");

	string token;
	while (colorFile >> token) {
		string colorName = token;

		Pixel color = { 0, 0, 0, 255 };
		
		colorFile >> token;
		color.red = stoi(token);
		colorFile >> token;
		color.green = stoi(token);
		colorFile >> token;
		color.blue = stoi(token);
		
		colorMap->insert(pair<string, Pixel>(colorName, color));
	}

	return colorMap;
}

string getColorString(const Pixel& p, const map<string, Pixel>& colorMap) {
	// Parameters: A pixel, and a map of names and their associated color values
	//    Returns: The string name which identifies the closest color to the pixel in the map

	int minColorDiff = 1000;
	string result = "";

	for (auto entry : colorMap) {
		
		if (p.getColorDiff(entry.second) < minColorDiff) {
			minColorDiff = p.getColorDiff(entry.second);
			result = entry.first;
		}
	}

	return result;
}

int main() {
	int width, height, bpp, channels = 4;
	uchar* img = stbi_load("pic.png", &width, &height, &bpp, channels);

	ofstream output("racket-graphics-lab.rkt");

	Pixel *start = reinterpret_cast<Pixel*>(img);
	Pixel *p = start;

	map<string, Pixel>* colorMap = buildColorMap();

	output << ";Zitelli Bruce\n;\n;CS A250\n;May 19, 2018\n;\n;Racket graphics lab\n\n";
	output << "(start 600 600)" << endl << endl;
	output << "(draw-solid-rect (make-posn 0 0) 600 600 'gray)" << endl << endl;
	output << "(draw-solid-rect (make-posn 140 140) 310 310 'black)" << endl << endl;

	int upscale = 6;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			output << "(draw-solid-disk (make-posn ";
			output << (150 + x * upscale) << " " << (150 + y * upscale);
			output << ") " << 4 << " '";
			output << getColorString(*p, *colorMap);
			output << ")" << endl;

			p++;
		}
	}

	output << "(draw-solid-rect (make-posn 140 140) 310 10 'white)" << endl;
	output << "(draw-solid-rect (make-posn 140 140) 10 310 'white)" << endl;
	output << "(draw-solid-rect (make-posn 140 440) 310 10 'white)" << endl;
	output << "(draw-solid-rect (make-posn 440 140) 10 310 'white)" << endl;

	output << "(draw-solid-string (make-posn 140 470) \"Hello! My name is Bruce\")" << endl;
	output << "(draw-solid-string (make-posn 140 490) \"Welcome to my Linkedin.\")" << endl;
	output << "(draw-solid-string (make-posn 140 510) \"Today I want to talk about\")" << endl;
	output << "(draw-solid-string (make-posn 140 530) \"Java, and why my favorite\")" << endl;
	output << "(draw-solid-string (make-posn 140 550) \"programming paradigm is:\")" << endl;
	output << "(draw-solid-string (make-posn 140 570) \"'Bloat and Die'\")" << endl;

	cout << endl;
	system("Pause");
	return 0;
}
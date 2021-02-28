/* Created on: 22.02.2021
   Author: daniel   */
#ifndef FONTS_H
#define FONTS_H

#include "Letter.h"
#include "bitoperations.h"
#include "cardSD.h"

using namespace std;

#define NUMBER_OF_LETTERS 	95

class Fonts{

public:
	Fonts(uint8_t width, uint8_t height, uint8_t width_real, uint8_t height_real);
	void send_uart (char *string);
	void createFont(const char* path);
	void createObjects(char* data);
	uint32_t* getLetter(uint8_t letter);
	uint8_t getWidth();
	uint8_t getHeight();
	uint8_t getWidthReal();
	uint8_t getHeightReal();

private:
	Letter** Font;
	uint8_t height;
	uint8_t width;
	uint8_t height_real;
	uint8_t width_real;
};

#endif

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
	Fonts(uint8_t width, uint8_t height, uint8_t width_to_see, uint8_t height_to_see);
	void send_uart (char *string);
	void createFont(const char* path);
	void createObjects(char* data);
	uint32_t* getLetter(uint8_t letter);
	uint8_t getWidth();
	uint8_t getHeight();
	uint8_t getWidthSeen();
	uint8_t getHeightSeen();

private:
	Letter** Font;
	uint8_t height;
	uint8_t width;
	uint8_t height_to_see;
	uint8_t width_to_see;
};

#endif

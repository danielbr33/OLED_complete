#ifndef FONTS_H
#define FONTS_H

#include "Letter.h"
#include "bitoperations.h"
#include "cardSD.h"

using namespace std;

class Fonts{

public:
	Fonts(uint8_t width, uint8_t height, uint8_t width_to_see, uint8_t height_to_see);
	void send_uart (char *string);
	void createFont(const char* path);
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

#endif FONTS_H

#ifndef LETTER_H
#define LETTER_H

#include "stdint.h"
#define MAX_WIDTH 16

class Letter{

public:
	Letter(uint16_t* tab, uint8_t height, uint8_t width);
	Letter(uint32_t* tab, uint8_t height, uint8_t width);
	~Letter();
	uint32_t* getLetter();
	uint8_t getWidth();
	uint8_t getHeight();

private:
	uint8_t width;
	uint8_t height;
	uint32_t* letter_tab;
};

#endif LETTER_H


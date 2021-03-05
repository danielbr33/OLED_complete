/* Created on: 22.02.2021
   Author: daniel   */
/***************README******************/
/* Record of the letter as horizontal table of the vertical lines of the letter*/

#ifndef LETTER_H
#define LETTER_H

#include "bitoperations.h"

#define MAX_WIDTH 16

class Letter{

public:
	Letter(uint32_t* tab, uint8_t height, uint8_t width);  /*max height=32 due to the size of uint32_t, if exceeded some bits may by losted
															it's written to table of size=width, one variable holds one collumn of letters pixels*/
	Letter(uint16_t* tab, uint8_t height, uint8_t width, uint8_t default_flag);  /*only for default, value of last parameter
																				irrelevant, it's only flag to distinguish it*/
	~Letter();
	uint32_t* getLetter();
	uint8_t getWidth();
	uint8_t getHeight();

private:
	uint8_t width;
	uint8_t height;
	uint32_t* letter_tab;
};

#endif


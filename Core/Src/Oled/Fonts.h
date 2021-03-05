/* Created on: 22.02.2021
   Author: daniel   */
#ifndef FONTS_H
#define FONTS_H

#include "Letter.h"
#include "bitoperations.h"
#include "cardSD.h"
#include "string.h"
#include "defaultFont.h"

using namespace std;

#define NUMBER_OF_LETTERS 	95

class Fonts{

public:
	Fonts(uint8_t width, uint8_t height, uint8_t width_real, uint8_t height_real, string name);
	void createFont(const char* path);  /*finding font in SD and  createObjects() */
	void createObjects(char* data);  /*creates objects of fonts which are actually used*/
	void createDefaultFont();
	uint32_t* getLetter(uint8_t letter);  /*return pointer to table of letter written as pixels in collumn*/
	uint8_t getWidth();  /*height written to object independent of size which is available on SD card, for example if you create a font of size 10x20,
							but the most similiar in SD is 11x18, it will be created but it can be found by 10x20*/
	uint8_t getHeight();	/*height written to object independent of size which is available on SD card, for example if you create a font of size 10x20,
							but the most similiar in SD is 11x18, it will be created but it can be found by 10x20*/
	uint8_t getWidthReal();		/*real size chosen from fonts available in SD card*/
	uint8_t getHeightReal();	/*real size chosen from fonts available in SD card*/
	string getName();	/*return name of font*/

private:
	Letter** Font;
	string name;
	uint8_t height;
	uint8_t width;
	uint8_t height_real;
	uint8_t width_real;
};

#endif

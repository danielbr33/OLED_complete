#ifndef BUFFERSSD1306_H_
#define BUFFERSSD1306_H_

#include "Fonts.h"
#include <vector>
#include "FontsJsonManager.h"
#include "bitoperations.h"
#include "string.h"
#include "cardSD.h"

#define BUFFOR_PART_HEIGHT 8
/* Created on: 22.02.2021
   Author: daniel   */
#define PART_BUFFOR_FILLED 255
#define PART_BUFFOR_NOT_FILLED	0

class BufferSSD1306{

public:
	typedef enum { Font6x8, Font7x10, Font11x18 } Font;
	typedef enum { Black, White } Color;
	void print();
	BufferSSD1306(uint8_t buffer_width, uint8_t buffer_height);
	~BufferSSD1306();
	void addLetter(uint8_t letter, uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y);
	void addText(char *text, uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y);
	void createFont(uint8_t width, uint8_t height);
	void fill(Color color);
	uint8_t* getBuffer(uint8_t sector);  //sector-8 verses
	uint8_t findFont(uint8_t width, uint8_t height);
	bool checkReady();

private:
	uint8_t** table;
	int buffer_width;
	int buffer_height;
	uint8_t buffor_element_height;
	Fonts* actualFont;
	vector<Fonts*> FontsAll;
	bool ready;
};

#endif


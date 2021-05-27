/* Created on: 22.02.2021
   Author: daniel   */

#ifndef BUFFERSSD1306_H_
#define BUFFERSSD1306_H_

//#define DEFAULT_MODE

#include "Fonts.h"
#include <vector>
#include "bitoperations.h"
#include "string.h"
#ifndef DEFAULT_MODE
#include "FontsJsonManager.h"
#include "cardSD.h"
#endif

using namespace std;

#define BUFFOR_PART_HEIGHT 8
#define PART_BUFFOR_FILLED 255
#define PART_BUFFOR_NOT_FILLED	0

class BufferSSD1306{

public:
	typedef enum { Black, White } Color;
	void print();
	BufferSSD1306(uint8_t buffer_width, uint8_t buffer_height);   /*buffor has a width equal of real width but the height is 8 times smaller
																	because it is segmented and data is written in uint8_t*/
	~BufferSSD1306();
	void addLetter(uint8_t letter, uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y);
	void addText(char *text, uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y);
	bool findFont(uint8_t width, uint8_t height);  /*check if available in vector, if not then createFont() */
	void createFont(uint8_t width, uint8_t height);	 /* finds the most simliar font in json file, creates the object and add it to vector */

	void addLetter(uint8_t letter, string name, Color color, uint8_t coord_X, uint8_t coord_Y);
	void addText(char *text, string name, Color color, uint8_t coord_X, uint8_t coord_Y);
	bool findFont(string name); /*check if available in vector, if not then createFont() */
	void createFont(string name);  /* finds the most simliar font in json file, creates the object and add it to vector */

	void fill(Color color);
	uint8_t* getBuffer(uint8_t sector);  //sector-8 verses
	bool checkReady();  /* return false if buffer is actually edited, true if ready to send to oled */

private:
	void operateWhiteTableValue(uint8_t x, uint8_t y, uint8_t value);  //function modifying element of buffor
	void operateBlackTableValue(uint8_t x, uint8_t y, uint8_t value);  //function modifying element of buffor
	void clearLines(uint8_t from, uint8_t to, Color color);
	void createDefaultFont();
	#ifndef DEFAULT_MODE
	bool checkJsonStatus();
	#endif
	uint8_t** table;
	int buffer_width;
	int buffer_height;
	uint8_t buffor_element_height;
	Fonts* actualFont = nullptr;
	vector<Fonts*> FontsAll;
	bool ready;
};

#endif


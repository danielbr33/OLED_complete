#ifndef BUFFER_H
#define BUFFER_H

#include "Fonts.h"
#include "bitoperations.h"
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"
#include "stdlib.h"
#include "cstring"
#include "string.h"
#include "stdio.h"
#include "stm32f4xx_hal.h"
#include <vector>
#include "stdlib.h"
#include "JsonFonts.h"

typedef enum { Font6x8, Font7x10, Font11x18 } Font;
typedef enum { Black, White } Color;
#define BUFFOR_PART_HEIGHT 8
#define BUFFOR_FILLED 255

class Buffer{ //Ta Klasa powinn miec inna nazwe np BufferSSD1306, tak aby było wiadomo do czego sie odnosi bo ogólnie w pojekcie buforów moze i pewnie bedzie wiecej

public:
	void print();
	Buffer(uint8_t buffer_width, uint8_t buffer_height);
	~Buffer();
	void addLetter(uint8_t letter, uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y);
	void addText(char *text, uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y);
	void createFont(uint8_t width, uint8_t height);
	void fill(Color color);
	uint8_t* getBuffer(uint8_t verse);
	void send_uart (char *string);
	uint8_t findFont(uint8_t width, uint8_t height);

private:
	uint8_t** table;
	int buffer_width;
	int buffer_height;
	uint8_t buffor_element_height;
	FATFS fs;  // file system
	FIL fil; // File
	FRESULT fresult;  // result
	FILINFO fno;
	UINT br, bw;  // File read/write count
	Fonts* ActualFont;
	vector<Fonts*> FontsAll;
};

#endif BUFFER_H


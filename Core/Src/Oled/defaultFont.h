
#include <iostream>
#include <string.h>
#include <cstdlib>
#include "main.h"

using namespace std;

#ifndef SRC_OLED_DEFAULTFONT_H_
#define SRC_OLED_DEFAULTFONT_H_

typedef struct {
	const uint8_t width;    /*!< Font width in pixels */
	uint8_t height;   /*!< Font height in pixels */
	const uint16_t *data; /*!< Pointer to data font data array */
	string name;
} FontDef;
extern FontDef defaultFont;

#endif

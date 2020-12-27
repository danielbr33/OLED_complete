#include "Letter.h"

Letter::Letter(uint32_t* tab, uint8_t height, uint8_t width) {
	this->height = height;
	this->width = width;
	this->letter_tab = new uint32_t[width];
	for (uint8_t i = 0; i < width; i++)
		this->letter_tab[i] = tab[i];  //<< (MAX_WIDTH - width)
}

Letter::Letter(uint16_t* tab, uint8_t height, uint8_t width) {
	this->height = height;
	this->width = width;
	this->letter_tab = new uint32_t[width];
	for (uint8_t i = 0; i < width; i++)
		this->letter_tab[i] = tab[i];  //<< (MAX_WIDTH - width)
}

uint32_t* Letter::getLetter() {
	return letter_tab;
}

uint8_t Letter::getWidth() {
	return this->width;
}

uint8_t Letter::getHeight() {
	return this->height;
}

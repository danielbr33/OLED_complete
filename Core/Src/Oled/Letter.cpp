#include "Letter.h"

Letter::Letter(uint32_t* tab, uint8_t height, uint8_t width) {
	this->height = height;
	this->width = width;
	this->letter_tab = new uint32_t[width];
	for (uint8_t j=0; j<width; j++){
		letter_tab[j]=0;
		for (uint8_t i = 0; i < height; i++){
			if(getBit(tab[i], j))
				setBit(letter_tab[j], i);
		}
	}
}

Letter::Letter(uint16_t* tab, uint8_t height, uint8_t width, uint8_t default_flag) {
	this->height = height;
	this->width = width;
	this->letter_tab = new uint32_t[width];
	for (uint8_t i = 0; i < width; i++){
		uint8_t temp = tab[i];
		this->letter_tab[i] = tab[i];
	}
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

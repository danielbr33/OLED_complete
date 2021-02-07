#include "Letter.h"

Letter::Letter(uint32_t* tab, uint8_t height, uint8_t width) {
	this->height = height;
	this->width = width;
	this->letter_tab = new uint32_t[width];
	uint16_t temp1=0;
	uint16_t temp2=0;
	for (uint8_t j=0; j<width; j++){
		letter_tab[j]=0;
		for (uint8_t i = 0; i < height; i++){
			temp1=tab[i];
			if(getBit(tab[i], j))
				setBit(letter_tab[j], i);
		}
		temp2=letter_tab[j];
	}
	uint8_t tttt=0;
	uint16_t tem1=letter_tab[0];
	uint16_t tem2=letter_tab[1];
	uint16_t tem3=letter_tab[2];
	uint16_t tem4=letter_tab[3];
	uint16_t tem5=letter_tab[4];
	uint16_t tem6=letter_tab[5];
	uint16_t tem7=letter_tab[6];
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

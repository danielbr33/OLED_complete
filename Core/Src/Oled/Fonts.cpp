#include "Fonts.h"

Fonts::Fonts(uint8_t width, uint8_t height, uint8_t width_real, uint8_t height_real, string name){
	this->width = width;
	this->height = height;
	this->width_real = width_real;
	this->height_real = height_real;
	this->name = name;
}

void Fonts::createDefaultFont(){
	Font = new Letter* [NUMBER_OF_LETTERS];
	for (uint8_t i = 0; i < 95; i++) {
		Font[i] = new Letter((uint16_t*)&defaultFont.data[i * width], height, width, 0);
	}
}

void Fonts::createFont(const char* path) {
	char* read_data;
	cardSD::getInstance().readFile((char*)path, &read_data) != cardSD::SD_OK;
	createObjects(read_data);
	delete(read_data);
}

void Fonts::createObjects(char* data){
	uint16_t counter = 0;
	uint32_t temp = 0;
	uint32_t table[this->height];
	uint8_t counter_width = 0;
	uint8_t counter_height = 0;

	Font = new Letter* [NUMBER_OF_LETTERS];
	for (uint8_t i = 0; i < NUMBER_OF_LETTERS; i++) {
		while (counter_height < this->height_real){
			while (data[counter]!='-' && data[counter]!='#'){
				counter+=1;
			}
			if (data[counter+1]!='-'  && data[counter+1]!='#'){  //skip single mark, being the symbol of the letter,
				counter+=1; 									//e.g to avoid reading'#' or '-' which not code the mark, mark are the symbol
			}													//if file that this mark is shown as binary
			while (data[counter]!='-' && data[counter]!='#'){
				counter+=1;
			}
			while (counter_width < this->width_real) {
				if(data[counter]=='#'){
					setBit(temp, counter_width);
				}
				counter_width+=1;
				counter+=1;
			}
			counter_width=0;
			table[counter_height] = temp;
			temp=0;
			counter_height+=1;
		}
		counter_height=0;
		Font[i] = new Letter(table, height_real, width_real);
	}
}

uint32_t* Fonts::getLetter(uint8_t letter) {
	return Font[letter - ' ']->getLetter();
}

uint8_t Fonts::getWidth() {
	return this->width;
}

uint8_t Fonts::getHeight() {
	return this->height;
}

uint8_t Fonts::getWidthReal() {
	return this->width_real;
}

uint8_t Fonts::getHeightReal() {
	return this->height_real;
}

string Fonts::getName(){
	return this->name;
}

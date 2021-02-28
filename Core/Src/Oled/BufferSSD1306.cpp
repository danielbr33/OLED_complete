#include <BufferSSD1306.h>

void BufferSSD1306::fill(Color color) {
	ready = false;
	for (uint8_t i = 0; i < this->buffer_height / BUFFOR_PART_HEIGHT; i++)
		for (uint8_t j = 0; j < this->buffer_width; j++) {
			if (color == White)
				table[i][j] = PART_BUFFOR_FILLED;
			else
				table[i][j] = PART_BUFFOR_NOT_FILLED;
		}
	ready = true;
}


uint8_t* BufferSSD1306::getBuffer(uint8_t sector){
	return this->table[sector];
}


BufferSSD1306::BufferSSD1306(uint8_t buffer_width, uint8_t buffer_height){
	this->buffer_height = buffer_height;
	this->buffer_width = buffer_width;
	table = new uint8_t* [this->buffer_height / BUFFOR_PART_HEIGHT];
	for (uint8_t i = 0; i < (this->buffer_height/BUFFOR_PART_HEIGHT); i++)
		table[i] = new uint8_t[this->buffer_width];
	for (uint8_t j=0; j < (this->buffer_height/BUFFOR_PART_HEIGHT); j++)
		for (uint8_t i = 0; i < this->buffer_width; i++)
			table[j][i] = 0;
	ready = true;
}

bool BufferSSD1306::checkReady(){
	return ready;
}

BufferSSD1306::~BufferSSD1306(){
	delete[] table;
}

void BufferSSD1306::addLetter(uint8_t letter, uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y) {
	ready = false;
	if(actualFont->getWidth()!=width || actualFont->getHeight()!=height)
		if(findFont(width, height) == false){
			createFont(width, height);
			findFont(width, height);
		}
	uint8_t temp;
	uint8_t number_of_verse = (uint8_t)(coord_Y/BUFFOR_PART_HEIGHT);
	uint8_t offset = coord_Y % BUFFOR_PART_HEIGHT;
	for (uint8_t i = 0; i < actualFont->getWidth(); i++) {
		if ( (coord_X + i) >= this->buffer_width)
			break;


		if (color == White) {
			table[number_of_verse][i + coord_X] &= PART_BUFFOR_NOT_FILLED;
			temp = actualFont->getLetter(letter)[i] << offset;
			operateWhiteTableValue(i+coord_X, number_of_verse, temp);

			if (height >= (BUFFOR_PART_HEIGHT-offset) ) {
				table[number_of_verse + 1][i + coord_X] &= PART_BUFFOR_NOT_FILLED;
				temp = actualFont->getLetter(letter)[i] >> (BUFFOR_PART_HEIGHT - offset);
				operateWhiteTableValue(i+coord_X, number_of_verse+1, temp);
			}

			if (height >= (2*BUFFOR_PART_HEIGHT-offset) ) {
				table[number_of_verse + 2][i + coord_X] &= PART_BUFFOR_NOT_FILLED;
				temp = actualFont->getLetter(letter)[i] >> (2*BUFFOR_PART_HEIGHT - offset);
				operateWhiteTableValue(i+coord_X, number_of_verse+2, temp);
			}
		}

		else if (color == Black) {
			table[number_of_verse][i + coord_X] = ~PART_BUFFOR_NOT_FILLED;
			temp = actualFont->getLetter(letter)[i] << offset;
			operateBlackTableValue(i+coord_X, number_of_verse, temp);
			if (height >= (BUFFOR_PART_HEIGHT-offset)) {
				table[number_of_verse + 1][i + coord_X] = ~PART_BUFFOR_NOT_FILLED;
				temp = actualFont->getLetter(letter)[i] >> (BUFFOR_PART_HEIGHT - offset);
				operateBlackTableValue(i + coord_X, number_of_verse + 1, temp);
			}
			if (height >= (2*BUFFOR_PART_HEIGHT-offset)) {
				table[number_of_verse + 2][i + coord_X] = ~PART_BUFFOR_NOT_FILLED;
				temp = actualFont->getLetter(letter)[i] >> (2*BUFFOR_PART_HEIGHT - offset);
				operateBlackTableValue(i + coord_X, number_of_verse + 2, temp);
			}
		}
	}
	ready = true;
}

void BufferSSD1306::addText(char* text,  uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y) {
	ready = false;
	if(actualFont->getWidth()!=width || actualFont->getHeight()!=height)
		if(findFont(width, height) == false){
			createFont(width, height);
			findFont(width, height);
		}
	for (uint8_t i = 0; i < strlen((char*)text); i++) { //przemylsec zmiane z z char* na std::string i zmiane archaicznych strlen na std::string string, string.size()
		uint8_t current_X = coord_X + i * actualFont->getWidth();
		addLetter(text[i], width, height, color, current_X, coord_Y);
	}
	ready = true;
}

void BufferSSD1306::createFont(uint8_t width, uint8_t height) {
	char* path;
	uint8_t width_to_see;
	uint8_t height_to_see;
	path = (char*)((FontsJsonManager::getInstance().getPath(width,  height)).c_str());
	width_to_see = FontsJsonManager::getInstance().getWidth(width,  height);
	height_to_see = FontsJsonManager::getInstance().getHeight(width,  height);
	actualFont = new Fonts(width, height, width_to_see, height_to_see);
	actualFont->createFont(path);
	FontsAll.push_back(new Fonts(*actualFont));
	delete actualFont;
}

uint8_t BufferSSD1306::findFont(uint8_t width, uint8_t height) {
	for (uint8_t i = 0; i < FontsAll.size(); i++) {
		if (FontsAll[i]->getHeight() == height  &&  FontsAll[i]->getWidth() == width) {
			actualFont = FontsAll[i];
			return 1;
		}
	}
	return 0;
}

void BufferSSD1306::operateWhiteTableValue(uint8_t x, uint8_t y, uint8_t value){
	if (  y < (this->buffer_height/BUFFOR_PART_HEIGHT)  &&  x < this->buffer_width  )
		table[y][x] |= value;
}

void BufferSSD1306::operateBlackTableValue(uint8_t x, uint8_t y, uint8_t value){
	if (  y < (this->buffer_height/BUFFOR_PART_HEIGHT)  &&  x < this->buffer_width  )
		table[y][x] &= ~value;
}

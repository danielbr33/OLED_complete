#include "BufferSSD1306.h"

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
	actualFont = nullptr;
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
#ifdef DEFAULT_MODE
	addLetter(letter, defaultFont.name, color, coord_X, coord_Y);
#else
	if (letter < ' ' || letter >'~')
		letter = ' ';
	ready = false;
	if(actualFont == nullptr){
		if(findFont(width, height) == false){
			createFont(width, height);
			findFont(width, height);
		}
	}
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
#endif
}

void BufferSSD1306::addLetter(uint8_t letter, string name, Color color, uint8_t coord_X, uint8_t coord_Y) {
	ready = false;
	#ifdef DEFAULT_MODE
	name = defaultFont.name;
	#endif
	if (letter < ' ' || letter >'~')
		letter = ' ';
	if(actualFont == nullptr){
		if(findFont(name) == false){
			if(name == defaultFont.name)
				createDefaultFont();
			else{
				createFont(name);
			}
			findFont(name);
		}
	}
	if(actualFont->getName()!=name)
		if(findFont(name) == false){
			if(name == defaultFont.name)
				createDefaultFont();
			else
				createFont(name);
			findFont(name);
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

			if (actualFont->getHeight() >= (BUFFOR_PART_HEIGHT-offset) ) {
				table[number_of_verse + 1][i + coord_X] &= PART_BUFFOR_NOT_FILLED;
				temp = actualFont->getLetter(letter)[i] >> (BUFFOR_PART_HEIGHT - offset);
				operateWhiteTableValue(i+coord_X, number_of_verse+1, temp);
			}

			if (actualFont->getHeight() >= (2*BUFFOR_PART_HEIGHT-offset) ) {
				table[number_of_verse + 2][i + coord_X] &= PART_BUFFOR_NOT_FILLED;
				temp = actualFont->getLetter(letter)[i] >> (2*BUFFOR_PART_HEIGHT - offset);
				operateWhiteTableValue(i+coord_X, number_of_verse+2, temp);
			}
		}

		else if (color == Black) {
			table[number_of_verse][i + coord_X] = ~PART_BUFFOR_NOT_FILLED;
			temp = actualFont->getLetter(letter)[i] << offset;
			operateBlackTableValue(i+coord_X, number_of_verse, temp);
			if (actualFont->getHeight() >= (BUFFOR_PART_HEIGHT-offset)) {
				table[number_of_verse + 1][i + coord_X] = ~PART_BUFFOR_NOT_FILLED;
				temp = actualFont->getLetter(letter)[i] >> (BUFFOR_PART_HEIGHT - offset);
				operateBlackTableValue(i + coord_X, number_of_verse + 1, temp);
			}
			if (actualFont->getHeight() >= (2*BUFFOR_PART_HEIGHT-offset)) {
				table[number_of_verse + 2][i + coord_X] = ~PART_BUFFOR_NOT_FILLED;
				temp = actualFont->getLetter(letter)[i] >> (2*BUFFOR_PART_HEIGHT - offset);
				operateBlackTableValue(i + coord_X, number_of_verse + 2, temp);
			}
		}
	}
	ready = true;
}

void BufferSSD1306::addText(char* text,  uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y) {
#ifdef DEFAULT_MODE
	addText(text, defaultFont.name, color, coord_X, coord_Y);
#else
	ready = false;
	if(actualFont == nullptr){
		if(findFont(width, height) == false){
			createFont(width, height);
			findFont(width, height);
		}
	}
	if(actualFont->getWidth()!=width || actualFont->getHeight()!=height)
		if(findFont(width, height) == false){
			createFont(width, height);
			findFont(width, height);
		}
	uint8_t current_X = coord_X;
	for (uint8_t i = 0; i < strlen((char*)text); i++) {
		if(text[i] == '\n'){
			coord_Y += (actualFont->getHeight() + 4);
			current_X = coord_X;
		}
		else
			addLetter(text[i], width, height, color, current_X, coord_Y);
		current_X += actualFont->getWidth();
	}
	ready = true;
#endif
}

void BufferSSD1306::addText(char* text,  string name, Color color, uint8_t coord_X, uint8_t coord_Y) {
	ready = false;
	#ifdef DEFAULT_MODE
	name = defaultFont.name;
	#endif
	if(actualFont == nullptr){
		if(findFont(name) == false){
			if(name==defaultFont.name)
				createDefaultFont();
			else
				createFont(name);
			findFont(name);
		}
	}
	if(actualFont->getName()!=name)
		if(findFont(name) == false){
			if(name==defaultFont.name)
				createDefaultFont();
			else
				createFont(name);
			findFont(name);
		}
	uint8_t current_X;
	for (uint8_t i = 0; i < strlen((char*)text); i++) {
		if(text[i] == '\n'){
			coord_Y += (actualFont->getHeight() + 4);
			current_X = coord_X;
		}
		else
			addLetter(text[i], name, color, current_X, coord_Y);
		current_X += actualFont->getWidth();
	}
	ready = true;
}

void BufferSSD1306::createFont(uint8_t width, uint8_t height) {
#ifdef DEFAULT_MODE
	createFont(defaultFont.name);
#else
	char* path;
	uint8_t width_to_see;
	uint8_t height_to_see;
	string name_temp;

	bool fonts_ready = true;
	fonts_ready = checkJsonStatus();

	if(fonts_ready == true){
		path = (char*)((FontsJsonManager::getInstance().getPath(width,  height)).c_str());
		if (path == "NO_FONT")
			fonts_ready = false;
		width_to_see = FontsJsonManager::getInstance().getWidth(width,  height);
		if (width_to_see == FontsJsonManager::NO_FONT_ERROR)
			fonts_ready = false;
		height_to_see = FontsJsonManager::getInstance().getHeight(width,  height);
		if (height_to_see == FontsJsonManager::NO_FONT_ERROR)
			fonts_ready = false;
		name_temp = FontsJsonManager::getInstance().getName(width,  height);
		if (name_temp == "NO_FONT")
			fonts_ready = false;
	}

	if(fonts_ready == false){
		if(findFont(defaultFont.name) == false)
			createDefaultFont();
		return;
	}
	actualFont = new Fonts(width, height, width_to_see, height_to_see, name_temp);
	actualFont->createFont(path);
	FontsAll.push_back(new Fonts(*actualFont));
	delete actualFont;
#endif
}


void BufferSSD1306::createFont(string name) {
#ifdef DEFAULT_MODE
	name = defaultFont.name;
#endif
	char* path;
	uint8_t width_to_see;
	uint8_t height_to_see;
	string name_temp;

	bool fonts_ready = false;
#ifndef DEFAULT_MODE
	// TODO: Przyjrzec sie
	fonts_ready = checkJsonStatus();

	if(fonts_ready == true){
		path = (char*)((FontsJsonManager::getInstance().getPath(name)).c_str());
		if (path == "NO_FONT")
			fonts_ready = false;
		width_to_see = FontsJsonManager::getInstance().getWidth(name);
		if (width_to_see == FontsJsonManager::NO_FONT_ERROR)
			fonts_ready = false;
		height_to_see = FontsJsonManager::getInstance().getHeight(name);
		if (height_to_see == FontsJsonManager::NO_FONT_ERROR)
			fonts_ready = false;
		name_temp = FontsJsonManager::getInstance().getName(name);
		if (name_temp == "NO_FONT")
			fonts_ready = false;
	}
#endif

	if(fonts_ready == false){
		if(findFont(defaultFont.name) == false)
			createDefaultFont();
		return;
	}
#ifndef DEFAULT_MODE
	if(name_temp == name){
		actualFont = new Fonts(width_to_see, height_to_see, width_to_see, height_to_see, name);
		actualFont->createFont(path);
		FontsAll.push_back(new Fonts(*actualFont));
		delete actualFont;
	}
#endif
}

void BufferSSD1306::createDefaultFont(){
	actualFont = new Fonts(defaultFont.width, defaultFont.height, defaultFont.width, defaultFont.height, defaultFont.name);
	actualFont->createDefaultFont();
	FontsAll.push_back(new Fonts(*actualFont));
	delete actualFont;
}

#ifndef DEFAULT_MODE
bool BufferSSD1306::checkJsonStatus(){
	FontsJsonManager::Json_FontsStatus status;
	status = FontsJsonManager::getInstance().getJsonFontsStatus();
	uint8_t coordX = 2;
	uint8_t coordY = buffer_height - 10;
	if (status == FontsJsonManager::JSON_KEY_ERR)
		addText((char*)"No font key in json", defaultFont.name, Black, coordX, coordY);
	if (status == FontsJsonManager::JSON_READ_ERR)
		addText((char*)"ERROR reading json file", defaultFont.name, Black, coordX, coordY);
	if (status == FontsJsonManager::JSON_SD_ERR)
		addText((char*)"ERROR reading SD card", defaultFont.name, Black, coordX, coordY);
	if (status == FontsJsonManager::JSON_OK)
		return true;
	return false;
}
#endif

#ifndef DEFAULT_MODE
bool BufferSSD1306::findFont(uint8_t width, uint8_t height) {
	for (uint8_t i = 0; i < FontsAll.size(); i++) {
		if (FontsAll[i]->getHeight() == height  &&  FontsAll[i]->getWidth() == width) {
			actualFont = FontsAll[i];
			return true;
		}
	}
	return false;
}
#endif

bool BufferSSD1306::findFont(string name) {
	for (uint8_t i = 0; i < FontsAll.size(); i++) {
		if (FontsAll[i]->getName() == name) {
			actualFont = FontsAll[i];
			return true;
		}
	}
	return false;
}

void BufferSSD1306::operateWhiteTableValue(uint8_t x, uint8_t y, uint8_t value){
	if (  y < (this->buffer_height/BUFFOR_PART_HEIGHT)  &&  x < this->buffer_width  )
		table[y][x] |= value;
}

void BufferSSD1306::operateBlackTableValue(uint8_t x, uint8_t y, uint8_t value){
	if (  y < (this->buffer_height/BUFFOR_PART_HEIGHT)  &&  x < this->buffer_width  )
		table[y][x] &= ~value;
}

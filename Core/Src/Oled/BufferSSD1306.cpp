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
	if(actualFont == nullptr){
		if(findFont(width, height) == false){ //szukanie czcionki nie powinno byc po nazwie? mozmemy miec dwie czcionki w tym samym rozmierze a innym wygladzie? to pytanie a nie krytyka, do przemylsnia
			createFont(width, height);
			findFont(width, height);
		}
	}
	if(actualFont->getWidth()!=width || actualFont->getHeight()!=height)
		if(findFont(width, height) == false){
			createFont(width, height);
			findFont(width, height);
		}

	uint8_t number_of_verse = (uint8_t)(coord_Y/8);
	uint8_t offset = coord_Y % 8;
	for (uint8_t i = 0; i < actualFont->getWidth(); i++) {
		if ( (coord_X + i) >= this->buffer_width)
			break;

		if (color == White) {
			if (number_of_verse < ((uint8_t)this->buffer_height / 8)) {
				table[number_of_verse][i+coord_X] |= (actualFont->getLetter(letter)[i] << offset);
			}
			if ((offset != 0) && (number_of_verse + 1) < ((uint8_t)buffer_height / 8)) {
				table[number_of_verse + 1][i + coord_X] |= (actualFont->getLetter(letter)[i] >> (BUFFOR_PART_HEIGHT - offset));
			}
			//TODO: przyjrzec się tym warunkom
			if ((offset != 0) && (number_of_verse + 2) < ((uint8_t)buffer_height / 8)  && actualFont->getHeight() >= 10) {
				table[number_of_verse + 2][i + coord_X] |= (actualFont->getLetter(letter)[i] >> (2*BUFFOR_PART_HEIGHT - offset));
			}
		}


		//To tez przepisac jakos, najlpeij na jakies mniejsze funkcje, tak abyło to było czytlne i odporone na błedy bo teraz w tych table[x +2][y-1] moza sie pogubic
		//przemyslec jak to zrobic dobrze, tzn sensownie i czytelnie, bo pewnie sie da
		//rowazyc przejscie z operacji na tabliach na funkcje zwracajaca pole w tablicy o wartosci x i y, wtedy funkcja np getTableValue(int x, int y) moze nam sprawdzac czy nie wychodzmy poza zakres
		//takie bezposrednie operacje na wskazniakch pamieci (a operartor [] tym jest) prosi sie o kłopty i błedy wychodzenia poza pamiec i tylko frustruje a nie pomaga znaleźc buga
		//te operacje na bitach np ~0 zmamienic na to czym sie faktycznie zajmuja (opis np isEmpty lub cos, nie wiem co dokładnie oznacza), ale nie wiem tez dlatego ze jest taki zapis :p
		else if (color == Black) {
			if (number_of_verse < ((uint8_t)this->buffer_height / 8)) {
				if (table[number_of_verse][i+coord_X] == 0)
					table[number_of_verse][i + coord_X] = ~0;
				table[number_of_verse][i + coord_X] &= ~(actualFont->getLetter(letter)[i] << offset);
			}
			if ((offset != 0) && (number_of_verse + 1) < ((uint8_t)buffer_height / 8)) {
				if (table[number_of_verse + 1][i + coord_X] == 0)
					table[number_of_verse + 1][i + coord_X] = ~0;
				table[number_of_verse + 1][i + coord_X] &= ~(actualFont->getLetter(letter)[i] >> (BUFFOR_PART_HEIGHT - offset));
			}
			if ((offset != 0) && (number_of_verse + 1) < ((uint8_t)buffer_height / 8) && actualFont->getHeight() >= 10) {
				if (table[number_of_verse + 2][i + coord_X] == 0)
					table[number_of_verse + 2][i + coord_X] = ~0;
				table[number_of_verse + 2][i + coord_X] &= ~(actualFont->getLetter(letter)[i] >> (2*BUFFOR_PART_HEIGHT - offset));
			}
		}
	}
	ready = true;
}

void BufferSSD1306::addText(char* text,  uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y) {
	ready = false;
	if(actualFont == nullptr ){
		if(findFont(width, height) == false){ //szukanie czcionki nie powinno byc po nazwie? mozmemy miec dwie czcionki w tym samym rozmierze a innym wygladzie? to pytanie a nie krytyka, do przemylsnia
			createFont(width, height);
			findFont(width, height);
		}
	}

	if(actualFont->getWidth()!=width || actualFont->getHeight()!=height)
		if(findFont(width, height) == false){ //szukanie czcionki nie powinno byc po nazwie? mozmemy miec dwie czcionki w tym samym rozmierze a innym wygladzie? to pytanie a nie krytyka, do przemylsnia
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


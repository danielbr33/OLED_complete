#include "Buffer.h"
#include "bitoperations.h"
#include "string.h"
#include "cardSD.h"
void Buffer::fill(Color color) {
	for (uint8_t i = 0; i < this->buffer_height / BUFFOR_PART_HEIGHT; i++)
		for (uint8_t j = 0; j < this->buffer_width; j++) {
			if (color == White)
				table[i][j] = BUFFOR_FILLED;
			else
				table[i][j] = 0; // tutaj nie powinmno byc np BLACK_VALUE?
		}
}


uint8_t* Buffer::getBuffer(uint8_t verse){
	return this->table[verse];
}

void Buffer::send_uart (char *string)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)string, strlen (string), HAL_MAX_DELAY);  //TODO change uart
	// jak potrzebujesz cos przetestowac to zrób funkcje getString np i definicje uarta robisz w maine i tak wyslielasz niz funkcje wysylaja na uart bezposrednio w klasie
	// lub w mainie print(std::string string) i wtedy sobie z klasy wyswietlasz, pomaga to po testowaniu posprzatac kod, bo jak mainie usunbiesz print to tutaj oraz kompilator zwróci bład z liniami gdzie jest wyswiretlanie wartosci testowych
}

Buffer::Buffer(uint8_t buffer_width, uint8_t buffer_height){
	this->buffer_height = buffer_height;
	this->buffer_width = buffer_width;
	table = new uint8_t* [this->buffer_height / BUFFOR_PART_HEIGHT];
	for (uint8_t i = 0; i < (this->buffer_height/BUFFOR_PART_HEIGHT); i++)
		table[i] = new uint8_t[this->buffer_width];
	for (uint8_t j=0; j < (this->buffer_height/BUFFOR_PART_HEIGHT); j++)
		for (uint8_t i = 0; i < this->buffer_width; i++)
			table[j][i] = 0;
}

Buffer::~Buffer(){
	delete[] table;
}

void Buffer::addLetter(uint8_t letter, uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y) {
	if(ActualFont == nullptr){
		if(findFont(width, height) == false){ //szukanie czcionki nie powinno byc po nazwie? mozmemy miec dwie czcionki w tym samym rozmierze a innym wygladzie? to pytanie a nie krytyka, do przemylsnia
			createFont(width, height);
			findFont(width, height);
		}
	}
	if(ActualFont->getWidth()!=width || ActualFont->getHeight()!=height)
		if(findFont(width, height) == false){
			createFont(width, height);
			findFont(width, height);
		}

	uint8_t number_of_verse = (uint8_t)(coord_Y/8);
	uint8_t offset = coord_Y % 8;
	uint8_t state;
	uint8_t writted_horizontal_bits;
	for (uint8_t i = 0; i < ActualFont->getWidth(); i++) {
		if (coord_X + i >= this->buffer_width)
			break;

		if (color == White) {
			if (number_of_verse < ((uint8_t)this->buffer_height / 8)) {
				table[number_of_verse][i+coord_X] |= (ActualFont->getLetter(letter)[i] << offset);
			}
			if ((offset != 0) && (number_of_verse + 1) < ((uint8_t)buffer_height / 8)) {
				table[number_of_verse + 1][i + coord_X] |= (ActualFont->getLetter(letter)[i] >> (BUFFOR_PART_HEIGHT - offset));
			}
			//TODO: przyjrzec się tym warunkom
			if ((offset != 0) && (number_of_verse + 2) < ((uint8_t)buffer_height / 8)  && ActualFont->getHeight() >= 10) {
				table[number_of_verse + 2][i + coord_X] |= (ActualFont->getLetter(letter)[i] >> (2*BUFFOR_PART_HEIGHT - offset));
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
				table[number_of_verse][i + coord_X] &= ~(ActualFont->getLetter(letter)[i] << offset);
			}
			if ((offset != 0) && (number_of_verse + 1) < ((uint8_t)buffer_height / 8)) {
				if (table[number_of_verse + 1][i + coord_X] == 0)
					table[number_of_verse + 1][i + coord_X] = ~0;
				table[number_of_verse + 1][i + coord_X] &= ~(ActualFont->getLetter(letter)[i] >> (BUFFOR_PART_HEIGHT - offset));
			}
			if ((offset != 0) && (number_of_verse + 1) < ((uint8_t)buffer_height / 8) && ActualFont->getHeight() >= 10) {
				if (table[number_of_verse + 2][i + coord_X] == 0)
					table[number_of_verse + 2][i + coord_X] = ~0;
				table[number_of_verse + 2][i + coord_X] &= ~(ActualFont->getLetter(letter)[i] >> (2*BUFFOR_PART_HEIGHT - offset));
			}
		}
	}
}

void Buffer::addText(char* text,  uint8_t width, uint8_t height, Color color, uint8_t coord_X, uint8_t coord_Y) {
	if(ActualFont == nullptr ){
		if(findFont(width, height) == false){ //szukanie czcionki nie powinno byc po nazwie? mozmemy miec dwie czcionki w tym samym rozmierze a innym wygladzie? to pytanie a nie krytyka, do przemylsnia
			createFont(width, height);
			findFont(width, height);
		}
	}

	if(ActualFont->getWidth()!=width || ActualFont->getHeight()!=height)
		if(findFont(width, height) == false){ //szukanie czcionki nie powinno byc po nazwie? mozmemy miec dwie czcionki w tym samym rozmierze a innym wygladzie? to pytanie a nie krytyka, do przemylsnia
			createFont(width, height);
			findFont(width, height);
		}
	for (uint8_t i = 0; i < strlen((char*)text); i++) { //przemylsec zmiane z z char* na std::string i zmiane archaicznych strlen na std::string string, string.size()
		uint8_t current_X = coord_X + i * ActualFont->getWidth();
		addLetter(text[i], width, height, color, current_X, coord_Y);
	}
}

void Buffer::createFont(uint8_t width, uint8_t height) {
	uint64_t temp = xPortGetFreeHeapSize();
	char* path;
	uint8_t width_to_see;
	uint8_t height_to_see;
	path = (char*)((FontsJsonManager::getInstance().getPath(width,  height)).c_str());
	width_to_see = FontsJsonManager::getInstance().getWidth(width,  height);
	height_to_see = FontsJsonManager::getInstance().getHeight(width,  height);
	ActualFont = new Fonts(width, height, width_to_see, height_to_see); //obiekty mała listera
	ActualFont->createFont(path);
	FontsAll.push_back(new Fonts(*ActualFont));
	delete ActualFont;
}

uint8_t Buffer::findFont(uint8_t width, uint8_t height) {
	for (uint8_t i = 0; i < FontsAll.size(); i++) {
		if (FontsAll[i]->getHeight() == height  &&  FontsAll[i]->getWidth() == width) {
			ActualFont = FontsAll[i];
			return 1;
		}
	}
	return 0;
}


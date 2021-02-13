#include "Buffer.h"
#include "bitoperations.h"
#include "string.h"

void Buffer::fill(Color color) {
	for (uint8_t i = 0; i < this->buffer_height / BUFFOR_PART_HEIGHT; i++)
		for (uint8_t j = 0; j < this->buffer_width; j++) {
			if (color == White)
				table[i][j] = BUFFOR_FILLED;
			else
				table[i][j] = 0;
		}
}


uint8_t* Buffer::getBuffer(uint8_t verse){
	return this->table[verse];
}

void Buffer::send_uart (char *string)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)string, strlen (string), HAL_MAX_DELAY);  //TODO change uart
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
	if(ActualFont->getWidth()!=width || ActualFont->getHeight()!=height)
		if(findFont(width, height) == false){
			createFont(width, height);
			findFont(width, height);
		}
	for (uint8_t i = 0; i < strlen((char*)text); i++) {
		uint8_t current_X = coord_X + i * ActualFont->getWidth();
		addLetter(text[i], width, height, color, current_X, coord_Y);
	}
}

void Buffer::createFont(uint8_t width, uint8_t height) {
	const char* path = 0;
	char* read_data;
	char name[20];
	uint32_t size;

	sprintf(name, "doc.json");
	fresult = f_mount(&fs, (const TCHAR*)"/", 1);
	if (fresult != FR_OK)
		send_uart ("ERROR!!! in mounting SD CARD...\n\n");
	fresult = f_stat (name, &fno);
	if (fresult != FR_OK)
		send_uart ("ERRROR!!! file does not exists\n\n");
	else {
		fresult = f_open(&fil, name, FA_READ);		/* Open file to read */
		if (fresult != FR_OK)
			send_uart ("ERROR!!! File not opened...\n\n");
		size = f_size(&fil);
	  	read_data = (char*)malloc(size);
	  	fresult = f_read (&fil,read_data, size, &br);	  	//Read data from the file
	  	send_uart(read_data);
	  	if (fresult != FR_OK) {
	 		free(read_data);
	 		send_uart ("ERROR!!! Problem with reading...\n\n");
		}
  		else  {
	  		/* Close file */
  			fresult = f_close(&fil);
  			if (fresult != FR_OK)
  				send_uart ("ERROR!!! not closed...\n\n");
	  		else
	  			send_uart ("ERROR!!! closed succesfully...\n\n");
	  	}
	}
	fresult = f_mount(NULL, (const TCHAR*)"/", 1);
	if (fresult == FR_OK) send_uart ("SD CARD UNMOUNTED successfully...\n\n\n");
	else send_uart("ERROR!!! in UNMOUNTING SD CARD\n\n\n");;

	const uint8_t capacity = JSON_OBJECT_SIZE(3);
	DynamicJsonDocument doc(1024);
	DeserializationError error = deserializeJson(doc, read_data);
	if (error)
		send_uart("error in json");
	JsonArray array = doc["fonts"];
	uint8_t width_to_see;
	uint8_t height_to_see;
	uint8_t difference = ~0;
	for (JsonObject repo : array) {
		if( (abs(width - repo["width"].as<uint8_t>()) + abs(height - repo["height"].as<uint8_t>())) < difference ){
			path = repo["file"].as<const char*>();
			width_to_see = repo["width"];
			height_to_see = repo["height"];
			difference = abs(width - repo["width"].as<uint8_t>()) + abs(height - repo["height"].as<uint8_t>());
		}
	}
	ActualFont = new Fonts(width, height, width_to_see, height_to_see);
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


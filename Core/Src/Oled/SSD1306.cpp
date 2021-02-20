/*
 * SSD1306.cpp
 *
 *  Created on: 22.03.2020
 *      Author: danie
 */

#include "SSD1306.h"


void SSD1306::reset(void) {
	// CS = High (not selected)
	if(connectionOled==SPI){
		HAL_GPIO_WritePin(CsPort, CsPin, GPIO_PIN_SET);

		// Reset the OLED
		HAL_GPIO_WritePin(ResetPort, ResetPin, GPIO_PIN_RESET);
		HAL_Delay(10);
		HAL_GPIO_WritePin(ResetPort, ResetPin, GPIO_PIN_SET);
		HAL_Delay(10);
	}
}
// Send a byte to the command register
void SSD1306::writeCommand() {
	if (connectionOled==SPI){
		HAL_GPIO_WritePin(CsPort, CsPin, GPIO_PIN_RESET); // select OLED
		HAL_GPIO_WritePin(DcPort, DcPin, GPIO_PIN_RESET); // command
		if (dma_status==SET_ON)
			HAL_SPI_Transmit_DMA(SpiPort, lineCommands, 3);
		else
			HAL_SPI_Transmit(SpiPort, lineCommands, 3, HAL_MAX_DELAY);
	}
	else {
		if (dma_status==SET_ON)
			HAL_I2C_Mem_Write_DMA(I2C_Port, I2C_ADDR, 0x00, 1, lineCommands, 3);
		else
			HAL_I2C_Mem_Write(I2C_Port, I2C_ADDR, 0x00, 1, lineCommands, 3, HAL_MAX_DELAY);
	}
}
// Send data
void SSD1306::writeData() {
	if (connectionOled == SPI){
		HAL_GPIO_WritePin(CsPort, CsPin, GPIO_PIN_RESET); // select OLED
		HAL_GPIO_WritePin(DcPort, DcPin, GPIO_PIN_SET); // data
		if (dma_status == SET_ON){
			HAL_SPI_Transmit_DMA(SpiPort, this->buffer->getBuffer(counter), width);
		}
		else
			HAL_SPI_Transmit(SpiPort, this->buffer->getBuffer(counter), width, HAL_MAX_DELAY);
	}
	else{
		if (dma_status == SET_ON)
			HAL_I2C_Mem_Write_DMA(I2C_Port, I2C_ADDR, 0x40, 1, this->buffer->getBuffer(counter), width);
		else
			HAL_I2C_Mem_Write(I2C_Port, I2C_ADDR, 0x40, 1,this->buffer->getBuffer(counter), width, HAL_MAX_DELAY);
	}
}


void SSD1306::oledInterruptDMA(){

	//if (dma_status == 1){
	if (status==2);
	else if (status==0){
		counter+=1;
		lineCommands[0]=SET_PAGE_START_ADDR + counter;
		lineCommands[1]=LOW_COLUMN_ADDR;
		lineCommands[2]=HIGH_COLUMN_ADDR;
		status=1;
		writeCommand();
	}
	else{
		status=0;
		if (counter==8)
			counter=0;
		writeData();
	}
	//}
}

void SSD1306::init(void) {
	// Reset OLED
	reset();
	// Wait for the screen to boot
	HAL_Delay(100);

	// Init OLED
	initCommands[0]=TURN_OFF;

	initCommands[1]=SET_MEMORY_ADDR_MODE;
	initCommands[2]=HORIZONTAL_ADDR_MODE;

	initCommands[3]=SET_PAGE_START_ADDR;

	if (mirror_vertical_status == SET_ON)
		initCommands[4]=MIRROR_VERTICAL;
	else
		initCommands[4]=COM_SCAN_DIRECTION;

	initCommands[5]=LOW_COLUMN_ADDR;
	initCommands[6]=HIGH_COLUMN_ADDR;

	initCommands[7]=SET_START_LINE_ADDR;

	initCommands[8]=SET_CONTRAST;
	initCommands[9]=CONTRAST;

	if (mirror_horizontal_status == SET_ON)
		initCommands[10]=MIRROR_HORIZONTAL;
	else
		initCommands[10]=SET_SEGMENT_REMAP;

	if (inversion_color_status == SET_ON)
		initCommands[11]=INVERSE_COLOR;
	else
		initCommands[11]=NORMAL_COLOR;

	initCommands[12]=SET_MULTIPLEX_RATIO;
	if (height == 32)
		initCommands[13]=RATIO_32;
	else if (height == 64)
		initCommands[13]=RATIO_64;

	initCommands[14]=OUT_FOLLOW_RAM_CONTENT;

	initCommands[15]=DISPLAY_OFFSET;
	initCommands[16]=DISPLAY_NOT_OFFSET;

	initCommands[17]=SET_CLOCK_DIVIDE_RATIO;
	initCommands[18]=DIVIDE_RATIO;

	initCommands[19]=SET_PRE_CHARGE_PERIOD;
	initCommands[20]=PRE_CHARGE_PERIOD;

	initCommands[21]=SET_COM_PIN;
	if (height == 32)
		initCommands[22]=COM_PIN_32;
	else if (height == 64)
		initCommands[22]=COM_PIN_64;

	initCommands[23]=SET_VCOMH;
	initCommands[24]=VOLTAGE_77;

	initCommands[25]=SET_DC_ENABLE;
	initCommands[26]=DC_ENABLE;
	initCommands[27]=TURN_ON;

	status=2;
	currentX = 0;
	currentY = 0;
	initialized = 1;

	fillBuffer(White);
	if (connectionOled == SPI){
		if (dma_status==SET_ON)
			HAL_SPI_Transmit_DMA(SpiPort, initCommands, 28);
		else
			HAL_SPI_Transmit(SpiPort, initCommands, 28, HAL_MAX_DELAY);
		status=0;
		oledInterruptDMA();
	}
	else{
		if (dma_status==SET_ON)
			HAL_I2C_Mem_Write_DMA(I2C_Port, I2C_ADDR, 0x00, 1, initCommands, 28);
		else
			HAL_I2C_Mem_Write(I2C_Port, I2C_ADDR, 0x00, 1, initCommands, 28, HAL_MAX_DELAY);
		status=0;
		//SPI_Interrupt_DMA();
	}
}

// Fill the whole screen with the given color
void SSD1306::fillBuffer(Color color) {
	/* Set memory */
	this->buffer->fill(color);
}

// Draw 1 char to the screen buffer
// color    => BLACK or WHITE
void SSD1306::writeChar(char ch, uint8_t font_width, uint8_t font_height, Color color, uint8_t coordX,uint8_t coordY) {
	this->buffer->addLetter((uint8_t)ch, font_width, font_height, color, coordX, coordY);
}

// Write full string to screenbuffer
void SSD1306::writeString(char* str,  uint8_t font_width, uint8_t font_height, Color color, uint8_t coordX, uint8_t coordY) {
	this->buffer->addText(str, font_width, font_height, color, coordX, coordY);
}

// Position the cursor
void SSD1306::setCursor(uint8_t x, uint8_t y) {
	if (x > SSD1306_WIDTH)
		x = SSD1306_WIDTH;
	if (y > SSD1306_HEIGHT)
		y = SSD1306_HEIGHT;
	currentX = x;
	currentY = y;
}

SSD1306::SSD1306(OledSettingsI2C oledSettingsI2C){
	this->I2C_Port = oledSettingsI2C.hi2c;
	this->I2C_ADDR = oledSettingsI2C.address;

	//To poniez to chyba do funkcji init, bo nie jest zwiazne a konstruktorzem, ewentualnie parametry poniższe można dodać do OledSettingsI2C np kolejne kole dma_status, i dać im wartosci domysle np dma_status = SET_OFF
	// Wtedy ktos bedzie mógł ustawić te dodatkowe paramrtery, ale jezeli ich nie ustawi i stworzu obiekt OledSettingsI2C to ustawia tylko adres i hi2c, a reszta ma wartosc domyslna, do przemyslenia jak uwazasz ze powinno byc to zrobione
	this->dma_status=SET_OFF;
	this->mirror_vertical_status = SET_OFF;
	this->mirror_horizontal_status = SET_OFF;
	this->inversion_color_status = SET_OFF;
	this->height=64;
	this->width=128;
	allocBuffer();
	connectionOled=I2C;
	counter=7;
	buffer = new Buffer (this->width, this->height);
}

SSD1306::SSD1306(I2C_HandleTypeDef* i2c, int I2C_ADDRESS){
	this->I2C_Port=i2c;
	this->I2C_ADDR=I2C_ADDRESS;
	this->dma_status=SET_OFF;
	this->mirror_vertical_status = SET_OFF;
	this->mirror_horizontal_status = SET_OFF;
	this->inversion_color_status = SET_OFF;
	this->height=64;
	this->width=128;
	allocBuffer();
	connectionOled=I2C;
	counter=7;
	buffer = new Buffer (this->width, this->height);
}

SSD1306::SSD1306(OledSettingsSPI oledSettingsSPI){
	this->SpiPort = oledSettingsSPI.hspi;
	this->ResetPort = oledSettingsSPI.reset.port;
	this->ResetPin = oledSettingsSPI.reset.pin;
	this->CsPort = oledSettingsSPI.cs.port;
	this->CsPin = oledSettingsSPI.cs.pin;
	this->DcPort = oledSettingsSPI.dc.port;
	this->DcPin = oledSettingsSPI.dc.pin;


	//To poniez to chyba do funkcji init, bo nie jest zwiazne a konstruktorzem
	this->dma_status=SET_OFF;
	this->mirror_vertical_status = SET_OFF;
	this->mirror_horizontal_status = SET_OFF;
	this->inversion_color_status = SET_OFF;
	this->height=64;
	this->width=128;
	allocBuffer();
	connectionOled=SPI;
	counter=7;
	buffer = new Buffer (this->width, this->height);
}

SSD1306::SSD1306(SPI_HandleTypeDef* hspi, gpio_struct reset, gpio_struct DC,
		gpio_struct CS) {
	this->SpiPort = hspi;
	this->ResetPort = reset.port;
	this->ResetPin = reset.pin;
	this->CsPort = CS.port;
	this->CsPin = CS.pin;
	this->DcPort = DC.port;
	this->DcPin = DC.pin;
	this->dma_status=SET_OFF;
	this->mirror_vertical_status = SET_OFF;
	this->mirror_horizontal_status = SET_OFF;
	this->inversion_color_status = SET_OFF;
	this->height=64;
	this->width=128;
	allocBuffer();
	connectionOled=SPI;
	counter=7;
	buffer = new Buffer (this->width, this->height);
}

SSD1306::~SSD1306() {
	// TODO Auto-generated destructor stub
}

void SSD1306::changeDMA(State dma){
	dma_status=dma;
}

void SSD1306::changeMirrorHorizontal(State mirror){
	mirror_horizontal_status = mirror;
}

void SSD1306::changeMirrorVertical(State mirror){
	mirror_vertical_status = mirror;
}

void SSD1306::allocBuffer(){
	this->SSD1306_Buffer=new uint8_t[width * height /8];
}

void SSD1306::changeInversionColor(State inversion){
	inversion_color_status = inversion;
}

void SSD1306::changeHeight(uint8_t height){
	this->height=height;
}

void SSD1306::changeWidth(uint8_t width){
	this->width=width;
}

#include "Fonts.h"
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"

#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"
#include "stdlib.h"
#include "cstring"
#include "string.h"
#include "stdio.h"
#include "stm32f4xx_hal.h"

FATFS fs;  // file system
FIL fil; // File
FRESULT fresult;  // result
FILINFO fno;
UINT br, bw;  // File read/write count

void Fonts::send_uart (char *string)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)string, strlen (string), HAL_MAX_DELAY);  //TODO change uart
}

Fonts::Fonts(uint8_t width, uint8_t height, uint8_t width_to_see, uint8_t height_to_see){
	this->width = width;
	this->height = height;
	this->width_to_see = width_to_see;
	this->height_to_see = height_to_see;
}

void Fonts::createFont(const char* path) {
	char* read_data;
	char name[20];
	uint32_t size;

	sprintf(name, path);
	fresult = f_mount(&fs, (const TCHAR*)"/", 1);
	if (fresult != FR_OK)
		send_uart ("ERROR!!! in mounting SD CARD...\n\n");
	else
		send_uart("SD CARD mounted successfully...\n");
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

	  	char *buf = (char*)malloc(100*sizeof(char));
	  	sprintf(buf, "%s", read_data);
	  	send_uart(buf);
	  	free(buf);
	  	if (fresult != FR_OK) {
	 		free(read_data);
	 		send_uart ("ERROR!!! Problem with reading...\n\n");
		}

  		else  {
  			free(read_data);
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

	uint16_t counter = 0;
	uint32_t temp = 0;

	uint32_t table[this->height];
	counter=0;
	temp=0;
	uint8_t counter_width = 0;
	uint8_t counter_height = 0;
	Font = new Letter* [95];
	for (uint8_t i = 0; i < 95; i++) {
		while (counter_height < this->height){
			while (read_data[counter]!='-' && read_data[counter]!='#')
				counter+=1;
			if (read_data[counter+1]!='-'  && read_data[counter+1]!='#')
				counter+=1;
			while (counter_width < this->width) {
				uint8_t a=read_data[counter];
				if(read_data[counter]=='#')
					setBit(temp, counter_width);
				counter_width+=1;
				counter+=1;
			}
			temp=temp;
			counter_width=0;
			table[counter_height] = temp;
			temp=0;
			counter_height+=1;
		}
		counter_height=0;
		Font[i] = new Letter(table, height, width);
	}
}

uint32_t* Fonts::getLetter(uint8_t letter) {
	return Font[letter - 32]->getLetter();
}

uint8_t Fonts::getWidth() {
	return this->width;
}

uint8_t Fonts::getHeight() {
	return this->height;
}

uint8_t Fonts::getWidthSeen() {
	return this->width_to_see;
}

uint8_t Fonts::getHeightSeen() {
	return this->height_to_see;
}

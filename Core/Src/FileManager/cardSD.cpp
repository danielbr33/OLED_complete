/*
 * cardSD.cpp
 *
 *  Created on: 15 lut 2021
 *      Author: danie
 */

#include "cardSD.h"

char* cardSD::readFile(char* path, char* read_data){
	uint32_t size;
	fresult = f_mount(&(this->fs), (const TCHAR*)"/", 1);
	fresult = f_stat (path, &fno);
	fresult = f_open(&fil, path, FA_READ);		/* Open file to read */
	size = f_size(&fil);
  	read_data = (char*)malloc(size);
  	fresult = f_read (&fil,read_data, size, &br);	  	//Read data from the file
  	if (fresult != FR_OK) {
 		free(read_data);
	}
 	else  {
  		/* Close file */
  		fresult = f_close(&fil);
	}
	fresult = f_mount(NULL, (const TCHAR*)"/", 1);
	return read_data;
}

uint16_t cardSD::getSizeOfFile(char* path){
	uint16_t size;
	fresult = f_mount(&(this->fs), (const TCHAR*)"/", 1);
	fresult = f_stat (path, &fno);
	fresult = f_open(&fil, path, FA_READ);		/* Open file to read */
	size = f_size(&fil);
	fresult = f_close(&fil);
	fresult = f_mount(NULL, (const TCHAR*)"/", 1);
	return size;
}


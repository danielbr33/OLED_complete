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

cardSD::SD_Status cardSD::readFile(char* path, char** read_data){
	uint32_t size;
	fresult = f_mount(&(this->fs), (const TCHAR*)"/", 1);
	if(fresult != FR_OK)
		return SD_ERROR;
	fresult = f_stat (path, &fno);
	if(fresult != FR_OK)
		return SD_ERROR;
	fresult = f_open(&fil, path, FA_READ);		/* Open file to read */
	if(fresult != FR_OK)
		return SD_ERROR_READ;
	size = f_size(&fil);
  	*read_data = (char*)malloc(size);
  	fresult = f_read (&fil,*read_data, size, &br);	  	//Read data from the file
  	if (fresult != FR_OK) {
 		free(*read_data);
 		return SD_ERROR_READ;
	}
 	else  {
  		/* Close file */
  		fresult = f_close(&fil);
  		if(fresult != FR_OK)
  			return SD_ERROR;
	}
	fresult = f_mount(NULL, (const TCHAR*)"/", 1);
	if(fresult != FR_OK)
		return SD_ERROR;
	return SD_OK;
}

cardSD::SD_Status cardSD::getSizeOfFile(char* path, uint32_t* size){
	fresult = f_mount(&(this->fs), (const TCHAR*)"/", 1);
	if(fresult != FR_OK)
		return SD_ERROR;
	fresult = f_stat (path, &fno);
	if(fresult != FR_OK)
		return SD_ERROR;
	fresult = f_open(&fil, path, FA_READ);		/* Open file to read */
	if(fresult != FR_OK)
		return SD_ERROR_READ;
	//*size = f_size(&fil);
	fresult = f_close(&fil);
	if(fresult != FR_OK)
		return SD_ERROR;
	fresult = f_mount(NULL, (const TCHAR*)"/", 1);
	if(fresult != FR_OK)
		return SD_ERROR;
	return SD_OK;
}

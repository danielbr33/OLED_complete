/*
 * cardSD.cpp
 *
 *  Created on: 15 lut 2021
 *      Author: danie
 */

#include "cardSD.h"

char* cardSD::readFile(char* path){
	//To przerzucic do osobnej klasu obsługuje karte SD, zobacz sobie na to repo, to co pisała marta, ja to poprawiłem https://github.com/rvbc1/STM32_Flash_Memory, obecnie jest tylko poprawny zapis tam
		// w klasie FlashMemoryManager.cpp w funkcji writeDataInMemory przekazywana jest ilosc bajktów i bajkty do zapisu, w klasie kary powinno byc podobnie, tylko jeszcze scieza do polku. Ale ogólnie popatrze na to bo ja to tam juz dosc mocno przekopałem i jest w miare dobrze napisane

	uint32_t size;
	char* read_data;
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


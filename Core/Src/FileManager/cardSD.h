/*
 * cardSD.h
 *
 *  Created on: 15 lut 2021
 *      Author: danie
 */
#include "ArduinoJson-v6.15.2.h"
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


#ifndef SRC_FILEMANAGER_CARDSD_H_
#define SRC_FILEMANAGER_CARDSD_H_

class cardSD {
private:
	cardSD() {}
	cardSD(const cardSD &);
	~cardSD(){}
	FATFS fs;  // file system
	FIL fil; // File
	FRESULT fresult;  // result
	FILINFO fno;
	UINT br, bw;  // File read/write count

public:
	static cardSD& getInstance(){
		static cardSD instance;
		return instance;
	}
	char* readFile(char* path);
};

#endif /* SRC_FILEMANAGER_CARDSD_H_ */

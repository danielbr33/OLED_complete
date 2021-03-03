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
#include "stdlib.h"
#include "cstring"
#include "string.h"


#ifndef SRC_FILEMANAGER_CARDSD_H_
#define SRC_FILEMANAGER_CARDSD_H_

class cardSD {
private:
	cardSD() = default;
	FATFS fs;  // file system
	FIL fil; // File
	FRESULT fresult;  // result
	FILINFO fno;
	UINT br, bw;  // File read/write count

public:
	cardSD(cardSD const&) = delete;
	void operator=(cardSD const&) = delete;
	~cardSD(){}
	static cardSD& getInstance(){
		static cardSD instance;
		return instance;
	}
	char* readFile(char* path, char* read_data);
	uint16_t getSizeOfFile(char* path);

};

#endif /* SRC_FILEMANAGER_CARDSD_H_ */

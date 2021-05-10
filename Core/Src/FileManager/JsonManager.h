/*
 * JsonFonts.h
 *
 *  Created on: 16 lut 2021
 *      Author: danie
 */
#include <vector>
#include <cardSD.h>
#include <ArduinoJson-v6.17.3.h>

#ifndef SRC_FILEMANAGER_JSONFONTS_H_
#define SRC_FILEMANAGER_JSONFONTS_H_

class JsonManager {
public:
	JsonManager(JsonManager const&) = delete;
	void operator=(JsonManager const&) = delete;
	virtual ~JsonManager();
	static JsonManager& getInstance(){
		static JsonManager instance;
		return instance;
	}
	typedef enum {JSON_OK, JSON_ERROR, SD_ERROR} Json_Status;
	Json_Status getJsonDocument(char *path, StaticJsonDocument<1024>* doc);
private:
	JsonManager();
};

#endif /* SRC_FILEMANAGER_JSONFONTS_H_ */

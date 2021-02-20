/*
 * JsonFonts.h
 *
 *  Created on: 16 lut 2021
 *      Author: danie
 */
#include <vector>
#include <cardSD.h>
#include <ArduinoJson-v6.15.2.h>

#ifndef SRC_FILEMANAGER_JSONFONTS_H_
#define SRC_FILEMANAGER_JSONFONTS_H_

class JsonManager {
private:
	JsonManager();
	StaticJsonDocument<1024> doc;
public:
	JsonManager(JsonManager const&) = delete;
	void operator=(JsonManager const&) = delete;
	virtual ~JsonManager();
	static JsonManager& getInstance(){
		static JsonManager instance;
		return instance;
	}
	StaticJsonDocument<1024>& getJsonDocument();
};

#endif /* SRC_FILEMANAGER_JSONFONTS_H_ */

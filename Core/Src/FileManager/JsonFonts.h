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

class JsonFonts {
private:
	JsonFonts();

	struct FontsSettings{
		std::string font;
		uint8_t height;
		uint8_t width;
		string path;
	};
	FontsSettings actualSettings;
	vector<FontsSettings> fontsSettings;

public:
	JsonFonts(JsonFonts const&) = delete;
	void operator=(JsonFonts const&) = delete;
	virtual ~JsonFonts();
	static JsonFonts& getInstance(){
		static JsonFonts instance;
		return instance;
	}

	void findFontToCreate(uint8_t width, uint8_t height);
	string getPath(uint8_t width, uint8_t height);
	uint8_t getWidth(uint8_t width, uint8_t height);
	uint8_t getHeight(uint8_t width, uint8_t height);
};

#endif /* SRC_FILEMANAGER_JSONFONTS_H_ */

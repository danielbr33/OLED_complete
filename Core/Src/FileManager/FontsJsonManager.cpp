/*
 * FontsFontsJsonManager.cpp
 *
 *  Created on: 20 lut 2021
 *      Author: danie
 */

#include <FontsJsonManager.h>

FontsJsonManager::FontsJsonManager() {
	// TODO Auto-generated constructor stub
	StaticJsonDocument<1024> document;
	jsonFontsStatus = JSON_OK;
	JsonManager::Json_Status jsonTempStatus;
	jsonTempStatus = JsonManager::getInstance().getJsonDocument("FontsJson.json", document);
	if(jsonTempStatus == JsonManager::SD_ERROR){
		jsonFontsStatus = JSON_SD_ERR;
	}
	else if(jsonTempStatus == JsonManager::JSON_ERROR){
		jsonFontsStatus = JSON_READ_ERR;
	}
	else if(jsonTempStatus == JsonManager::JSON_OK){
		if(document.containsKey("fonts")){
			JsonArray array = document["fonts"];
			for (JsonObject repo : array) {
				if(repo.containsKey("font"))
					actualFontSettings.font = repo["font"].as<string>();
				if(repo.containsKey("width"))
					actualFontSettings.width = repo["width"].as<uint8_t>();
				if(repo.containsKey("height"))
					actualFontSettings.height = repo["height"].as<uint8_t>();
				if(repo.containsKey("file"))
					actualFontSettings.path = repo["file"].as<string>();
				uint64_t temp3 = xPortGetFreeHeapSize();
				fontsSettings.push_back(actualFontSettings);
			}
		}
		else
			jsonFontsStatus = JSON_KEY_ERR;
	}
}

FontsJsonManager::Json_FontsStatus FontsJsonManager::getJsonFontsStatus(){
	return jsonFontsStatus;
}

FontsJsonManager::~FontsJsonManager() {
	// TODO Auto-generated destructor stub
}

void FontsJsonManager::findFontToCreate(uint8_t width, uint8_t height){
	uint8_t difference = ~0;
	for (uint8_t i = 0; i <fontsSettings.size(); i++) {
		if( (abs(width - fontsSettings[i].width) + abs(height - fontsSettings[i].height)) < difference ){
			actualFontSettings.path = fontsSettings[i].path;
			actualFontSettings.width = fontsSettings[i].width;
			actualFontSettings.height = fontsSettings[i].height;
			actualFontSettings.font = fontsSettings[i].font;
			difference = abs(width - fontsSettings[i].width) + abs(height - fontsSettings[i].height);
		}
	}
}

void FontsJsonManager::findFontToCreate(string name){
	for (uint8_t i = 0; i <fontsSettings.size(); i++) {
		if(name == fontsSettings[i].font){
			actualFontSettings.path = fontsSettings[i].path;
			actualFontSettings.width = fontsSettings[i].width;
			actualFontSettings.height = fontsSettings[i].height;
			actualFontSettings.font = fontsSettings[i].font;
		}
	}
}

string FontsJsonManager::getPath(uint8_t width, uint8_t height){
	findFontToCreate(width, height);
	if(&actualFontSettings.path)
		return actualFontSettings.path;
	else
		return "NO_FONT";
}

uint8_t FontsJsonManager::getWidth(uint8_t width, uint8_t height){
	findFontToCreate(width, height);
	if (&actualFontSettings.width)
		return actualFontSettings.width;
	else
		return NO_FONT_ERROR;
}

uint8_t FontsJsonManager::getHeight(uint8_t width, uint8_t height){
	findFontToCreate(width, height);
	if (&actualFontSettings.height)
		return actualFontSettings.height;
	else
		return NO_FONT_ERROR;
}

string FontsJsonManager::getName(uint8_t width, uint8_t height){
	findFontToCreate(width, height);
	if (&actualFontSettings.font)
		return actualFontSettings.font;
	else
		return "NO_FONT";
}

string FontsJsonManager::getPath(string name){
	findFontToCreate(name);
	if(&actualFontSettings.path)
		return actualFontSettings.path;
	else
		return "NO_FONT";
}

uint8_t FontsJsonManager::getWidth(string name){
	findFontToCreate(name);
	if (&actualFontSettings.width)
		return actualFontSettings.width;
	else
		return NO_FONT_ERROR;
}

uint8_t FontsJsonManager::getHeight(string name){
	findFontToCreate(name);
	if (&actualFontSettings.height)
		return actualFontSettings.height;
	else
		return NO_FONT_ERROR;
}

string FontsJsonManager::getName(string name){
	findFontToCreate(name);
	if (&actualFontSettings.font)
		return actualFontSettings.font;
	else
		return "NO_FONT";
}



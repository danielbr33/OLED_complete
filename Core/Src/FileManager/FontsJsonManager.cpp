/*
 * FontsFontsJsonManager.cpp
 *
 *  Created on: 20 lut 2021
 *      Author: danie
 */

#include <FontsJsonManager.h>

FontsJsonManager::FontsJsonManager() {
	// TODO Auto-generated constructor stub
	DynamicJsonDocument doc(1024);
	json_fonts_status = JSON_OK;
	if(JsonManager::getInstance().getJsonStatus() == JsonManager::SD_ERROR){
		json_fonts_status = JSON_SD_ERR;
	}
	else if(JsonManager::getInstance().getJsonStatus() == JsonManager::JSON_ERROR){
		json_fonts_status = JSON_READ_ERR;
	}
	else if(JsonManager::getInstance().getJsonStatus() == JsonManager::JSON_OK){
		if(JsonManager::getInstance().getJsonDocument().containsKey("fonts")){
			JsonArray array = JsonManager::getInstance().getJsonDocument()["fonts"];
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
			json_fonts_status = JSON_KEY_ERR;
	}
}

FontsJsonManager::Json_FontsStatus FontsJsonManager::getJsonFontsStatus(){
	return json_fonts_status;
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
	return actualFontSettings.path;
}

uint8_t FontsJsonManager::getWidth(uint8_t width, uint8_t height){
	findFontToCreate(width, height);
	return actualFontSettings.width;
}

uint8_t FontsJsonManager::getHeight(uint8_t width, uint8_t height){
	findFontToCreate(width, height);
	return actualFontSettings.height;
}

string FontsJsonManager::getName(uint8_t width, uint8_t height){
	findFontToCreate(width, height);
	return actualFontSettings.font;
}

string FontsJsonManager::getPath(string name){
	findFontToCreate(name);
	return actualFontSettings.path;
}

uint8_t FontsJsonManager::getWidth(string name){
	findFontToCreate(name);
	return actualFontSettings.width;
}

uint8_t FontsJsonManager::getHeight(string name){
	findFontToCreate(name);
	return actualFontSettings.height;
}

string FontsJsonManager::getName(string name){
	findFontToCreate(name);
	return actualFontSettings.font;
}



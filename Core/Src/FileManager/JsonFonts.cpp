/*
 * JsonFonts.cpp
 *
 *  Created on: 16 lut 2021
 *      Author: danie
 */

#include <JsonFonts.h>
#include <cardSD.h>

JsonFonts::JsonFonts() {
	// TODO Auto-generated constructor stub
	char* path = "FontsJson.json";
	char* read_data;
	uint16_t size;
	size = cardSD::getInstance().getSizeOfFile((char*)path);
	read_data = cardSD::getInstance().readFile((char*)path, read_data);
	DynamicJsonDocument doc(1024);
	DeserializationError error = deserializeJson(doc, read_data);
	JsonArray array = doc["fonts"];
	for (JsonObject repo : array) {
//	//	if( (abs(width - repo["width"].as<uint8_t>()) + abs(height - repo["height"].as<uint8_t>())) < difference ){ //kod powinien byc bezpieczny jak korzystasz z jsona to sprawdz czy posida dane pole np repo.containsKey("width")
		path = (char*)repo["file"].as<const char*>();
		actualSettings.font = repo["font"].as<string>();
		actualSettings.width = repo["width"].as<uint8_t>();
		actualSettings.height = repo["height"].as<uint8_t>();
		actualSettings.path = repo["file"].as<string>();
		uint64_t temp3 = xPortGetFreeHeapSize();
		fontsSettings.push_back(actualSettings);
	}
}

void JsonFonts::findFontToCreate(uint8_t width, uint8_t height){
	uint8_t difference = ~0;
	for (uint8_t i = 0; i <fontsSettings.size(); i++) {
		if( (abs(width - fontsSettings[i].width) + abs(height - fontsSettings[i].height)) < difference ){ //kod powinien byc bezpieczny jak korzystasz z jsona to sprawdz czy posida dane pole np repo.containsKey("width")
			actualSettings.path = fontsSettings[i].path;
			actualSettings.width = fontsSettings[i].width;
			actualSettings.height = fontsSettings[i].height;
			difference = abs(width - fontsSettings[i].width) + abs(height - fontsSettings[i].height);
		}
	}
}

string JsonFonts::getPath(uint8_t width, uint8_t height){
	findFontToCreate(width, height);
	return actualSettings.path;
}

uint8_t JsonFonts::getWidth(uint8_t width, uint8_t height){
	findFontToCreate(width, height);
	return actualSettings.width;
}

uint8_t JsonFonts::getHeight(uint8_t width, uint8_t height){
	findFontToCreate(width, height);
	return actualSettings.height;
}

JsonFonts::~JsonFonts() {
	// TODO Auto-generated destructor stub
}


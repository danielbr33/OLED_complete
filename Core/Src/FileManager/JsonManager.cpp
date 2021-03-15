/*
 * JsonFonts.cpp
 *
 *  Created on: 16 lut 2021
 *      Author: danie
 */

#include <JsonManager.h>

JsonManager::JsonManager() {
	// TODO Auto-generated constructor stub
	char* path = "FontsJson.json";
	char* read_data;
	uint8_t sd_status;
	sd_status = cardSD::getInstance().readFile((char*)path, &read_data);
	DeserializationError error = deserializeJson(doc, read_data);
	delete (read_data);
}

JsonManager::~JsonManager() {
	// TODO Auto-generated destructor stub
}

StaticJsonDocument<1024>& JsonManager::getJsonDocument(){
	return doc;
}

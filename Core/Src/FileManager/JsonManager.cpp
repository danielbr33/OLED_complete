/*
 * JsonFonts.cpp
 *
 *  Created on: 16 lut 2021
 *      Author: danie
 */

#include <cardSD.h>
#include <JsonManager.h>

JsonManager::JsonManager() {
	// TODO Auto-generated constructor stub
	char* path = "FontsJson.json";
	char* read_data;
	uint16_t size;
	size = cardSD::getInstance().getSizeOfFile((char*)path);
	read_data = new char[size];
	read_data = cardSD::getInstance().readFile((char*)path, read_data);
	DeserializationError error = deserializeJson(doc, read_data);
	delete (read_data);
}

JsonManager::~JsonManager() {
	// TODO Auto-generated destructor stub
}

StaticJsonDocument<1024>& JsonManager::getJsonDocument(){
	return doc;
}

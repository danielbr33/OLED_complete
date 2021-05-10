/*
 * JsonFonts.cpp
 *
 *  Created on: 16 lut 2021
 *      Author: danie
 */

#include <JsonManager.h>

JsonManager::JsonManager() {
	// TODO Auto-generated constructor stub
}

JsonManager::~JsonManager() {
	// TODO Auto-generated destructor stub
}

JsonManager::Json_Status JsonManager::getJsonDocument(char *path, StaticJsonDocument<1024>* doc){
	Json_Status json_status;
	char* read_data = nullptr;
	cardSD::SD_Status sd_status;
	json_status = JSON_OK;
	sd_status = cardSD::getInstance().readFile((char*)path, &read_data);
	if (sd_status != cardSD::SD_OK){
		json_status = SD_ERROR;
		if(read_data!=nullptr)
			delete(read_data);
		return json_status;
	}
	if(json_status == JSON_OK){
		DeserializationError error = deserializeJson(*doc, read_data);
		if (error){
			json_status = JSON_ERROR;
			if(read_data!=nullptr)
				delete(read_data);
			return json_status;
		}
	}
	delete (read_data);
	return json_status;
}

/*
 * ErrorCRC.cpp
 *
 *  Created on: 29 mar 2021
 *      Author: danie
 */

#include <ErrorsOLED.h>

ErrorsOLED::ErrorsOLED() {
	// TODO Auto-generated constructor stub

}

ErrorsOLED::~ErrorsOLED() {
	// TODO Auto-generated destructor stub
}

string ErrorsOLED::getNameOfError(uint8_t value){
	for (uint8_t i=0; i<errors.size(); i++){
		if(errors[i]->value == value)
			return errors[i]->name;
	}
}

void ErrorsOLED::addError(string name, uint8_t value){
	ErrorBank *err;
	err = new ErrorBank;
	err->name = name;
	err->value = value;
	errors.push_back(err);
	delete err;
}

string ErrorsOLED::getAllValues(){
	stringstream stream;
	for (uint8_t i=0; i<errors.size(); i++){
		stream << hex << errors[i]->value;
		stream << ' ';
	}
	string result( stream.str() );
	return result;
}


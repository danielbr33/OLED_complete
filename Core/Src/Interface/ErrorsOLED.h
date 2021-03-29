/*
 * ErrorCRC.h
 *
 *  Created on: 29 mar 2021
 *      Author: danie
 */

#ifndef SRC_INTERFACE_ERRORSOLED_H_
#define SRC_INTERFACE_ERRORSOLED_H_

#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class ErrorsOLED {
public:
	ErrorsOLED();
	virtual ~ErrorsOLED();
	void addError(string name, uint8_t value);
	string getNameOfError(uint8_t value);
	string getAllValues();
private:
	struct ErrorBank{
		uint8_t value;
		string name;
	};
	vector<ErrorBank*> errors;
};

#endif /* SRC_INTERFACE_ERRORSOLED_H_ */

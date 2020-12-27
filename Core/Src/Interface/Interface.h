#include "List.h"

#ifndef INTERFACE_H_
#define INTERFACE_H_

class Interface{
private :
	Parameter *battery_voltage ;
	Parameter *work_time ;
	Parameter *distance ;
	Parameter *energy_consumed ;
	Parameter *temperature ;
	void get_Value() ;
	List *list_of_elements ;

public:
	Interface() ;
	void sendAction(Interface_Element::Button) ;
	void displayError();
	void refresh() ;
	uint8_t isNoChangeableErrorCounting() ;
	string getParameterHeadline() ;
	uint8_t isBackFromSubListParameter() ;
	uint8_t hasSubList() ;
	uint8_t isVisibleValue() ;
	string getParameterUnit() ;
	uint16_t getParameterValue() ;
};

#endif /* INTERFACE_H_ */

#include "Interface_Element.h"

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <iostream>
#include <cstdio>
#include <stdint.h>
#include <cstdlib>
using namespace std;

class List;

class Parameter {
private:
	string headline;
	uint16_t value ;
	string unit;
    uint8_t edit_mode ;
    List *list;
    uint8_t in_sub_list = false ;
    uint8_t has_sub_list = false;
    uint8_t visible_value = true ;
    uint8_t changeable_value ;
    void createList();
    uint8_t back_from_sub_list = false ;
    uint8_t visible_no_changeable_error = false ;
    uint8_t edit_mode_counting = false ;
    uint8_t no_changeable_error_counting = false ;
    uint8_t start_counting_no_changeable_error = false ;

public:
	Parameter(string, uint16_t = 0 , string = "" , uint8_t = false ) ;
	Interface_Element::Action getButton(Interface_Element::Button) ;
	void sendErrorNoChangeable() ;
    Parameter* getParametr();
	void addToSubList(Parameter *p);
	string getHeadLine();
	List* getSubList() ;
	uint8_t ifHasSubList() ;
	uint8_t ifInSubList() ;
	Parameter* getLastElementOfSubList() ;
	void setOutOfSubList() ;
	void newMove(Interface_Element::Action action) ;
	void refreshEditMode() ;
	void refreshNoChangeableError() ;
	void setAsBackParameter() ;
	uint8_t isBackParameter() ;
	void addBackParameterToList() ;
	void closeLastOpenSubList() ;
    uint16_t getValue() ;
	uint8_t isCountingNoChangeableError() ;
	string getUnit() ;
	uint8_t isValueVisible();
};


#endif /* PARAMETER_H_ */

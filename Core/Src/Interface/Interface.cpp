#include "Interface.h"
Interface::Interface(){

	list_of_elements = new List();

	list_of_elements->addParameter(new Parameter("U battery" , 7.4 , "V", 0 )) ;
	list_of_elements->addParameter(new Parameter("Work time" , 2 , "h", 1)) ;
	list_of_elements->addParameter(new Parameter("Distance" , 100 , "m", 1)) ;
	list_of_elements->addParameter(new Parameter("En consumed" , 3 , "kWh", 0)) ;
	list_of_elements->addParameter(new Parameter("Temperature" , 20 , "C" , 0)) ;

	Parameter *pid = new Parameter("pid", 3, "P I D", 0);
	pid->addToSubList(new Parameter("P" , 20 , "kp" , 1));
	pid->addToSubList(new Parameter("I" , 20 , "ki" , 1));
	pid->addToSubList(new Parameter("D" , 20 , "kd" , 1));
	list_of_elements->addParameter(pid);
}

void Interface::sendAction(Interface_Element::Button button){

	Interface_Element::Action action = list_of_elements->getParameter()->getButton(button);

	switch(action){
        case Interface_Element::ERROR_NO_CHANGEABLE:
            displayError() ;
            break ;

        case Interface_Element::MOVE_LEFT :
            list_of_elements->moveLeft() ;
            break ;

        case Interface_Element::MOVE_RIGHT:
            list_of_elements->moveRight();
            break ;

        case Interface_Element::SET_OUT_OF_SUB_LIST:
            list_of_elements->setOutOfSubList() ;
            break ;
	}
}
void Interface::displayError(){
    list_of_elements->getParameter()->sendErrorNoChangeable() ;
}

void Interface::refresh(){
    list_of_elements->getParameter()->refreshEditMode() ;
    list_of_elements->getParameter()->refreshNoChangeableError() ;
}

uint8_t Interface::isNoChangeableErrorCounting(){
    return list_of_elements->getParameter()->isCountingNoChangeableError() ;
}
string Interface::getParameterHeadline(){
    return list_of_elements->getParameter()->getHeadLine() ;
}
uint8_t Interface::isBackFromSubListParameter(){
    return list_of_elements->getParameter()->isBackParameter() ;
}
uint8_t Interface::hasSubList(){
    return list_of_elements->getParameter()->ifHasSubList() ;
}
uint8_t Interface::isVisibleValue(){
    return list_of_elements->getParameter()->isValueVisible();
}
uint16_t Interface::getParameterValue(){
    return list_of_elements->getParameter()->getValue() ;
}
string Interface::getParameterUnit(){
    return list_of_elements->getParameter()->getUnit() ;
}

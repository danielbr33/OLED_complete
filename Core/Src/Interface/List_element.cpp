#include "List_element.h"

List_element::List_element(Parameter *parametr) {
     parameter_element  = parametr ;
}

void List_element::setNextPointer(List_element *next_pointer ){
    next = next_pointer ;
}
void List_element::setPrevPointer(List_element *prev_pointer ){
    prev = prev_pointer ;
}

List_element* List_element::getNextPointer() {
    return next ;
}
List_element* List_element::getPrevPointer() {
    return prev ;
}

Parameter* List_element::getCurrentParameter(){
    return parameter_element->getParametr() ; //return sub list parameter
}

Parameter* List_element::getMainParameter(){
    return parameter_element ;
}

/*
void List_element::print(){
	cout<<parameter_element->getHeadLine() << endl;
}
*/

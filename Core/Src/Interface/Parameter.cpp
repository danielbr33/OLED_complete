#include "Parameter.h"
#include "List.h"
#define EDIT_MODE_TIME 10
#define ERROR_TIME 10

Parameter::Parameter(string h, uint16_t v, string u , uint8_t ch ){
	headline = h;
	value = v ;
	unit = u ;
	changeable_value = ch;
	edit_mode = false ;
}

List* Parameter::getSubList(){
    if( has_sub_list)
        return list ;
}
void Parameter::createList(){
    list = new List();
    has_sub_list = true;
    list->addBackParameter() ;
}

void Parameter::addBackParameterToList(){
    list->addBackParameter() ;
}

void Parameter::addToSubList(Parameter *p){
	if( !has_sub_list)
        createList() ;
    list->addParameter(p) ;
}

uint8_t Parameter::ifHasSubList(){
    return has_sub_list ;
}

uint8_t Parameter::ifInSubList(){
    return in_sub_list ;
}

void Parameter::refreshEditMode(){
    if(edit_mode){
        edit_mode_counting++ ;
        if(edit_mode_counting > EDIT_MODE_TIME){
            edit_mode_counting = false ;
            visible_value = !visible_value ;
        }
    }
}

void Parameter::refreshNoChangeableError(){
    if(start_counting_no_changeable_error)
        no_changeable_error_counting++ ;
    if(no_changeable_error_counting > ERROR_TIME ){
        no_changeable_error_counting = false ;
        start_counting_no_changeable_error = false ;
    }
}

void Parameter::sendErrorNoChangeable(){
    start_counting_no_changeable_error = true ;
}

Parameter* Parameter::getParametr(){
    if(has_sub_list && in_sub_list)
        return list->getParameter();
    else
        return this ;
}

Interface_Element::Action Parameter::getButton(Interface_Element::Button button){

    if( button == Interface_Element::ENTER){
        if(edit_mode){
                edit_mode = false ;
                visible_value = true ;
        }
        else{
            if(changeable_value){
                edit_mode = true ;
                visible_value = false ;
                edit_mode_counting = false ;
            }
            else if(has_sub_list){
                 in_sub_list = true ;
            }
            else if(back_from_sub_list)
                return Interface_Element::SET_OUT_OF_SUB_LIST ;
            else
                return Interface_Element::ERROR_NO_CHANGEABLE;
        }
        return Interface_Element::DO_NOTHING ;
    }
    else if(edit_mode) {
        visible_value = true ;
        edit_mode_counting = false ;
		if(button == Interface_Element::RIGHT_BUTTON){
			value++;
			return Interface_Element::DO_NOTHING ;
		}
		else if(button == Interface_Element::LEFT_BUTTON){
            value--;
            return Interface_Element::DO_NOTHING ;
		}
    }
    else if( button == Interface_Element::LEFT_BUTTON){
        return Interface_Element::MOVE_LEFT ;
    }
    else if( button == Interface_Element::RIGHT_BUTTON){
        return Interface_Element::MOVE_RIGHT ;
    }
}

string Parameter::getHeadLine(){
	return this->headline;
}

void Parameter::setOutOfSubList(){
    in_sub_list = false ;
    list->resetSubList() ;
}

void Parameter::newMove(Interface_Element::Action action){

   if(action == Interface_Element::MOVE_RIGHT)
        list->moveRight() ;
    else if( action == Interface_Element::MOVE_LEFT)
        list->moveLeft() ;
}
void Parameter::closeLastOpenSubList(){
    if( in_sub_list ){
        if( list->hasOpenSubList())
            list->setOutOfSubList() ;
        else
          setOutOfSubList() ;
    }
}
void Parameter::setAsBackParameter(){
    back_from_sub_list = true ;
}

uint8_t Parameter::isBackParameter(){
    return back_from_sub_list ;
}
uint8_t Parameter::isCountingNoChangeableError(){
    return no_changeable_error_counting ;
}
uint8_t Parameter::isValueVisible(){
    return visible_value ;
}
uint16_t Parameter::getValue(){
    return value ;
}
string Parameter::getUnit(){
    return unit ;
}

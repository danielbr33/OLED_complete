#include "List.h"

//#define DEBUG

#ifdef DEBUG
string intToStr(int n){
	string tmp, ret;
	if(n < 0) {
		ret = "-";
		n = -n;
	}
	do {
		tmp += n % 10 + 48;
		n -= n % 10;
	}
	while(n /= 10);
	for(int i = tmp.size()-1; i >= 0; i--)
		ret += tmp[i];
	return ret;
}
#endif

List::List( ){

}

void List::addFirstElement(List_element *element){
	first_element = current_element = last_element = element;
	size++;
}

void List::addLastElement(List_element *element){

    last_element->setNextPointer(element) ;
    first_element->setPrevPointer(element) ;
    element->setPrevPointer(last_element) ;
    last_element = element;
    last_element->setNextPointer(first_element) ;
	size++;
}

void List::addBeforeTheLastOne(List_element *element){
    if(size == 1 ){
        first_element = current_element = element ;
        last_element->setNextPointer(first_element) ;
        first_element->setPrevPointer(last_element) ;
    }
    else{
        last_element->getPrevPointer()->setNextPointer(element) ;
        element->setPrevPointer(last_element->getPrevPointer()) ;
    }
    last_element->setPrevPointer(element) ;
    element->setNextPointer(last_element) ;
    size++ ;

}

void List::addBackParameter(){

    Parameter *Back = new Parameter("BACK") ;
    addParameter(Back) ;
    Back->setAsBackParameter() ;
}

void List::addParameter(Parameter *parameter){
#ifdef DEBUG
	cout << "Dodawnie " + intToStr(size) + " elementu:" << endl;
	cout << parameter->getHeadLine() << endl;
#endif

	if(size == false){
		addFirstElement(new List_element(parameter));
	}else if( last_element->getMainParameter()->isBackParameter())
        addBeforeTheLastOne(new List_element(parameter)) ;
	 else {
		addLastElement(new List_element(parameter));
	}

#ifdef DEBUG
	cout << "Dodano, aktualny rozmiar listy: " << size << endl << endl;
#endif
	//     first_pointer =  ;
	//    if(first_element == 0)
	//    {
	//        cout << "Pierwszy " << endl;
	//
	//      current_element = first_element ;
	//    }
	//    else{
	//            cout << "Nie pierwszy " << endl;
	//        last_element = new List_element(parameter) ;
	//
	//        current_element->set_Next_Pointer(last_element);
	//       // first_element->set_Prev_Pointer(last_element);
	//
	//        last_element->set_Next_Pointer(first_element);
	//        //last_element->set_Prev_Pointer(current_element);
	//
	//        current_element = last_element ;
	//    }

}

Parameter* List::getParameter(){
    return current_element->getCurrentParameter() ;
}
/*
void List::print(){
	cout << "Rozmiar listy: " << size << endl;
	List_element *printing_element = first_element;
	for(int i = 0; i <size; i++){
		cout << "element: " << i << endl;
		cout << printing_element->getCurrentParameter()->getHeadLine() << endl;
		printing_element = printing_element->getNextPointer();
	}
}
*/
uint16_t List::getSize(){
    return size ;
}

void List::moveRight(){

    if(current_element->getMainParameter()->ifInSubList())
        current_element->getMainParameter()->newMove(Interface_Element::MOVE_RIGHT);
    else
        current_element = current_element->getNextPointer() ;

}

void List::moveLeft(){
    if( current_element->getMainParameter()->ifInSubList()){
        current_element->getMainParameter()->newMove(Interface_Element::MOVE_LEFT) ;
    }
    else
        current_element = current_element->getPrevPointer();
}
void List::setOutOfSubList(){

    current_element->getMainParameter()->closeLastOpenSubList() ;

}

void List::resetSubList(){
    current_element = first_element ;
}

uint8_t List::hasOpenSubList(){
    return current_element->getMainParameter()->ifInSubList() ;
}

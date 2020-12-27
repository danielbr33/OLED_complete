#include "List_element.h"
#ifndef LIST_H_
#define LIST_H_

class Back ;
class List{
private:

    List_element *current_element;
    List_element *last_element ;
    List_element *first_element ;

    void addFirstElement(List_element *element);
    void addLastElement(List_element *element);
    void addBeforeTheLastOne(List_element *element);

    uint16_t size = false;

public :
    List();
    Parameter* getParameter();
    void addParameter(Parameter *parameter) ;
    void addBackParameter();
    void moveRight() ;
    void moveLeft() ;
    uint16_t getSize() ;
    void resetSubList() ;
    void print();
    void setOutOfSubList() ;
    uint8_t hasOpenSubList() ;
};
#endif /* LIST_H_ */

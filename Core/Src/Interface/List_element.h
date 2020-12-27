#include "Parameter.h"

#ifndef LISTELEMENT_H_
#define LISTELEMENT_H_

class List_element{

  private:
      List_element *next , *prev;
      Parameter *parameter_element ;
  public:
      List_element(Parameter *parametr);

      List_element* getNextPointer() ;
      List_element* getPrevPointer() ;
      Parameter* getCurrentParameter() ;
      Parameter* getMainParameter() ;

      void setNextPointer(List_element *next_pointer ) ;
      void setPrevPointer(List_element *prev_pointer ) ;

      void print();
};
#endif /* LISTELEMENT_H_ */

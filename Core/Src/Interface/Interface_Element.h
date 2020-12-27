#ifndef INTERFACEELEMENT_H_
#define INTERFACEELEMENT_H_

class Interface_Element {
public:
	enum Button{LEFT_BUTTON, ENTER, RIGHT_BUTTON};
	enum Action{DO_NOTHING, PRINT, ERROR_NO_CHANGEABLE, MOVE_RIGHT , MOVE_LEFT , SET_OUT_OF_SUB_LIST};

private:
	Interface_Element();
//	virtual ~Interface_Element();
};

#endif /* INTERFACEELEMENT_H_ */

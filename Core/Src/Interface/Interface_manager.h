#include <ErrorsOLED.h>
#include "Interface.h"
#include "stm32f4xx_hal.h"
#include "SSD1306.h"

#ifndef INTERFACEMANAGER_H_
#define INTERFACEMANAGER_H_
#ifdef __cplusplus
extern SSD1306* oled;

class Interface_manager{
public:
	Interface_manager(UART_HandleTypeDef* huart, SSD1306* oled) ;
	void interrupt();
	void init();
	ErrorsOLED* getErrorObject();
private:
	Interface *Ssd_1306 ;
	SSD1306* oled;
	Interface_Element::Button readKey() ;
	void display() ;
	uint8_t button;
	UART_HandleTypeDef* uart_interface;
	ErrorsOLED* errors;
};
#endif
#endif /* INTERFACEMANAGER_H_ */

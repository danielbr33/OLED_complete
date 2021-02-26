#include "Interface_manager.h"
#include "usart.h"
#define BUTTON_1 'a' // left
#define BUTTON_2 'd' // right
#define BUTTON_3 's'// down
#define SPECIAL_BUTTON 224
#define INTERVAL 0.1

Interface_manager::Interface_manager(UART_HandleTypeDef* huart, SSD1306* oled){
    Ssd_1306 = new Interface ;
    uart_interface=huart;
    this->oled=oled;
}

void Interface_manager::init(){
    HAL_UART_Receive_IT(uart_interface, &button, 1);
}

void Interface_manager::interrupt(){
	if(button!=0)
		Ssd_1306->sendAction( readKey() ) ;
	Ssd_1306->refresh() ;
	display() ;
	button=0;
    HAL_UART_Receive_IT(uart_interface, (uint8_t*)&button, 1);
}

Interface_Element::Button Interface_manager::readKey(){
	switch(this->button){
		case BUTTON_1:
			return Interface_Element::LEFT_BUTTON;
        case BUTTON_2:
            return Interface_Element::RIGHT_BUTTON;
        case BUTTON_3:
        	return Interface_Element::ENTER ;
        break;
    }
}
void Interface_manager::display(){
	oled->fillBuffer(BufferSSD1306::White);
    if( Ssd_1306->isNoChangeableErrorCounting() ){
        oled->writeString("No change", 7, 10, BufferSSD1306::Black, 2, 2);
        oled->writeString("possible", 7, 10, BufferSSD1306::Black, 2, 17);
    }
    else{
    	oled->writeString( (char*)Ssd_1306->getParameterHeadline().c_str(), 7, 10, BufferSSD1306::Black, 2, 2);
        if( !(Ssd_1306->isBackFromSubListParameter()) && !(Ssd_1306->hasSubList()) ){
            if( Ssd_1306->isVisibleValue() ){
            	char temp[15];
            	sprintf(temp, "%d", Ssd_1306->getParameterValue());
        		oled->writeString( temp, 7, 10, BufferSSD1306::Black, 2, 17);
            }
            else{
                for( uint16_t i = (Ssd_1306->getParameterValue() )*10 ; i > 0 ; i /= 10)
                    oled->writeString(" ", 7, 10, BufferSSD1306::Black, 2, 2);
                oled->writeString((char*)Ssd_1306->getParameterUnit().c_str(), 7, 10, BufferSSD1306::Black, 2, 17);
            }
        }
    }
    oled->writeString("ABCDEFGHIJKLMVWXYZ", 11, 18, BufferSSD1306::Black, 5, 36);
}

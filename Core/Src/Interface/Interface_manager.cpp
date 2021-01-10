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
	oled->Fill(White);
    if( Ssd_1306->isNoChangeableErrorCounting() ){
        oled->WriteString("No change", Font7x10, Black, 2, 2);
        oled->WriteString("possible", Font7x10, Black, 2, 17);
    }
    else{
    	oled->WriteString( (char*)Ssd_1306->getParameterHeadline().c_str(), Font7x10, Black, 2, 2);
        if( !(Ssd_1306->isBackFromSubListParameter()) && !(Ssd_1306->hasSubList()) ){
            if( Ssd_1306->isVisibleValue() ){
            	char temp[15];
            	sprintf(temp, "%d", Ssd_1306->getParameterValue());
        		oled->WriteString( temp, Font7x10, Black, 2, 17);
            }
            else{
                for( uint16_t i = (Ssd_1306->getParameterValue() )*10 ; i > 0 ; i /= 10)
                    oled->WriteString(" ", Font7x10, Black, 2, 2);
                oled->WriteString((char*)Ssd_1306->getParameterUnit().c_str(), Font7x10, Black, 2, 17);
            }
        }
    }
}

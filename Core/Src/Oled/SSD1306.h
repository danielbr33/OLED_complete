/* Created on: 22.02.2021
   Author: daniel   */


/*******************************README*******************************/
/*OLED is divided to 8 parts, each included 8pixels vertically, to write data it's needed to send two commands informonig about sending data
 * and one command which means a number of sector. In this code it's written by counting to 8 (variable counter) and sending data from buffer
 * Library support sending using both I2C and SPI, and in DMA and polling mode, but only I2C was tested
 * You need to create an object depending on that, which communication standard you want to use, DMA is turned off by default,
 * you can use it by setting variable DMA_status using suitable function.
 * Another configuration of init commands not tested*/

#ifndef __SSD1306_H__
#define __SSD1306_H__

#include <BufferSSD1306.h>

//To nie wiem czy ty robiles ale tez ładnie zrobione, ze gdyby ktos chciał skompilowac na innym procku dostanie info ze moze nie działać w pełni i sam musi przetestować, lekko bym to zmodyfikował ale opowiem o tym na nastepynm spotkaniu
#define STM32F4
#if defined(STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(STM32L0)
#include "stm32l0xx_hal.h"
#elif defined(STM32L4)
#include "stm32l4xx_hal.h"
#elif defined(STM32F3)
#include "stm32f3xx_hal.h"
#elif defined(STM32H7)
#include "stm32h7xx_hal.h"
#elif defined(STM32F7)
#include "stm32f7xx_hal.h"
#else
 #error "SSD1306 library was tested only on STM32F1, STM32F3, STM32F4, STM32F7, STM32L0, STM32L4, STM32H7 MCU families. Please modify ssd1306.h if you know what you are doing. Also please send a pull request if it turns out the library works on other MCU's as well!"
#endif

#define NUMBER_OF_COMMANDS_INIT  28
#define NUMBER_OF_COMMANDS_DATA	3

class SSD1306 {
public:
	enum State {SET_OFF, SET_ON};
	enum ConnectionOled{SPI,I2C};
	struct gpio_struct {
		GPIO_TypeDef* port;
		uint16_t pin;
	};

	struct OledSettingsSPI{
		gpio_struct dc;
		gpio_struct reset;
		gpio_struct cs;
		SPI_HandleTypeDef* hspi;
	};

	struct OledSettingsI2C {
		int address;
		I2C_HandleTypeDef* hi2c;
	};

	SSD1306(OledSettingsSPI oledSettingsSPI);
	SSD1306(OledSettingsI2C oledSettingsI2C);
	virtual ~SSD1306();

	// Procedure definitions
	void init(void);
	void fillBuffer(BufferSSD1306::Color color);
	void writeChar(char ch,  uint8_t font_width, uint8_t font_height, BufferSSD1306::Color color, uint8_t coordX,uint8_t coordY);
	void writeString(char* str,  uint8_t font_width, uint8_t font_height, BufferSSD1306::Color color, uint8_t coordX, uint8_t coordY);
	void setCursor(uint8_t x, uint8_t y);
	void oledInterruptDMA(); //put in oled SPI interrupt or in freertos
	void sendScreen(); //polling mode

	// Low-level procedures
	void reset(void);
	void changeDMA(State dma);
	void changeMirrorHorizontal(State mirror);
	void changeMirrorVertical(State mirror);
	void changeInversionColor(State inversion);
	void changeHeight(uint8_t height);
	void changeWidth(uint8_t width);
	bool checkBufferReady();

private:
	I2C_HandleTypeDef* I2C_Port;
	int I2C_ADDR;	//(0x3C << 1) //To nie jest w rozumieniu ogólnym, to zmienna która sie nie zmienia jak cos
	SPI_HandleTypeDef* SpiPort;
	GPIO_TypeDef* DcPort;
	GPIO_TypeDef* CsPort;
	GPIO_TypeDef* ResetPort;
	uint16_t DcPin;
	uint16_t CsPin;
	uint16_t ResetPin;

	void allocBuffer();
	void writeCommand();
	void writeData();

	ConnectionOled connectionOled;
	State dma_status;
	State mirror_vertical_status;
	State mirror_horizontal_status;
	State inversion_color_status;
	int height;
	int width;
    uint16_t currentX;
    uint16_t currentY;
    uint8_t inverted;
    uint8_t initialized;
    uint8_t status;   // 0 mean ready data to send
    uint8_t initCommands[NUMBER_OF_COMMANDS_INIT];
    uint8_t lineCommands[NUMBER_OF_COMMANDS_DATA];
    BufferSSD1306 *buffer;
    uint8_t* SSD1306_Buffer;
    uint8_t counter;  //Readme on the top
};

#define TURN_OFF	0xAE
#define TURN_ON 	0xAF
#define SET_MEMORY_ADDR_MODE	0x20
#define HORIZONTAL_ADDR_MODE	0x00		// 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;							// 10b,Page Addressing Mode (RESET); 11b,Invalid
#define SET_PAGE_START_ADDR		0xB0	//Set Page Start Address for Page Addressing Mode,B0-B7
#define MIRROR_VERTICAL		0xC0		// Mirror vertically
#define COM_SCAN_DIRECTION		0xC8	//Set COM Output Scan Direction
#define MIRROR_HORIZONTAL	0xA0		//mirror horizontally
#define SET_SEGMENT_REMAP	0xA1		//--set segment re-map 0 to 127 - CHECK
#define LOW_COLUMN_ADDR		0x00
#define HIGH_COLUMN_ADDR	0x10
#define SET_START_LINE_ADDR		0x40
#define SET_CONTRAST	0x81	//check
#define CONTRAST	0xFF
#define INVERSE_COLOR	0xA7
#define NORMAL_COLOR	0xA6
#define SET_MULTIPLEX_RATIO 0xA8	//1-64
#define RATIO_32 0x1F
#define RATIO_64 0x3F
#define OUT_FOLLOW_RAM_CONTENT 0xA4		//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
#define DISPLAY_OFFSET 0xD3
#define DISPLAY_NOT_OFFSET	0x00
#define SET_CLOCK_DIVIDE_RATIO	0xD5	 //--set display clock divide ratio/oscillator frequency
#define DIVIDE_RATIO 	0xF0
#define SET_PRE_CHARGE_PERIOD 	0xD9
#define PRE_CHARGE_PERIOD 	0x22
#define SET_COM_PIN 	0xDA	 //--set com pins hardware configuration - CHECK
#define COM_PIN_32		0x02
#define COM_PIN_64		0x12
#define SET_VCOMH	0xDB	//--set vcomh
#define VOLTAGE_77	0x20	//0x20,0.77xVcc
#define SET_DC_ENABLE	0x8D
#define DC_ENABLE	0x14

#endif

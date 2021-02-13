/*
 * SSD1306.h
 *
 *  Created on: 22.03.2020
 *      Author: danie
 */

#ifndef APPLICATION_USER_SSD1306_H_
#define APPLICATION_USER_SSD1306_H_

#ifndef __SSD1306_H__
#define __SSD1306_H__


#include "Buffer.h"


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


// Enumeration for screen colors
typedef enum {
    BLACK, // BLACK color, no pixel
    WHITE  // Pixel is set. Color depends on OLED
} SSD1306_COLOR;

typedef enum state {SET_OFF, SET_ON};
typedef enum connection{SPI,I2C};

// Struct to store transformations

class SSD1306 {
public:

	struct gpio_struct {
		GPIO_TypeDef* port;
		uint16_t pin;
	};

	SSD1306(I2C_HandleTypeDef* hi2c, int I2C_ADDRESS);
	SSD1306(SPI_HandleTypeDef* hspi, gpio_struct reset, gpio_struct DC, gpio_struct CS);
	virtual ~SSD1306();
	// Procedure definitions
	int Init(void);
	void Fill(Color color);
	void DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
	void WriteChar(char ch,  uint8_t font_width, uint8_t font_height, Color color, uint8_t coordX,uint8_t coordY);
	void WriteString(char* str,  uint8_t font_width, uint8_t font_height, Color color, uint8_t coordX, uint8_t coordY);
	void SetCursor(uint8_t x, uint8_t y);
	void process(void);
	void SPI_Interrupt_DMA();
	void SendScreen();
	// Low-level procedures
	void Reset(void);
	void WriteCommand();
	void WriteData();
	void ChangeDMA(state dma);
	void ChangeMirrorHorizontal(state mirror);
	void ChangeMirrorVertical(state mirror);
	void ChangeInversionColor(state inversion);
	void ChangeHeight(uint8_t height);
	void ChangeWidth(uint8_t width);
	void AllocBuffer();
	void print();

private:
	I2C_HandleTypeDef* I2C_Port;
	int I2C_ADDR;	//(0x3C << 1)
	SPI_HandleTypeDef* SPI_Port;
	GPIO_TypeDef* DC_Port;
	GPIO_TypeDef* CS_Port;
	GPIO_TypeDef* RESET_Port;
	uint16_t DC_Pin;
	uint16_t CS_Pin;
	uint16_t RESET_Pin;

	connection i2c_or_spi;
	state dma_status;
	state mirror_vertical_status;
	state mirror_horizontal_status;
	state inversion_color_status;
	int height;
	int width;

    uint16_t currentX;
    uint16_t currentY;
    uint8_t inverted;
    uint8_t initialized;
    uint8_t status;
    uint8_t initCommands[28];
    uint8_t lineCommands[3];
    Buffer *buffer;
    uint8_t* SSD1306_Buffer;
    uint8_t counter;
};

#endif /* APPLICATION_USER_SSD1306_H_ */
#endif // __SSD1306_H__

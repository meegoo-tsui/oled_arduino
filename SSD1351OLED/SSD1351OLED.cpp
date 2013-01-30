/********************** (C) COPYRIGHT 2013 meegoo tsui ************************/
/*!
 * @file      SSD1351OLED.cpp
 * @brief     SSD1351 OLED libs
 * @author    meegoo tsui
 * @version   1.0
 * @date      2013/01/29
 *
 * 版本历史:
 * - <meegoo tsui，2013/01/29>：初始版本；
 */
/******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "SSD1351OLED.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RES                  8                             /* Gadgeteer PIN 4 */
#define DC                   A2                            /* Gadgeteer PIN 5 */
#define CS                   A0                            /* Gadgeteer PIN 6 */
#define PW                   A1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SSD1351OLED SSD1351Oled;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*!
 * @fn    void init(void)
 * @brief 初始化SPI及1351。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::init(void)
{
	/* init GPIO */
	pinMode(RES,OUTPUT);
	pinMode(DC,OUTPUT);
	pinMode(CS,OUTPUT);
	pinMode(PW, OUTPUT);
	digitalWrite(PW, HIGH);

	/* init SPI module */
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	SPI.setDataMode(SPI_MODE3);

	/* init 1351 oled */
	digitalWrite(RES,HIGH);                          /* Reset the oled module */
	delay(100);
	digitalWrite(RES,LOW);
	delay(100);
	digitalWrite(RES,HIGH);
	delay(100);

	WriteCommand(SSD1351_CMD_SETCOMMANDLOCK);
	WriteData(0x12);                            /* Unlocked to enter commands */
	WriteCommand(SSD1351_CMD_SETCOMMANDLOCK);
	WriteData(0xB1);                          /* Make all commands accessible */ 
	WriteCommand(SSD1351_CMD_SLEEPMODE_DISPLAYOFF);
	WriteCommand(SSD1351_CMD_SETFRONTCLOCKDIV);
	WriteData(0xF1);
	WriteCommand(SSD1351_CMD_SETMUXRRATIO);
	WriteData(0x7f);
	WriteCommand(SSD1351_CMD_COLORDEPTH);
	WriteData(0x74);           /* Bit 7:6 = 65,536 Colors, Bit 3 = BGR or RGB */
	WriteCommand(SSD1351_CMD_SETCOLUMNADDRESS);
	WriteData(0x00);
	WriteData(0x7F);
	WriteCommand(SSD1351_CMD_SETROWADDRESS);
	WriteData(0x00);
	WriteData(0x7F);
	WriteCommand(SSD1351_CMD_SETDISPLAYSTARTLINE);
	WriteData(0x00);
	WriteCommand(SSD1351_CMD_SETDISPLAYOFFSET);
	WriteData(0x00);
	WriteCommand(SSD1351_CMD_SETGPIO);
	WriteData(0x00);                                     /* Disable GPIO pins */
	WriteCommand(SSD1351_CMD_FUNCTIONSELECTION);
	WriteData(0x01);             /* External VDD (0 = External, 1 = Internal) */
	WriteCommand(SSD1351_CMD_SETPHASELENGTH);
	WriteData(0x32);
	WriteCommand(SSD1351_CMD_SETSEGMENTLOWVOLTAGE);
	WriteData(0xA0);                                   /* Enable External VSL */
	WriteData(0xB5);
	WriteData(0x55);
	WriteCommand(SSD1351_CMD_SETPRECHARGEVOLTAGE);
	WriteData(0x17);
	WriteCommand(SSD1351_CMD_SETVCOMHVOLTAGE);
	WriteData(0x05);
	WriteCommand(SSD1351_CMD_SETCONTRAST);
	WriteData(0xC8);
	WriteData(0x80);
	WriteData(0xC8);
	WriteCommand(SSD1351_CMD_MASTERCONTRAST);
	WriteData(0x0F);                                      /* Maximum contrast */
	WriteCommand(SSD1351_CMD_SETSECONDPRECHARGEPERIOD);
	WriteData(0x01);
	WriteCommand(SSD1351_CMD_SETDISPLAYMODE_RESET);
	
	WriteCommand(SSD1351_CMD_GRAYSCALELOOKUP);
	WriteData(0x05);
	WriteData(0x06);
	WriteData(0x07);
	WriteData(0x08);
	WriteData(0x09);
	WriteData(0x0a);
	WriteData(0x0b);
	WriteData(0x0c);
	WriteData(0x0D);
	WriteData(0x0E);
	WriteData(0x0F);
	WriteData(0x10);
	WriteData(0x11);
	WriteData(0x12);
	WriteData(0x13);
	WriteData(0x14);
	WriteData(0x15);
	WriteData(0x16);
	WriteData(0x18);
	WriteData(0x1a);
	WriteData(0x1b);
	WriteData(0x1C);
	WriteData(0x1D);
	WriteData(0x1F);
	WriteData(0x21);
	WriteData(0x23);
	WriteData(0x25);
	WriteData(0x27);
	WriteData(0x2A);
	WriteData(0x2D);
	WriteData(0x30);
	WriteData(0x33);
	WriteData(0x36);
	WriteData(0x39);
	WriteData(0x3C);
	WriteData(0x3F);
	WriteData(0x42);
	WriteData(0x45);
	WriteData(0x48);
	WriteData(0x4C);
	WriteData(0x50);
	WriteData(0x54);
	WriteData(0x58);
	WriteData(0x5C);
	WriteData(0x60);
	WriteData(0x64);
	WriteData(0x68);
	WriteData(0x6C);
	WriteData(0x70);
	WriteData(0x74);
	WriteData(0x78);
	WriteData(0x7D);
	WriteData(0x82);
	WriteData(0x87);
	WriteData(0x8C);
	WriteData(0x91);
	WriteData(0x96);
	WriteData(0x9B);
	WriteData(0xA0);
	WriteData(0xA5);
	WriteData(0xAA);
	WriteData(0xAF);
	WriteData(0xB4);
}

/******************************************************************************/
/*!
 * @fn    void WriteCommand(void)
 * @brief 发送命令到1351。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::WriteCommand(uint8_t cmd)
{
	digitalWrite(CS,LOW);
	digitalWrite(DC,LOW);
	SPI.transfer(cmd);
	digitalWrite(DC,HIGH);
	digitalWrite(CS,HIGH);
}

/******************************************************************************/
/*!
 * @fn    void WriteData(void)
 * @brief 发送数据到1351。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::WriteData(uint8_t data)
{
	digitalWrite(CS,LOW);
	digitalWrite(DC,HIGH);
	SPI.transfer(data);
	digitalWrite(DC,HIGH);
	digitalWrite(CS,HIGH);
}

/******************************************************************************/
/*!
 * @fn    void SetAddress(void)
 * @brief 设置1351行列地址，矩形范围。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::SetAddress(uint8_t a,uint8_t b,uint8_t c,uint8_t d)
{
	WriteCommand(SSD1351_CMD_SETCOLUMNADDRESS);         /* set column address */
	WriteData(a);                                       /* start address      */
	WriteData(b);                                       /* end address        */

	WriteCommand(SSD1351_CMD_SETROWADDRESS);            /* set row address    */
	WriteData(c);                                       /* start address      */
	WriteData(d);                                       /* end address        */
}

/******************************************************************************/
/*!
 * @fn    void FillRGB(uint8_t r,uint8_t g,uint8_t b)
 * @brief 填充1351为同一颜色。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::FillRGB(uint8_t r,uint8_t g,uint8_t b)
{
	uint8_t x, y, data1, data2;
	
    SetAddress(0x00,0x7f,0x00,0x7f);
    WriteCommand(SSD1351_CMD_WRITERAM);
	data1 = (r &  0xF8) | (g>>5);
	data2 = (b >> 3)    | ((g>>2)<<5);

    for(x=0; x<128; x++) {
		for(y=0; y<128; y++) {
			WriteData(data1);
			WriteData(data2);
		}
	}
}

/******************************************************************************/
/*!
 * @fn    void OledEnable(uint8_t en)
 * @brief 使能或禁止1351显示。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::OledEnable(uint8_t en)
{
	if(en){
		WriteCommand(SSD1351_CMD_SLEEPMODE_DISPLAYON);
	}
	else{
		WriteCommand(SSD1351_CMD_SLEEPMODE_DISPLAYOFF);
	}
}

/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

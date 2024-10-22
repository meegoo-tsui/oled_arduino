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
#include "font_8x8.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RES                  8                             /* Gadgeteer PIN 4 */
#define DC                   A2                            /* Gadgeteer PIN 5 */
#define CS                   A0                            /* Gadgeteer PIN 6 */
#define PW                   A1

/* Private macro -------------------------------------------------------------*/
#define _SSD1351OLED_absDiff(x,y) ((x>y) ?  (x-y) : (y-x))
#define _SSD1351OLED_swap(a,b) \
do\
{\
uint8_t t;\
	t=a;\
	a=b;\
	b=t;\
} while(0)

/* Private variables ---------------------------------------------------------*/
SSD1351OLED SSD1351Oled;
uint8_t     RotateSet[4] = {0x66, 0x65, 0x74, 0x77};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*!
 * @fn    void Init(void)
 * @brief 初始化SPI及1351。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::Init(void)
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
	SetTextXY(0, 0);
	SetFontColor(0xFF, 0xFF, 0xFF);
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
	WriteData(0xD0);
	WriteCommand(SSD1351_CMD_SETMUXRRATIO);
	WriteData(0x7f);
	WriteCommand(SSD1351_CMD_COLORDEPTH);
	WriteData(RotateSet[0]);   /* Bit 7:6 = 65,536 Colors, Bit 3 = BGR or RGB */
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

#if SSD1351OLED_DEBUG
	Serial.begin(SSD1351OLED_BAUD);
	while (!Serial);
	Printf("Ready ....\r\n");
#endif
}

/******************************************************************************/
/*!
 * @fn    void Printf(char *fmt, ...)
 * @brief 发送命令到1351。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::Printf(char *fmt, ...)
{
#if SSD1351OLED_DEBUG
	char tmp[128]; /* resulting string limited to 128 chars */

	va_list args;
	va_start (args, fmt );
	vsnprintf(tmp, 128, fmt, args);
	va_end (args);
	Serial.print(tmp);
#endif
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
 * @fn    void SetDot(uint8_t x,uint8_t y)
 * @brief 画点。
 * \author meegoo (2013/01/30)
 */void SSD1351OLED::SetDot(uint8_t x,uint8_t y)
{
    SetAddress(x,x,y,y);
    WriteCommand(SSD1351_CMD_WRITERAM);
	WriteData(font_color_1);
	WriteData(font_color_2);
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
 * @fn    void FillRGBEx(uint8_t r,uint8_t g,uint8_t b)
 * @brief 填充1351某一区域为同一颜色。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::FillRGBEx(uint8_t r,uint8_t g,uint8_t b, uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
{
	uint8_t x, y, data1, data2;
	
    SetAddress(x1, x2, y1, y2);
    WriteCommand(SSD1351_CMD_WRITERAM);
	data1 = (r &  0xF8) | (g>>5);
	data2 = (b >> 3)    | ((g>>2)<<5);

    for(x=x1; x<=x2; x++) {
		for(y=y1; y<=y2; y++) {
			WriteData(data1);
			WriteData(data2);
		}
	}
}

/******************************************************************************/
/*!
 * @fn    void SSD1351Enable(uint8_t en)
 * @brief 使能或禁止1351显示。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::Enable(uint8_t en)
{
	if(en){
		WriteCommand(SSD1351_CMD_SLEEPMODE_DISPLAYON);
	}
	else{
		WriteCommand(SSD1351_CMD_SLEEPMODE_DISPLAYOFF);
	}
}

/******************************************************************************/
/*!
 * @fn     void DrawBitmap(uint8_t *bitmaparray,uint16_t bytes, uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
 * @brief  显示图片在设置区域。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::DrawBitmap(const uint8_t *bitmaparray,uint16_t bytes, uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
{
	uint16_t i;
	uint8_t val;

	SetAddress(x1, x2, y1, y2);
	WriteCommand(SSD1351_CMD_WRITERAM);
	for(i=0; i<bytes; i++){
		val = pgm_read_byte(&(bitmaparray[i]));
		WriteData(val);
	}
}

/******************************************************************************/
/*!
 * @fn     void DrawBitmap(uint8_t *bitmaparray,uint16_t bytes, uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
 * @brief  顺时针旋转屏幕rx90度。
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::Rotate(uint8_t r)
{
	rotate = r%4;
	WriteCommand(SSD1351_CMD_COLORDEPTH);
	WriteData(RotateSet[rotate]);
}

/******************************************************************************/
/*!
 * @fn     void SetTextXY(uint8_t x, uint8_t y)
 * @brief  设置显示字符位置，单位8个像素点。
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::SetTextXY(uint8_t x, uint8_t y)
{
	if(rotate & 0x01){
		pos_x = y << 3;
		pos_y = x << 3;		
	} else{
		pos_x = x << 3;
		pos_y = y << 3;
	}
}

/******************************************************************************/
/*!
 * @fn     void GotoXY(uint8_t x, uint8_t y)
 * @brief  设置显示字符位置，单位1个像素点。
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::GotoXY(uint8_t x, uint8_t y)
{
	if(rotate & 0x01){
		pos_x = y;
		pos_y = x;		
	} else{
		pos_x = x;
		pos_y = y;
	}
}

/******************************************************************************/
/*!
 * @fn    void PutChar(uint8_t C)
 * @brief 打印一个字符在[pos_x, pos_y]。
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::PutChar(uint8_t C)
{
	uint16_t i, j;
	uint8_t val, b_val;

	if(C < 32 || C > 127){
		C=' ';
	}	

	/* 写字符 */
	SetAddress(pos_x, pos_x + 7, pos_y, pos_y + 7);
	WriteCommand(SSD1351_CMD_WRITERAM);
	for(i=0; i<8; i++){
		val = pgm_read_byte(&(BasicFont[C - 32][i]));
		/* 每个bit位一个点的颜色 */
		for(j=0; j<8; j++){
			b_val = val & (0x80 >> j);
			if(b_val){
				WriteData(font_color_1);
				WriteData(font_color_2);
			} else{
				WriteData(0x00);
				WriteData(0x00);
			}
		}
	}	

	/* 设置新坐标 */
	if(rotate & 0x01){
		pos_y = pos_y + 8;
		if(pos_y >= 0x7F){
			pos_y = 0;
			pos_x = pos_x + 8;
			if(pos_x >= 0x7F){
				pos_x = 0;
			}
		}
	} else{
		pos_x = pos_x + 8;
		if(pos_x >= 0x7F){
			pos_x = 0;
			pos_y = pos_y + 8;
			if(pos_y >= 0x7F){
				pos_y = 0;
			}
		}
	}
}

/******************************************************************************/
/*!
 * @fn    void PutString(const char *String)
 * @brief 打印字符串。
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::PutString(const char *String)
{
	uint8_t i = 0;

	while(String[i]){
		PutChar(String[i]);     
		i++;
	}
}

/******************************************************************************/
/*!
 * @fn    void PutString(const char *String)
 * @brief 打印字符串。
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::SetFontColor(uint8_t r,uint8_t g,uint8_t b)
{
	font_color_1 = (r &  0xF8) | (g>>5);
	font_color_2 = (b >> 3)    | ((g>>2)<<5);
}

/******************************************************************************/
/*!
 * @fn    void HorizontalScroll(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e)
 * @brief 水平移动。
 * \author meegoo (2013/02/05)
 * OLED horizontal scroll
 *  a: 0x00     ..no scrolling
 *     0x01-0x3f..scroll towards SEG127 with 1 column offset
 *     0x40-0xff..scroll towards SEG0   with 1 column offset
 *  b: 0x00-0x7f..start row address
 *  c: 0x00-0xff..number of rows to be h-scrolled  (b + c <= 0x80)
 *  d: reserved (0x00 by reset)
 *  e: scrolling time interval
 *      0x00..test mode
 *      0x01..normal
 *      0x02..slow
 *      0x03..slowest
 */
void SSD1351OLED::HorizontalScroll(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e)
{
	if(rotate & 0x01){ /* 不支持90度水平移动 */
		return;
	}
    WriteCommand(SSD1351_CMD_HORIZONTALSCROLL);
    WriteData(a);
    WriteData(b);
    WriteData(c);
    WriteData(d);
    WriteData(e);
}

/******************************************************************************/
/*!
 * @fn    void StopMoving(void)
 * @brief 停止水平移动。
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::StopMoving(void)
{
    WriteCommand(SSD1351_CMD_STOPMOVING);
}

/******************************************************************************/
/*!
 * @fn    void StartMoving(void)
 * @brief 开始水平移动。
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::StartMoving(void)
{
	if(rotate & 0x01){ /* 不支持90度水平移动 */
		StopMoving();
		return;
	}
    WriteCommand(SSD1351_CMD_STARTMOVING);
}

/******************************************************************************/
/*!
 * @fn    SetContrast(uint8_t level)
 * @brief Set Contrast
 * \author meegoo (2013/03/08)
 */
void SSD1351OLED::SetContrast(uint8_t level)
{
	if(level > MAX_BRIGHTNESS){
		return;
	}
	WriteCommand(SSD1351_CMD_MASTERCONTRAST);
	WriteData(level);
	Enable(level);
}

/******************************************************************************/
/*!
 * @fn    void FadeIn(void)
 * @brief Fade in (Full Screen)。
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::FadeIn(void)
{
	uint8_t i;

	for(i=0; i<(MAX_BRIGHTNESS + 1); i++){
		SetContrast(i);
		delay(FADE_DELAY);
	}
}

/******************************************************************************/
/*!
 * @fn    void FadeOut(void)
 * @brief Fade out (Full Screen)。
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::FadeOut(void)
{
	uint8_t i;

	for(i=0; i<(MAX_BRIGHTNESS + 1); i++){
		SetContrast(MAX_BRIGHTNESS - i);
		delay(FADE_DELAY);
	}
}

/******************************************************************************/
/*!
 * @fn    void DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
 * @brief Draw line.
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	uint8_t deltax, deltay, x,y, steep;
	int8_t error, ystep;

	steep = _SSD1351OLED_absDiff(y1,y2) > _SSD1351OLED_absDiff(x1,x2);  
	if (steep){
		_SSD1351OLED_swap(x1, y1);
		_SSD1351OLED_swap(x2, y2);
	}
	if (x1 > x2){
		_SSD1351OLED_swap(x1, x2);
		_SSD1351OLED_swap(y1, y2);
	}

	deltax = x2 - x1;
	deltay =_SSD1351OLED_absDiff(y2,y1);  
	error = deltax / 2;
	y = y1;
	if(y1 < y2){
		ystep = 1;
	}
	else {
		ystep = -1;
	}

	for(x = x1; x <= x2; x++) {
		if (steep) 
			SetDot(y,x); 
		else 
			SetDot(x,y);
   		error = error - deltay;
		if (error < 0)
		{
			y = y + ystep;
			error = error + deltax;
    	}
	}
}

/******************************************************************************/
/*!
 * @fn    void SetPixels(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2)
 * @brief 填充1351某一区域为同一颜色。
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::SetPixels(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2)
{
	uint8_t x, y, data1, data2;
	
    SetAddress(x1, x2, y1, y2);
    WriteCommand(SSD1351_CMD_WRITERAM);
    for(x=x1; x<=x2; x++) {
		for(y=y1; y<=y2; y++) {
			WriteData(font_color_1);
			WriteData(font_color_2);
		}
	}
}

/******************************************************************************/
/*!
 * @fn    void DrawVLine(uint8_t x, uint8_t y, uint8_t height)
 * @brief Draw a Vertical Line.
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::DrawVLine(uint8_t x, uint8_t y, uint8_t height)
{
	SetPixels(x,y,x,y+height);
}

/******************************************************************************/
/*!
 * @fn    void DrawHLine(uint8_t x, uint8_t y, uint8_t width)
 * @brief Draw a Horizontal Line.
 * \author meegoo (2013/01/30)
 */
void SSD1351OLED::DrawHLine(uint8_t x, uint8_t y, uint8_t width)
{
	SetPixels(x,y, x+width, y);
}

/******************************************************************************/
/*!
 * @fn    void DrawRoundRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius)
 * @brief Draw a rectangle with rounder corners.
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::DrawRoundRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius) 
{
  	int16_t tSwitch; 
	uint8_t x1 = 0, y1 = radius;
  	tSwitch = 3 - 2 * radius;
	
	while (x1 <= y1) {
	    SetDot(x+radius - x1, y+radius - y1);
	    SetDot(x+radius - y1, y+radius - x1);

	    SetDot(x+width-radius + x1, y+radius - y1);
	    SetDot(x+width-radius + y1, y+radius - x1);
	    
	    SetDot(x+width-radius + x1, y+height-radius + y1);
	    SetDot(x+width-radius + y1, y+height-radius + x1);

	    SetDot(x+radius - x1, y+height-radius + y1);
	    SetDot(x+radius - y1, y+height-radius + x1);

	    if (tSwitch < 0) {
	    	tSwitch += (4 * x1 + 6);
	    } else {
	    	tSwitch += (4 * (x1 - y1) + 10);
	    	y1--;
	    }
	    x1++;
	}
	  	
	DrawHLine(x+radius, y, width-(2*radius));			/* top    */
	DrawHLine(x+radius, y+height, width-(2*radius));	/* bottom */
	DrawVLine(x, y+radius, height-(2*radius));			/* left   */
	DrawVLine(x+width, y+radius, height-(2*radius));	/* right  */
}

/******************************************************************************/
/*!
 * @fn    void DrawCircle(uint8_t xCenter, uint8_t yCenter, uint8_t radius)
 * @brief Draw a Circle.
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::DrawCircle(uint8_t xCenter, uint8_t yCenter, uint8_t radius)
{
   DrawRoundRect(xCenter-radius, yCenter-radius, 2*radius, 2*radius, radius);
}

/******************************************************************************/
/*!
 * @fn    void DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
 * @brief Draw a Filled in a Circle.
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::FillCircle(uint8_t xCenter, uint8_t yCenter, uint8_t radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	uint8_t x = 0;
	uint8_t y = radius;

	/*
	 * Fill in the center between the two halves
	 */
	DrawLine(xCenter, yCenter-radius, xCenter, yCenter+radius);
 
	while(x < y){
		if(f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;    

		/*
		 * Now draw vertical lines between the points on the circle rather than
		 * draw the points of the circle. This draws lines between the 
		 * perimeter points on the upper and lower quadrants of the 2 halves of the circle.
		 */
		DrawLine(xCenter+x, yCenter+y, xCenter+x, yCenter-y);
		DrawLine(xCenter-x, yCenter+y, xCenter-x, yCenter-y);
		DrawLine(xCenter+y, yCenter+x, y+xCenter, yCenter-x);
		DrawLine(xCenter-y, yCenter+x, xCenter-y, yCenter-x);
  	}
}

/******************************************************************************/
/*!
 * @fn    void AnalogClockInit(byte x, byte y, byte r)
 * @brief Analog Clock Init.
 * \author meegoo (2013/02/05)
 */
/* Look-up sine table for integer math */
byte byteSine[16] = {0,  27,  54,  79, 104, 128, 150, 171, 190, 201, 221, 233, 243, 250, 254, 255} ;
void SSD1351OLED::AnalogClockInit(byte x, byte y, byte r)
{
	/* calculate sizes and position of clock */
	x_centre = x ;
	y_centre = y ;
	radius = r ;
	l_hour =  r / 2 ;           /* hour hand is half radius                   */
	l_minute = (r*3) / 4 ;      /* minute hand is 3/4 radius                  */
	l_second  = l_minute + 2;   /* second hand is 2 pixels larger than minute */

	/* Initialise previous positions of hour and minute hand */
	hLine = 0;
	mLine = 0;
	sLine = 0;
	PX_Hour = PX_Minute = PX_Second = x_centre ;
	PY_Hour = PY_Minute = PY_Second = y_centre ;
	DrawCircle(x,y, r + 3);                    /* draw the surrounding circle */
	DrawFace() ;                                 /* draw the clock dial       */
}

/******************************************************************************/
/*!
 * @fn    void DisplayTime( byte hours, byte minutes, byte seconds )
 * @brief Display Time.
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::DisplayTime( byte hours, byte minutes, byte seconds )
/* draw the hands at the specified positions */
{
	byte angle ;
	uint8_t font_color_1_bak, font_color_2_bak;
	
	if( hours == 0 )
           hours = 12 ;

	/* erase previous hands */
	font_color_1_bak = font_color_1;
	font_color_2_bak = font_color_2;
	font_color_1 = 0;
	font_color_2 = 0;
	angle = ( ( 5*hours ) + ( minutes/12 ) ) % 60 ;
	if(hLine != angle){
		DrawLine( x_centre, y_centre, PX_Hour, PY_Hour) ;
		hLine = angle;
	}
	if(mLine != minutes){
		DrawLine( x_centre, y_centre, PX_Minute, PY_Minute) ;
		mLine = minutes;
	}
	if(sLine != seconds){
		DrawLine( x_centre, y_centre, PX_Second, PY_Second) ;
		sLine = seconds;
	}
	font_color_1 = font_color_1_bak;
	font_color_2 = font_color_2_bak;

	/* calculate new position of second hand and draw it */
	angle = seconds ;
	CalcHands( angle, l_second, &PX_Second, &PY_Second) ;
	DrawLine( x_centre, y_centre, PX_Second, PY_Second) ;

	/* calculate new position of minute hand and draw it */
	angle = minutes ;
	CalcHands( angle, l_minute, &PX_Minute, &PY_Minute) ;
	DrawLine( x_centre, y_centre, PX_Minute, PY_Minute) ;

	/* calculate new position of hour hand and draw it */
	angle = hLine ;
	CalcHands( angle, l_hour, &PX_Hour, &PY_Hour) ;
	DrawLine( x_centre, y_centre, PX_Hour, PY_Hour);
  
	/* re-draw clock centre */
	Box( x_centre, y_centre) ;

#if SSD1351OLED_DEBUG
	Printf("\r\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	Printf("hours:   %d @ (%d, %d).%d\n", hours,   PX_Hour,   PY_Hour,   l_hour);
	Printf("minutes: %d @ (%d, %d).%d\n", minutes, PX_Minute, PY_Minute, l_minute);
	Printf("seconds: %d @ (%d, %d).%d\n", seconds, PX_Second, PX_Second, l_second);
#endif
}

/******************************************************************************/
/*!
 * @fn    void CalcHands( byte angle, byte radius, byte *x, byte *y )
 * @brief Calc Hands.
 * \author meegoo (2013/02/05)
 * angle is location of hand on dial (0-60)
 * radius is length of hand
 * *x   return x-coordinate of hand on dial face
 * *y   return y-coordinate of hand on dial face
 */
void SSD1351OLED::CalcHands( byte angle, byte radius, byte *x, byte *y )
{
	short quadrant, x_flip, y_flip ;

	/* calculate which quadrant the hand lies in */
	quadrant = angle/15 ;

	/* setup for reflection or rotation */
	switch ( quadrant ) {
	  case 0 : x_flip = 1 ; y_flip = -1 ; break ;
	  case 1 : angle = abs(angle-30) ; x_flip = y_flip = 1 ; break ;
	  case 2 : angle = angle-30 ; x_flip = -1 ; y_flip = 1 ; break ;
	  case 3 : angle = abs(angle-60) ; x_flip = y_flip = -1 ; break ; 
	  default:  x_flip = y_flip =1; // this should not happen
	}
	*x = x_centre ;
	*y = y_centre ;
	*x += ( x_flip*(( byteSine[angle]*radius ) >> 8 )) ;
	*y += ( y_flip*(( byteSine[15-angle]*radius ) >> 8 )) ;
}

/******************************************************************************/
/*!
 * @fn    void DrawFace(void)
 * @brief Draw Face.
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::DrawFace(void)
/* draw clock face */
{
	byte hr, x, y ;

	Box( x_centre, y_centre ) ;                            /* draw center box */

	/* draw hour marks or numerals around the clock face */
	for( hr = 0; hr < 60; hr += 5 ) {
	  if ( !( hr % 15 ) )
		 SegBox( hr ) ;                           /* draw quarter hour shapes */
	  else{
		 CalcHands( hr, radius, &x, &y ) ;
	     Box( x, y ) ;
	  }
	}
}

/******************************************************************************/
/*!
 * @fn    void Box( byte x, byte y  )
 * @brief draw a 3 x 3 pixel box centered at x,y.
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::Box( byte x, byte y  )
{
	DrawLine( x-1, y-1, x+1, y-1) ;
	DrawLine( x-1, y,   x+1, y) ;
	DrawLine( x-1, y+1, x+1, y+1) ;	
}

/******************************************************************************/
/*!
 * @fn    void SegBox( byte FaceAngle )
 * @brief draw quarter hour dial markers.
 *        FaceAngle is position of marker around face (0-55)
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::SegBox( byte FaceAngle )
{
	byte quadrant;
	byte hour; 

	/* find the nearest quadrant to the marker position */
	quadrant = ( ( FaceAngle + 7 ) / 15 ) ;
	hour =  FaceAngle == 0 ? 12 : FaceAngle  / 5;

	switch( quadrant ) {
		case 0 :
		case 4 :  // 12 oclock
			GotoXY(x_centre-6,  y_centre - radius -1 );		       
			break;
		case 1 : // 3 oclock
			GotoXY(x_centre -6 + radius,  y_centre -3 );
			break;
		case 2 : // 6 oclock
			GotoXY(x_centre-2,  y_centre + radius -5);
			break;
		case 3 : // 9 oclock
			GotoXY(x_centre- radius ,  y_centre -3 );
			break;
	}

#if SSD1351OLED_DEBUG
	Printf("\r\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	Printf("quadrant: %d\n", quadrant);
	Printf("x_centre: %d\n", x_centre);
	Printf("y_centre: %d\n", y_centre);
	Printf("radius:   %d\n", radius);
	Printf("[%d, %d]: %d\n", pos_x, pos_y, hour);
#endif

	PrintNumber(hour);
}

/******************************************************************************/
/*!
 * @fn    void PrintNumber(long n)
 * @brief Print Number.
 * \author meegoo (2013/02/05)
 */
void SSD1351OLED::PrintNumber(long n)
{
	uint8_t buf[10];                                /* prints up to 10 digits */
	uint8_t i=0;
	if(n==0){
		PutChar('0');
	}
	else{
		if(n < 0){
			PutChar('-');
			n = -n;
		}
		while(n>0 && i <= 10){
			buf[i++] = n % 10;
			n /= 10;
		}
		for(; i >0; i--){
			PutChar((char) (buf[i-1] < 10 ? '0' + buf[i-1] : 'A' + buf[i-1] - 10));
		}
	}
}

/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

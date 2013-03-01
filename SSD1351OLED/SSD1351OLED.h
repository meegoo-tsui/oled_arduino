/********************** (C) COPYRIGHT 2013 meegoo tsui ************************/
/*!
 * @file      SSD1351OLED.h
 * @brief     SSD1351 OLED libs
 * @author    meegoo tsui
 * @version   1.0
 * @date      2013/01/29
 *
 * 版本历史:
 * - <meegoo tsui，2013/01/29>：初始版本；
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIB_SSD1351OLED_H
#define __LIB_SSD1351OLED_H

/* Includes ------------------------------------------------------------------*/
#include <SPI.h>
#include <Arduino.h>

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  SSD1351_CMD_SETCOLUMNADDRESS          = 0x15,
  SSD1351_CMD_SETROWADDRESS             = 0x75,
  SSD1351_CMD_WRITERAM                  = 0x5C, // Write data to GRAM and increment until another command is sent
  SSD1351_CMD_READRAM                   = 0x5D, // Read data from GRAM and increment until another command is sent
  SSD1351_CMD_COLORDEPTH                = 0xA0, // Numerous functions include increment direction ... see DS 
                                                // A0[0] = Address Increment Mode (0 = horizontal, 1 = vertical)
                                                // A0[1] = Column Address Remap (0 = left to right, 1 = right to left)
                                                // A0[2] = Color Remap (0 = ABC, 1 = CBA) - HW RGB/BGR switch
                                                // A0[4] = COM Scan Direction (0 = top to bottom, 1 = bottom to top)
                                                // A0[5] = Odd/Even Paid Split
                                                // A0[7:6] = Display Color Mode (00 = 8-bit, 01 = 65K, 10/11 = 262K, 8/16-bit interface only)
  SSD1351_CMD_SETDISPLAYSTARTLINE       = 0xA1,
  SSD1351_CMD_SETDISPLAYOFFSET          = 0xA2, 
  SSD1351_CMD_SETDISPLAYMODE_ALLOFF     = 0xA4, // Force entire display area to grayscale GS0
  SSD1351_CMD_SETDISPLAYMODE_ALLON      = 0xA5, // Force entire display area to grayscale GS63
  SSD1351_CMD_SETDISPLAYMODE_RESET      = 0xA6, // Resets the display area relative to the above two commands
  SSD1351_CMD_SETDISPLAYMODE_INVERT     = 0xA7, // Inverts the display contents (GS0 -> GS63, GS63 -> GS0, etc.)
  SSD1351_CMD_FUNCTIONSELECTION         = 0xAB, // Enable/Disable the internal VDD regulator
  SSD1351_CMD_SLEEPMODE_DISPLAYOFF      = 0xAE, // Sleep mode on (display off)
  SSD1351_CMD_SLEEPMODE_DISPLAYON       = 0xAF, // Sleep mode off (display on)
  SSD1351_CMD_SETPHASELENGTH            = 0xB1, // Larger capacitance may require larger delay to discharge previous pixel state
  SSD1351_CMD_ENHANCEDDRIVINGSCHEME     = 0xB2, 
  SSD1351_CMD_SETFRONTCLOCKDIV          = 0xB3, // DCLK divide ration fro CLK (from 1 to 16)
  SSD1351_CMD_SETSEGMENTLOWVOLTAGE      = 0xB4,
  SSD1351_CMD_SETGPIO                   = 0xB5,
  SSD1351_CMD_SETSECONDPRECHARGEPERIOD  = 0xB6,
  SSD1351_CMD_GRAYSCALELOOKUP           = 0xB8,
  SSD1351_CMD_LINEARLUT                 = 0xB9,
  SSD1351_CMD_SETPRECHARGEVOLTAGE       = 0xBB,
  SSD1351_CMD_SETVCOMHVOLTAGE           = 0xBE,
  SSD1351_CMD_SETCONTRAST               = 0xC1,
  SSD1351_CMD_MASTERCONTRAST            = 0xC7,
  SSD1351_CMD_SETMUXRRATIO              = 0xCA,
  SSD1351_CMD_NOP3                      = 0xD1,
  SSD1351_CMD_NOP4                      = 0xE3,
  SSD1351_CMD_SETCOMMANDLOCK            = 0xFD,
  SSD1351_CMD_HORIZONTALSCROLL          = 0x96,
  SSD1351_CMD_STOPMOVING                = 0x9E,
  SSD1351_CMD_STARTMOVING               = 0x9F  
} ssd1351Cmd_e;

/* Exported constants --------------------------------------------------------*/
#define SSD1351OLED_DEBUG                 1               /* Debug mode ctrl  */
#define SSD1351OLED_BAUD                  57600

#define R0                                0
#define R90                               1
#define R180                              2
#define R270                              3
#define MAX_COLUMN	                      0x7f
#define MAX_ROW		                      0x7f
#define	MAX_BRIGHTNESS	                  0x0F
#define FADE_DELAY                        0x40

#define DISPLAY_WIDTH                     128
#define DISPLAY_HEIGHT                    128

/* Exported macro ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
class SSD1351OLED {
public:
	void Init(void);
	void Printf(char *fmt, ...);
	void SetDot(uint8_t x,uint8_t y);
	void FillRGB(uint8_t r,uint8_t g,uint8_t b);
	void FillRGBEx(uint8_t r,uint8_t g,uint8_t b, uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
	void Enable(uint8_t en);
	void DrawBitmap(const uint8_t *bitmaparray,uint16_t bytes, uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
	void Rotate(uint8_t r);
	void SetTextXY(uint8_t x, uint8_t y);
	void GotoXY(uint8_t x, uint8_t y);
	void PutChar(uint8_t C);
	void PutString(const char *String);
	void SetFontColor(uint8_t r,uint8_t g,uint8_t b);
	void HorizontalScroll(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e);
	void StopMoving(void);
	void StartMoving(void);
	void FadeIn(void);
	void FadeOut(void);
	void DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
	void SetPixels(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2);
	void DrawVLine(uint8_t x, uint8_t y, uint8_t height);
	void DrawHLine(uint8_t x, uint8_t y, uint8_t width);
	void DrawRoundRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius);
	void DrawCircle(uint8_t xCenter, uint8_t yCenter, uint8_t radius);
	void FillCircle(uint8_t xCenter, uint8_t yCenter, uint8_t radius);

	void AnalogClockInit(byte x, byte y, byte r); //  x & y are the coordinates of the center of the clock, r is the radius of the clock face
	void DisplayTime( byte hours, byte minutes, byte seconds = -1 ); // draw hands in the position for the given hours and minutes 
	void PrintNumber(long n);

		//Device Properties - these are read only constants	 
	static const uint8_t Width = DISPLAY_WIDTH; 	/**< Display width in pixels */
	static const uint8_t Height = DISPLAY_HEIGHT;	/**< Display height in pixels */
	static const uint8_t Right = DISPLAY_WIDTH-1;	/**< Right most pixel on Display (equals Width -1)*/
	static const uint8_t Bottom = DISPLAY_HEIGHT-1; /**< Bottom most pixel on Display (equals Height -1)*/
	static const uint8_t CenterX = DISPLAY_WIDTH/2;	/**< Horizontal center pixel on Display (equals Width/2)*/
	static const uint8_t CenterY = DISPLAY_HEIGHT/2;/**< Vertical center pixel on Display (equals Height/2)*/
private:
	uint8_t rotate;
	uint8_t pos_x, pos_y;
	uint8_t font_color_1, font_color_2;

	/* Sizes and positions of clock */
	byte x_centre      ; /* x-coordinate of clock centre                  */
	byte y_centre      ; /* y-coordinate of clock centre                  */
	byte radius        ; /* radius of clock face                          */
	byte radius_aspect ; /* radius of clock face adjuted for aspect ratio */
	byte l_hour        ; /* length of hour hand                           */
	byte l_minute      ; /* length of minute hand                         */
	byte l_second      ; /* length of second hand                         */

	/* Previous positions of hour and minute hands */
	byte PX_Hour   ; /* previous x-coordinate of hour hand   */
	byte PY_Hour   ; /* previous y-coordinate of hour hand   */
	byte PX_Minute ; /* previous x-coordinate of minute hand */
	byte PY_Minute ; /* previous y-coordinate of minute hand */
	byte PX_Second ; /* previous x-coordinate of second hand */
	byte PY_Second ; /* previous y-coordinate of second hand */

	/* Positions of digital clock and date, and time offset */
	byte DigRow     ; /* row position of digital clock    */
	byte DigColumn  ; /* column position of digital clock */
	byte Offset     ; /* time offset from system clock    */
	byte Hours      ; /* current hours                    */
	byte Minutes    ; /* current minutes                  */
	byte Seconds    ; /* current seconds                  */ 
	byte DateRow    ; /* row position of date string      */
	byte DateColumn ; /* column position of date string   */

	void CalcHands( byte angle, byte radius, byte *x, byte *y );
	void DrawFace();
	void Box( byte x, byte y );
	void SegBox( byte FaceAngle );

	void WriteCommand(uint8_t cmd);
	void WriteData(uint8_t data);
	void SetAddress(uint8_t a,uint8_t b,uint8_t c,uint8_t d);
};

extern SSD1351OLED SSD1351Oled;

#endif /* __LIB_SSD1351OLED_H */
/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

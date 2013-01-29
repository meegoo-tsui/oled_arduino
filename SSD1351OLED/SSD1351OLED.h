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

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint8_t width;                                // LCD width in pixels (default orientation)
  uint8_t height;                               // LCD height in pixels (default orientation)
} lcdProperties_t;

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
/* Exported macro ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#endif /* __LIB_SSD1351OLED_H */
/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

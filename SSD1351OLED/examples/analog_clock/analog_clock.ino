/********************** (C) COPYRIGHT 2013 meegoo tsui ************************/
/*!
 * @file      analog_clock.ino
 * @brief     analog clock demo. 
 * @author    meegoo tsui
 * @version   1.0
 * @date      2013/02/06
 *
 * 版本历史:
 * - <meegoo tsui，2013/02/06>：初始版本；
 */
/******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <SSD1351OLED.h>
#include <SPI.h>
#include <stdarg.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*!
 * @fn    void setup(void)
 * @brief 系统初始化。
 * \author meegoo (2013/01/30)
 */
void setup(void)
{
	/* 初始化oled */
	SSD1351Oled.Init();
	SSD1351Oled.FillRGB(0x00, 0x00, 0x00);
	SSD1351Oled.Rotate(0);
	SSD1351Oled.SetFontColor(0xFF, 0xFF, 0xFF);
	SSD1351Oled.DrawLine(0x00,0x00, 0x7F,0x7F);
	SSD1351Oled.DrawLine(0x00,0x7F, 0x7F,0x00);
	SSD1351Oled.DrawLine(0x00,0x40, 0x7F,0x40);
	SSD1351Oled.DrawLine(0x40,0x00, 0x40,0x7F);
	SSD1351Oled.FadeIn();
}

/******************************************************************************/
/*!
 * @fn    void setup(void)
 * @brief 系统主循环。
 * \author meegoo (2013/01/30)
 */
void loop(void)
{
}

/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

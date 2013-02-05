/********************** (C) COPYRIGHT 2013 meegoo tsui ************************/
/*!
 * @file      drawbitmap.cpp
 * @brief     draw bitmap and rotate. 
 * @author    meegoo tsui
 * @version   1.0
 * @date      2013/01/30
 *
 * 版本历史:
 * - <meegoo tsui，2013/01/30>：初始版本；
 */
/******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <SSD1351OLED.h>
#include <SPI.h>
#include "beauty_64x64.h"

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
	SSD1351Oled.Init();
	SSD1351Oled.FillRGB(0x00, 0x00, 0x00);
	SSD1351Oled.Enable(1);
}

/******************************************************************************/
/*!
 * @fn    void setup(void)
 * @brief 系统主循环。
 * \author meegoo (2013/01/30)
 */
void loop(void)
{
	/* 逆时针0度 */
	SSD1351Oled.Rotate(R0);
	SSD1351Oled.DrawBitmap((uint8_t *)gImage_beauty_64x64, gImage_beauty_64x64_size, 0x20,0x5f,0x20,0x5f);	
	delay(1000);

	/* 逆时针90度 */
	SSD1351Oled.Rotate(R90);
	SSD1351Oled.DrawBitmap((uint8_t *)gImage_beauty_64x64, gImage_beauty_64x64_size, 0x20,0x5f,0x20,0x5f);	
	delay(1000);

	/* 逆时针180度 */
	SSD1351Oled.Rotate(R180);
	SSD1351Oled.DrawBitmap((uint8_t *)gImage_beauty_64x64, gImage_beauty_64x64_size, 0x20,0x5f,0x20,0x5f);
	delay(1000);

	/* 逆时针270度 */
	SSD1351Oled.Rotate(R270);
	SSD1351Oled.DrawBitmap((uint8_t *)gImage_beauty_64x64, gImage_beauty_64x64_size, 0x20,0x5f,0x20,0x5f);
	delay(1000);
}

/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

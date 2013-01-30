/********************** (C) COPYRIGHT 2013 meegoo tsui ************************/
/*!
 * @file      BLE_Watch_OLED.cpp
 * @brief     BLE watch demo
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
	SSD1351Oled.init();
	SSD1351Oled.FillRGB(0x00, 0x00, 0x00);
	SSD1351Oled.OledEnable(1);
}

/******************************************************************************/
/*!
 * @fn    void setup(void)
 * @brief 系统主循环。
 * \author meegoo (2013/01/30)
 */
void loop(void)
{
	SSD1351Oled.FillRGB(0xFF, 0x00, 0x00);
	SSD1351Oled.FillRGB(0x00, 0xFF, 0x00);
	SSD1351Oled.FillRGB(0x00, 0x00, 0xFF);
}

/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

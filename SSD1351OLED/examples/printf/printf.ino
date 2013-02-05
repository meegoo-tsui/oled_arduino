/********************** (C) COPYRIGHT 2013 meegoo tsui ************************/
/*!
 * @file      printf.ino
 * @brief     printf demo. 
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
	int i;

	SSD1351Oled.Init();
	SSD1351Oled.FillRGB(0x00, 0x00, 0x00);

	SSD1351Oled.SetTextXY(2, 2);
	SSD1351Oled.PutString("123456");
	SSD1351Oled.SetTextXY(2, 3);
	SSD1351Oled.PutString("Hello, world, haaaaaaaaaaaaaaaaaaaaaaaax");
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
}

/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

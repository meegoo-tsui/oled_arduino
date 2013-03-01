/********************** (C) COPYRIGHT 2013 meegoo tsui ************************/
/*!
 * @file      printf_scroll.ino
 * @brief     scroll demo. 
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
 * @fn    void print_test(void)
 * @brief 系统初始化。
 * \author meegoo (2013/01/30)
 */
void print_test(void)
{
	SSD1351Oled.FillRGB(0x00, 0x00, 0x00);
	
	SSD1351Oled.SetFontColor(0xFF, 0xFF, 0xFF);
	SSD1351Oled.SetTextXY(2, 2);
	SSD1351Oled.PutString("0123456789");
	
	SSD1351Oled.SetFontColor(0xFF, 0x00, 0x00);
	SSD1351Oled.SetTextXY(2, 3);
	SSD1351Oled.PutString("Hello, world");
	
	SSD1351Oled.SetFontColor(0x00, 0xFF, 0x00);
	SSD1351Oled.SetTextXY(2, 4);
	SSD1351Oled.PutString("Hello, world");
		
	SSD1351Oled.SetFontColor(0x00, 0x00, 0xFF);
	SSD1351Oled.SetTextXY(2, 5);
	SSD1351Oled.PutString("Hello, world");	

	SSD1351Oled.HorizontalScroll(0x3f, 40, 8, 0x00, 0x01);
	SSD1351Oled.StartMoving();
}

/******************************************************************************/
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
}

/******************************************************************************/
/*!
 * @fn    void setup(void)
 * @brief 系统主循环。
 * \author meegoo (2013/01/30)
 */
void loop(void)
{
	uint8_t i;

	SSD1351Oled.Printf("Demo - printf and scroll\n");
	for(i=0; i<4; i++){
		SSD1351Oled.Rotate(i);
		print_test();
		SSD1351Oled.FadeIn();
		delay(2000);
		SSD1351Oled.FadeOut();
	}
}

/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

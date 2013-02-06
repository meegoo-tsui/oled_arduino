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
#include <stdarg.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*!
 * @fn    p(char *fmt, ... )
 * @brief 串口打印。
 * \author meegoo (2013/01/30)
 */
#if 0
void p(char *fmt, ...)
{ 
	char tmp[128];                   /* resulting string limited to 128 chars */
	va_list args;
	va_start (args, fmt );
	vsnprintf(tmp, 128, fmt, args);
	va_end (args);
	Serial.print(tmp);
}
#endif

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
	SSD1351Oled.Enable(1);

#if 0
	/* init uart */
	Serial.begin(57600);
	while (!Serial);
	p("Ready ....\r\n");
#endif
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

	while(1){	
		for(i=0; i<4; i++){ /* 打印测试 */
			SSD1351Oled.FillRGB(0x00, 0x00, 0x00);
			SSD1351Oled.Rotate(i);
			
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

			delay(3000);
		}
	}
}

/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

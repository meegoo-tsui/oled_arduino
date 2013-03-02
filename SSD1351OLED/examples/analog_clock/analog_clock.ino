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
byte h, m, s;

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

	/* 对角线 */
	SSD1351Oled.SetFontColor(0xFF, 0xFF, 0xFF);
	SSD1351Oled.DrawLine(0x00,0x00, 0x7F,0x7F);
	/* 对角线 */
	SSD1351Oled.SetFontColor(0xFF, 0x00, 0x00);
	SSD1351Oled.DrawLine(0x00,0x7F, 0x7F,0x00);
	/* 垂直线 */
	SSD1351Oled.SetFontColor(0x00, 0xFF, 0x00);
	SSD1351Oled.DrawVLine(0x40,0x00, 0x7F);
	/* 水平线 */
	SSD1351Oled.SetFontColor(0x00, 0x00, 0xFF);
	SSD1351Oled.DrawHLine(0x00,0x40, 0x7F);
	/* 实心圆 */
	SSD1351Oled.FillCircle(64, 64, 10);
	/* 空心圆 */
	SSD1351Oled.DrawCircle(64, 64, 20);

	SSD1351Oled.FadeIn();
	delay(1000);
	SSD1351Oled.FillRGB(0x00, 0x00, 0x00);

	SSD1351Oled.Printf("Demo - analog clock\n");
	SSD1351Oled.AnalogClockInit(SSD1351Oled.CenterX,SSD1351Oled.CenterY,SSD1351Oled.CenterY-4);
	h = 0;
	m = 0;
	s = 0;
}

/******************************************************************************/
/*!
 * @fn    void setup(void)
 * @brief 系统主循环。
 * \author meegoo (2013/01/30)
 */
void loop(void)
{
	while(1){
		SSD1351Oled.DisplayTime(h, m, s);
		s++;
		if(s == 60){
			s = 0;
			m++;
			if(m == 60){
				m = 0;
				h = (h + 1)%12;
			}
		}
		delay(1000);
	}
}

/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

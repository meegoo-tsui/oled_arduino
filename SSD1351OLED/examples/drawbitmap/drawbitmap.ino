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
#define BMP_64_64                      0

#if (BMP_64_64 == 1)
	#include "beauty_64x64.h"
#else
	#include "photo_128x128.h"
#endif

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
		for(i=0; i<4; i++){
			#if (BMP_64_64 == 1)
				SSD1351Oled.Rotate(i);
				SSD1351Oled.DrawBitmap((uint8_t *)gImage_beauty_64x64, gImage_beauty_64x64_size, 0x20,0x5f,0x20,0x5f);
			#else
				//SSD1351Oled.DrawBitmap((uint8_t *)gImage_photo_128x128_0, gImage_photo_128x32_size, 0x00,0x7f,0x00,0x1f);
				//SSD1351Oled.DrawBitmap((uint8_t *)gImage_photo_128x128_1, gImage_photo_128x32_size, 0x00,0x7f,0x20,0x3f);
				SSD1351Oled.DrawBitmap((uint8_t *)gImage_photo_128x128_2, gImage_photo_128x32_size, 0x00,0x7f,0x40,0x5f);
				SSD1351Oled.DrawBitmap((uint8_t *)gImage_photo_128x128_3, gImage_photo_128x32_size, 0x00,0x7f,0x60,0x7f);
			#endif
			SSD1351Oled.FadeIn();
			delay(2000);
			SSD1351Oled.FadeOut();
		}
	}
}

/********************** (C) COPYRIGHT 2013 meegoo tsui  *********END OF FILE***/

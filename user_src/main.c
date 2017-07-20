/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <iostm8l151g4.h> // CPU型号
#include "Pin_define.h"   // 管脚定义
#include "initial.h"      // 初始????? 预定?????
#include "Timer.h"        // 定时?????
#include "uart.h"         // uart
#include "lcd.h"          // lcd
#include "stdlib.h"
#include "time.h"
/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

UINT16 rand_data = 0;
u8 FLAG_SW10 = 0;
u16 KEY_COUNT = 0;
void main(void)
{
    u8 Key_Value;
    _DI();       // 关全局中断
    RAM_clean(); // 清除RAM
    VHF_GPIO_INIT();
    SysClock_Init();
    TIM4_Init();
    UART1_INIT(); // UART1 for PC Software
    _EI();        // 允许中断
    WDT_init();
    lcd_init();
    ClearWDT(); // Service the WDT
    beep_init();
    srand((unsigned)time(NULL));
    while (1)
    {
        ClearWDT(); // Service the WDT
        lcd_desplay();
        Key_Value = KEY_SCAN(0);
        LEDCtr();
        if (Key_Value != KEY_Empty)
        {
            switch (Key_Value)
            {
            case KEY_Empty:
                break;
            case KEY_SW2_Down:
                break;
            case KEY_SW3_Down:
                break;
            case KEY_SW4_Down:
                break;
            default:
                break;
            }
        }
    }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

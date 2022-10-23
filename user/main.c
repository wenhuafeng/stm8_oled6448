/*
 * Project:  sc1086
 * MCU:      STM8L051F3
 * Main OSC: IRC_16MHz
 * Sub OSC:  IRC_32.768KHZ
 * Author:   wenhuafeng
 */

#include "includes.h"

#define SOFTWARE_VERSION "101"

void main(void)
{
    Sys_Init();
    COMMON_Init();

    do {
        COMMON_Process();
    } while (1);
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
    while (1) {
    }
}
#endif

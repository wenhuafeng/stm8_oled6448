#include "includes.h"

#warning message "Software_Version: <V300>"
#warning message "Software_Date:    2019/01/12"
#warning message "Software_Project: SC-1086"
#warning message "Software_MCU:     STM8L051F3"
#warning message "Main_OSC:         IRC_16MHz"
#warning message "SUB_OSC:          IRC_32.768KHZ"
#warning message "Author:           wenhuafeng"

CONST uint8_t Version[3] = "300";

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

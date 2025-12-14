#include "init.h"
#define DELAY_BUTTON_FILTER 100    // антидребезг / минимальный интервал [file:21]
void EXTI15_10_IRQHandler(void);
void SysTick_Handler(void);
void EXTI_ITR_Init(void);
void SysTick_Init(void);
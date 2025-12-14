#include "it_handlers.h"

extern uint16_t GlobalTickCount;
uint16_t ExternInterruptTickCount = 0;

void SysTick_Handler(void)
{
    GlobalTickCount++;
    ExternInterruptTickCount++;           // считаем время между нажатиями [file:21]
}

void EXTI15_10_IRQHandler(uint8_t *led)
{
    // сброс флага прерывания по линии кнопки (PC13 в методичке)
    SET_BIT(EXTI->PR, EXTI_PR_PR13);      // очистка pending-бита [file:21]

    if (ExternInterruptTickCount >= DELAY_BUTTON_FILTER) {   // защита от дребезга [file:21]
        led++;                               // каждое нажатие: Led = Led + 1
        if (led > 6) led = 1;                // цикл 1..3, под себя подправь количество светодиодов
        ExternInterruptTickCount = 0;
    }
}
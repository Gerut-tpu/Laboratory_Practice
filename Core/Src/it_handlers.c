#include "it_handlers.h"

extern volatile uint8_t led;       // из main.c: 1..6
extern volatile uint32_t GlobalTickCount;  // не обязателен, но для debounce

#define DEBOUNCE_MS 100u  // антидребезг 100 мс [file:21]

static volatile uint16_t ExternInterruptTickCount = 0;

void SysTick_Handler(void)
{
    GlobalTickCount++;
    ExternInterruptTickCount++;
}

void EXTI15_10_IRQHandler(void)
{
    // Сброс pending линии 13 [file:21]
    SET_BIT(EXTI->PR, EXTI_PR_PR13);

    // Антидребезг: пропускаем, если <100 мс от прошлого
    if (ExternInterruptTickCount < DEBOUNCE_MS) return;
    ExternInterruptTickCount = 0;

    // Каждое валидное нажатие/отпускание: следующий LED
    led++;
    if (led > 6) led = 1;
}
void EXTI_ITR_Init(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);  // SYSCFG clock [file:21]

    MODIFY_REG(SYSCFG->EXTICR[3],
               SYSCFG_EXTICR4_EXTI13_Msk,
               SYSCFG_EXTICR4_EXTI13_PC);  // EXTI13 = PC13 [file:21]

    SET_BIT(EXTI->IMR, EXTI_IMR_MR13);             // unmask [file:21]

    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13);           // rising edge
    CLEAR_BIT(EXTI->FTSR, EXTI_FTSR_TR13);           // falling edge

    NVIC_SetPriority(EXTI15_10_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(EXTI15_10_IRQn);                // NVIC [file:21]
}

void SysTick_Init(void)
{
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);  // stop [file:21]
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);   // interrupt enable
    SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk); // AHB clock

    MODIFY_REG(SysTick->LOAD, SysTick_LOAD_RELOAD_Msk, 179999u << SysTick_LOAD_RELOAD_Pos);  // 1мс @180МГц [file:21]
    MODIFY_REG(SysTick->VAL, SysTick_VAL_CURRENT_Msk, 0u);

    SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);    // start [file:21]
}
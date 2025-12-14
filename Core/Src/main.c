#include "init.h"
int main(void)
{
    RCC_Init();
    GPIO_Init();
    while(1)
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0);
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS7);
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS14);
        SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS0);
        SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS1);
        SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS2);
    }
}
#include "init.h"
int main(void)
{
    RCC_Init();
    GPIO_Init();
    uint8_t led = 0;
    while(1)
    {
    if (led == 1)
    {
    SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR2);
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0);   // включить первый
    }    
    else if (led == 2)
    {
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0);
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS7);   // второй
    }    
    else if (led == 3)
    {
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR7);
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS14);   // третий
    }
    else if (led == 4)
    {
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR14);
    SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS0);   // четвертый   
    }   
    else if (led == 5)
    {
    SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR0);
    SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS1);   // пятый  
    }   
    else if (led == 6)
    {
    SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR1);
    SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS2);   // пятый  
    }   
    }
}
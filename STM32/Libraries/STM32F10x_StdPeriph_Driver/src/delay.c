#include "delay.h"

uint32_t real_ms, real_us ;

void delay_init(uint32_t SYSCLK){
SysTick->CTRL = 0x00; // use SYSCLK/8 for counting
real_ms = SYSCLK / 8000;
real_us = real_ms / 1000;
}
void delay_us(uint32_t us){
SysTick->VAL = 0x00; // Counting value
SysTick->LOAD = us * real_us; // Load value to count 
SysTick->CTRL = 0x01;
while (SysTick->CTRL == 0x01);
SysTick->CTRL = 0x00;
SysTick->VAL = 0x00;
}
void delay_ms(uint16_t ms)
{
SysTick->VAL = 0x00;
SysTick->LOAD = ms * real_ms;
SysTick->CTRL = 0x01;
while (SysTick->CTRL == 0x01);
SysTick->CTRL = 0x00;
SysTick->VAL = 0x00;
}

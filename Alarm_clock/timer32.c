/*
 * timer32_init.c
 *
 *  Created on: Apr 6, 2020
 *      Author: Brandon Chase
 */


#include <timer32.h>

void initialize_timer32(void)
{
    TIMER32_1->CONTROL = 0xE2;
    TIMER32_1->LOAD = LOAD_VALUE; // Represent 1 second
    NVIC_SetPriority(T32_INT1_IRQn, 1);
    NVIC_DisableIRQ(T32_INT1_IRQn);
}


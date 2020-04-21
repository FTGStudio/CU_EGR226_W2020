/*
 * timer16_init.c
 *
 *  Created on: Apr 6, 2020
 *      Author: Brandon Chase
 */


#include "timer16.h"
#include "msp.h"

void initialize_timer_a1(void)
{
    TIMER_A1->CTL = 0x02D1;// SMCLK, ID= /8, up mode, TA clear
    TIMER_A1->EX0 = 7; // Divide by 8;
    TIMER_A1->CCR[0] = 47; // 29
    TIMER_A1->CCTL[0] |= 0x10; // Enable TA1.0 interrupt
    NVIC_SetPriority(TA1_0_IRQn, 2); // Set priority to 3 in NVIC
    NVIC_EnableIRQ(TA1_0_IRQn);
}

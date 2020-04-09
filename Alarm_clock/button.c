/*
 * button.c
 *
 *  Created on: Feb 9, 2020
 *      Author: michael
 */

#include "button.h"
#include "util.h"
#include "msp.h"

/*
 *
 * Description:
 *
 * This function initializes the ARMING button.
 * P1.6 is setup as input
 *
 */
void init_button_zero()
{
    CLR(P5->SEL0, 0); /* Enable GPIO for P5.0 */
    CLR(P5->SEL1, 0);
    SET(P5->DIR, 0);/* Configure P1.6 as input */
    SET(P5->REN, 0);/* Enable up/down resistor for P5.0 */
    CLR(P5->OUT, 0);/* Enable pull down resistor for P5.0 */
    CLR(P5->IES, 0);//Clear the interrupt slect for low to high transition
    SET(P5->IE, 0);//enable interupt
}


/*
 *
 * Description:
 *
 * This function initializes the DISARMING button.
 * P1.7 is setup as input
 *
 */
void init_button_one()
{
    CLR(P5->SEL0, 1);/* Enable GPIO */
    CLR(P5->SEL1, 1);
    SET(P5->DIR, 1);/* Configure P5.1 as input */
    SET(P5->REN, 1);/* Enable up/down resistor for P5.1 */
    CLR(P5->OUT, 1);/* Enable pull down resistor for P5.1 */
    CLR(P5->IES, 1);//Clear the interrupt slect for low to high transition
    SET(P5->IE, 1);//enable interupt
}


void init_button_interrupts()
{
    NVIC_SetPriority(PORT5_IRQn, 3);
    NVIC_EnableIRQ(PORT5_IRQn);
}
/*
 * Description:
 *
 * This function is setup to scan for ARM input on the P1->IN register
 *
 *
 */
bool button_read_zero()
{
    bool is_pressed = false;
    if(P5->IN & BUTTON_ZERO_MASK)
        is_pressed = true;

    return is_pressed;
}


/*
 *
 * Description:
 *
 * This function is setup to scan for DISARM input on P1->IN register
 *
 */
bool button_read_one()
{
    bool is_pressed = false;
    if(P5->IN & BUTTON_ONE_MASK)
        is_pressed = true;

    return is_pressed;
}


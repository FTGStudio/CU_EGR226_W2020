/*
 * button.c
 *
 *  Created on: Feb 9, 2020
 *      Author: michael
 */

#include "button.h"
#include "util.h"
#include "msp.h"


// TODO Refactor button setup logic for reusability (Create #define MACRO for initialising buttons) or (Generic function)

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


/*
 *
 * Description:
 *
 * Sets up P5.2
 *
 */
void init_button_two()
{
    CLR(P5->SEL0, 2);/* Enable GPIO */
    CLR(P5->SEL1, 2);
    SET(P5->DIR, 2);/* Configure P5.1 as input */
    SET(P5->REN, 2);/* Enable up/down resistor for P5.1 */
    CLR(P5->OUT, 2);/* Enable pull down resistor for P5.1 */
    CLR(P5->IES, 2);//Clear the interrupt slect for low to high transition
    SET(P5->IE, 2);//enable interupt
}


/*
 *
 * Description:
 *
 * Sets up P6.7
 *
 */
void init_button_three()
{
    CLR(P6->SEL0, 7);/* Enable GPIO */
    CLR(P6->SEL1, 7);
    SET(P6->DIR, 7);/* Configure P5.1 as input */
    SET(P6->REN, 7);/* Enable up/down resistor for P5.1 */
    CLR(P6->OUT, 7);/* Enable pull down resistor for P5.1 */
    CLR(P6->IES, 7);//Clear the interrupt slect for low to high transition
    SET(P6->IE, 7);//enable interupt
}


void init_button_interrupts()
{
    NVIC_SetPriority(PORT5_IRQn, 3);
    NVIC_EnableIRQ(PORT5_IRQn);
    NVIC_SetPriority(PORT6_IRQn, 3);
    NVIC_EnableIRQ(PORT6_IRQn);
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


// TODO refactor the button read functions to take input parameters PORT, and PIN.  Return which button was pressed


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

/*
 *
 * Description:
 *
 * This function is setup to scan for DISARM input on P5->IN register
 *
 */
bool button_read_two()
{
    bool is_pressed = false;
    if(P5->IN & BUTTON_TWO_MASK)
        is_pressed = true;

    return is_pressed;
}

/*
 *
 * Description:
 *
 * This function is setup to scan for DISARM input on P6->IN register
 *
 */
bool button_read_three()
{
    bool is_pressed = false;
    if(P6->IN & BUTTON_THREE_MASK)
        is_pressed = true;

    return is_pressed;
}


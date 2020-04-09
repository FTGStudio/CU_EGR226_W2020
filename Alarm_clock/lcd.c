/*
 * lcd.c
 *
 *  Created on: Apr 9, 2020
 *      Author: michael
 */
#include "lcd.h"
#include "msp.h"


/*
 * Description:
 *
 * The LCD for this system is dedicated to Port 4.  Therefore we have
 * to configure the port as output.
 *
 * Returns:
 *
 * Nothing
 *
 */


void lcd_init()
{
    P4->SEL1 &= ~0xFF;
    P4->SEL0 &= ~0xFF;
    P4->DIR |= 0xFF;
    P1->SEL1 &= ~0xC0;
    P1->SEL0 &= ~0xC0;
    P1->DIR |= 0xC0;
}

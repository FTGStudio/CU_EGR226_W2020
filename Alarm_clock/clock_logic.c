/*
 * clock_logic.c
 *
 *  Created on: Apr 6, 2020
 *      Author: Brandon Chase
 */

#include "clock_logic.h"
#include "hd44780/hd44780.h"


void display_welcome_screen()
{
    hd44780_write_string("WELCOME", 1, 1, CR_LF);
    hd44780_write_string("PRESS BUTTON", 3, 3, CR_LF);
    hd44780_write_string("TO START", 4, 3, CR_LF);
}

void setup_initial_conditions()
{


}

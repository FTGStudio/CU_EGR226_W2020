/*
 * util.c
 *
 *  Created on: Feb 10, 2020
 *      Author: michael
 */


#include "util.h"


/*
 *  delay in milliseconds when using a system clock of 3 MHz
 *
 */
void delay_ms(int ms)
{
    int i, j;

    for(j=0; j < ms; j++) // will denote ms
    {
        for(i = 250; i > 0; i--)
        {
            // do nothing
            // When we enter this for loop
            // "no-op"
            // "1 iteration = 1 tick of system clock
        }
    }
}


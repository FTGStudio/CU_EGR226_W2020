/*
 * led.c
 *
 *  Created on: Feb 9, 2020
 *      Author: michael
 */

#include "led.h"
#include "util.h"
#include "msp.h"


/*
 *
 * Decription
 *
 * This initalises the 3.2 and 3.2
 */

void led_init()
{
    CLR(P3->SEL0, 3);
    CLR(P3->SEL1, 3);
    SET(P3->DIR, 3);
    CLR(P3->OUT, 3); // Set P3.3 as output

    CLR(P3->SEL0, 2);
    CLR(P3->SEL1, 2);
    SET(P3->DIR, 2);
    CLR(P3->OUT, 2); // Set P3.2 as output


    CLR(P6->SEL0, 1);
    CLR(P6->SEL1, 1);
    SET(P6->DIR, 1);
    CLR(P6->OUT, 1);// Set p3.2 as output

}
/*
 * Description
 *
 * This function takes one input parametrer that will decide if
 * LED0 or LED1 should be on.
 *
 * returns:
 *
 * Nothing
 */

void led_on(int led)
{

    if(led == LED0)
    {
        SET(P3->OUT,3);
    }
   if(led == LED1)
    {
        SET(P3->OUT, 2);
    }

}

/*
 * Description
 *
 * This function takes one input parametrer that will decide if
 * LED0 or LED1 should be off.
 *
 * returns:
 *
 * Nothing
 */
void led_off(int led)
{
    if(led == LED0)
    {
        CLR(P3->OUT,3);
    }
    else if(led == LED1)
    {
        CLR(P3->OUT, 2);
    }


}


void led_system_power()
{
    SET(P3->OUT, 3);
}
void led_alarm_is_set()
{
    SET(P3->OUT, 2);
}
void led_alarm_notifcation()
{
    SET(P6->OUT, 1);
    delay_ms(500);
    CLR(P6->OUT, 1);
    delay_ms(500);
}
void led_alarm_off()
{
    CLR(P3->OUT, 2);
    CLR(P6->OUT, 1);

}

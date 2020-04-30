/*
 * lcd.c
 *
 *  Created on: Apr 9, 2020
 *      Author: michael
 */
#include "lcd.h"
#include "msp.h"
#include "hd44780/hd44780.h"
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include <strings.h>
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

void display_current_time()
{
    hd44780_write_string("12:00", 2, 6, CR_LF);

}

void display_set_hour(char* h_pos_0, char* h_pos_1)
{
    char* tmp_string = "";
    strcat(h_pos_0, h_pos_1);
    hd44780_write_string("  ", 2, 6, CR_LF);
    delay_ms(500);
    hd44780_write_string(tmp_string, 2, 6, CR_LF);
    delay_ms(500);
}

void display_set_minute(char* m_pos_0, char* m_pos_1)
{
    char* tmp_string = "";
    strcat(m_pos_0, m_pos_1);


    hd44780_write_string("  ", 2, 9, CR_LF);
    delay_ms(500);
    hd44780_write_string(tmp_string, 2, 6, CR_LF);
    delay_ms(500);
}

void display_user_prompt()
{
    hd44780_write_string("0) Set System", 1, 1, CR_LF);
    hd44780_write_string("time", 2, 1, CR_LF);
    hd44780_write_string("1) Set System", 3, 1, CR_LF);
    hd44780_write_string("time", 4, 1, CR_LF);
}

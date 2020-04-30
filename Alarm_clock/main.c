#include <stdbool.h>
#include <stdio.h>
#include "timer16.h"
#include "timer32.h"
#include "clock_logic.h"
#include "piezzo.h"
#include "rtc.h"
#include "msp.h"
#include "util.h"
#include "hd44780/hd44780.h"
#include "button.h"
#include "led.h"
#include "lcd.h"
#include "I2C.h"
#include "ascii_time.h"

//TODO
/*
 * Implement button handling (specifically detect releases button, instead of pushes)
 * Implement functionality for button (set the time)
 * Implement a way to monitor the alarm time
 */



// Testing
void system_init(void);
//void initialize_timer32(void);
void display_reaction_time(void);
void handle_button_input(void);
void confirm_system_time(void);
void confirm_alarm_time(void);
void set_time(bool alarm);
bool set_time_flag = false;
bool set_hour_flag = false;
bool set_min_flag = false;
bool time_confirm_flag = false;
enum STATES {
    IDLE,
    SET_SYSTEM_TIME,
    SNOOZE,
    ALARM_OFF,
    ALARM_EXECUTE,
    USER_PROMPT,
    HANDLE_USER_SELECTION,
    SET_ALARM_TIME
};
int current_state = IDLE;
int underflow_count = 0;
int hour_counter = 5;
int minute_counter = 7;
/**
 * main.c
 */
void main(void)
{

    system_init();

    while(1)
    {
        switch(current_state)
        {
        case USER_PROMPT:
            display_user_prompt();
            current_state = HANDLE_USER_SELECTION;
            break;
        case SET_SYSTEM_TIME:
            set_time(false);
            break;
//        case BUTTON1:
//            break;
        case SNOOZE:   //Button2 has now become a function to snooze the alarm
            piezzo_turn_alarm_off();
            led_alarm_off();
            //TODO add conditional logic to analyze time interval
            if(underflow_count == 10)
            {
                current_state = ALARM_EXECUTE;
                underflow_count = 0;
            }
            break;
        case ALARM_OFF: //Button3 has now become a function to turn off the alarm
            piezzo_turn_alarm_off();
            led_alarm_off();
            break;
        case ALARM_EXECUTE:
            led_alarm_notification();
            piezzo_turn_alarm_on();
            break;
        case HANDLE_USER_SELECTION:
            break;
        case SET_ALARM_TIME:
            break;
        default:
            break;
        }
        //rtc_read_seconds();
        //delay_ms(1000);
    }
}

/*
 *
 * Description:
 *
 * This function will initialize the entire system for the reaction timer game.
 *
 * This includes the button interrupts, leds, and lcd screen.
 *
 * Returns:
 *
 * nothing
 *
 */
void system_init()
{
    __disable_irq();
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    piezzo_init();
    init_button_zero();
    init_button_one();
    init_button_two();
    init_button_three();
    lcd_init();
    init_button_interrupts();
    led_init();
    initialize_timer32();
    initialize_timer_a1();
    setup_initial_conditions();
    I2C1_init();

    __enable_irq();
    hd44780_clear_screen();
//    display_welcome_screen();
    led_system_power();
//    display_current_time();


}
/*
 *
 * Description:
 *
 * This is our button interrupt handler.  It is configured to detect
 * GPIO changes and determine if BTN0 or BTN1 was pressed.
 *
 * Returns:
 *
 * Nothing
 *
 */
void PORT5_IRQHandler()
{
    if(button_read_zero() && set_time_flag == false && current_state != HANDLE_USER_SELECTION)
    {
        current_state = USER_PROMPT;
        set_time_flag = true;
    }
    else if(button_read_zero() && set_time_flag == true && current_state == HANDLE_USER_SELECTION)
    {
        hd44780_clear_screen();
        current_state = SET_SYSTEM_TIME;
        set_hour_flag = true;
    }
    else if(button_read_zero() && current_state == SET_SYSTEM_TIME && set_min_flag == false)
    {
        set_min_flag = true;
        set_hour_flag = false;
    }
    else if(button_read_zero() && current_state == SET_SYSTEM_TIME && set_min_flag == true)
    {
        time_confirm_flag = true;
        set_min_flag = false;
    }
    P5->IFG &= ~0x07;// Clear the flags for Button0, Button1, and Button2

}


void PORT6_IRQHandler()
{
    if(button_read_three())
    {
        current_state = ALARM_OFF;
    }
    P6->IFG &= ~0x80;// Clear the flag for Button3
}

/*
 * Description
 *
 * This is the the IRQ handler for the row/column sync.
 *
 * Returns:
 *
 * Nothing
 *
 */
void TA1_0_IRQHandler(void)
{
    TIMER_A1->CCTL[0] &= ~1;  // clear the interrupt flag
    hd44780_timer_isr();
}
void T32_INT1_IRQHandler(void)
{
    TIMER32_1->INTCLR = 0; // clear the raw interrupt flag
    TIMER32_1->LOAD = THREE_MHZ;
    underflow_count++;
}

void handle_button_input()
{

}

void confirm_alarm_time()
{

}

void confirm_system_time()
{

}
void set_time(bool alarm)
{
    if(set_hour_flag == true)
    {
        display_set_hour(hour_characters[hour_counter][0], hour_characters[hour_counter][1]);
    }
    else if(set_min_flag == true)
    {
        display_set_minute(minutes_characters[minute_counter][0], minutes_characters[minute_counter][1]);
    }
    else if(time_confirm_flag == true)
    {
            if(alarm)
            {
                confirm_alarm_time();
            }
            else
            {
                confirm_system_time();
            }
            current_state = IDLE;
            set_time_flag = false;
            delay_ms(1000);
            hd44780_clear_screen();
    }
}

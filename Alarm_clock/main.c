#include <stdbool.h>
#include <stdio.h>
#include "clock_logic.h"
#include "piezzo.h"
#include "rtc.h"
#include "msp.h"
#include "util.h"
#include "hd44780/hd44780.h"
#include "button.h"
#include "led.h"
#include "timer16.h"
#include "timer32.h"
#include "lcd.h"
#include "i2c.h"


void system_init(void);
void initialize_timer_a1(void);
void initialize_timer32(void);
void handle_button_input(void);
void handle_user_selection(void);
void set_time(bool alarm);

enum STATES {
                IDLE,
                SET_SYSTEM_TIME,
                BUTTON1,
                SNOOZE,
                ALARM_OFF,
                ALARM_EXECUTE,
                USER_PROMPT,
                HANDLE_BUTTON_INPUT,
                HANDLE_USER_SELECTION,
                SET_ALARM_TIME,
            };
int current_state = IDLE;
int underflow_count = 0;
bool set_hour = false;
bool set_min = false;
bool confirm_hour = false;
bool confirm_min = false;


/**
 * main.c
 */
void main(void)
{

    system_init();
    delay_ms(1000);


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
        case SNOOZE: // press button 2 to snooze the alarm
            piezzo_turn_alarm_off();
            // TODO add conditional logic to analyze the time interval
            if(underflow_count == 10)
            {
                current_state = ALARM_EXECUTE;
                underflow_count = 0;
            }
            break;
        case ALARM_OFF:     //button 3 used to turn of the alarm led and turn off the buzzer
            piezzo_turn_alarm_off();
            led_alarm_off();
            break;
        case ALARM_EXECUTE:
            led_alarm_notifcation();
            piezzo_turn_alarm_on();
            break;
        case HANDLE_BUTTON_INPUT:
            handle_button_input();
            break;
        case HANDLE_USER_SELECTION:
            handle_user_selection();
            break;
        case SET_ALARM_TIME:
            set_time(true);
            break;
        default:
            break;
        }
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
    led_system_power();
    I2C1_init();

    __enable_irq();
    hd44780_clear_screen();
    display_current_time();


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
    current_state = HANDLE_BUTTON_INPUT;
    P5->IFG &= ~0x07;// Clear the flags for btn0, btn1, bt2
}

void PORT6_IRQHandler()
{
    if(button_read_three())
    {
        current_state = ALARM_OFF;
    }
    P6->IFG &= ~0x80; // clear the flags for
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

/*
 *
 *
 *
 */
void T32_INT1_IRQHandler(void)
{
    TIMER32_1->INTCLR = 0; // clear the raw interrupt flag
    TIMER32_1->LOAD = THREE_MHZ;
    underflow_count++; // Add 1 for each second
}


void handle_button_input()
{
    if(current_state != HANDLE_USER_SELECTION)
    {
        if(button_read_zero())
        {
            if(confirm_hour == false && confirm_min == false)
            {
                current_state = USER_PROMPT;
                confirm_hour = true;
            }
            else if(confirm_hour == true && confirm_min == false)
            {
                // TODO set the system hour
                confirm_min = true;
                set_hour = false;
                set_min = true;
            }
            else if(confirm_hour == true && confirm_min == true)
            {
                // TODO set the system minute
                confirm_hour = false;
                confirm_min = false;
            }
        }
        else if(button_read_two())
        {
            current_state = SNOOZE;
        }
    }
    else if(current_state == HANDLE_USER_SELECTION)
    {
        handle_user_selection();
    }
}

void handle_user_selection()
{
    if(button_read_zero())
    {
       current_state = SET_SYSTEM_TIME;
    }
    else if(button_read_one())
    {
       current_state = SET_ALARM_TIME;
    }
}

void set_time(bool alarm)
{
    if(set_hour == false && set_min == false)
    {
        set_hour = true;
    }
    else if(set_hour == true && set_min == false)
    {
        display_set_hour();
        // TODO to actually set the hour
    }
    else if(set_hour == false && set_min == true)
    {
        //clear the lcd screen
        display_set_minute();
        // TODO actually set the minute
    }
}

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
void set_time(bool alarm);
void confirm_alarm_time(void);
void confirm_system_time(void);

enum STATES {
                IDLE,
                SET_SYSTEM_TIME,
                BUTTON1,
                SNOOZE,
                ALARM_OFF,
                ALARM_EXECUTE,
                USER_PROMPT,
                HANDLE_USER_SELECTION,
                SET_ALARM_TIME,
            };
int current_state = IDLE;
int underflow_count = 0;
bool set_time_flag = false; // indicate if we're setting time for an alarm or the system
bool set_hour_flag = false; // indicates if we're setting the hour
bool set_min_flag = false; // indicates if we're setting the min
bool time_confirm_flag = false; // indicates that the time we want to save for the alarm or system


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
        case HANDLE_USER_SELECTION:
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

    if(button_read_zero() &&
            set_time_flag == false &&
            current_state != HANDLE_USER_SELECTION)
    {
        current_state = USER_PROMPT;
        set_time_flag = true;
    }
    else if(button_read_zero() &&
            set_time_flag == true &&
            current_state == HANDLE_USER_SELECTION)
    {
        hd44780_clear_screen();
        current_state = SET_SYSTEM_TIME;
        set_hour_flag = true;
    }
    else if(button_read_one() &&
            set_time_flag == true &&
            current_state == HANDLE_USER_SELECTION)
    {
        current_state = SET_ALARM_TIME;
        set_hour_flag = true;
    }
    else if(button_read_zero() &&
            current_state == SET_SYSTEM_TIME &&
            set_min_flag == false)
    {
        set_min_flag = true;
        set_hour_flag = false;
    }
    else if(button_read_zero() &&
            current_state == SET_SYSTEM_TIME &&
            set_min_flag == true)
    {
        time_confirm_flag = true;
        set_min_flag = false;
    }

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
        display_set_hour();
    }
    else if(set_min_flag == true)
    {
        display_set_minute();
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

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
#include "timer16.h"
#include "timer32.h"
#include "clock_logic.h"
#include "lcd.h"
#define LOAD_VALUE 0x02
// Testing
void system_init(void);
void initialize_timer32(void);
void display_reaction_time(void);

enum STATES {IDLE, BUTTON0, BUTTON1, SNOOZE, ALARM_OFF, ALARM_EXECUTE, SET_MINUTES};
int current_state = IDLE;

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
        case BUTTON0:
            piezzo_turn_alarm_on();
            led_alarm_is_set();
            led_alarm_notification();
            break;
        case BUTTON1:
            break;
        case SNOOZE:   //Button2 has now become a function to snooze the alarm
            piezzo_turn_alarm_off();
            break;
        case ALARM_OFF: //Button3 has now become a function to turn off the alarm
            piezzo_turn_alarm_off();
            led_alarm_off();
            break;
        case ALARM_EXECUTE:
            led_alarm_notification();
            piezzo_turn_alarm_on();
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
    setup_initial_conditions();

    __enable_irq();
    hd44780_clear_screen();
    display_welcome_screen();
    led_system_power();


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

    if(button_read_zero())
    {
        current_state = BUTTON0;
    }
    if(button_read_one())
    {
        current_state = BUTTON1;
    }
    if(button_read_two())
    {
        current_state = SNOOZE;
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

        TIMER32_1->LOAD = LOAD_VALUE;
}


/*
 *
 *
 *
 */





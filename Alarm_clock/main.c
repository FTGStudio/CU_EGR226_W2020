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
#include "i2c.h"
#define LOAD_VALUE 0x02

void system_init(void);
void initialize_timer_a1(void);

enum STATES {IDLE, BUTTON0, BUTTON1, SNOOZE, ALARM_OFF, ALARM_EXECUTE};
int current_state = IDLE;

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
        case BUTTON0:

            led_alarm_is_set();

            break;
        case BUTTON1:
            piezzo_turn_alarm_off();
            break;
        case SNOOZE: // press button 2 to snooze the alarm
            piezzo_turn_alarm_off();
            break;
        case ALARM_OFF:     //button 3 used to turn of the alarm led and turn off the buzzer
            piezzo_turn_alarm_off();
            led_alarm_off();
            break;
        case ALARM_EXECUTE:
            led_alarm_notifcation();
            piezzo_turn_alarm_on();
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
    display_welcome_screen();


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
    else if(button_read_one())
    {
        current_state = BUTTON1;
    }
    else if(button_read_two())
    {
        current_state = SNOOZE;
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


void T32_INT1_IRQHandler(void)
{
    TIMER32_1->INTCLR = 0; // clear the raw interrupt flag

    TIMER32_1->LOAD = LOAD_VALUE;
}


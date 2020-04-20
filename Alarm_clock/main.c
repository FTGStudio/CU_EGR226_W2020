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

void system_init(void);
void initialize_timer32(void);
void display_reaction_time(void);

enum STATES {IDLE, BUTTON0, BUTTON1, BUTTON2, BUTTON3, TURN_ON_LED};
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
            break;
        case BUTTON1:
            piezzo_turn_alarm_off();
            break;
        case BUTTON2:
            piezzo_turn_alarm_off();
            break;
        case BUTTON3:
            piezzo_turn_alarm_off();
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
    //lcd_init();
    init_button_interrupts();
    led_init();
    initialize_timer32();
    setup_initial_conditions();

    __enable_irq();
    hd44780_clear_screen();
    display_welcocom_screen();


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
        current_state = BUTTON2;
    }
    P5->IFG &= ~3;// Clear the flag
}

void PORT6_IRQHandler()
{
    if(button_read_three())
    {
        current_state = BUTTON3;
    }
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





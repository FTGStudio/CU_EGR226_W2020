#include "msp.h"
#include "util.h"
#include "hd44780/hd44780.h"
#include "button.h"
#include "led.h"

#include <stdbool.h>
#include <stdio.h>
#include "piezzo_init.h"
#include "rtc_init.h"
#include "timer32_init.h"
#include "timer16_init.h"
#include "clock_logic.h"
#define LOAD_VALUE 0x02

void system_init(void);

void initialize_timer32(void);
void lcd_init(void);
void display_reaction_time(void);


/**
 * main.c
 */
void main(void)
{
    system_init();
    while(1)
    {

    }
}
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

    init_button_zero();
    init_button_one();
    lcd_init();
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

    P5->IFG &= ~3;// Clear the flag
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





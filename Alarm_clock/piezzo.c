#include "piezzo.h"
#include "msp.h"


/*
 *  Description:
 *
 *  This function will initialize timer 16 as a pwm for our piezzo buzzer
 *
 */
void piezzo_init(void)
{
    /* Configure P2.4 as Timer A0.1 output */
    P2->SEL0 |= 0x80;
    P2->SEL1 &= ~0x80;
    P2->DIR |= 0x80;

    /* configure TimerA0.4 as PWM */
    TIMER_A0->CCR[0] = 3826-1;     /* PWM Period */
    TIMER_A0->CCR[4] = 3826/2;     /* CCR4 PWM duty cycle */
    TIMER_A0->CCTL[4] = 0xE0;       /* CCR4 reset/set mode */
    TIMER_A0->CTL = 0x0214;         /* use SMCLK, count up, clear TA0R register */

    NVIC_SetPriority(TA0_N_IRQn, 3);
    NVIC_EnableIRQ(TA0_N_IRQn);
}


/*
 *  Description:
 *
 *  This function will turn off the alarm
 *
 */
void piezzo_turn_alarm_off()
{
    /* Configure P2.7 as Timer A0.1 output */
    P2->SEL0 &= ~0x80;
    P2->SEL1 &= ~0x80;
    P2->DIR &= ~0x80;
}



/*
 *  Description:
 *
 *  This function will turn on the alarm
 *
 */
void piezzo_turn_alarm_on()
{
    /* Configure P2.7 as Timer A0.1 output */
    P2->SEL0 |= 0x80;
    P2->SEL1 &= ~0x80;
    P2->DIR |= 0x80;
}


void TA0_N_IRQHandler(void)
{
    TIMER_A0->CCTL[1] &= ~1;
}


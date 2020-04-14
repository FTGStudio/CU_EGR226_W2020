#include "piezzo.h"
#include "msp.h"

void redirect(void);
void piezzo_init(void)
{
    /*
     * Duty Cycle = 50%
     * Output Frequency  = (F(timer) / Prescalers) / (TAxCCR0 + 1)
     *  We desire a PWM of 10kHz
     *
     *  3 MHz / 10 kHz = 300
     *  10kHz = Output Frequency
     */


    TIMER_A0->CTL = 0x212;
    TIMER_A0->CCTL[1] = 0xB0;
    TIMER_A0->CCR[1] = 300;
    TIMER_A0->CCTL[1] |= 0x10;

    // Configure 2.4 as Timer A).1 compare output
    P2->SEL0 |= 0x10;
    P2->SEL1 &= 0x10;
    P2->DIR |= 0x10;

    redirect();

    NVIC_SetPriority(TA0_N_IRQn, 3);
    NVIC_EnableIRQ(TA0_N_IRQn);

}


void TA0_N_IRQHandler(void)
{
    TIMER_A0->CCTL[1] &= ~1;
}


void redirect(void)
{
    PMAP->KEYID = 0x2D52;
    P2MAP->PMAP_REGISTER1 = PMAP_TA0CCR1A; // Map P2.4 to TA0.1
    P2->DIR |= 16;
    P2->SEL0 |= 16;
    P2->SEL1 |= 16;
    PMAP->CTL= 1;
    PMAP->KEYID = 0;
}

#include "piezzo.h"
#include "msp.h"


void redirect(void);

/*
 *
 * Decription:
 *
 * This function will initialize timer 16 as pwm for our piezzo buzzer
 *
 *
*/

void piezzo_init(void)
{
    //Dudty cycle = 50%
    // Fout = (ftimer/perscalers) / (TAxCCR) +1)


    //10KHz = fout
    // 3MHz/10KHZ= 300

    TIMER_A0->CTL = 0x212;
    TIMER_A0->CCR[0] = 300;
    TIMER_A0->CCR[1] = 300/2;
    TIMER_A0->CCR[1] |= 0x10;

    // configure 2.4as timer A0.1 compare output
    P2->SEL0 |= 0x10;
    P2->SEL1 &= 0x10;
    P2->DIR |= 0x80;
    NVIC_SetPriority(TA0_N_IRQn, 3);
    NVIC_EnableIRQ(TA0_N_IRQn);


}

void TA0_N_IRQHandler(void)
{
    TIMER_A0->CCTL[0] &= ~1;
    P2->OUT ^= 16;

}

void redirect(void)
{

    PMAP->KEYID = 0x2D52;
    P2MAP->PMAP_REGISTER1 = PMAP_TA0CCR1A; // MAP p2.4 TO ta0.1
    P2->DIR |= 16;
    P2->SEL0 |= 16;
    P2->SEL1 |= 16;
    PMAP->KEYID = 0;



}

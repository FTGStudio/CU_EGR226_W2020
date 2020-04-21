/*
 * rtc_init.c
 *
 *
 *  Created on: Apr 6, 2020
 *      Author: Brandon Chase
 */


#include "rtc.h"
#include "msp.h"
#include "I2C.h"

unsigned char rtc_read_seconds(void)
{
    unsigned char data;
    I2C1_Read(RTC_ADDR, RTCSEC, &data);

    return data;
}

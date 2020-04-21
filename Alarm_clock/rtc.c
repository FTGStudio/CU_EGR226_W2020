/*
 * rtc_init.c
 *
 *
 *  Created on: Apr 6, 2020
 *      Author: Brandon Chase
 */


#include "rtc.h"
#include "msp.h"
#include "i2c.h"

unsigned char rtc_read_seconds()
{
    unsigned char data;
    I2C1_Read(RTC_ADDR, 0, &data);

    return data;
}

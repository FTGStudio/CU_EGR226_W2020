/*
 * I2C.h
 *
 *  Created on: Apr 21, 2020
 *      Author: Tatec
 */

#ifndef I2C_H_
#define I2C_H_

#define RTC_ADDR 0x68

void I2C1_init(void);
int I2C1_Read(int slaveAddr, unsigned char memAddr, unsigned char* data);


#endif /* I2C_H_ */

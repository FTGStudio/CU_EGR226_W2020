/*
 * util.h
 *
 *  Created on: Feb 9, 2020
 *      Author: michael
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

#define SET(REG,N) (REG |=  (1<<N))
#define CLR(REG,N) (REG &= ~(1<<N))

void delay_ms(int32_t ms);


#endif /* UTIL_H_ */

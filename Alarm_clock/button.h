/*
 * button.h
 *
 *  Created on: Feb 9, 2020
 *      Author: michael
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdbool.h>
#include <stdint.h>

#define BUTTON_ZERO_MASK 0x01
#define BUTTON_ONE_MASK 0x02

void init_button_zero(void);
void init_button_one(void);
bool button_read_zero(void);
bool button_read_one(void);
void init_button_interrupts(void);



#endif /* BUTTON_H_ */

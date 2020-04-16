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
#define BUTTON_TWO_MASK 0x04
#define BUTTON_THREE_MASK 0x80

void init_button_zero(void);
void init_button_one(void);
void init_button_two(void);
void init_button_three(void);

void init_button_interrupts(void);

bool button_read_zero(void);
bool button_read_one(void);
bool button_read_two(void);
bool button_read_three(void);




#endif /* BUTTON_H_ */

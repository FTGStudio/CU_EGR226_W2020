/*
 * piezzo_init.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Brandon Chase
 */

#ifndef PIEZZO_H_
#define PIEZZO_H_

#include "util.h"
#define F_CPU 3000000 // 3MHz

void piezzo_init(void);
void piezzo_turn_alarm_off(void);
void piezzo_turn_alarm_on(void);
void play_note(int note);

#endif /* PIEZZO_H_ */

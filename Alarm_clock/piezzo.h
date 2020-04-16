/*
 * piezzo_init.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Brandon Chase
 */

#ifndef PIEZZO_H_
#define PIEZZO_H_

#define F_CPU 3000000 // 3MHz
#define BUZZER 0x10 // BIT 4

void piezzo_init(void);
void piezzo_turn_alarm_off(void);

#endif /* PIEZZO_H_ */

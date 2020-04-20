/*
 * led.h
 *
 *  Created on: Feb 9, 2020
 *      Author: michael
 */

#ifndef LED_H_
#define LED_H_

#define LED0 0x08 //3.3
#define LED1 0x04 //3.2
#define LED2 0x02 //6.1
<<<<<<< HEAD
=======
#include "util.h"
>>>>>>> 8403434... Updated code with working alarm off and alarm exicute function

void led_init(void);
void led_on(int led);
void led_off(int led);
<<<<<<< HEAD
void led_alarm_is_set(void);
void led_alarm_off(void);
void led_system_power(void);
void led_alarm_notification(void);
=======
void led_system_power();
void led_alarm_is_set();
void led_alarm_notifcation();
void led_alarm_off();


>>>>>>> 8403434... Updated code with working alarm off and alarm exicute function


#endif /* LED_H_ */

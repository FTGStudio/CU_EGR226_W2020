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

void led_init(void);
void led_on(int led);
void led_off(int led);
void led_alarm_is_set(void);
void led_alarm_off(void);
void led_system_power(void);
void led_alarm_notification(void);


#endif /* LED_H_ */

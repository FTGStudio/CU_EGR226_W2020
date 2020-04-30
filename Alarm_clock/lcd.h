/*
 * lcd.h
 *
 *  Created on: Apr 9, 2020
 *      Author: michael
 */

#ifndef LCD_H_
#define LCD_H_


void lcd_init(void);
void display_current_time(void);
void display_set_minute(char* h_pos_0, char* h_pos_1);
void display_set_hour(char* m_pos_0, char* m_pos_1);
void display_user_prompt();
#endif /* LCD_H_ */

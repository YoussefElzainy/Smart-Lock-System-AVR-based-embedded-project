/*
 * lcd.h
 *
 * Created: 8/9/2025 12:40:23 PM
 *  Author: DELL
 */ 


#ifndef LCD_H_

#define F_CPU 8000000UL
#define LCD_H_

#include <avr/io.h>
#include <avr/delay.h>
typedef unsigned char U8;

#define lcd_ctrl_port PORTC
#define lcd_data_port PORTD
#define lcd_ctrl_dir DDRC
#define lcd_data_dir DDRD

#define RS_pin PC0
#define RW_pin PC1
#define EN_pin PC2



void lcd_data(U8 data);
void lcd_command(U8 cmnd);
void lcd_init();
void lcd_display(U8 string[]);




#endif /* LCD_H_ */
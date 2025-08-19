/*
 * lcd.c
 *
 * Created: 8/9/2025 12:40:12 PM
 *  Author: DELL
 */ 
#include "lcd.h"
void lcd_init(){
	lcd_data_dir = 0xFF; // Data port
	lcd_ctrl_dir |= (1 << RS_pin) | (1 << RW_pin) | (1 << EN_pin); // Control port
	// Set data and control ports as outputs
	lcd_data_port = 0xFF; // Data port
	lcd_ctrl_port |= (1 << RS_pin) | (1 << RW_pin) | (1 << EN_pin); // Control port
	_delay_ms(20); // LCD Power ON delay
	lcd_command(0x38); // 2 lines, 5x7 matrix
	lcd_command(0x0C); // Display on, cursor on
	lcd_command(0x01); // Clear display
	_delay_ms(2);
}
void lcd_command(U8 cmnd){
	lcd_data_port = cmnd; // Send the command to the data port
	lcd_ctrl_port &= ~(1 << RS_pin); // RS = 0 for command
	lcd_ctrl_port &= ~(1 << RW_pin); // RW = 0 for write
	lcd_ctrl_port |= (1 << EN_pin); // Enable high
	_delay_ms(1);
	lcd_ctrl_port &= ~(1 << EN_pin); // Enable low
	_delay_ms(1);
}

void lcd_data(U8 data){
	lcd_data_port = data; // Send the data to the data port
	lcd_ctrl_port |= (1 << RS_pin); // RS = 1 for data
	lcd_ctrl_port &= ~(1 << RW_pin); // RW = 0 for write
	lcd_ctrl_port |= (1 << EN_pin); // Enable high
	_delay_ms(1);
	lcd_ctrl_port &= ~(1 << EN_pin); // Enable low
	_delay_ms(1);
}

void lcd_display(U8 *str)
{
	for (U8 i = 0 ; str[i] != '\0' ; i++)
	{
		lcd_data(str[i]);
		_delay_ms(1);
	}
}

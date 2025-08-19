/*
 * keypad.h
 *
 * Created: 8/16/2025 10:41:34 AM
 *  Author: DELL
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define  F_CPU 8000000UL
#define keypad_port PORTA
#define keypad_pin PINA
#define keypad_dir DDRA

typedef unsigned char U8;

#include <avr/io.h>
#include <avr/delay.h>


void keypad_init();
char read_keypad();
char keypad_scan();


#endif /* KEYPAD_H_ */
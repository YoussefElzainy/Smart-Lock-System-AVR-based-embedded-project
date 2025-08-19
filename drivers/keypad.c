/*
 * keypad.c
 *
 * Created: 8/16/2025 10:41:49 AM
 *  Author: DELL
 */ 
#include "keypad.h"


char keypad[4][4] = {
	{'D' , 'C' , 'B' , 'A'},
	{'#' , '9' , '6' , '3'},
	{'0' , '8' , '5' , '2'},
	{'*' , '7' , '4' , '1'}
};


void keypad_init(void){
	keypad_dir = 0xF0;   // high nibble = output, low nibble = input
	keypad_port = 0x0F;  // enable pull-up resistors on low nibble
}

char read_keypad(){
	for (U8 column = 0 ; column < 4 ; column++)
	{
		keypad_port = ~(1 << (column+4));
		
		for (U8 row = 0 ; row < 4 ; row++)
		{
			if (!(keypad_pin & (1 << row)))
			{
				while(!(keypad_pin & (1 << row)));
				 
				 return keypad[row][column];
			}
		}
	}
	return '\0';
}


char keypad_scan(){
	char key = read_keypad();
	if(key != '\0'){
		return key;
	}
	return '\0';
}
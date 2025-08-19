/*
 * password management system.c
 *
 * Created: 8/17/2025 12:58:42 PM
 * Author : DELL
 */ 

#include "lcd.h"
#include "keypad.h"

const char* users[] = {
	"youssef",
	"adham",
	"ahmed",
	"karim",
	"omar",
	"ali",
	"hossam",
	"mostafa",
	"mahmoud"
};

struct admin{
	U8 name [20];
	U8 password [5];
	};

int main(void)
{
    struct admin a1[9] = {
	    {"youssef", "1234"} ,
		{"adham"  , "2345"}
    };
	a1[2].name[0] = '\0';
	a1[2].password[0] = '\0';
	U8 choice = 0;
	U8 state = 0;
	U8 pass[5];
	U8 newPass[5];
	U8 tries = 0;
	U8 passIndex = 0;
	U8 editChoice = '\0';
	U8 secure = 1;
	U8 userCtr = 1;
	U8 curr = 0;
	
	lcd_init();
	keypad_init();
	
    while (1) 
    {
		U8 key = keypad_scan();
		if (key == '#' && secure == 1)
		{
			state = 0;
		
		}
		
		
		if (state == 0)
		{
			lcd_command(0x01);
			lcd_command(0x80);
			lcd_display("choose user:1-9");
			lcd_command(0xc0);
			state++;
		}
		if (state == 1 && key != '\0' && key >= '0' && key <='9')
		{
			
			lcd_data(key);
			choice = key ;
			state++;
			_delay_ms(400);
		} if(state == 2){
			
			for (U8 i = 0 ; i < 9 ; i++)
			{
				if ((choice - '1' == i && a1[i].name[0] == '\0'))
				{
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("invalid user!!");
					_delay_ms(1000);
					state = 0;
					break;
				}
				else if (choice - '1' == i && state == 2)
				{
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("pass of user ");
					lcd_data(i + '1');
					lcd_data('?');
					lcd_command(0xc0);
					state++;
					
				}
				
			}
			
		}
		else if (state == 3 && key != '\0' && key >= '0' && key <='9')
		{
			if (passIndex < 4)
			{
				lcd_enc_data(key);
				pass[passIndex++] = key;
				pass[passIndex] = '\0';
			}if (passIndex == 4)
			{
				if (strcmp(pass , a1[choice - '1'].password) == 0)
				{
					curr = choice;
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("welcome, ");
					lcd_display(a1[choice - '1'].name);
					tries = 0;
					state++;
					passIndex = 0;
					_delay_ms(1000);
					
				}else if (tries == 2)
				{
					secure = 0;
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("security lock");
					for (U8 i = 0 ; i < 30 ; i++)
					{
						lcd_command(0xc0);
						U8 counter [4];
						sprintf(counter , "%u" , 30 -i);
						lcd_display("wait for ");
						if (i <= 20)
						{
							lcd_display(counter);
						}else{
														
							lcd_data(counter[0]);
							lcd_display("    ");	
						}
						
						_delay_ms(1000);
					}
					tries = 0;
					passIndex = 0;
					state = 0;
					secure =1;
				}
				else{
						passIndex = 0;
						state = 2;
						pass[0] = '\0';
						lcd_command(0x01);
						lcd_command(0x80);
						lcd_display("wrong password!");
						lcd_command(0xc0);
						lcd_data('2' - tries);
						lcd_display(" left");
						tries++;
						_delay_ms(1000);
				}
			}
			
		}else if (state == 4)
		{
			lcd_command(0x01);
			lcd_command(0x80);
			lcd_display("select(A,B,C,D)");
			lcd_command(0xc0);
			lcd_display("select # to exit");
			state++;
		}else if (state == 5 && ((key >= 'A' && key <= 'D') || key == '#') )
		{
			
			editChoice = key;
			state++;
		}else if (state == 6)
		{
			switch(editChoice){
				case 'A':
				if (userCtr == 8)
				{
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("limit reached");
					_delay_ms(1000);
					state = 4;
				}else{
					userCtr++;
					
					strcpy(a1[userCtr].name, users[userCtr]);
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("pass of ");
					lcd_display(a1[userCtr].name);
					lcd_data('?');
					lcd_command(0xc0);
					state=7;
				}
					break;
				case 'B':
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("user to edit?");
					lcd_command(0xc0);
					
					state = 8;
					break;
				case 'C':
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("user to delete?");
					lcd_command(0xc0);
					
					state = 10;
					break;
				case 'D':
					lcd_command(0x01);
					state = 11;
					break;
				case '#':
					state = 0;
					
			}
		}else if (state == 7 && key> '0' && key <='9')
		{
			
			if (passIndex < 4)
			{
				lcd_enc_data(key);
				a1[userCtr].password[passIndex] = key;
				passIndex++;
			}if (passIndex == 4)
			{
				_delay_ms(200);
				lcd_command(0x01);
				lcd_command(0x80);
				lcd_display("password saved");
				passIndex = 0;
				state = 4;
				_delay_ms(700);
			}
			
			
			
		}else if (state == 8 && key > '0' && key <= '9')
		{
			choice = key;
			lcd_data(key);
			_delay_ms(200);
			for (U8 i = 0 ; i < 9 ; i++)
			{
				if ((choice - '1' == i && a1[i].password[0] == '\0') )
				{
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("invalid user!!");
					_delay_ms(1000);
					state = 6;
					break;
				}
				
				else if (choice - '1' == i && state == 8)
				{
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("updated pass ");
					lcd_data(i + '1');
					lcd_data('?');
					lcd_command(0xc0);
					state++;
					
				}
		}
		}else if (state == 9)
		{
			if (passIndex < 4 && key >= '0' && key <= '9')
			{
				lcd_enc_data(key);
				a1[choice - '1'].password[passIndex++] = key;
				a1[choice - '1'].password[passIndex] = '\0';
			}if (passIndex == 4)
			{
				lcd_command(0x01);
				lcd_command(0x80);
				lcd_display("password updated");
				_delay_ms(1000);
				passIndex = 0;
				
				state = 4; 
			}
			 
		}else if (state == 10 && key >'0' && key <= '9' )
		{
			choice = key;
			lcd_command(0xc0);
			lcd_data(key);
			_delay_ms(200);
			for (U8 i = 0 ; i < 9 ; i++)
			{
				if ((choice - '1' == i && a1[i].password[0] == '\0'))
				{
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("invalid user!!");
					state= 6;
					_delay_ms(1000);
					break;
				}
				
				else if (choice - '1' == i && state == 10)
				{
					if (choice == curr)
					{
						lcd_command(0x01);
						lcd_command(0x80);
						lcd_display("invalid");
						lcd_command(0xc0);
						lcd_display("operation");
						state= 6;
						_delay_ms(1000);
					}else {
						for (U8 i = choice - '1' ; i < 8 ; i++)
					{
						strcpy(a1[i].name, a1[i+1].name);
						strcpy(a1[i].password, a1[i+1].password);
					}
					a1[userCtr].name[0] = '\0';
					a1[userCtr].password[0] = '\0';
						userCtr--;
						
					
					lcd_command(0x01);
					lcd_command(0x80);
					lcd_display("deleted..");
					
					_delay_ms(1000);
					
					state = 4;
					}
				}
			}
		}else if (state == 11){
			U8 limit = 0;
			if (userCtr %2 == 0)
			{
				limit= userCtr + 1;
			}else {
				limit = userCtr;
			}
			for (U8 i = 0 ; i <limit ; i+= 2)
			{
				lcd_command(0x01);
				lcd_command(0x80);
				lcd_display(a1[i].name);
				if (i != 8)
				{
					lcd_command(0xc0);
					lcd_display(a1[i+1].name);
				}
				
				_delay_ms(800);
			}
			state = 4;
			
		}
		
    }
}


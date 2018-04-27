/*
 * proj2.c
 *
 * Created: 4/25/2018 10:06:54 AM
 * Author : Divergent
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "avr.h"
#include "lcd.h"


int is_pressed(int r, int c)
{
	//Initialize keypad (setting to no connect)
	DDRC = 0;
	PORTC = 0;
	
	//write weak one on column
	SET_BIT(PORTC,c+4);
	
	//write strong zero on row
	SET_BIT(DDRC,r);
	CLR_BIT(PORTC,r);
	
	
	
	//check state of the button
	if ((GET_BIT(PINC,c+4)))
		return 0;
	else
		return 1;
}
int get_key()
{
	int r, c;
	for (r = 0; r < 4; r++)
	{
		for (c = 0; c < 4; c++)
		{
			if (is_pressed(r,c))
				return r * 4 + c + 1;
		}
	}
	return 0;
}
void init()
{
}

void blink_led(int delay_ms)
{
	//test blinking
	SET_BIT(PORTB,0);		//Turn on LED
	wait_avr(delay_ms);			//delay
	CLR_BIT(PORTB,0);		//Turn off LED
	wait_avr(delay_ms);			//delay
}
int main(void)
{
	// Blink LED Test
	//SET_BIT(DDRB,0);				//Setting pin 0 for output mode
	//CLR_BIT(PORTB,0);				//Turn off LED
	
	// LCD Display
	ini_lcd();

	int key;
	char buf[17];
	ini_avr();

    while (1) 
    {
		key = get_key();
		pos_lcd(0, 0);
		
		if (key == 0x01) // Key 1
		{
			sprintf(buf, "%02i", key);
			puts_lcd2(buf);

			//blink_led(100);			
		}
		else if (key == 0x02) // 2
		{
			blink_led(200);			
		}
		else if (key == 0x03) // 3
		{
			blink_led(300);
		}
		else if (key == 0x04) // Key A
		{
			blink_led(100);
		}
		else if (key == 0x05) // 4
		{
			blink_led(400);
		}
		else if (key == 0x06) // 5
		{
			blink_led(500);
		}
		else if (key == 0x07) // 6
		{
			blink_led(600);
		}
		else if (key == 0x08) // B
		{
			blink_led(100);
		}
		else if (key == 0x09) // 7
		{
			blink_led(700);
		}
		else if (key == 0x0A) // 8
		{
			blink_led(800);
		}
		else if (key == 0x0B) // 9
		{
			blink_led(900);
		}
		else if (key == 0x0C) // C
		{
			blink_led(100);
		}
		else if (key == 0x0D) // Key *
		{
			blink_led(200);
		}
		else if (key == 0x0E) // 0
		{
			blink_led(1000);
		}
		else if (key == 0x0F) // #
		{
			blink_led(200);
		}
		else if (key == 0x10) // D
		{
			blink_led(400);
		}

    }
}


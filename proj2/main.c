/*
 * proj2.c
 *
 * Created: 4/25/2018 10:06:54 AM
 * Author : Divergent
 */ 

#include <avr/io.h>
#include "avr.h"


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
	//Setting DDRC for input mode
	CLR_BIT(DDRC,0);
	SET_BIT(PORTC,0);
}
int main(void)
{
	SET_BIT(DDRB,0);				//Setting pin 0 for output mode
	CLR_BIT(PORTB,0);				//Turn off LED
	//init();
    /* Replace with your application code */
    while (1) 
    {
		int key = get_key();
		if (key == 0x01)
		{
			//test blinking
			SET_BIT(PORTB,0);		//Turn on LED
			wait_avr(500);			//delay
			CLR_BIT(PORTB,0);		//Turn off LED
			wait_avr(500);			//delay
		}
		else
			CLR_BIT(PINC,0);
		
    }
}


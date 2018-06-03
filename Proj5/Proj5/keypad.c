/*
 * keypad.c
 *
 * Created: 5/15/2018 5:27:39 PM
 *  Author: Divergent
 */ 

#include "avr.h"
#include "keypad.h"

int is_pressed(int r, int c)
{
	//Initialize keypad (setting to no connect)
	DDRC = 0;
	PORTC = 0;
	//write weak one on column
	SET_BIT(PORTC, c+4);
	//write strong zero on row
	SET_BIT(DDRC, r);
	CLR_BIT(PORTC, r);
	//check state of the button
	if ((GET_BIT(PINC, c+4)))
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
unsigned int get_key_value()
{
	unsigned char r;
	unsigned char c;
	// If A to D pressed
	for(r = 0; r < 4; ++r){
		if(is_pressed(r,3))
		{
			return 65+r;
		}
	}
	
	// 1 to 9 Pressed
	for(r = 0; r < 3; ++r){
		for(c = 0; c < 3; ++c){
			if(is_pressed(r,c)){
				return ((r*3)+c+1)+48;
			}
		}
	}
	//If zero pressed
	if(is_pressed(3,1)){
		return '0';
	}
	// If * pressed
	else if(is_pressed(3,0)){
		return 42;
	}
	// If # pressed
	else if(is_pressed(3,2)){
		return 35;
	}
	//otherwise just return some random char for not pressed
	return 'Z';
}


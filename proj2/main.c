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

#define MAXTIMER 60 // for clock, e.g. 1 minute is 60 seconds, then max is 60
#define MAXHOUR 24 // 24 hours in a day

/*Global Variables Declarations*/
char buf[17];

int year = 2018;
int month = 12;
int day = 31;

int hours = 23;
int minutes = 58;
int seconds = 00;


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


//TEST
void blink_led(int delay_ms)
{
	//test blinking
	SET_BIT(PORTB,0);		//Turn on LED
	wait_avr(delay_ms);		//delay
	CLR_BIT(PORTB,0);		//Turn off LED
	wait_avr(delay_ms);		//delay
}
void test_key(int key)
{
	sprintf(buf, "%i",  key);
	pos_lcd(1, 0);
	puts_lcd2(buf);
}
//-------



// 30 - 4, 6, 9, 11
// 31 - 1, 3, 5, 7, 8, 10, 12
// 28, 29 - 2


void increment_timer()
{
	seconds++;

	if(seconds>=MAXTIMER){
		minutes++;
		seconds=0;
	}
	if(minutes>=MAXTIMER){
		hours++;
		minutes=0;
	}
	if(hours>=MAXHOUR){
		hours=0;
		minutes=0;
		seconds=0;
	}
	increment_date();

}
void increment_date()
{
	if (hours == 0 && minutes == 0 && seconds == 0)
	{

		if (day == 31 && month == 1)
		{
			month=2;
			day=1;
		}
		else if (day == 28 && month == 2)
		{	month = 3;
			day = 1;
		}
		else if (day == 31 && month == 3)
		{	month = 4;
			day = 1;
		}
		else if (day == 30 && month == 4)
		{	month = 5;
			day = 1;
		}
		else if (day == 31 && month == 5)
		{	month = 6;
			day = 1;
		}
		else if (day == 30 && month == 6)
		{	month = 7;
			day = 1;
		}
		else if (day == 31 && month == 7)
		{	month = 8;
			day = 1;
		}
		else if (day == 31 && month == 8)
		{	month = 9;
			day = 1;
		}
		else if (day == 30 && month == 9)
		{	month = 10;
			day = 1;
		}
		else if (day == 31 && month == 10)
		{	month = 11;
			day = 1;
		}
		else if (day == 30 && month == 11)
		{	month = 12;
			day = 1;
		}
		else if (day == 31 && month == 12)
		{	month = 1;
			day = 1;
			year++;
		}
		else
			day++;
	}
	
	

}
void display()
{
	while (1)
	{

		clr_lcd();
		sprintf(buf, "%02i:%02i:%02i",  hours, minutes, seconds);
		pos_lcd(1, 4);
		puts_lcd2(buf);
		sprintf(buf, "%02i/%02i/%04i",  month, day, year);
		pos_lcd(0, 3);
		puts_lcd2(buf);
		increment_timer();
		wait_avr(5);

	}
}
void input_mode()
{
	sprintf(buf, "%s",  "You Type:");
	pos_lcd(0, 0);
	puts_lcd2(buf);



}
int main(void)
{
	// Blink LED Test
	//SET_BIT(DDRB, 0);				//Setting pin 0 for output mode
	//CLR_BIT(PORTB, 0);				//Turn off LED


	// LCD Display
	ini_lcd();

	ini_avr();

	int key;
	char inputBuf[17];

	sprintf(buf, "%s",  "Input Year:");
	pos_lcd(0, 0);
	puts_lcd2(buf);


	//input_mode();

	//display();


    while (1) 
    {
		key = get_key();
		
		if (key == 0x01) // Key 1
		{
			test_key(key);
			sprintf(inputBuf, "%i", key);
			clr_lcd();
			pos_lcd(0, 0);
			puts_lcd2(inputBuf);

		}
		else if (key == 0x02) // 2
		{
			test_key(key);
		
		}
		else if (key == 0x03) // 3
		{
				test_key(key);

		}
		else if (key == 0x04) // Key A
		{
				test_key(key);
		}
		else if (key == 0x05) // 4
		{
				test_key(key);
		}
		else if (key == 0x06) // 5
		{
				test_key(key);
		}
		else if (key == 0x07) // 6
		{
				test_key(key);
		}
		else if (key == 0x08) // B
		{
				test_key(key);
		}
		else if (key == 0x09) // 7
		{
				test_key(key);
		}
		else if (key == 0x0A) // 8
		{
				test_key(key);
		}
		else if (key == 0x0B) // 9
		{
				test_key(key);
		}
		else if (key == 0x0C) // C
		{
				test_key(key);
		}
		else if (key == 0x0D) // Key *
		{
				test_key(key);
		}
		else if (key == 0x0E) // 0
		{
				test_key(key);
		}
		else if (key == 0x0F) // #
		{
				test_key(key);
		}
		else if (key == 0x10) // D
		{
				test_key(key);
		}

		

    }
}
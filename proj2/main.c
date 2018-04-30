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

#define MAXTIMER 60		// for clock, e.g. 1 minute is 60 seconds, then max is 60
#define MAXHOUR 24		// 24 hours in a day 00:00 ~ 23:59 --> 12 hr format --> 00:00~11:59 is AM, 12:00~23:59 is PM
#define CLOCKSPEED 5	// INTERNAL CPU CLOCK SPEED: smaller the faster

/*Global Variables Declarations*/
char buf[17];	// display 16 + '\0' char

// 30 - 4, 6, 9, 11
// 31 - 1, 3, 5, 7, 8, 10, 12
// 28, 29 - 2
int year = 2016;
int month = 2;
int day = 28;

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


void increment_date()
{
	if (hours == 0 && minutes == 0 && seconds == 0)
	{
		int daysInFeb = 28; // default Feb days
		if (year % 4 == 0)	// leap year determination
		{
			if (year % 100 == 0)
			{
				if (year % 400 == 0)
				{
					daysInFeb = 29;
				}
				else
					daysInFeb = 28;
			}
			else
				daysInFeb = 29;
		}
		else
			daysInFeb = 28;

		// 30 - 4, 6, 9, 11
		// 31 - 1, 3, 5, 7, 8, 10, 12
		// 28, 29 - 2

		if (day == daysInFeb && month == 2) // February Case, need to account leap year
		{
			month = 3;
			day = 1;
		}
		else if (day == 31)
		{
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10)
			{
				month++;
				day = 1;
			}
			else if (month == 12)
			{
				month = 1;
				day = 1;
				year++;
			}
			else
				day++;
		}
		else if (day == 30)
		{
			if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				month++;
				day = 1;
			}
			else
				day++;
		}
		else
			day++;

		/*
		if (day == 31 && month == 1)
		{
			month=2;
			day=1;
		}
		else if (day == daysInFeb && month == 2) // February Case, need to account leap year
		{	
			month = 3;
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
		*/
	}		
}
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
void display(int militaryTime) // 1 = military time, 2 = 12 hours
{
	while (1)
	{
		if (militaryTime == 1)
		{
			clr_lcd();
			sprintf(buf, "%02i:%02i:%02i",  hours, minutes, seconds);
			pos_lcd(1, 4);
			puts_lcd2(buf);
		}
		if (militaryTime == 2)
		{
			clr_lcd();

			if (hours-12 == -12) //12 AM because 00 hour is 12AM
			{
				int midnight = 12;
				sprintf(buf, "%02i:%02i:%02iAM",  midnight, minutes, seconds);
			}
			else if (hours-12 < 0) // AM
				sprintf(buf, "%02i:%02i:%02iAM",  hours, minutes, seconds);
			else if (hours-12 == 0) // 12 hour is 12PM
				sprintf(buf, "%02i:%02i:%02iPM",  hours, minutes, seconds);
			else // PM
			{
				int afternoonHr = hours-12;
				sprintf(buf, "%02i:%02i:%02iPM",  afternoonHr, minutes, seconds);
			}
			pos_lcd(1, 3);
			puts_lcd2(buf);
		}
		
		// Calendar Display
		sprintf(buf, "%02i/%02i/%04i",  month, day, year);
		pos_lcd(0, 3);
		puts_lcd2(buf);

		// increment time based on clock speed
		increment_timer();
		wait_avr(CLOCKSPEED);
	}
}

void input_mode()
{
	sprintf(buf, "%s",  "Enter Year:");
	pos_lcd(0, 0);
	puts_lcd2(buf);

	int numOfChar = 0;
	int yearArray[4];
	while (numOfChar < 4)
	{
		yearArray[numOfChar] = key_value();

		sprintf(buf, "%i",  yearArray);
		pos_lcd(1, 0);
		puts_lcd2(buf);

		numOfChar++;
	}


}

int key_value()
{
	int key = get_key();
	int value = 0;

	if (key == 0x01) // Key 1
	{
		value = 1;
	}
	else if (key == 0x02) // 2
	{
		value = 2;

	}
	else if (key == 0x03) // 3
	{
		value = 3;
	}
	else if (key == 0x04) // Key A
	{
		// A
	}
	else if (key == 0x05) // 4
	{

		value = 4;

	}
	else if (key == 0x06) // 5
	{
		value = 5;
	}
	else if (key == 0x07) // 6
	{
		value = 6;
	}
	else if (key == 0x08) // B
	{
		// B
	}
	else if (key == 0x09) // 7
	{
		value = 7;
	}
	else if (key == 0x0A) // 8
	{
		value = 8;
	}
	else if (key == 0x0B) // 9
	{
		value = 9;
	}
	else if (key == 0x0C) // C
	{
		// C
	}
	else if (key == 0x0D) // Key *
	{
		// *
	}
	else if (key == 0x0E) // 0
	{
		value = 0;
	}
	else if (key == 0x0F) // #
	{
		// #
	}
	else if (key == 0x10) // D
	{
		// D
	}
	return value;
}


int main(void)
{
	// Blink LED Test
	//SET_BIT(DDRB, 0);				//Setting pin 0 for output mode
	//CLR_BIT(PORTB, 0);				//Turn off LED


	// LCD Display
	ini_lcd();
	ini_avr();


	input_mode();

	// toggle will determine military or 12 hour clock
	// this will be programmed by button input
	//display(2); // 1 is military , 2 is 12 hr format


   
}


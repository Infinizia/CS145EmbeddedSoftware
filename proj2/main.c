/*
 * proj2.c
 *
 * Created: 4/25/2018 10:06:54 AM
 * Author : Danny and Kevin
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
static int mode = 1;
// 30 - 4, 6, 9, 11s
// 31 - 1, 3, 5, 7, 8, 10, 12
// 28, 29 - 2
static int year = 2018;
static int month = 1;
static int day = 1;

int hours = 0;
int minutes = 0;
int seconds = 0;

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




		// MAP C KEY to 12 hour mode
		int key = get_key_value();
		if (key == 'C')
		{	
			if (mode == 1)
				mode = 2;
			else if (mode == 2)
				mode = 1;
			display(mode);
		}


		// MAP D KEY to INPUT MODE
		key = get_key_value();
		if (key == 'D')
		{
			clr_lcd();
			input_mode();
		}

	}
}


void input_mode()
{
	char buf2[17];
	
		sprintf(buf2, "%s",  "Enter Year:"); // YEAR
		pos_lcd(0, 0);
		puts_lcd2(buf2);

		int yFirst = get_key_value();
		while (yFirst == -1)
		{
			yFirst = get_key_value();
			if (yFirst == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", yFirst);
		pos_lcd(1, 0);
		puts_lcd2(buf2);

		wait_avr(100);
		int ySecond = get_key_value();
		while (ySecond == -1)
		{
			ySecond = get_key_value();
			if (ySecond == 'D')
			display(mode);
		}

		sprintf(buf2, "%i", ySecond);
		pos_lcd(1, 1);
		puts_lcd2(buf2);

		wait_avr(100);

		int yThird = get_key_value();
		while (yThird == -1)
		{
			yThird = get_key_value();
			if (yThird == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", yThird);
		pos_lcd(1, 2);
		puts_lcd2(buf2);

		wait_avr(100);


		int yFourth = get_key_value();
		while (yFourth == -1)
		{
			yFourth = get_key_value();
			if (yFourth == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", yFourth);
		pos_lcd(1, 3);
		puts_lcd2(buf2);

		wait_avr(100);

		// display year
		year = (1000*yFirst) + (100*ySecond) + (10*yThird) + yFourth;


		clr_lcd();

		sprintf(buf2, "%s",  "Enter Month:"); // MONTH
		pos_lcd(0, 0);
		puts_lcd2(buf2);

		int monFirst = get_key_value();
		while (monFirst == -1)
		{
			monFirst = get_key_value();
			if (monFirst == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", monFirst);
		pos_lcd(1, 0);
		puts_lcd2(buf2);

		wait_avr(100);
		int monSecond = get_key_value();
		while (monSecond == -1)
		{
			monSecond = get_key_value();
			if (monSecond == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", monSecond);
		pos_lcd(1, 1);
		puts_lcd2(buf2);

		wait_avr(100);

		month = (10*monFirst) + monSecond;

		
		clr_lcd();

		sprintf(buf2, "%s",  "Enter Day:"); // DAY
		pos_lcd(0, 0);
		puts_lcd2(buf2);

		int dFirst = get_key_value();
		while (dFirst == -1)
		{
			dFirst = get_key_value();
			if (dFirst == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", dFirst);
		pos_lcd(1, 0);
		puts_lcd2(buf2);

		wait_avr(100);
		int dSecond = get_key_value();
		while (dSecond == -1)
		{
			dSecond = get_key_value();
			if (dSecond == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", dSecond);
		pos_lcd(1, 1);
		puts_lcd2(buf2);

		wait_avr(100);

		day = (10*dFirst) + dSecond;


		// TIME
		clr_lcd();

		sprintf(buf2, "%s",  "Enter Hour:"); // HOUR
		pos_lcd(0, 0);
		puts_lcd2(buf2);

		int hFirst = get_key_value();
		while (hFirst == -1)
		{
			hFirst = get_key_value();
			if (hFirst == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", hFirst);
		pos_lcd(1, 0);
		puts_lcd2(buf2);

		wait_avr(100);

		int hSecond = get_key_value();
		while (hSecond == -1)
		{
			hSecond = get_key_value();
			if (hSecond == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", hSecond);
		pos_lcd(1, 1);
		puts_lcd2(buf2);

		wait_avr(100);

		hours = (10*hFirst) + hSecond;

		clr_lcd();

		sprintf(buf2, "%s",  "Enter Minute:"); // MINUTE
		pos_lcd(0, 0);
		puts_lcd2(buf2);

		int minFirst = get_key_value();
		while (minFirst == -1)
		{
			minFirst = get_key_value();
			if (minFirst == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", minFirst);
		pos_lcd(1, 0);
		puts_lcd2(buf2);

		wait_avr(100);

		int minSecond = get_key_value();
		while (minSecond == -1)
		{
			minSecond = get_key_value();
			if (minSecond == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", minSecond);
		pos_lcd(1, 1);
		puts_lcd2(buf2);

		wait_avr(100);

		minutes = (10*minFirst) + minSecond;

		clr_lcd();

		sprintf(buf2, "%s",  "Enter Second:"); // SECONDS
		pos_lcd(0, 0);
		puts_lcd2(buf2);

		int secFirst = get_key_value();
		while (secFirst == -1)
		{
			secFirst = get_key_value();
			if (secFirst == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", secFirst);
		pos_lcd(1, 0);
		puts_lcd2(buf2);

		wait_avr(100);

		int secSecond = get_key_value();
		while (secSecond == -1)
		{
			secSecond = get_key_value();
			if (secSecond == 'D')
				display(mode);
		}

		sprintf(buf2, "%i", secSecond);
		pos_lcd(1, 1);
		puts_lcd2(buf2);

		wait_avr(100);

		seconds = (10*secFirst) + secSecond;

		clr_lcd();

		display(mode);


}


int get_key_value()
{
	int key;

	while(1)
	{
		wait_avr(50);

		key = get_key();

		if (key == 0x01) // Key 1
		{
			return 1;
		}
		else if (key == 0x02) // 2
		{
			return 2;
		}
		else if (key == 0x03) // 3
		{
			return 3;
		}
		else if (key == 0x04) // Key A
		{
			//
		}
		else if (key == 0x05) // 4
		{
			return 4;
		}
		else if (key == 0x06) // 5
		{
			return 5;
		}
		else if (key == 0x07) // 6
		{
			return 6;
		}
		else if (key == 0x08) // B
		{
			// B
		}
		else if (key == 0x09) // 7
		{
			return 7;
		}
		else if (key == 0x0A) // 8
		{
			return 8;
		}
		else if (key == 0x0B) // 9
		{
			return 9;
		}
		else if (key == 0x0C) // C
		{
			return 'C';
		}
		else if (key == 0x0D) // Key *
		{
			// *
		}
		else if (key == 0x0E) // 0
		{
			return 0;
		}
		else if (key == 0x0F) // #
		{
			// #
		}
		else if (key == 0x10) // D
		{
			return 'D';
		}
		else
		{
			return -1;
		}
	}
}


int main(void)
{
	// Blink LED Test
	//SET_BIT(DDRB, 0);				//Setting pin 0 for output mode
	//CLR_BIT(PORTB, 0);				//Turn off LED


	// LCD Display
	ini_lcd();
	ini_avr();

	//display(1);

	input_mode();

	// toggle will determine military or 12 hour clock
	// this will be programmed by button input
	//display(2); // 1 is military , 2 is 12 hr format

}


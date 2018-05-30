/*
 * proj4.c
 *
 * Created: 5/15/2018 5:20:25 PM
 * Author : Danny and Kevin
 */ 

#include <avr/io.h>
//#include <limits.h>
#include <stdio.h>
#include "avr.h"
#include "keypad.h"
#include "voltmeter.h"
#include <stdbool.h>

void mainMenu()
{
	char buf2[17];
	sprintf(buf2, "C:---- A:----"); //Current and Avg
	pos_lcd(0, 0);
	puts_lcd2(buf2);
	sprintf(buf2, "M:---- m:----"); // Max and Min
	pos_lcd(1, 0);
	puts_lcd2(buf2);
}

int main(void)
{
	ini_lcd();
	//ini_avr();
	// set PA0 to input
	//SET_BIT(DDRA,0);
	//CLR_BIT(PORTA,0);
    
	ADMUX |= (1 << REFS0);
	//ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	//ADCSRA = (1 << ADEN) | (1 << ADSC);

	struct Voltage myVoltage;


	bool sampling = false;

	while(1)
	{
		myVoltage.total = 0;
		myVoltage.count = 0;
		myVoltage.avg = 0;
		myVoltage.min = 999;
		myVoltage.max = 0;

		mainMenu();
		int key = get_key_value();
		if (key == '1')
		{
			sampling = true;

			while(sampling)
			{
				//unsigned int voltage = get_a2c();
				//myVoltage.curr = voltage;
				updateStats(&myVoltage);
				displayVoltage(myVoltage);
				wait_avr(500);

				key = get_key_value();
				if (key == '2')
				{
					sampling = false;
				}
			}
		}


	}


}


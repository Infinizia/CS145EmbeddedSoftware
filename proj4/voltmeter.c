/*
 * voltmete.c
 *
 * Created: 5/15/2018 5:36:33 PM
 *  Author: Divergent
 */ 

#include "voltmeter.h"
#include "avr.h"
#include "lcd.h"
//This function get voltage sample readings from avr
unsigned int get_a2c()
{
	ADCSRA = (1 << ADEN) | (1<<ADSC);
	return 5 * ( (ADC) / 10.23 ) ;	  // volt = raw/1024 * 5
	// we want 500, so 1023/10.23=500 *5=500
	//return ADC;

}
//This function update the current voltage stats
void updateStats(struct Voltage *stats)
{
	unsigned int voltage = get_a2c();
	stats->curr = voltage;
	stats->total += stats->curr;
	stats->count++;
	stats->avg = stats->total / stats->count;

	
	if (stats->curr > stats->max)
	{
		stats->max = stats->curr;
	}
	if (stats->curr < stats->min)
	{
		stats->min = stats->curr;
	}
}

void displayVoltage(struct Voltage stats)
{

	char buf2[17];
	sprintf(buf2, "C:%01d.%02d A:%01d.%02d",  (stats.curr/100), (stats.curr%100), (stats.avg/100), (stats.avg%100)); //Current and Avg
	pos_lcd(0, 0);
	puts_lcd2(buf2);
	sprintf(buf2, "M:%01d.%02d m:%01d.%02d",  (stats.max/100), (stats.max%100), (stats.min/100), (stats.min%100)); // Max and Min
	pos_lcd(1, 0);
	puts_lcd2(buf2);

}


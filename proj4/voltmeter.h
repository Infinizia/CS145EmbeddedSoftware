/*
 * voltmeter.h
 *
 * Created: 5/15/2018 5:23:48 PM
 *  Author: Divergent
 */ 


#ifndef VOLTMETER_H_
#define VOLTMETER_H_

struct Voltage
{
	unsigned int min;
	unsigned int max;
	unsigned int curr;
	unsigned int avg;
	unsigned int total;
	unsigned int count;
	
};
unsigned int get_a2c();
void updateStats(struct Voltage *stats);
void displayVoltage(struct Voltage stats);
void reset();
#endif /* VOLTMETER_H_ */
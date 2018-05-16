/*
 * voltmeter.h
 *
 * Created: 5/15/2018 5:23:48 PM
 *  Author: Divergent
 */ 


#ifndef VOLTMETER_H_
#define VOLTMETER_H_
#define struct Voltage Voltage
struct Voltage
{
	unsigned int min;
	unsigned int max;
	unsigned int curr;
	unsigned int avg;	
	
};
unsigned short get_a2c();
void updateStats(Voltage stats);
void displayVoltage(Voltage stats);

#endif /* VOLTMETER_H_ */
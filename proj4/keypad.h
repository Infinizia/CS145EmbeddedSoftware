/*
 * keypad.h
 *
 * Created: 5/15/2018 5:25:49 PM
 *  Author: Divergent
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

int is_pressed(int r, int c);
int get_key();
unsigned int get_key_value();

#endif /* KEYPAD_H_ */
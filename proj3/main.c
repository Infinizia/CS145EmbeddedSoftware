/*
 * proj3.c
 *
 * Created: 5/8/2018 5:12:18 PM
 * Author : Danny and Kevin
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"

struct note {
	int freq;	//the freqency of a note
	int dur;	//the duration of a note	
};

//-------------------------Keypad functions--------------------------------
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
//This get key function just returns a key at the position r,c 
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
//This get key function returns the value of the key pressed
unsigned get_key_value()
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
		return '~';	
}
//------------------------End Keypad functions-------------------------------
//------------------------Music functions-------------------------------
//Initialize the PORT# for speaker output
void init_speaker()
{
	
}
//Function to play the note
void play_note(int freq,int dur)
{
	int k;//K?
	int t;//T?
	for (int i = 0; i < k; ++i)
	{
		//SET PORT_ to 1
		//wait(T_h) high frequency
		//SET PORT_ to 0
		//wait(T_l) low frequency
		
	}
}
//Function to play the song, where n is the size of song
void play_music(struct note *song, int n)
{
	for (int i = 0; i < n;++i)
	{
		play_note(song[i].freq,song[i].dur);
	}	
}
//------------------------End music functions-------------------------------
//function to test speaker
void test_speaker()
{
	
}
int main(void)
{
	//Initialize LCD
    ini_lcd();
	
	//Begin rogram
    while (1) 
    {
    }
}


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
	int freq;	//the frequency of a note
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
	SET_BIT(DDRA,0);
	CLR_BIT(PORTA,0);
	
}
//Function to play the note
void play_note(int freq,int dur)
{
	//double wavelength = 1000 / freq;
	int k = freq * dur;//K?
	//int t;//T?
	//for (int i = 0; i < k; ++i)
	//{
		//SET_BIT(PORTA,0);	//SET PORT_ to 1
		//wait_avr(dur);		//wait(T_h) high frequency
		//CLR_BIT(PORTA,0);	//SET PORT_ to 0
		//wait_avr(dur);		//wait(T_l) low frequency
		//
	//}
	for(int i = 0; i < (dur); i++)
		{
			SET_BIT(PORTA,0);
			wait_avr(freq);
			CLR_BIT(PORTA,0);
			wait_avr(freq);
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
	SET_BIT(PORTA,0);
	wait_avr(1);
	CLR_BIT(PORTA,0);
	wait_avr(1);
}
void play_note_volume(int freq, int dur, double ratio, int tempo) {
	int duration = (dur)/tempo;
	for(int i = 0; i < duration; i++)
	{
		SET_BIT(PORTA,0);
		wait_avr(freq*(1-ratio));
		CLR_BIT(PORTA,0);
		wait_avr(freq*ratio);
	}
	
}
void play_music_volume(struct note *song,int numNotes, double ratio, int tempo)
{
	for (int i = 0;  i < numNotes; i++)
	{
		if ((i > 0) && (song[i].freq == song[i-1].freq)) {
			// int delay = song[i].duration * 0.01;
			wait_avr(5);
		}
		play_note_volume(song[i].freq*2, (song[i].dur), ratio, tempo);
		
		
	}
}
void playHotCrossBuns(int tempo, double volumeRatio) {
	//hot cross buns: bb aa gggg bb aa gggg g g g g a a a a gg bb aa
	int numNotesCross = 17;

	struct note hot_cross_buns[] = {
		{101.2391674,493.88}, // b
		{113.6363636,440}, // a
		{127.5510204,(392*2)}, // g for 2 seconds
		{101.2391674,493.88},
		{113.6363636,440},
		{127.5510204,(392*2)},
		{127.5510204,(392/2)},
		{127.5510204,(392/2)},
		{127.5510204,(392/2)},
		{127.5510204,(392/2)},
		{113.6363636,(440/2)},
		{113.6363636,(440/2)},
		{113.6363636,(440/2)},
		{113.6363636,(440/2)},
		{101.2391674,493.88},
		{113.6363636,440},
		{127.5510204,(392*2)}
	};
	
	play_music_volume(hot_cross_buns, numNotesCross, volumeRatio, tempo);
}

void play_test()
{
	int numOfNotes = 2;
	struct note test[] = {
			{440,113},
			{466,107},
		};
		play_music(test,numOfNotes);
}
int main(void)
{
	
	//Initialize LCD
    ini_lcd();
	init_speaker();

	struct note A = {440, 1};
	//Begin program
    while (1) 
    {
		//test_speaker();
		//play_note(A.freq,A.dur);
		//play_music(test,4);
		//playHotCrossBuns(2,0.5);
		play_test();
    }
}


/*
 * Project3
 *
 * Created: 5/14/2018 7:52:24 AM
 * Author : Danny and Kevin
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include <stdbool.h>

#define C4		262
#define Csh4	277
#define D4		294
#define Dsh4	311
#define E4		330
#define F4		349
#define Fsh4	370
#define G4		392
#define Gsh4	415
#define A4		440
#define Ash4	466
#define B4		494
#define C5		523
#define Csh5	554
#define D5		587
#define Dsh5	622
#define E5		659
#define F5		698
#define Fsh5	740
#define G5		784
#define Gsh5	831
#define A5		880
#define Ash5	932
#define B5		988
#define C6		1047
#define Csh6	1109
#define D6		1175
#define Dsh6	1245
#define E6		1319
#define F6		1397
#define Fsh6	1480
#define G6		1568
#define Gsh6	1661
#define A6		1760

#define SLOWEST	0.9
#define SLOW	0.7
#define NORMAL	0.5
#define FASTER	0.3
#define FASTEST	0.1

char buf[17];	// display 16 + '\0' char
char key;

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
unsigned int get_key_value()
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
	return 'Z';
}


struct note {
	int freq;	//the frequency of a note
	int dur;	//the duration of a note
};

void init_speaker()
{
	SET_BIT(DDRA,0);
	SET_BIT(PORTA,0);
}

void play_note(int freq, int dur, double speed)
{
	double period = (1.0 / freq) * 10000; // 440HZ = 2.27 ms in 1 sec
	double t = period/2;
	double k = freq * dur * speed;

	for (int i = 0; i < k; ++i)
	{
		SET_BIT(PORTA, 0);
		wait_avr(t);
		CLR_BIT(PORTA, 0);
		wait_avr(t);
	}
}

void play_music(struct note *song, int n, double speed) // n = number of note in the song array
{
	for (int i = 0; i < n;++i)
	{
		play_note(song[i].freq, song[i].dur, speed);
		wait_avr(100);
	}
}


/***************** SONG ******************/
void happyBirthday(double speed)
{
	displayWhilePlaying(speed);
	struct note song[] = {
		{ C4, 1  },
		{ C4, 1  },
		{ D4, 1  },
		{ C4, 1  },
		{ F4, 1  },
		{ E4, 1  },
		{ C4, 2  },
		{ C4, 1  },
		{ D4, 1  },
		{ C4, 1  },
		{ G4, 1  },
		{ F4, 1  },
		{ C4, 1  },
		{ C4, 1  },
		{ C5, 1  },
		{ A4, 1  },
		{ F4, 1  },
		{ E4, 1  },
		{ D4, 1  },
		{ B4, 2  },
		{ F4, 1  },
		{ G4, 1  },
		{ F4, 1  }
	};
	play_music(song, 23, speed); //has 23 notes
	SongSpeedMenu();
}

void twinkleStar(double speed)
{
	displayWhilePlaying(speed);
	struct note song[] = {
		// verse 1
		{ C4, 1  },
		{ C4, 1  },
		{ G4, 1  },
		{ G4, 1  },
		{ A4, 1  },
		{ A4, 1  },
		{ G4, 2  },
		{ F4, 1  },
		{ F4, 1  },
		{ E4, 1  },
		{ E4, 1  },
		{ D4, 1  },
		{ D4, 1  },
		{ C4, 2  },
		// verse 2
		{ G4, 1  },
		{ G4, 1  },
		{ F4, 1  },
		{ F4, 1  },
		{ E4, 1  },
		{ E4, 1  },
		{ D4, 2  },
		// verse 3
		{ G4, 1  },
		{ G4, 1  },
		{ F4, 1  },
		{ F4, 1  },
		{ E4, 1  },
		{ E4, 1  },
		{ D4, 2  },
		// verse 4
		{ C4, 1  },
		{ C4, 1  },
		{ G4, 1  },
		{ G4, 1  },
		{ A4, 1  },
		{ A4, 1  },
		{ G4, 2  },
		{ F4, 1  },
		{ F4, 1  },
		{ E4, 1  },
		{ E4, 1  },
		{ D4, 1  },
		{ D4, 1  },
		{ C4, 3  }
	};
	play_music(song, 42, speed); //has 42 notes
	SongSpeedMenu();
}
/*****************************************/

/*****************DISPLAY ****************/
void displayWhilePlaying(double speed)
{
	char buf2[17];
	clr_lcd();

	if (speed == SLOWEST)
	{
		sprintf(buf2, "%s",  "Speed 1: ");
		pos_lcd(0, 0);
		puts_lcd2(buf2);
		sprintf(buf2, "%s",  "Slowest");
		pos_lcd(1, 0);
		puts_lcd2(buf2);
	}
	else if (speed == SLOW)
	{
		sprintf(buf2, "%s",  "Speed 2: ");
		pos_lcd(0, 0);
		puts_lcd2(buf2);
		sprintf(buf2, "%s",  "Slower");
		pos_lcd(1, 0);
		puts_lcd2(buf2);
	}
	else if (speed == NORMAL)
	{
		sprintf(buf2, "%s",  "Speed 3: ");
		pos_lcd(0, 0);
		puts_lcd2(buf2);
		sprintf(buf2, "%s",  "Normal");
		pos_lcd(1, 0);
		puts_lcd2(buf2);
	}
	else if (speed == FASTER)
	{
		sprintf(buf2, "%s",  "Speed 4: ");
		pos_lcd(0, 0);
		puts_lcd2(buf2);
		sprintf(buf2, "%s",  "Faster");
		pos_lcd(1, 0);
		puts_lcd2(buf2);
	}
	else if (speed == FASTEST)
	{
		sprintf(buf2, "%s",  "Speed 5: ");
		pos_lcd(0, 0);
		puts_lcd2(buf2);
		sprintf(buf2, "%s",  "Fastest");
		pos_lcd(1, 0);
		puts_lcd2(buf2);
	}
}

void SongSpeedMenu()
{
	clr_lcd();
	sprintf(buf, "%s",  "Speed? Normal<3>"); 
	pos_lcd(0, 0);
	puts_lcd2(buf);
	//sprintf(buf, "%s",  "SW 1 2 N3 4 5 FT");
	sprintf(buf, "%s",  " S1 S2 N3 F4 F5 ");
	pos_lcd(1, 0);
	puts_lcd2(buf);

}

void mainMenu()
{
	clr_lcd();
	sprintf(buf, "%s",  "A: Happy B-Day");
	pos_lcd(0, 0);
	puts_lcd2(buf);
	sprintf(buf, "%s",  "B: Twinkle Star");
	pos_lcd(1, 0);
	puts_lcd2(buf);
}
/*****************************************/


int main(void)
{
	ini_lcd();
	ini_avr();
	init_speaker();

	mainMenu();

	bool flagA = false;
	bool flagB = false;

    while (1) 
    {
		wait_avr(50);
		
		key = get_key_value();
		while( key != 'Z' && (!flagA || !flagB ))
		{
			if (key == 'A') // happy bday
			{
				flagA = true;
				SongSpeedMenu();		
				while (flagA)
				{
					if (key == 'D')
						flagA = false;
					else
					{
						key = get_key_value();
						if (key == '1')
							happyBirthday(SLOWEST);
						else if (key == '2')
							happyBirthday(SLOW);
						else if (key == '3')
							happyBirthday(NORMAL);
						else if (key == '4')
							happyBirthday(FASTER);
						else if (key == '5')
							happyBirthday(FASTEST);
						wait_avr(50);
					}
				}
			}
			else if (key == 'B') // twinkle star
			{
				flagB = true;
				SongSpeedMenu();
				while (flagB)
				{
					if (key == 'D')
						flagB = false;
					else
					{
						key = get_key_value();
						if (key == '1')
							twinkleStar(SLOWEST);
						else if (key == '2')
							twinkleStar(SLOW);
						else if (key == '3')
							twinkleStar(NORMAL);
						else if (key == '4')
							twinkleStar(FASTER);
						else if (key == '5')
							twinkleStar(FASTEST);
						wait_avr(50);
					}
				}
			}
		}
	}
}
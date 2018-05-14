/*
 * Project3Temp.c
 *
 * Created: 5/14/2018 7:52:24 AM
 * Author : Danny and Kevin
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"

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

struct note {
	int freq;	//the frequency of a note
	int dur;	//the duration of a note
};
void init_speaker()
{
	SET_BIT(DDRA,0);
	SET_BIT(PORTA,0);
}

void play_note(int freq, int dur)
{
	double period = (1.0 / freq) * 10000; // 440HZ = 2.27 ms in 1 sec
	double t = period/2;
	double k = freq * dur * 0.5; //<-- vari for speed

	for (int i = 0; i < k; ++i)
	{
		SET_BIT(PORTA, 0);
		wait_avr(t);
		CLR_BIT(PORTA, 0);
		wait_avr(t);
	}
}

void play_music(struct note *song, int n) // n = number of note in the song array
{
	for (int i = 0; i < n;++i)
	{
		play_note(song[i].freq,song[i].dur);
		wait_avr(100);
	}
}
int main(void)
{
	init_speaker();

	struct note song[] = {
		{ C4, 1     },
		{  C4, 1    },
		{   D4, 1   },
		{  C4, 1    },
		{  F4, 1    },
		{   E4, 1   },
		{ C4, 2     },
		{ C4, 1     },
		{   D4, 1   },
		{ C4, 1     },
		{ G4, 1     },
		{ F4, 1     },
		{ C4, 1     },
		{ C4, 1     },
		{ C5, 1     },
		{ A4, 1     },
		{ F4, 1     },
		{ E4, 1     },
		{ D4, 1     },
		{ B4, 2     },
		{ F4, 1     },
		{ G4, 1     },
		{ F4, 1     }
	};


	play_music(song, 23);


		//C, D, E, F, G, A, B    
		//play_note(C4, 1);
	//wait_avr(10000);
		//play_note(C4, 1);
		//play_note(D4, 1);
		//play_note(E4, 1);
		//play_note(F4, 1);
		//play_note(G4, 1);
		//play_note(A4, 1);
		//play_note(B4, 1);

    while (1) 
    {
		//play_note(440, 113.63);
		//play_note(C4, 1);
		//wait_avr(500);
		//play_note(C4, 1);
		//wait_avr(500);
		//play_note(D4, 1);
		//wait_avr(500);
		//play_note(C4, 1);
		//wait_avr(500);
		//play_note(F4, 1);
		//wait_avr(500);
		//play_note(E4, 1);
		//wait_avr(500);


		//113.6363636,440




    }
}


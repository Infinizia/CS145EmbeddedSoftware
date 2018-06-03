/*
 * Project5
 *
 * Created: 5/14/2018 7:52:24 AM
 * Author : Danny and Kevin
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include <stdbool.h>
#include "music.h"
#include "keypad.h"

char buf[17];	// display 16 + '\0' char
static int num = 0;

/*****************DISPLAY ****************/
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
int piano()
{
	int key = get_key_value();
	if (key == '1') // CDEFGABC
	{
		play_note(C4, 1);
		test_key(1);
	}
	if (key == '2')
	{
		play_note(D4, 1);
		test_key(2);
	}
	if (key == '3')
	{
		play_note(E4, 1);
		test_key(3);
	}
	if (key == '4')
	{
		play_note(F4, 1);
		test_key(4);
	}
	if (key == '5')
	{
		play_note(G4, 1);
		test_key(5);
	}
	if (key == '6')
	{
		play_note(A4, 1);
		test_key(6);
	}
	if (key == '7')
	{
		play_note(B4, 1);
		test_key(7);
	}
	if (key == '8')
	{
		play_note(C5, 1);
		test_key(8);
	}
	return key;
}
void test_key(int key)
{
	char buf2[17];
	sprintf(buf2, "%i",  key);
	pos_lcd(1, 0);
	puts_lcd2(buf2);
	wait_avr2(50);
	//clr_lcd();
}
bool compare_game_key(char gameSong[], int size)
{
	wait_avr2(10);
	int key = piano();
	if (num < size)
	{	
		//int key = piano();
		if( key == gameSong[num])
		{
			num++;
			SET_BIT(PORTA,2);
				sprintf(buf, "CORRECT!");
				pos_lcd(1, 0);
				puts_lcd2(buf);
			wait_avr2(50);
			clr_lcd();

		}
		else if (key != 'Z')
		{
			SET_BIT(PORTA,1);
			wait_avr2(50);
		}

		CLR_BIT(PORTA,1);
		CLR_BIT(PORTA,2);

		sprintf(buf, "Press: %c", gameSong[num]);
		pos_lcd(0, 0);
		puts_lcd2(buf);
		
	}
	if (num == size)
		return true;
		

	return false;
	
}

int main(void)
{
	ini_lcd();
	init_speaker();

	SET_BIT(DDRA,1); // RED
	SET_BIT(DDRA,2); // GREEN
	//CLR_BIT(PORTA,1);				
	//SET_BIT(PORTA,1);				
	//CLR_BIT(PORTA,2);			
	//SET_BIT(PORTA,2);			

	//happyBirthday(NORMAL);

	char testSong[5] = {

		'1', '2', '1', '4', '3'
	};

	char gameSongHappyBDay[23] = {

	'1', '2', '1', '4', '3', '1', '1', 

	'2', '1', '5', '4', '1', '1', '8',

	'6', '4', '3', '2', '7', '4', '5', '4'
	};

	int index = 0;
	bool isDone = false;

	while (1)
	{
		isDone = compare_game_key(testSong, 5);
		if (isDone)
		{	
			clr_lcd();
			sprintf(buf, "Done");
			pos_lcd(0, 0);
			puts_lcd2(buf);
		}
	}

}
/*
 * Project5
 *
 * Created: 6/6/2018 7:52:24 AM
 * Author : Danny and Kevin
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include <stdbool.h>
#include "music.h"
#include "keypad.h"
#include "game.h"
#include <stdio.h>

char key;
char buf[17];	// display 16 + '\0' char
int num = 0;

// A New Song To Record
char recording[50]; // Char Array
struct note aNewSong[50]; // Struct Array
int sizeOfSong = 0; // Num of note in song

void convert_charArray_to_struct(char* recording, int size)
{
	int note;
	for (int i = 0; i < size; i++)
	{
		if (recording[i] == '1')
			note = C4;
		else if (recording[i] == '2')
			note = D4;
		else if (recording[i] == '3')
			note = E4;
		else if (recording[i] == '4')
			note = F4;
		else if (recording[i] == '5')
			note = G4;
		else if (recording[i] == '6')
			note = A4;
		else if (recording[i] == '7')
			note = B4;
		else if (recording[i] == '8')
			note = C5;

		// NOW ADD TO STRUCT ARRAY
		aNewSong[i].freq = note;
		aNewSong[i].dur = 1; //just single speed for each note
	}
}

void instant_playback_visual_note(char* recording, int size) //MUST use BOTH charArray AND struct
{
	clr_lcd();
	for (int i=0; i < size; i++)
	{
		int number = i+1;
		sprintf(buf, "Your note# %i", number);
		pos_lcd(0, 0);
		puts_lcd2(buf);

		test_key(recording[i]); // use charArray to display note
		play_note2(aNewSong[i].freq, 1, FASTER); // use struct to play note
	}
}

/*****************DISPLAY ****************/
void mainMenu()
{
	clr_lcd();
	sprintf(buf, "%s",  "A:Song1 C:Record");
	pos_lcd(0, 0);
	puts_lcd2(buf);
	sprintf(buf, "%s",  "B:Song2 D:RePlay");
	pos_lcd(1, 0);
	puts_lcd2(buf);
}
void junkie()
{
	sprintf(buf, "DDDD");
	pos_lcd(0, 0);
	puts_lcd2(buf);
}
/****************************************/


int main(void)
{
	ini_lcd();
	init_speaker();
	SET_BIT(DDRA,1); // RED LED
	SET_BIT(DDRA,2); // GREEN LED

	// ********* GAME SONGS CHAR ARRAY ***********************
	char testSong[3] = {
		'1', '2', '5'
	};
	char testSong2[5] = {
		'4', '3', '5', '6' ,'7'
	};
	char gameSongHappyBDay[25] = {
		'1', '1', '2', '1', '4', '3', '1', '1',
		'2', '1', '5', '4', '1', '1', '8',
		'6', '4', '3', '2', '7', '7', '6', '4', '5', '4'
	};
	char gameSongTwinkle[42] = {
		'1', '1', '5', '5', '6', '6', '5', '4', '4', '3', '3', '2', '2', '1',
		'5', '5', '4', '4', '3', '3', '2',
		'5', '5', '4', '4', '3', '3', '2',
		'1', '1', '5', '5', '6', '6', '5', '4', '4', '3', '3', '2', '2', '1'
	};
	char gameSongTwinkleShort[14] = {
		'1', '1', '5', '5', '6', '6', '5', '4', '4', '3', '3', '2', '2', '1'
	};
	//**********************************************************

	
	
	mainMenu();
	while(1)
	{	
		key = get_key_value();
		bool isDone = false;
		bool offMainMenu = false;

		while( key != 'Z' && !offMainMenu)
		{		
			if (key == 'A')
			{
				offMainMenu = true;
				while (offMainMenu)
				{
					while (!isDone)
					{
						isDone = compare_game_key(gameSongHappyBDay, 25, 1); // SONG ONE
					}
					if (isDone)
					{
						offMainMenu = false;
						mainMenu();
					}
				}
			}
			else if (key == 'B')
			{
				offMainMenu = true;
				while (offMainMenu)
				{
					while (!isDone)
					{
						isDone = compare_game_key(gameSongTwinkleShort, 14, 2); // SONG TWO
					}
					if (isDone)
					{
						offMainMenu = false;
						mainMenu();
					}
				}
			}
			else if (key == 'C') // RECORD A NEW SONG
			{
				offMainMenu = true;
				while (offMainMenu)
				{
					while (!isDone)
					{
						SET_BIT(PORTA, 1); //RED for recording
						isDone = recordSong(recording, 50); //50 note song
						CLR_BIT(PORTA, 1);
					}
					if (isDone)
					{
						convert_charArray_to_struct(recording, sizeOfSong); // convert to struct to play later

						SET_BIT(PORTA, 2); //GREEN for playback
						instant_playback_visual_note(recording, sizeOfSong); // display note playing
						CLR_BIT(PORTA, 2);
						offMainMenu = false;
						mainMenu();
					}
				}
			}
			else if (key == 'D') // PLAY
			{
				clr_lcd();

				offMainMenu = true;
				while (offMainMenu)
				{
					while (!isDone)
					{
						key = get_key_value();
						if (sizeOfSong == 0) // if no song was recorded
						{
							sprintf(buf, "No song to play");
							pos_lcd(0, 0);
							puts_lcd2(buf);
							sprintf(buf, "press * to exit");
							pos_lcd(1, 0);
							puts_lcd2(buf);
						}
						else if (sizeOfSong > 0)
						{
							sprintf(buf, "Playing");
							pos_lcd(0, 0);
							puts_lcd2(buf);
							sprintf(buf, "your song...");
							pos_lcd(1, 0);
							puts_lcd2(buf);
							SET_BIT(PORTA, 2); //GREEN for playback
							play_music2(aNewSong, sizeOfSong, FASTER);
							CLR_BIT(PORTA, 2);
							isDone = true;
						}
						if (key == '*') //back to menu
						{
							isDone = true;
						}
					}
					if (isDone)
					{
						offMainMenu = false;
						mainMenu();
						key = get_key_value();
					}
				}
			}
			else // on main menu, when press any other button, it should stay on main menu
			{
				key = get_key_value();
			}

			if (!isDone) // this is for when we use '*' to return to main menu
			{
				key = get_key_value();
			}



		}
	}
}
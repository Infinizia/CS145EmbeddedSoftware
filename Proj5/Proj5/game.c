/*
 * game.c
 *
 * Created: 6/6/2018 8:17:55 PM
 *  Author: Danny
 */
 #include "avr.h"
 #include "lcd.h"
 #include "music.h"
 #include "keypad.h"
 #include <stdbool.h>
 #include <stdio.h>

 extern char key;
 extern char buf[17];
 extern int num;
 extern int sizeOfSong;

 void test_key(char key)
 {
	 char buf2[17];
	 sprintf(buf2, "%c",  key);
	 pos_lcd(1, 0);
	 puts_lcd2(buf2);
	 wait_avr2(50);
 }
 int piano()
 {
	 key = get_key_value();
	 if (key == '1') // CDEFGABC
	 {
		 play_note2(C4, 1, FASTER);
	 }
	 if (key == '2')
	 {
		 play_note2(D4, 1, FASTER);
	 }
	 if (key == '3')
	 {
		 play_note2(E4, 1, FASTER);
	 }
	 if (key == '4')
	 {
		 play_note2(F4, 1, FASTER);
	 }
	 if (key == '5')
	 {
		 play_note2(G4, 1, FASTER);
	 }
	 if (key == '6')
	 {
		 play_note2(A4, 1, FASTER);
	 }
	 if (key == '7')
	 {
		 play_note2(B4, 1, FASTER);
	 }
	 if (key == '8')
	 {
		 play_note2(C5, 1, FASTER);
	 }

	 if (key != 'Z')
		test_key(key);

	 return key;
 }
 bool recordSong(char* recording, int size)
 {
	 wait_avr2(5);
	 char key = piano();

	 clr_lcd();
	 sprintf(buf, "Rec. NoteLeft:%i", size-num);
	 pos_lcd(0, 0);
	 puts_lcd2(buf);

	if (key != 'Z')
	{
		if (key == '1' || key == '2'|| key == '3'|| key == '4'|| 
		key == '5'|| key == '6'|| key == '7'|| key == '8')
		{
			recording[num] = key;
			num++;
		}
		if (key == '*') // exit before size done, must save the current size
		{
			sizeOfSong = num;
			num = 0;
			return true;
		}
	}

	if (num == size) // the size is done
	{
		sizeOfSong = num;
		num = 0;
		return true;
	}

	return false;
 }
 bool compare_game_key(char* gameSong, int size, int songNum)
 {
	 wait_avr2(5);
	 char key = piano();
	 if (num < size)
	 {		 
		clr_lcd();
		sprintf(buf, "Press: %c", gameSong[num]);
		pos_lcd(0, 0);
		puts_lcd2(buf);
		sprintf(buf, "%02i/%02i", size-num, size);
		pos_lcd(1, 11);
		puts_lcd2(buf);

		 if( key == gameSong[num])
		 {
			 SET_BIT(PORTA,2); //Green for correct
			 sprintf(buf, "CORRECT!");
			 pos_lcd(1, 0);
			 puts_lcd2(buf);
			 wait_avr2(50);
			 num++;
		 }
		 else if (key != 'Z')
		 {
			SET_BIT(PORTA,1); //Red for wrong
			wait_avr2(50);
		 }

		// turn led off
		CLR_BIT(PORTA,1);
		CLR_BIT(PORTA,2);

		if (key == '*') // EXIT
		{
			num = 0;
			return true;
		}

	 }
	 else if (num == size) // Completed The Song
	 {
		SET_BIT(PORTA,2); // green led on
		clr_lcd();
		sprintf(buf, "Completed Song %i", songNum);
		pos_lcd(0, 0);
		puts_lcd2(buf);
		wait_avr2(50);
		
		 num = 0;

		 if (songNum == 1) //<===================SONG ONE
		 {
			happyBirthday(FASTEST);
		 }
		 else if (songNum == 2)//<===============SONG TWO
		 {
			twinkleStarShort(FASTEST);
		 }

		 CLR_BIT(PORTA,2); //led off
		 return true;
	 }
	 
	 return false;
 }
/*
 * game.h
 *
 * Created: 6/6/2018 8:18:06 PM
 *  Author: Danny
 */ 
 #ifndef GAME_H_
 #define GAME_H_
 #include "avr.h"
 #include "lcd.h"
 #include "music.h"
 #include "keypad.h"
 #include <stdbool.h>
 #include <stdio.h>

 void test_key(char key);
 int piano();
 bool recordSong(char recording[], int size);
 bool compare_game_key(char* gameSong, int size, int songNum);


 #endif
/*
 * music.h
 *
 * Created: 6/2/2018 1:59:42 PM
 *  Author: Danny
 */
 
 #ifndef __music__
 #define __music__
 #include "avr.h"

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


 struct note {
	 int freq;	//the frequency of a note
	 int dur;	//the duration of a note
 };
void init_speaker();
void play_note(int freq, int dur);
void play_note2(int freq, int dur, double speed);
void play_music(struct note *song, int n);
void play_music2(struct note *song, int n, double speed);
void happyBirthday(double speed);
void twinkleStar(double speed);
void displayWhilePlaying(double speed);
 #endif
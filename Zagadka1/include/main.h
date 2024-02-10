#ifndef _MAIN_H_
#define _MAIN_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

#ifdef __SERVO
	#include <Servo.h>
#endif

//========== DEFINES ===========================================================
#ifdef __VEMOS
	#define PIN_LAMP1										D1
	#define PIN_LAMP2										D3
	#define PIN_LAMP3										D4
	#define PIN_LAMP4										D5

	#define PIN_BUTTON1										D6
	#define PIN_BUTTON2										D7
	#define PIN_BUTTON3										D8
	#define PIN_BUTTON4										D9
	#define PIN_BUTTON_END									D10
	#define PIN_BUTTON_START								D10

	#define PIN_SERVO										D11

	#define PIN_LEDS										D2
#else
	#define PIN_LAMP1										A0
	#define PIN_LAMP2										A3
	#define PIN_LAMP3										A4
	#define PIN_LAMP4										A5

	#define PIN_BUTTON1										2
	#define PIN_BUTTON2										3
	#define PIN_BUTTON3										4
	#define PIN_BUTTON4										5
	#define PIN_BUTTON_END									6
	#define PIN_BUTTON_START								7

	#define PIN_SERVO										9

	#define PIN_LEDS										8
#endif

#define PIN_RANDOM											A6
#define PIN_BEEPER											13

#define SECS_BEFORE_RESET									60

#define LEDS_COUNT											6
#define LAMPS_COUNT											4

/// MP3 Player
#define PLAYER_TX											A1
#define PLAYER_RX											A2
#define MELODY_INIT											0
#define MELODY_START										1
#define MELODY_BEEP											2
#define MELODY_FALSE										3
#define MELODY_TRUE											4
#define MELODY_SUCCESS										5
#define MELODY_END											6

//========== STRUCTURES ========================================================
struct Stage
{
	enum{
		init,
		start,
		game,
		game_end,
		wait_to_reset,
	};
};

//========== VARIABLES =========================================================
extern uint8_t reset_counter;
extern uint8_t stage;
extern uint8_t subStage;
extern uint8_t keyNum;
extern uint8_t keys[][ LEDS_COUNT ];
extern Adafruit_NeoPixel pixels;
extern long time;
extern SoftwareSerial softSerial;
extern DFRobotDFPlayerMini myDFPlayer;

#ifdef __SERVO
	extern Servo servo;
#endif

//========== FUNCTIONS =========================================================






#endif // _MAIN_H_
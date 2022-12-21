#ifndef _MAIN_H_
#define _MAIN_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

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

#define PIN_RANDOM											A1
#define PIN_BEEPER											13

#define LEDS_COUNT											6
#define LAMPS_COUNT											4

//========== STRUCTURES ========================================================
//========== VARIABLES =========================================================
extern uint8_t stage;
extern uint8_t subStage;
extern uint8_t keyNum;
extern uint8_t keys[][ LEDS_COUNT ];
extern Adafruit_NeoPixel pixels;
extern long time;

#ifdef __SERVO
	extern Servo servo;
#endif

//========== FUNCTIONS =========================================================






#endif // _MAIN_H_
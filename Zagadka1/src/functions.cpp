#include "functions.h"
#include "main.h"
#include "pitches.h"

//========== DEFINES ===========================================================
//========== STRUCTURES ========================================================
//========== VARIABLES =========================================================
uint8_t showLeds[ LEDS_COUNT ];

//========== FUNCTIONS =========================================================
uint8_t isPressButton(const uint8_t pin)
{
	uint8_t res = 0;
	if( !digitalRead( pin ) ){
		uint8_t i = 0;
		for( i = 0; i < 100; i++ ){
			if( digitalRead( pin ) ) break;
		}
		if( i >= 100 && !digitalRead( pin ) ) res = 1;
	}
	return res;
}

//==============================================================================
void onLamp(const uint8_t lampNum)
{
	switch( lampNum ){
		case 1:	digitalWrite( PIN_LAMP1, HIGH );	break;
		case 2:	digitalWrite( PIN_LAMP2, HIGH );	break;
		case 3:	digitalWrite( PIN_LAMP3, HIGH );	break;
		case 4:	digitalWrite( PIN_LAMP4, HIGH );	break;
		default:
			digitalWrite( PIN_LAMP1, LOW );
			digitalWrite( PIN_LAMP2, LOW );
			digitalWrite( PIN_LAMP3, LOW );
			digitalWrite( PIN_LAMP4, LOW );
		break;
	}
}

//==============================================================================
void offLamp(const uint8_t lampNum)
{
	switch( lampNum ){
		case 1:	digitalWrite( PIN_LAMP1, LOW );	break;
		case 2:	digitalWrite( PIN_LAMP2, LOW );	break;
		case 3:	digitalWrite( PIN_LAMP3, LOW );	break;
		case 4:	digitalWrite( PIN_LAMP4, LOW );	break;
	}
}

//==============================================================================
void setLed(const uint8_t ledNum, uint8_t r, uint8_t g, uint8_t b)
{
	if( ledNum >= LEDS_COUNT ) return;
	pixels.setPixelColor( ledNum, pixels.Color( r, g, b ) );
}

//==============================================================================
void setStage1(void)
{
	stage = Stage::start;

#ifdef __DEV
	Serial.println( "Stage1" );
#endif
	
	// beep( 100, 550 );
	myDFPlayer.playMp3Folder( MELODY_START );
	delay( 2000 );

	for( uint8_t i = 0; i < LEDS_COUNT; i++ ){
		myDFPlayer.playMp3Folder( MELODY_BEEP );
		onLamp( keys[ keyNum ][ i ] );
		setLed( i, 0, 0, 255 ); pixels.show();
		delay( 1000 );
		offLamp( keys[ keyNum ][ i ] );
		setLed( i, 0, 0, 0 ); pixels.show();
		delay( 1000 );
	}

	delay( 1000 );
	pixels.clear(); pixels.show();
	setStage2();
}

//==============================================================================
void setStage2(void)
{
	subStage = 0;
	uint8_t j;

#ifdef __DEV
	Serial.println( "Stage2" );
#endif

	//clear array
	for( j = 0; j < LEDS_COUNT; j++ ) showLeds[ j ] = 0xFF;

#ifdef __DEV
	Serial.print( "LED`S: [ " );
#endif

	for( uint8_t i = 0; i < LEDS_COUNT; i++ ){
		uint8_t num = random( 0, LEDS_COUNT );
		uint8_t find = 1;
		while( find ){
			find = 0;
			for( j = 0; j < LEDS_COUNT; j++ ){
				if( showLeds[ j ] == num ){
					find = 1;
					num = random( 0, LEDS_COUNT );
					break;
				}
			}
		}
		showLeds[ i ] = num;
#ifdef __DEV
		// Serial.print( i );
		// Serial.print( ": " );
		Serial.print( num );
		Serial.print( " " );
#endif
	}

#ifdef __DEV
	Serial.println( "]" );
#endif

	stage = Stage::game;

	setLed( showLeds[ subStage ], 0, 0, 0xFF ); pixels.show(); //beep( 700, 550 );
	myDFPlayer.playMp3Folder( MELODY_BEEP );
}

//==============================================================================
void processStage2(const uint8_t button)
{
	// beep( 700, 550 );

	uint8_t ledNum = showLeds[ subStage ];
	uint8_t lampNum = keys[ keyNum ][ ledNum ];

#ifdef __DEV
	Serial.print( "B [" );
	Serial.print( button );
	Serial.print( "] " );
	Serial.print( "[" );
	Serial.print( keyNum );
	Serial.print( "] LED: [" );
	Serial.print( ledNum );
	Serial.print( "] STAGE: [" );
	Serial.print( subStage );
	Serial.print( "] LAMP: [" );
	Serial.print( lampNum );
	Serial.print( "]" );
	Serial.println( "" );
#endif

	if( button == lampNum ){
		setLed( ledNum, 0, 0xFF, 0 ); pixels.show(); delay( 500 );
		// setLed( ledNum, 0, 0, 0 ); pixels.show(); delay( 500 );
		myDFPlayer.playMp3Folder( MELODY_TRUE );
		subStage++;
		if( subStage >= LEDS_COUNT ){
			setStage3();
		}else{
			setLed( showLeds[ subStage ], 0, 0, 0xFF ); pixels.show();
		}
	}else{
		setLed( ledNum, 0xFF, 0, 0 ); pixels.show(); delay( 500 );
		// beep( 700, 550 ); beep( 700, 550 );
		myDFPlayer.playMp3Folder( MELODY_FALSE );
		pixels.clear();
		pixels.show();
		stage = Stage::init;
	}
}

//==============================================================================
void setStage3(void)
{
	stage = Stage::game_end;

#ifdef __DEV
	Serial.println( "Stage3" );
#endif

	offLamp( 1 );
	offLamp( 2 );
	offLamp( 3 );
	offLamp( 4 );

	time = millis();

	pixels.clear(); pixels.show();
	myDFPlayer.playMp3Folder( MELODY_SUCCESS );

	// beep( 400, 250 );
	for( uint8_t i = 0; i < LEDS_COUNT; i++ ) setLed( i, 0, 0xFF, 0 );
	pixels.show();

	delay( 500 ); pixels.clear(); pixels.show(); delay( 500 );

	// beep( 400, 250 );
	for( uint8_t i = 0; i < LEDS_COUNT; i++ ) setLed( i, 0, 0xFF, 0 );
	pixels.show();

	delay( 500 ); pixels.clear(); pixels.show(); delay( 500 );

	// beep( 400, 250 );
	for( uint8_t i = 0; i < LEDS_COUNT; i++ ) setLed( i, 0, 0xFF, 0 );
	pixels.show();

	delay( 500 ); pixels.clear(); pixels.show(); delay( 500 );

	// beep( 400, 250 );
	for( uint8_t i = 0; i < LEDS_COUNT; i++ ) setLed( i, 0, 0xFF, 0 );
	pixels.show();

	delay( 500 ); pixels.clear(); pixels.show(); delay( 500 );

	// beep( 400, 250 );
	for( uint8_t i = 0; i < LEDS_COUNT; i++ ) setLed( i, 0, 0xFF, 0 );
	pixels.show();

	delay( 500 ); pixels.clear(); pixels.show();

	myDFPlayer.playMp3Folder( MELODY_END );

	unlock();

	//Задержка в 10 сек.
	// delay( 10000 );

	stage = Stage::wait_to_reset;
	reset_counter = SECS_BEFORE_RESET;
	time = millis();
}

//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
void setStageError(void)
{
	pixels.clear();
	stage = Stage::init;
}

//==============================================================================
void beep(const uint16_t on, const uint16_t off)
{
	// tone( PIN_BEEPER, on, off );
	// digitalWrite( PIN_BEEPER, HIGH ); delay( on );
	// digitalWrite( PIN_BEEPER, LOW ); delay( off );
	// tone( PIN_BEEPER, on, off );
	// tone( PIN_BEEPER, 2000 ); // Запустили звучание
	// delay( 500 );
	// noTone(); // Остановили звучание
}

//==============================================================================
void startMelody(void)
{
	uint16_t melody[] = {
		NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
	};

	// note durations: 4 = quarter note, 8 = eighth note, etc.:
	uint8_t noteDurations[] = {
		4, 8, 8, 4, 4, 4, 4, 4
	};

	for( uint8_t thisNote = 0; thisNote < 8; thisNote++ ){
		// to calculate the note duration, take one second divided by the note type.
		//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
		int noteDuration = 1000 / noteDurations[thisNote];
		tone( 8, melody[thisNote], noteDuration );
		// to distinguish the notes, set a minimum time between them.
		// the note's duration + 30% seems to work well:
		int pauseBetweenNotes = noteDuration * 1.30;
		delay( pauseBetweenNotes );
		// stop the tone playing:
		noTone( 8 );
	}
}

//==============================================================================
void lock(void)
{
#ifdef __DEV
	Serial.println( "lock" );
#endif
#ifdef __SERVO
	servo.write( 0 );
#else
	digitalWrite( PIN_SERVO, LOW );
#endif
}

//==============================================================================
void unlock(void)
{
#ifdef __DEV
	Serial.println( "unlock" );
#endif
#ifdef __SERVO
	servo.write( 180 );
#else
	digitalWrite( PIN_SERVO, HIGH );
#endif
}

//==============================================================================

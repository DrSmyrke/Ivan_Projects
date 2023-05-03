#include "main.h"
#include "functions.h"

//========== DEFINES ===========================================================
//========== STRUCTURES ========================================================
//========== VARIABLES =========================================================
uint8_t stage;
uint8_t subStage;
uint8_t keyNum;
long time;

// extern "C" {
	uint8_t keys[][ LEDS_COUNT ] = {
		{ 1, 2, 1, 2, 3, 4 },
		{ 1, 2, 1, 2, 4, 3 },
		{ 1, 2, 3, 1, 2, 4 },
		{ 1, 2, 3, 1, 3, 4 },
		{ 1, 2, 3, 1, 4, 2 },
		{ 1, 2, 3, 1, 4, 3 },
		{ 1, 2, 3, 2, 1, 4 },
		{ 1, 2, 3, 2, 3, 4 },
		{ 1, 2, 3, 2, 4, 1 },
		{ 1, 2, 3, 4, 3, 1 },
		{ 1, 2, 4, 1, 2, 3 },
		{ 1, 2, 4, 1, 3, 2 },
		{ 1, 2, 4, 2, 1, 3 },
		{ 1, 2, 4, 2, 3, 1 },
		{ 1, 2, 4, 3, 1, 2 },
		{ 1, 2, 4, 3, 1, 3 },
		{ 1, 2, 4, 3, 1, 4 },
		{ 1, 2, 4, 3, 2, 1 },
		{ 1, 2, 4, 3, 2, 3 },
		{ 1, 2, 4, 3, 2, 4 },
		{ 1, 2, 4, 3, 4, 1 },
		{ 1, 2, 4, 3, 4, 2 },
		{ 1, 2, 4, 3, 4, 3 },
		{ 1, 3, 2, 3, 2, 4 },
		{ 1, 3, 2, 3, 4, 2 },
		{ 1, 3, 2, 3, 1, 4 },
		{ 1, 3, 2, 3, 4, 1 },
		{ 1, 4, 2, 3, 4, 2 },
		{ 1, 4, 2, 3, 2, 4 },
		{ 1, 4, 2, 3, 2, 1 },
		{ 2, 1, 2, 4, 3, 1 },
		{ 2, 3, 1, 4, 2, 1 },
		{ 2, 3, 4, 1, 4, 3 },
		{ 2, 3, 4, 1, 3, 4 },
		{ 2, 4, 1, 3, 4, 1 },
		{ 2, 4, 2, 3, 1, 4 },
		{ 3, 1, 2, 3, 4, 1 },
		{ 3, 1, 2, 3, 1, 4 },
		{ 3, 1, 2, 3, 4, 2 },
		{ 3, 1, 2, 3, 2, 4 },
		{ 3, 2, 1, 3, 1, 4 },
		{ 3, 2, 1, 3, 4, 1 },
		{ 3, 2, 1, 3, 2, 4 },
		{ 3, 2, 1, 3, 4, 2 },
		{ 3, 2, 1, 4, 1, 2 },
		{ 3, 2, 1, 4, 1, 3 },
		{ 3, 2, 1, 4, 1, 4 },
		{ 3, 2, 1, 4, 2, 1 },
		{ 3, 2, 1, 4, 2, 3 },
		{ 3, 2, 1, 4, 2, 4 },
		{ 3, 2, 1, 4, 3, 1 },
		{ 3, 2, 1, 4, 3, 2 },
		{ 3, 2, 1, 4, 3, 4 },
		{ 3, 4, 3, 2, 1, 2 },
		{ 3, 4, 2, 3, 1, 2 },
		{ 4, 1, 3, 2, 1, 4 },
		{ 4, 2, 3, 2, 1, 4 },
		{ 4, 2, 1, 2, 4, 3 },
		{ 4, 1, 2, 4, 3, 2 },
		{ 4, 3, 4, 2, 3, 1 },
	};
// };

Adafruit_NeoPixel pixels( LEDS_COUNT, PIN_LEDS, NEO_GRB + NEO_KHZ800 );

#ifdef __SERVO
	Servo servo;
#endif

//========== FUNCTIONS =========================================================
void setup()
{
	stage					= 0;
	keyNum					= 0;

	pinMode( PIN_LAMP1, OUTPUT );
	pinMode( PIN_LAMP2, OUTPUT );
	pinMode( PIN_LAMP3, OUTPUT );
	pinMode( PIN_LAMP4, OUTPUT );

	pinMode( PIN_BEEPER, INPUT );

	pinMode( PIN_BUTTON1, INPUT );
	pinMode( PIN_BUTTON2, INPUT );
	pinMode( PIN_BUTTON3, INPUT );
	pinMode( PIN_BUTTON4, INPUT );
	pinMode( PIN_BUTTON_END, INPUT );
	pinMode( PIN_BUTTON_START, INPUT );
	pinMode( PIN_RANDOM, INPUT );



#ifdef __SERVO
	servo.attach( PIN_SERVO );
#else
	pinMode( PIN_SERVO, OUTPUT );
#endif
	lock();



	pixels.begin();
	pixels.clear();
	pixels.show();
	pixels.setBrightness( 150 );


	
	for( uint8_t i = 1; i <= LAMPS_COUNT; i++ ){
		if( i == 1 ){
			setLed( 0, 0xFF, 0, 0 ); pixels.show();
		}else if( i == 2 ){
			setLed( 1, 0xFF, 0xFF, 0 ); pixels.show();
		}else if( i == 3 ){
			setLed( 2, 0, 0x80, 0 );
			setLed( 3, 0, 0, 0xFF );
			pixels.show();
		}else if( i == 4 ){
			setLed( 4, 0x4B, 0, 0x82 );
			setLed( 5, 0xEE, 0x82, 0xEE );
			pixels.show();
		}
		onLamp( i ); delay( 500 );
	}



	beep( 500, 1000 );
	// startMelody();
	// beep( 250, 500 );
	// beep( 300, 100 );
	// beep( 250, 500 );
	beep( 400, 500 );
	beep( 250, 100 );
	

	uint32_t seed = 0;
	for( uint8_t i = 0; i < 0xFF; i++ ){
		seed += analogRead( PIN_RANDOM );
	}
	randomSeed( seed );

	//Заполнение данных о лпмпочках
	keyNum = random( 0, sizeof( keys ) / LEDS_COUNT );

#ifdef __DEV
	Serial.begin( 9600 );
	Serial.println( "" );

	Serial.print( "[" );
	Serial.print( seed );
	Serial.print( "] " );
	Serial.print( "[" );
	Serial.print( keyNum );
	Serial.print( "] " );
	for( uint8_t i = 0; i < LEDS_COUNT; i++ ){
		Serial.print( keys[ keyNum ][ i ] );
		Serial.print( " " );
	}
	Serial.println( "" );
#endif



	for( uint8_t i = 1; i <= LAMPS_COUNT; i++ ){
		offLamp( i ); delay( 500 );
	}

	pixels.clear();
	pixels.show();
}

//-------------------------------------------------------------------------------
void loop()
{
	if( isPressButton( PIN_BUTTON_START ) ){
		if( stage == 0 ){
			setStage1();
		}
	}

	if( isPressButton( PIN_BUTTON1 ) ){
		if( stage == 0 || stage == 2 || stage == 3 ) onLamp( 1 );
		if( stage == 2 ) processStage2( 1 );
	}else{
		if( stage == 0 || stage == 2 || stage == 3 ) offLamp( 1 );
	}

	if( isPressButton( PIN_BUTTON2 ) ){
		if( stage == 0 || stage == 2 || stage == 3 ) onLamp( 2 );
		if( stage == 2 ) processStage2( 2 );
	}else{
		if( stage == 0 || stage == 2 || stage == 3 ) offLamp( 2 );
	}

	if( isPressButton( PIN_BUTTON3 ) ){
		if( stage == 0 || stage == 2 || stage == 3 ) onLamp( 3 );
		if( stage == 2 ) processStage2( 3 );
	}else{
		if( stage == 0 || stage == 2 || stage == 3 ) offLamp( 3 );
	}
	
	if( isPressButton( PIN_BUTTON4 ) ){
		if( stage == 0 || stage == 2 || stage == 3 ) onLamp( 4 );
		if( stage == 2 ) processStage2( 4 );
	}else{
		if( stage == 0 || stage == 2 || stage == 3 ) offLamp( 4 );
	}

	if( isPressButton( PIN_BUTTON_END ) ){
		setStage3();
	}
}


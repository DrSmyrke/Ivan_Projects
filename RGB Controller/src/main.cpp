#include "main.h"

//----------- VARIABLES --------------------------------------------------------------------
AppData app;
ESP8266WebServer webServer( 80 );
DNS_Server dnsServer;
Timer timer0( 0, 1000, timer0Interrupt );
Timer timer1( 0, 25, timer1Interrupt );
// CRGB leds1[ LENTA1_COUNT ];
// CRGB leds2[ LENTA2_COUNT ];
Adafruit_NeoPixel lenta1( LENTA1_COUNT, LENTA1_PIN, NEO_GRB + NEO_KHZ800 );
Adafruit_NeoPixel lenta2( LENTA2_COUNT, LENTA2_PIN, NEO_GRB + NEO_KHZ800 );
// Adafruit_NeoPixel lenta3( LENTA3_COUNT, LENTA3_PIN, NEO_GRB + NEO_KHZ800 );
// Adafruit_NeoPixel lenta4( LENTA4_COUNT, LENTA4_PIN, NEO_GRB + NEO_KHZ800 );
// Adafruit_NeoPixel lenta5( LENTA5_COUNT, LENTA5_PIN, NEO_GRB + NEO_KHZ800 );
char pageBuff[ WEB_PAGE_BUFF_SIZE ];
Pixel rainbow[ 7 ];

//----------- FUNCTIONS--------------------------------------------------------------------
void setup()
{
	app.flags.timer0						= 0;
	app.flags.timer1						= 0;
	app.flags.use_lenta1					= 0;
	app.flags.use_lenta2					= 0;
	app.flags.use_lenta3					= 0;
	app.flags.use_lenta4					= 0;
	app.flags.use_lenta5					= 0;
	app.animationNum						= 0;
	app.animationCounter					= 0;

	ESP.wdtEnable( 10000 );

	esp::init();
	
	pinMode( LED_BUILTIN, OUTPUT );
	
#ifdef __DEV
	while( !Serial );
	Serial.begin( 115200 );
	app.flags.use_lenta1 = 1;
	app.flags.use_lenta2 = 1;
#endif
	ESP_DEBUG( "INIT...\n" );

	loadSettings();

	// FastLED.addLeds<NEOPIXEL, LENTA1_PIN>( leds1, LENTA1_COUNT );

	if( app.flags.use_lenta1 ){
		lenta1.begin();
		lenta_clear( lenta1 );
	}

	if( app.flags.use_lenta2 ){
		lenta2.begin();
		lenta_clear( lenta2 );
	}


	//Инициализация Wi-Fi
	IPAddress apIP( 10, 10, 10, 10 );
	esp::wifi_init( DEVICE_NAME, apIP, apIP, IPAddress( 255, 255, 255, 0 ) );
	if( esp::flags.ap_mode ){
		dnsServer.setErrorReplyCode( DNSReplyCode::NoError );
		dnsServer.addRecord( "*", WiFi.softAPIP() );
		dnsServer.start( DNS_PORT );
	}

	//Инициализация Web сервера
	esp::pageBuff = pageBuff;
	esp::addWebServerPages( &webServer, true, true, true );
	// webServer.on( "/storageReset", [ webServer ](void){
	// 	if( esp::checkWebAuth( &webServer, SYSTEM_LOGIN, SYSTEM_PASSWORD, ESP_AUTH_REALM, "access denied" ) ){
	// 		webServer.send ( 200, "text/html", "OK" );
	// 		homekit_storage_reset();
	// 		ESP.reset();
	// 	}
	// } );
	// webServer.on( "/", indexPageHeadler );
	// webServer.on( "/get", getPageHeadler );
	webServer.begin();




	start();
	

	ESP_DEBUG( "INIT OK\n" );
}

//-----------------------------------------------------------------------------------------
void loop()
{
	ESP.wdtFeed();

	
	//Условие срабатывания по таймеру0 (1сек.)
	if( app.flags.timer0 ){
		app.flags.timer0 = 0;

		//Меняем состояние светодиода для индикации корректности работы
		digitalWrite( LED_BUILTIN, !digitalRead( LED_BUILTIN ) );
	}

	//Условие срабатывания по таймеру1 (25мсек.)
	if( app.flags.timer1 ){
		app.flags.timer1 = 0;

		animationProcess();
	}
}

//-----------------------------------------------------------------------------------------
void timer0Interrupt(void*)
{
	app.flags.timer0 = 1;
}

//-----------------------------------------------------------------------------------------
void timer1Interrupt(void*)
{
	app.flags.timer1 = 1;
}

//-----------------------------------------------------------------------------------------
void saveSettings(void)
{
	ESP_DEBUG( "Save settings\n" );

	uint8_t data[ 5 ];
	data[ 0 ]								= 0;

	if( app.flags.use_lenta1 ) setPlus( data[ 0 ], 0 );
	if( app.flags.use_lenta2 ) setPlus( data[ 0 ], 1 );
	if( app.flags.use_lenta3 ) setPlus( data[ 0 ], 2 );
	if( app.flags.use_lenta4 ) setPlus( data[ 0 ], 3 );
	if( app.flags.use_lenta5 ) setPlus( data[ 0 ], 4 );

	esp::saveSettings( data, sizeof( data ) );
}

//-----------------------------------------------------------------------------------------
void loadSettings(void)
{
	ESP_DEBUG( "Load settings\n" );

	uint8_t data[ 5 ];
	if( esp::loadSettings( data, sizeof( data ) ) == sizeof( data ) ){
		app.flags.use_lenta1				= CheckBit( data[ 0 ], 0 );
		app.flags.use_lenta2				= CheckBit( data[ 0 ], 1 );
		app.flags.use_lenta3				= CheckBit( data[ 0 ], 2 );
		app.flags.use_lenta4				= CheckBit( data[ 0 ], 3 );
		app.flags.use_lenta5				= CheckBit( data[ 0 ], 4 );
	}

#ifdef __DEV
	if( app.flags.use_lenta1 ) ESP_DEBUG( "Lenta1 [ACTIVATED]\n" );
	if( app.flags.use_lenta2 ) ESP_DEBUG( "Lenta2 [ACTIVATED]\n" );
	if( app.flags.use_lenta3 ) ESP_DEBUG( "Lenta3 [ACTIVATED]\n" );
	if( app.flags.use_lenta4 ) ESP_DEBUG( "Lenta4 [ACTIVATED]\n" );
	if( app.flags.use_lenta5 ) ESP_DEBUG( "Lenta5 [ACTIVATED]\n" );
#endif
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

#include "functions.h"


//----------- VARIABLES --------------------------------------------------------------------

//----------- FUNCTIONS--------------------------------------------------------------------
void lenta_clear(Adafruit_NeoPixel &lenta)
{
	lenta.clear(); lenta.show();
}

//-----------------------------------------------------------------------------------------
void setLed(Adafruit_NeoPixel &lenta, const uint16_t ledNum, uint8_t r, uint8_t g, uint8_t b, const bool show)
{
	lenta.setPixelColor( ledNum, lenta.Color( r, g, b ) );
	if( show ) lenta.show();
}

//-----------------------------------------------------------------------------------------
void setLed(Adafruit_NeoPixel &lenta, const uint16_t ledNum, uint32_t pixel, const bool show)
{
	lenta.setPixelColor( ledNum, pixel );
	if( show ) lenta.show();
}

//-----------------------------------------------------------------------------------------
void setBrightnessPrz(Adafruit_NeoPixel &lenta, const uint8_t percent)
{
	setBrightness( lenta, map( percent, 0, 100, 0, 255 ) );
}

//-----------------------------------------------------------------------------------------
void setBrightness(Adafruit_NeoPixel &lenta, const uint8_t value)
{
	lenta.setBrightness( value );
	lenta.show();
}

//-----------------------------------------------------------------------------------------
void start(void)
{
	rainbow[ 0 ]					= { 0xFF, 0, 0 };
	rainbow[ 1 ]					= { 0xFF, 0x35, 0 };
	rainbow[ 2 ]					= { 0xFF, 0xFF, 0 };
	rainbow[ 3 ]					= { 0, 0x80, 0 };
	rainbow[ 4 ]					= { 0, 0, 0xFF };
	rainbow[ 5 ]					= { 0x4B, 0, 0x82 };
	rainbow[ 6 ]					= { 0xEE, 0x82, 0xEE };

	if( app.flags.use_lenta1 ){
		setBrightnessPrz( lenta1, 45 );
		uint8_t ri = 0;
		for( uint16_t i = 0; i <= lenta1.numPixels(); i++ ){
			if( ri >= 6 ) ri = 0;
			setLed( lenta1, i, rainbow[ ri ].r, rainbow[ ri ].g, rainbow[ ri ].b, true ); delay( 100 );
			ri++;
		}
		delay( 250 );
	}
	if( app.flags.use_lenta2 ){
		setBrightnessPrz( lenta2, 45 );
		uint8_t ri = 0;
		for( uint16_t i = 0; i <= lenta2.numPixels(); i++ ){
			if( ri >= 6 ) ri = 0;
			setLed( lenta2, i, rainbow[ ri ].r, rainbow[ ri ].g, rainbow[ ri ].b, true ); delay( 100 );
			ri++;
		}
		delay( 250 );
	}
}

//-----------------------------------------------------------------------------------------
void animationProcess(void)
{
	// return;
	// switch( app.animationNum ){
	// 	case 1:
	// 		if( app.animationCounter ){

	// 			app.animationCounter--;
	// 		}else{
	// 			app.animationNum = 0;
	// 			clearAll();
	// 		}
	// 	break;
	// }
}

//-----------------------------------------------------------------------------------------
void clearAll(void)
{
	if( app.flags.use_lenta1 ) lenta_clear( lenta1 );
	if( app.flags.use_lenta2 ) lenta_clear( lenta2 );
	if( app.flags.use_lenta3 ) lenta_clear( lenta3 );
	if( app.flags.use_lenta4 ) lenta_clear( lenta4 );
	if( app.flags.use_lenta5 ) lenta_clear( lenta5 );
}

//-----------------------------------------------------------------------------------------
void getPageHeadler(void)
{
	strcpy( pageBuff, "{\"mode\": " );
	strcat( pageBuff, utoa( app.mode, esp::tmpVal, 10 ) );

	// strcat( pageBuff, ",\"status1\":" ); strcat( pageBuff, utoa( app.status_1, esp::tmpVal, 10 ) );
	// strcat( pageBuff, ",\"status2\":" ); strcat( pageBuff, utoa( app.status_2, esp::tmpVal, 10 ) );
	// strcat( pageBuff, ",\"status3\":" ); strcat( pageBuff, utoa( app.status_3, esp::tmpVal, 10 ) );

	strcat( pageBuff, ",\"lents\": {" );
		strcat( pageBuff, "\"1\": {\"use\":" ); strcat( pageBuff, utoa( app.flags.use_lenta1, esp::tmpVal, 10 ) );
		strcat( pageBuff, ",\"leds\":" ); strcat( pageBuff, utoa( app.lenta1_leds, esp::tmpVal, 10 ) ); strcat( pageBuff, "}" );
		strcat( pageBuff, ",\"2\": {\"use\":" ); strcat( pageBuff, utoa( app.flags.use_lenta2, esp::tmpVal, 10 ) );
		strcat( pageBuff, ",\"leds\":" ); strcat( pageBuff, utoa( app.lenta2_leds, esp::tmpVal, 10 ) ); strcat( pageBuff, "}" );
		strcat( pageBuff, ",\"3\": {\"use\":" ); strcat( pageBuff, utoa( app.flags.use_lenta3, esp::tmpVal, 10 ) );
		strcat( pageBuff, ",\"leds\":" ); strcat( pageBuff, utoa( app.lenta3_leds, esp::tmpVal, 10 ) ); strcat( pageBuff, "}" );
		strcat( pageBuff, ",\"4\": {\"use\":" ); strcat( pageBuff, utoa( app.flags.use_lenta4, esp::tmpVal, 10 ) );
		strcat( pageBuff, ",\"leds\":" ); strcat( pageBuff, utoa( app.lenta4_leds, esp::tmpVal, 10 ) ); strcat( pageBuff, "}" );
		strcat( pageBuff, ",\"5\": {\"use\":" ); strcat( pageBuff, utoa( app.flags.use_lenta5, esp::tmpVal, 10 ) );
		strcat( pageBuff, ",\"leds\":" ); strcat( pageBuff, utoa( app.lenta5_leds, esp::tmpVal, 10 ) ); strcat( pageBuff, "}" );
	strcat( pageBuff, "}}" );
	webServer.send ( 200, "application/json", pageBuff );
}

//-----------------------------------------------------------------------------------------
void indexPageHeadler(void)
{
	esp::webSendFile( &webServer, "/index.html", "text/html" );
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
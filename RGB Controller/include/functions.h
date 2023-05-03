#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

//-----------------------------------------------------------------------------------------
#include "main.h"

//-----------------------------------------------------------------------------------------


//----------- DEFINES ---------------------------------------------------------------------


//----------- VARIABLES -------------------------------------------------------------------


//----------- FUNCTIONS--------------------------------------------------------------------
void lenta_clear(Adafruit_NeoPixel &lenta);
void setLed(Adafruit_NeoPixel &lenta, const uint16_t ledNum, uint8_t r, uint8_t g, uint8_t b, const bool show = false);
void setLed(Adafruit_NeoPixel &lenta, const uint16_t ledNum, uint32_t pixel, const bool show = false);
void setBrightnessPrz(Adafruit_NeoPixel &lenta, const uint8_t percent);
void setBrightness(Adafruit_NeoPixel &lenta, const uint8_t value);
void start(void);
void animationProcess(void);
void clearAll(void);

//-----------------------------------------------------------------------------------------




#endif //__FUNCTIONS_H__
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdint.h>

//========== DEFINES ===========================================================
//========== STRUCTURES ========================================================
//========== VARIABLES =========================================================
//========== FUNCTIONS =========================================================
uint8_t isPressButton(const uint8_t pin);
void onLamp(const uint8_t lampNum);
void offLamp(const uint8_t lampNum);
void setLed(const uint8_t ledNum, uint8_t r, uint8_t g, uint8_t b);
void setStage1(void);
void setStage2(void);
void processStage2(const uint8_t button);
void setStage3(void);
void setStageError(void);
void beep(const uint16_t on, const uint16_t off = 0);
void startMelody(void);
void lock(void);
void unlock(void);






#endif // _FUNCTIONS_H_
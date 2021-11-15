#ifndef Arduino_h
#define Arduino_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "binary.h"

#ifdef __cplusplus
extern "C"{
#endif

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif


#define KEY_BYTE 0xD8

/*
   Выбор предделителя
*/
#define CORE_PRESCALER_1   0x00
#define CORE_PRESCALER_2   0x01
#define CORE_PRESCALER_4   0x02
#define CORE_PRESCALER_8   0x03
#define CORE_PRESCALER_16  0x04
#define CORE_PRESCALER_32  0x05
#define CORE_PRESCALER_64  0x06
#define CORE_PRESCALER_128 0x07
#define CORE_PRESCALER_256 0x08
#define CORE_PRESCALER_DEFAULT CORE_PRESCALER_8
#define CORE_PRESCALER_CLEAR   CORE_PRESCALER_1

/*
   Выбор источника тактирования
*/
#define CORE_CLOCK_INTERNAL 0x00
#define CORE_CLOCK_WDT  	0x01
#define CORE_CLOCK_EXTERNAL 0x02


#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define clockCyclesPerMicrosecond() (F_CPU / 1000000L)
#define clockCyclesToMicroseconds(a) ((a) / clockCyclesPerMicrosecond())
#define microsecondsToClockCycles(a) ((a) * clockCyclesPerMicrosecond())

#define interrupts() sei()
#define noInterrupts() cli()

#define bit(b) (1UL << (b))
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bitToggle(value, bit) ((value) ^= (1 << bit))

#define	A0 PB0
#define	A1 PB1
#define	A2 PB2
#define	A3 PB3

#define LOW 0
#define HIGH 1

#define LSBFIRST 0
#define MSBFIRST 1

#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

#define CHANGE 1
#define FALLING 2
#define RISING 3

typedef unsigned int word;
typedef uint8_t boolean;
typedef uint8_t byte;

void init(void);
void setup(void);
void loop(void);

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, bool state);
void analogWrite(uint8_t pin, uint8_t duty);
uint8_t analogRead(uint8_t pin);
bool digitalRead(uint8_t pin);
void delay(uint32_t ms);
void delayMicroseconds(uint32_t us);

#ifdef _TINY10_MILLIS_WDT
uint32_t millis(void);
#endif

#ifdef _TINY10_MILLIS_IMPLEMENT
uint32_t millis(void);
uint32_t micros(void);
#endif
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);

void attachInterrupt(uint8_t num,void (*isr)(), uint8_t type);
void detachInterrupt(uint8_t);
void setSystemPrescaler(uint8_t prescaler);
void setSystemClock(uint8_t clock);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

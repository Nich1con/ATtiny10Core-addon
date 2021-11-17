#include <Arduino.h>
#include <avr/interrupt.h>

/*
   Внешние прерывания
*/

// Указатель на функцию прерывания		
extern void (*ext_isr)();		
void (*ext_isr)();

// Вектор прерывания INT0
ISR(INT0_vect) {			
  (*ext_isr)();
}

// Включение прерывания на INT0
void attachInterrupt(uint8_t num, void (*handler)(), uint8_t type) {	
  if (num > 0) return;	// У нас только нулевое
  ext_isr = *handler;   // Передаем указатель на функцию
  EICRA = type;			// Настраиваем тип прерывания
  EIMSK |= 1 << INT0;   // Включаем прерывание
}

void detachInterrupt(uint8_t num) {
  if (num > 0) return;	// У нас только нулевое
  EIMSK &= ~ 1 << INT0; // Отключаем прерывание
  EIFR &= ~ 1 << INTF0; // Очищаем флаг прерывания
}

#include <Arduino.h>

/*
   Основные фунции ввода-вывода Arduino
*/

void pinMode(uint8_t pin, uint8_t mode) {
  switch (mode) {
    case INPUT:		
      DDRB &= ~ 1 << pin;
      PUEB &= ~ 1 << pin;
      return;
    case OUTPUT:
      DDRB |= 1 << pin;
      PUEB &= ~ 1 << pin;
      return;
    case INPUT_PULLUP:
      DDRB &= ~ 1 << pin;
      PUEB |= 1 << pin;
      return;
  }
}

void digitalWrite(uint8_t pin, bool state) {
  if (state) {
    PORTB |= 1 << pin;
  } else {
    PORTB &= ~1 << pin;
  }
}

void analogWrite(uint8_t pin, uint8_t duty) {
  if (duty < 1) {		// Костыль - детачить ногу от таймера нельзя, все ломается		
   pinMode(pin, INPUT);	// Вместо этого просто притворяемся шлангом (входом) когда нужно		
   return;
  } else pinMode(pin, OUTPUT);	

  switch (pin) {
    case PB0:
      TCCR0A |= 1 << COM0A1;
      OCR0A = duty;
      return;
    case PB1:
      TCCR0A |= 1 << COM0B1;
      OCR0B = duty;
      return;
    default: return;
  }
}

uint8_t analogRead(uint8_t pin) {
  if (pin > 3) return 0; 		// Пинов всего 4	
  ADMUX = pin;			 		// Настраиваем вход
  ADCSRA |= 1 << ADSC;   		// Запускаем
  while (ADCSRA & (1 << ADSC)); // Ждем окончания
  return ADCL;					// Получаем результат
}

bool digitalRead(uint8_t pin) { 
  return (bool)(PINB & (1 << pin));
}

void setSystemPrescaler(uint8_t prescaler){
  CCP = KEY_BYTE;
  CLKPSR = prescaler;
} 

void setSystemClock(uint8_t clock){
  CCP = KEY_BYTE;
  CLKMSR = clock;
}

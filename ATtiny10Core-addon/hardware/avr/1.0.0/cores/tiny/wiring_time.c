#include <Arduino.h>

void delay(uint32_t ms) {
#if defined(_TINY10_MILLIS_IMPLEMENT) && defined(_TINY10_TIMER_INIT)
  uint32_t start = millis();
  while (millis() - start < ms);	// Делей на миллисе если он есть
#else
  while (ms) {						// Или цикл 
    _delay_ms(1);					// С фикс. делеем
    ms--;
  }
#endif
}

void delayMicroseconds(uint32_t us) {
  while (us) {						// Тут всегда цикл					
    _delay_us(1);   
    us--;
  }
}

#ifdef _TINY10_MILLIS_WDT				// Миллис на WDT
volatile uint32_t _wdt_millis_cnt = 0;	// Счетчик

uint32_t millis(void) {    				// Миллис
  return (uint32_t)_wdt_millis_cnt;     // Возвразаем счетчик	     
}

ISR(WDT_vect) {							// Прерывание WDT
  _wdt_millis_cnt += 16;				// Добавляем 16 (шаг 16 мс)
}
#endif

#ifdef _TINY10_MILLIS_IMPLEMENT	        // Полноценный ардуиновский millis/micros
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)
#define MICROS_MULT (64 / clockCyclesPerMicrosecond())

volatile uint32_t timer0_overflow_count = 0;
volatile uint32_t timer0_millis = 0;
static uint8_t timer0_fract = 0;

uint32_t millis(void) {    
  return (uint32_t)timer0_millis;          
}

uint32_t micros(void) {
  return (uint32_t)(((timer0_overflow_count << 8) + TCNT0) * MICROS_MULT);
}

ISR(TIM0_OVF_vect) {
  timer0_millis += MILLIS_INC;
  timer0_fract += FRACT_INC;
  if (timer0_fract >= FRACT_MAX) {
    timer0_fract -= FRACT_MAX;
    timer0_millis++;
  }
  timer0_overflow_count++;
}
#endif
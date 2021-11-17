/*
   Инциализация перед void setup(){}
*/

#include <Arduino.h>

#define ADC_PRESCALER 0b111						// Предделитель АЦП (максимальный - 128)

void init(void){
  cli();										// Запрещаем прерывания (на всякий случай, они и так должны быть выключены)
#if (F_CPU == 8000000L) || (F_CPU == 128000L)	// Если выбран клок не 1МГц
  setSystemPrescaler(CORE_PRESCALER_CLEAR);		// Сбрасываем системный делитель
#endif

#if (F_CPU == 128000L)							// Если выбран клок от WDT
  setSystemClock(CORE_CLOCK_WDT);				// Выбираем его
#endif
	
#ifdef _TINY10_ADC_INIT							// Если включена инициализация АЦП
  ADCSRA = 1 << ADEN | ADC_PRESCALER;			// Включаем АЦП
#endif

#ifdef _TINY10_MILLIS_WDT						// Если миллис на WDT
  CCP = KEY_BYTE;								// Разрешаем вмешательство
  WDTCSR = 1 << WDIE;							// Включаем WDT в режиме interrupt
#endif

#ifdef _TINY10_TIMER_INIT						// Если включена инициализация таймера 0
   TCCR0A = 1 << WGM00;							// Fast PWM 
   TCCR0B = 1 << WGM02 | 0b11;					// С делителем /64
#ifdef _TINY10_MILLIS_IMPLEMENT					// Если включен миллис на таймере
   TIMSK0 = 1 << TOIE0;							// Включаем прерывание переполения
#endif
#endif
   sei();										// Разрешаем прерывания
}

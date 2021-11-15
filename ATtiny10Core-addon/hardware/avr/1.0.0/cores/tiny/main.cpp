#include <Arduino.h>

/*
   Главный цикл программы
*/

int main(void) {		// <- Точка входа в программу
  init();				// <- Инициализация (wiring_init.h)	
  setup();				// <- Setup
  while(true) loop();	// <- Бесконечный loop
  return 0;
}

ATtiny10Core add-on
============
Дополнение к ядру ATtiny10Core (https://github.com/technoblogy/attiny10core)

### Возможности
Добавляет все стандартные функции ввода-вывода, привычные пользователям Arduino.
Список реализованных функций:

* **pinMode()**
* **digitalWrite()**
* **digitalRead()**
* **analogWrite()**
* **analogRead()**
* **millis()**
* **micros()**
* **delay()**
* **delayMicroseconds()**
* **shiftOut()**
* **shiftIn()**

Дополнительно реализованы функции управления тактированием:
* setSystemPrescaler() - установить предделитель системной частоты
* **CORE_PRESCALER_1** 
* **CORE_PRESCALER_2**
* **CORE_PRESCALER_4**
* **CORE_PRESCALER_8**
* **CORE_PRESCALER_16**
* **CORE_PRESCALER_32**
* **CORE_PRESCALER_64**
* **CORE_PRESCALER_128**
* **CORE_PRESCALER_256**
* **CORE_PRESCALER_DEFAULT**

* setSystemClock() - выбрать источник тактирования
* **CORE_CLOCK_INTERNAL** 	- Внутренний источник 8 МГц
* **CORE_CLOCK_WDT**		 	- Внутренний источник WDT, 128 кГц
* **CORE_CLOCK_EXTERNAL**		- Внешнее тактирование, до 12 МГц

Дополнительно в меню платы можно:
* Выбрать частоту тактирования
* Отключить и включить инициализацию АЦП (**analogRead()**)
* Отключить и включить инициализацию таймера 0 (**analogWrite()**)
* Выбрать вариант реализации **millis()** и **micros()**

### Установка

* Установить ядро ATtiny10Core (https://github.com/technoblogy/attiny10core)
* Перейти по пути **C:\Users\username\AppData\Local\Arduino15\packages\ATtiny10Core**
* Скачать архив этого репозитория
* Заменить папку **hardware** той, что лежит в архиве
* Перезапустить Arduino IDE
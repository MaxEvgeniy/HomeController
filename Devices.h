#ifndef DEVICES_H
#define DEVICES_H

#include "main.h"
#include "stdint.h"    
#include "stdbool.h"

#include "TasksForAll.h"

////////////////////////////////////Основные платы//////////////////////////////////
typedef struct                                                                  // Описание платы с камнем
{
uint8_t Address;                                                                // Адрес платы  (Должен быть уникален)
uint8_t Name;                                                                   // Имя платы (Может повторяться)
uint8_t State;                                                                  // Cостояние платы
}Board;

enum BoardStates                                                                // Список состояний платы
{
BoardOnLine=0x01,                                                               // Плата в сети, работает нормально
BoardStateUnknown,                                                              // Состояние платы не отпределено
BoardOffLine,                                                                   // Плата отключена
BoardInAlarm,                                                                   // Плата в состоянии тревоги
BoardError                                                                      // Плата в состоянии ошибки
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////Светодиоды//////////////////////////////////
typedef struct                                                                  // Описание светодиода
{
uint8_t Address;                                                                // Адрес лампочки
uint16_t Pin;                                                                   // Пин лампочки
GPIO_TypeDef* Port;                                                             // Порт лампочки
}Led;

enum LedStates                                                                  // Список состояний светодиода
{
LedIsOn=0x01,                                                                   // Светодиод включен
LedIsOff,                                                                       // Светодиод выключен
LedUnknown                                                                      // Состояние светодиода неизвестно
};

void LedOn (Led LedLamp);                                                        // Включить светодиод
void LedOff (Led LedLamp);                                                       // Выключить светодиод
void LedToggle (Led LedLamp);                                                    // Переключить светодиод
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////Кнопки//////////////////////////////////////
typedef struct                                                                  // Описание кнопки
{
uint8_t Address;                                                                // Адрес кнопки
uint16_t Pin;                                                                   // Пин кнопки
GPIO_TypeDef* Port;                                                             // Порт кнопки
uint8_t State;                                                                  // Состояние кнопки
uint16_t HotPointTime;                                                          // Счетчик времени до контрольной точки
uint8_t HotPoint;                                                               // Счетчик пройденных контрольных точек
bool FirstPointState;                                                           // Положение кнопки при прохождении первой контрольной точки
bool SecondPointState;                                                          // Положение кнопки при прохождении второй контрольной точки
bool FinalPointState;                                                           // Положение кнопки при прохождении последней контрольной точки
uint8_t Result;                                                                 // Результирующее положение кнопки

uint8_t ShortClickScenario;                                                     // Номер сценария по короткому нажатию  
uint8_t ButtonLongPressScenario;                                                // Номер сценария по длинному нажатию 
uint8_t DoubleClickScenario;                                                    // Номер сценария по двойному нажатию 
uint8_t ButtonHoldScenari;                                                      // Номер сценария по удержанию 
}Button;

enum ButtonStates                                                               // Список состояний кнопки
{
ButtonIsPress=0x01,                                                             // Кнопка нажата
ButtonIsNoPress,                                                                // Кнопка не нажата
};

enum ButtonResults                                                              // Список результирующих положений кнопки
{
ButtonUp=0x01,                                                                  // Кнопка не нажималась                        
ButtonShortClick,                                                               // Короткое нажатие
ButtonLongPress,                                                                // Длинное нажатие
ButtonDoubleClick,                                                              // Двойное нажатие
ButtonHold,                                                                     // Удерживание
};

uint8_t ReadButton (Button ButKey);                                             // Считать кнопку
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////Реле////////////////////////////////////////
typedef struct                                                                  // Описание реле
{
uint8_t Address;                                                                // Адрес реле
uint16_t Pin;                                                                   // Пин реле
GPIO_TypeDef* Port;                                                             // Порт реле
uint8_t State;                                                                  // Состояние реле
}Relay;

enum RelayStates                                                                // Список состояний кнопки
{
RelayDisabled=0x01,                                                             // Реле разомкнуто
RelayEnabled,                                                                   // Реле замкнуто
};

void RelayOn (Relay RelaySwitch);                                               // Замкнуть реле
void RelayOff (Relay RelaySwitch);                                              // Разомкнуть реле
void RelayToggle (Relay RelaySwitch);                                           // Переключить реле
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////Датчик движения/////////////////////////////
typedef struct                                                                  // Описание датчика движения
{
uint8_t Address;                                                                // Адрес датчика движения
uint16_t Pin;                                                                   // Пин датчика движения
GPIO_TypeDef* Port;                                                             // Порт датчика движения
}MovingSensor;

bool ReadMovingSensor (MovingSensor MovSensor);                                 // Считать датчик движения
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////Датчик приближения/////////////////////////////
typedef struct                                                                  // Описание датчика приближения
{
uint8_t Address;                                                                // Адрес датчика приближения
uint16_t Pin;                                                                   // Пин датчика приближения
GPIO_TypeDef* Port;                                                             // Порт датчика приближения
}ProximitySensor;

bool ReadProximitySensor (ProximitySensor ProxSensor);                          // Считать датчик приближения
////////////////////////////////////////////////////////////////////////////////

#endif

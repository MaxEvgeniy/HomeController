#ifndef SCENARIOS_H
#define SCENARIOS_H

#include "stdint.h"    
#include "stdbool.h"

typedef struct 
{
uint8_t Name;                                                                   // Номер имени сценария в списке имен 
  
bool Active;                                                                    // Указатель на то, что сценарий выполняется

uint32_t TimerStep;
uint8_t Position;                                                               // Текущая позиция на кадре сценария. 0-начальная задержка, 1-действие, 2- конечная задержка
uint8_t Frame;                                                                  // Текущий кадр сценария

uint32_t BeforeDelay[20];                                                       // Массив со временем задержек перед действием по шагу сценария
uint8_t NumberOfStep[20];                                                       // Массив с номерами действий по сценарию
uint8_t Parametr1[20];                                                          // Массив с дополнительным параметром действием по сценарию
uint32_t AfterDelay[20];                                                        // Массив со временем задержек после действия по шагу сценария

}Scenario;                                                                      // Класс сценария

enum ScenarioActionNumers                                                       // Список номеров действий по сценарию
{
ScenRelayOn=0x01,                                                               // Замкнуть реле
ScenRelayOff,                                                                   // Разомкнуть реле
ScenLedOn,                                                                      // Включить светодиод
ScenLedOff,                                                                     // Выключть светодиод
};

enum ScenarioNames                                                              // Список имен сценариев для порядка
{
TestDiodOnOff=0x01,                                                             // Включить и выключить диодик
MovieSensor,                                                                    // Сценарий для датчка движения
MainLightStart,                                                                 // Сценарий включения света 
MainLightStop                                                                   // Сценарий включения света
};

void ScenarioAction(void);                                                      // Обработка сценариев
void ScenariosInit(void);                                                       // Инициализация сценариев для плат

#endif
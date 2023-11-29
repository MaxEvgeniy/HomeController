#include "RooomRooom.h"
#include "Devices.h"
#include "Scenarios.h"
#include "main.h"

uint8_t RooomRooomMainCountMax=100;                                             // Максимальноезначение основного таймера для работы BathLighter (для перевода в секунды)
uint8_t RooomRooomMainCount=100;                                                // Основной таймер для работы BathLighter
uint8_t RooomRooomMainCountOLD=0;                                               // Старое значение основного таймера для работы BathLighter

uint16_t MainLightTimerCount=0;                                                 // Счетчик таймера работы основного освещения в секундах
uint16_t MainLightTimerMax=14400;//10;//14400;                                          // Максимальное значение счетчика таймера работы основного освещения в секундах (4 часа)

bool MainLightIndicator=false;                                                  // Флажок основной свет включен или нет

extern Relay Relays[11];                                                        // Массив реле
extern Button Buttons[1];                                                       // Массив кнопок
extern Scenario BasicScenarios[10];                                             // Основной набор сценариев


void RooomRooomInit (void)
{ 
Relays[0].Address=1;
Relays[0].Pin=Relay1_Pin;
Relays[0].Port=Relay1_GPIO_Port;
Relays[0].State=RelayDisabled;

Relays[1].Address=2;
Relays[1].Pin=Relay2_Pin;
Relays[1].Port=Relay2_GPIO_Port;
Relays[1].State=RelayDisabled;

Relays[2].Address=3;
Relays[2].Pin=Relay3_Pin;
Relays[2].Port=Relay3_GPIO_Port;
Relays[2].State=RelayDisabled;

Relays[3].Address=4;
Relays[3].Pin=Relay4_Pin;
Relays[3].Port=Relay4_GPIO_Port;
Relays[3].State=RelayDisabled;

Relays[4].Address=5;
Relays[4].Pin=Relay5_Pin;
Relays[4].Port=Relay5_GPIO_Port;
Relays[4].State=RelayDisabled;

Relays[5].Address=6;
Relays[5].Pin=Relay6_Pin;
Relays[5].Port=Relay6_GPIO_Port;
Relays[5].State=RelayDisabled;

Relays[6].Address=7;
Relays[6].Pin=Relay7_Pin;
Relays[6].Port=Relay7_GPIO_Port;
Relays[6].State=RelayDisabled;

Relays[7].Address=8;
Relays[7].Pin=Relay8_Pin;
Relays[7].Port=Relay8_GPIO_Port;
Relays[7].State=RelayDisabled;

Relays[8].Address=9;
Relays[8].Pin=Relay9_Pin;
Relays[8].Port=Relay9_GPIO_Port;
Relays[8].State=RelayDisabled;

Relays[9].Address=10;
Relays[9].Pin=Relay10_Pin;
Relays[9].Port=Relay10_GPIO_Port;
Relays[9].State=RelayDisabled;

Relays[10].Address=11;
Relays[10].Pin=Relay11_Pin;
Relays[10].Port=Relay11_GPIO_Port;
Relays[10].State=RelayDisabled;

RelayOff(Relays[0]);
RelayOff(Relays[1]);
RelayOff(Relays[2]);
RelayOff(Relays[3]);
RelayOff(Relays[4]);
RelayOff(Relays[5]);
RelayOff(Relays[6]);
RelayOff(Relays[7]);
RelayOff(Relays[8]);
RelayOff(Relays[9]);
RelayOff(Relays[10]);

Buttons[0].Address=1;  
Buttons[0].Pin=Button1_Pin;
Buttons[0].Port=Button1_GPIO_Port; 
Buttons[0].State=ButtonIsNoPress;
}

void RooomRooomDrive (void)
{ 
LightDrive();

}

void RooomRooomReadSensors(void)
{
ButtonsListen(); 
ButtonsCheck();
}

void LightDrive (void)
{
  
if (RooomRooomMainCountOLD!=RooomRooomMainCount)                                // Если старое значение счетчика не совпадает с новым 
  {  
  if (RooomRooomMainCount<=0)                                                   // Если основной счетчик обнулился- 
    {
    RooomRooomMainCount=RooomRooomMainCountMax;                                 // Запускаем заново  
    
    if(MainLightTimerCount>0)                                                   // Если счетчик времени основного света запущен
      {
      MainLightTimerCount--;                                                    // Снижаем значение
      if(MainLightTimerCount==0)
        {
        MainLightIndicator=false;  
        if(BasicScenarios[2].Active==false){BasicScenarios[2].Active=true;};    // Сценарий отключения света 
        };                              // Если таймер подошел к концу выключаем свет
      };  
   };
  RooomRooomMainCountOLD=RooomRooomMainCount;                                   // Выравниваем старое и новое значение
  };

};

void MainLightOn (void)
{
MainLightTimerCount=MainLightTimerMax;                                          // Запуск таймера включения основного света
MainLightIndicator=true;                                                        // Ставим флажок, что свет включен
RelayOn(Relays[0]);                                                             // Замыкаем реле 1
osDelay(20);                                                                    // Задержка для пущего эффекту
RelayOn(Relays[1]);                                                             // Замыкаем реле 2
osDelay(20);                                                                    // Задержка для пущего эффекту
RelayOn(Relays[2]);                                                             // Замыкаем реле 3
osDelay(20);                                                                    // Задержка для пущего эффекту
RelayOn(Relays[3]);                                                             // Замыкаем реле 4
osDelay(20);                                                                    // Задержка для пущего эффекту
RelayOn(Relays[4]);                                                             // Замыкаем реле 5
osDelay(20);                                                                    // Задержка для пущего эффекту
RelayOn(Relays[5]);                                                             // Замыкаем реле 6
osDelay(20);                                                                    // Задержка для пущего эффекту
RelayOn(Relays[6]);                                                             // Замыкаем реле 7
osDelay(20);                                                                    // Задержка для пущего эффекту
RelayOn(Relays[7]);                                                             // Замыкаем реле 8
osDelay(20);                                                                    // Задержка для пущего эффекту
RelayOn(Relays[8]);                                                             // Замыкаем реле 9
osDelay(20);                                                                    // Задержка для пущего эффекту
RelayOn(Relays[9]);                                                             // Замыкаем реле 10
osDelay(20);                                                                    // Задержка для пущего эффекту
RelayOn(Relays[10]);                                                            // Замыкаем реле 11
}

void MainLightOff (void)
{
MainLightTimerCount=0;                                                          // Стоп таймера включения основного света
MainLightIndicator=false;                                                       // Ставим флажок, что свет выключен  
RelayOff(Relays[0]);                                                            // Отпускаем реле 1
RelayOff(Relays[1]);                                                            // Отпускаем реле 2
RelayOff(Relays[2]);                                                            // Отпускаем реле 3
RelayOff(Relays[3]);                                                            // Отпускаем реле 4
RelayOff(Relays[4]);                                                            // Отпускаем реле 5
RelayOff(Relays[5]);                                                            // Отпускаем реле 6
RelayOff(Relays[6]);                                                            // Отпускаем реле 7
RelayOff(Relays[7]);                                                            // Отпускаем реле 8
RelayOff(Relays[8]);                                                            // Отпускаем реле 9
RelayOff(Relays[9]);                                                            // Отпускаем реле 10
RelayOff(Relays[10]);                                                           // Отпускаем реле 11
RelayOff(Relays[11]);                                                           // Отпускаем реле 12
}

void ButtonsCheck (void)
{ 
////////////////////////////Кнопка 1//////////////////////////////////////////// 

switch (Buttons[0].Result)                                                      // Проверка состояния кнопки                     
  {
  case ButtonShortClick:                                                        // Короткое нажатие
    { 
    if(MainLightIndicator==true)                                                // Если основной свет включен
      {
      MainLightIndicator=false;                                                 // Ставим флажок, что свет выключен
      MainLightTimerCount=0;                                                    // Запуск таймера включения основного света
      if(BasicScenarios[2].Active==false){BasicScenarios[2].Active=true;};      // Сценарий отключения света
      }
    else
      {
      MainLightTimerCount=MainLightTimerMax;                                    // Запуск таймера включения основного света
      MainLightIndicator=true;                                                  // Ставим флажок, что свет включен
      if(BasicScenarios[1].Active==false){BasicScenarios[1].Active=true;};      // Сценарий включения света
      }; 
    
    ButtonsReset(0);                                                            // Сбросить состояние кнопки 
    osDelay(1);
    break;
    } 
  case ButtonLongPress:                                                         // Длинное нажатие 
    {
    if(MainLightIndicator==true)                                                // Если основной свет включен
      {
      MainLightIndicator=false;                                                 // Ставим флажок, что свет выключен
      if(BasicScenarios[2].Active==false){BasicScenarios[2].Active=true;};      // Сценарий отключения света
      }
    else
      {
      MainLightTimerCount=MainLightTimerMax;                                    // Запуск таймера включения основного света
      MainLightIndicator=true;                                                  // Ставим флажок, что свет включен
      if(BasicScenarios[1].Active==false){BasicScenarios[1].Active=true;};      // Сценарий включения света
      };
    ButtonsReset(0);                                                            // Сбросить состояние кнопки 
    osDelay(1);
    break;
    }  
  case ButtonDoubleClick:                                                       // Двойное нажатие
    {
    ButtonsReset(0);                                                            // Сбросить состояние кнопки
    osDelay(1);
    break;
    }  
  case ButtonHold:                                                              // Удержание 
    {
    ButtonsReset(0);                                                            // Сбросить состояние кнопки 
    break;      
    } 
  default:                                                              
    {
                 //группа операторов;
    };
  };

////////////////////////////////////////////////////////////////////////////////
}
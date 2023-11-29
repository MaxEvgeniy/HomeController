#include "BathLighter.h"
#include "TasksForAll.h"
#include "Scenarios.h"
#include "main.h"

extern uint8_t MyName;

extern Button Buttons[4];                                                       // Массив кнопок
extern uint8_t ButtonsCount;                                                    // Количество светодиодов на плате 

extern Led Leds[1];                                                             // Массив светодиодов
extern Relay Relays[8];                                                         // Массив реле
extern MovingSensor MovingSensors[1];                                           // Массив датчиков движения
extern ProximitySensor ProximitySensors[2];                                     // Массив датчиков движения
extern Scenario BasicScenarios[10];                                             // Основной набор сценариев

uint8_t BathMainCountMax=100;                                                   // Максимальное значение основного таймера для работы BathLighter (для перевода в секунды)
uint8_t BathMainCount=100;                                                      // Основной таймер для работы BathLighter
uint8_t BathMainCountOLD=0;                                                     // Старое значение основного таймера для работы BathLighter

uint16_t MainLightTimerCount=0;                                                 // Счетчик таймера работы основного освещения в секундах
uint16_t MainLightTimerMax=1800;                                                // Максимальное значение счетчика таймера работы основного освещения в секундах

uint16_t BigVentTimerCount=0;                                                   // Счетчик таймера работы большой вытяжки в секундах
uint16_t BigVentTimerMax=1800;                                                  // Максимальное значение счетчика таймера работы большой вытяжки в секундах

uint16_t BoxLightTimerCount=0;                                                  // Счетчик таймера работы освещения в коробе в секундах
uint16_t BoxLightTimerMax=600;                                                  // Максимальное значение счетчика таймера работы освещения в коробе в секундах

uint16_t MirrorLightTimerCount=0;                                               // Счетчик таймера работы подсветки зеркала в секундах
uint16_t MirrorLightTimerMax=1200;                                              // Максимальное значение счетчика таймера работы подсветки зеркала в секундах

bool MainLightIndicator=false;                                                  // Флажок основной свет включен или нет
bool BoxLightIndicator=false;                                                   // Флажок свет в коробе включен или нет
bool VentIndicator=false;                                                       // Флажок ветиляция включена или нет
bool MirrorLightIndicator=false;                                                // Флажок подсветки зеркала

void BathLighterInit(void)
{
Leds[0].Address=1;  
Leds[0].Pin=Led1_Pin;
Leds[0].Port=Led1_GPIO_Port; 

LedOff(Leds[0]);  
  
Buttons[0].Address=1;  
Buttons[0].Pin=Button1_Pin;
Buttons[0].Port=Button1_GPIO_Port; 
Buttons[0].State=ButtonIsNoPress;

Buttons[1].Address=2;  
Buttons[1].Pin=Button2_Pin;
Buttons[1].Port=Button2_GPIO_Port;
Buttons[1].State=ButtonIsNoPress;

Buttons[2].Address=3;  
Buttons[2].Pin=Button3_Pin;
Buttons[2].Port=Button3_GPIO_Port;
Buttons[2].State=ButtonIsNoPress;

Buttons[3].Address=4;  
Buttons[3].Pin=Button4_Pin;
Buttons[3].Port=Button4_GPIO_Port;
Buttons[3].State=ButtonIsNoPress;

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

MovingSensors[0].Address=1;  
MovingSensors[0].Pin=MovingSensor1_Pin;
MovingSensors[0].Port=MovingSensor1_GPIO_Port; 

ProximitySensors[0].Address=1;  
ProximitySensors[0].Pin=ProximitySensor1_Pin;
ProximitySensors[0].Port=ProximitySensor1_GPIO_Port; 

ProximitySensors[1].Address=2;  
ProximitySensors[1].Pin=ProximitySensor2_Pin;
ProximitySensors[1].Port=ProximitySensor2_GPIO_Port; 
}

void BathLighterDrive(void)
{ 
LightDrive();
////////////////////////////////////////////////////////////////////////////////

/*
if(ReadMovingSensor(MovingSensors[0])==true)
  {if(BasicScenarios[1].Active==false){BasicScenarios[1].Active=true;};};
*/
/*
if(ReadProximitySensor(ProximitySensors[0])==true)
  {LedOn(Leds[0]);}
else
  {LedOff(Leds[0]);};
*/
////////////////////////////////////////////////////////////////////////////////
}

void ButtonsCheck (void)
{ 
////////////////////////////Кнопка 1//////////////////////////////////////////// 
switch (Buttons[0].Result)                                                      // Проверка состояния кнопки                     
  {
  case ButtonShortClick:                                                        // Короткое нажатие
    {
      if(BasicScenarios[0].Active==false){BasicScenarios[0].Active=true;};
      /*
    if(MainLightIndicator==false)                                               // Если основной свет выключен
      {MainLightOn();}                                                          // Включить основной свет 
    else
      {MainLightOff();};                                                        // Выключить основной свет
      */
    ButtonsReset(0);                                                            // Сбросить состояние кнопки
    break;
    } 
  case ButtonLongPress:                                                         // Длинное нажатие 
    {
     if(BasicScenarios[0].Active==false){BasicScenarios[0].Active=true;};
      /*
    if(MainLightIndicator==false)                                                      // Если основной свет выключен
      {MainLightOn();}                                                          // Включить основной свет 
    else
      {MainLightOff();};                                                        // Выключить основной свет
      */
      ButtonsReset(0);                                                          // Сбросить состояние кнопки
    break;
    }  
  case ButtonDoubleClick:                                                       // Двойное нажатие
    {
     /* 
    if(VentIndicator==false)                                                           // Если вытяжка выключена
      {VentOn();}                                                               // Включить вытяжку
    else
      {VentOff();};                                                             // Выключить вытяжку
*/
    ButtonsReset(0);                                                            // Сбросить состояние кнопки
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

void BathLighterReadSensors(void)
{
ButtonsListen(); 
ButtonsCheck();
}

void LightDrive (void)
{
if (BathMainCountOLD!=BathMainCount)                                            // Если старое значение счетчика не совпадает с новым 
  {  
  if (BathMainCount<=0)                                                         // Если основной счетчик обнулился- 
    {
    BathMainCount=BathMainCountMax;                                             // Запускаем заново  
    
    if(MainLightTimerCount>0)                                                   // Если счетчик времени основного света запущен
      {
      MainLightTimerCount--;                                                    // Снижаем значение
      if(MainLightTimerCount==0){MainLightOff();};                              // Если таймер подошел к концу выключаем свет
      };
    
    if(BigVentTimerCount>0)                                                     // Если счетчик времени большой вытяжки запущен
      {
      BigVentTimerCount--;                                                      // Снижаем значение
      if(BigVentTimerCount==0){VentOff();};                                     // Если таймер подошел к концу выключаем большую вытяжку     
      };
    
    if(BoxLightTimerCount>0)                                                    // Если счетчик времени света в коробе запущен
      {
      BoxLightTimerCount--;                                                     // Снижаем значение
      if(BoxLightTimerCount==0){BoxLightOff();};                                // Если таймер подошел к концу выключаем подсветку короба      
      };
    
    if(MirrorLightTimerCount>0)                                                 // Если счетчик времени подсветки зеркала запущен
      {
      MirrorLightTimerCount--;                                                  // Снижаем значение
      if(MirrorLightTimerCount==0){MirrorLightOff();};                          // Если таймер подошел к концу выключаем подсветку зеркала 
      }; 
    };
  
  BathMainCountOLD=BathMainCount;                                               // Выравниваем старое и новое значение
  };
};

void MainLightOn (void)
{
LedOn(Leds[0]); 
/*  
MainLightTimerCount=MainLightTimerMax;                                          // Запуск таймера включения основного света
MainLightIndicator=true;                                                        // Ставим флажок, что свет включен
RelayOn(Relays[0]);                                                             // Замыкаем реле 1
osDelay(200);                                                                   // Задержка для пущего эффекту
RelayOn(Relays[1]);                                                             // Замыкаем реле 2
osDelay(200);                                                                   // Задержка для пущего эффекту
RelayOn(Relays[2]);                                                             // Замыкаем реле 3
 */
}

void MainLightOff (void)
{
LedOff(Leds[0]);
/*
MainLightTimerCount=0;                                                          // Стоп таймера включения основного света
MainLightIndicator=false;                                                       // Ставим флажок, что свет выключен  
RelayOff(Relays[0]);                                                            // Отпускаем реле 1
RelayOff(Relays[1]);                                                            // Отпускаем реле 2
RelayOff(Relays[2]);                                                            // Отпускаем реле 3
*/
}

void VentOn (void)
{
BigVentTimerCount=BigVentTimerMax;                                              // Запуск таймера включения вытяжки
VentIndicator=true;                                                             // Ставим флажок, что ветиляция включена
RelayOn(Relays[3]);                                                             // Замыкаем реле 4
}

void VentOff (void)
{
BigVentTimerCount=0;                                                            // Стоп таймера включения вытяжки
VentIndicator=false;                                                            // Ставим флажок, что ветиляция выключена
RelayOff(Relays[3]);                                                            // Отпускаем реле 4
}

void BoxLightOn (void)
{
BoxLightTimerCount=BoxLightTimerMax;                                            // Запуск таймера включения освещения короба
BoxLightIndicator=true;                                                         // Ставим флажок, что освещение включено
RelayOn(Relays[4]);                                                             // Замыкаем реле 5
}

void BoxLightOff (void)
{
BoxLightTimerCount=0;                                                           // Стоп таймера включения освещения короба
BoxLightIndicator=false;                                                        // Ставим флажок, что освещение выключено
RelayOff(Relays[4]);                                                            // Отпускаем реле 5
}

void MirrorLightOn (void)
{
MirrorLightTimerCount=MirrorLightTimerMax;                                      // Запуск таймера включения подсветки зеркала
MirrorLightIndicator=true;                                                      // Ставим флажок, что освещение включено
RelayOn(Relays[5]);                                                             // Замыкаем реле 6
}

void MirrorLightOff (void)
{
MirrorLightTimerCount=0;                                                        // Стоп таймера включения подсветки зеркала
MirrorLightIndicator=false;                                                     // Ставим флажок, что освещение выключено
RelayOff(Relays[5]);                                                            // Отпускаем реле 6
}

void RunIndividualComands (uint8_t Command,uint8_t Parametr2,uint8_t Parametr3,uint8_t Parametr4,uint8_t Parametr5,uint8_t Parametr6,uint8_t Parametr7)// Обработка индивидуальных команд
{
switch (Command)                                                                // Проверяем команду                       
    {
    case CommandLightOn:                                                        // Команда включения света
      {
      MainLightOn();  
      break;
      }
    case CommandLightOff:                                                        // Команда выключения света
      {
      MainLightOff(); 
      break;
      } 
    case CommandVentOn:                                                        // Команда включения света
      {
      VentOn();
      break;
      }
    case CommandVentOff:                                                        // Команда выключения света
      {
      VentOn(); 
      break;
      }       
    default:                                                                    // Если команда не входит ни в одну из групп
      {
      //группа операторов
      };
    }; 
};
#include "Scenarios.h"
#include "TasksForAll.h"

Scenario BasicScenarios[10];                                                    // Основной набор сценариев
uint8_t BasicScenariosCount=10;                                                 // Количество базовых сценариев. Для правильного перебора массива
uint8_t ScenarioTimerMainCount;                                                 // Счетчик для опрелеления пауз в сценарии
uint8_t ScenarioTimerMax=1;                                                     // Максимальное значение счетчика паузы между шагами в сценарии

void ScenariosInit(void)
{
#ifdef NetMasterBoard 

#endif  
  
#ifdef TaskMasterBoard 
 
#endif
  
#ifdef BathLighterBoard 
///////////////////////////////Сценарии///////////////////////////////////////// 
  
//////////////////////////////Тестовый сценарий/////////////////////////////////  
  BasicScenarios[0].Name=TestDiodOnOff;
  
  BasicScenarios[0].Active=false;
  BasicScenarios[0].TimerStep=0;
  BasicScenarios[0].Position=0;
  BasicScenarios[0].Frame=0;
//////////////////////////////////Кадр 1////////////////////////////////////////  
  BasicScenarios[0].BeforeDelay[0]=10;                                           // Задержка до
  BasicScenarios[0].NumberOfStep[0]=ScenLedOn;                                  // Включить лампочку
  BasicScenarios[0].Parametr1[0]=0;                                             // Адрес лампочки        
  BasicScenarios[0].AfterDelay[0]=1;                                           // Задержка после

//////////////////////////////////Кадр 2////////////////////////////////////////  
  BasicScenarios[0].BeforeDelay[1]=10;                                          // Задержка до
  BasicScenarios[0].NumberOfStep[1]=ScenLedOff;                                 // Выключить лампочку
  BasicScenarios[0].Parametr1[1]=0;                                             // Адрес лампочки        
  BasicScenarios[0].AfterDelay[1]=0;                                           // Задержка после

//////////////////////////////////Кадр 3////////////////////////////////////////  
  BasicScenarios[0].BeforeDelay[2]=1;                                            // Задержка до
  BasicScenarios[0].NumberOfStep[2]=0;                                          // Пустое действие
  BasicScenarios[0].Parametr1[2]=0;                                             // Адрес лампочки        
  BasicScenarios[0].AfterDelay[2]=0;                                           // Задержка после
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
  
//////////////////////////////Сценарий на датчик движения///////////////////////
  BasicScenarios[1].Name=MovieSensor;
  
  BasicScenarios[1].Active=false;
  BasicScenarios[1].TimerStep=0;
  BasicScenarios[1].Position=0;
  BasicScenarios[1].Frame=0;
//////////////////////////////////Кадр 1////////////////////////////////////////  
  BasicScenarios[1].BeforeDelay[0]=5;                                           // Задержка до
  BasicScenarios[1].NumberOfStep[0]=ScenLedOn;                                  // Включить лампочку
  BasicScenarios[1].Parametr1[0]=0;                                             // Адрес лампочки        
  BasicScenarios[1].AfterDelay[0]=0;                                           // Задержка после

//////////////////////////////////Кадр 2////////////////////////////////////////  
  BasicScenarios[1].BeforeDelay[1]=5;                                          // Задержка до
  BasicScenarios[1].NumberOfStep[1]=ScenLedOff;                                 // Выключить лампочку
  BasicScenarios[1].Parametr1[1]=0;                                             // Адрес лампочки        
  BasicScenarios[1].AfterDelay[1]=0;                                           // Задержка после

//////////////////////////////////Кадр 3////////////////////////////////////////  
  BasicScenarios[1].BeforeDelay[2]=5;                                           // Задержка до
  BasicScenarios[1].NumberOfStep[2]=ScenLedOn;                                  // Включить лампочку
  BasicScenarios[1].Parametr1[2]=0;                                             // Адрес лампочки        
  BasicScenarios[1].AfterDelay[2]=0;                                           // Задержка после

//////////////////////////////////Кадр 4////////////////////////////////////////  
  BasicScenarios[1].BeforeDelay[3]=5;                                          // Задержка до
  BasicScenarios[1].NumberOfStep[3]=ScenLedOff;                                 // Выключить лампочку
  BasicScenarios[1].Parametr1[3]=0;                                             // Адрес лампочки        
  BasicScenarios[1].AfterDelay[3]=0;                                           // Задержка после
  
  //////////////////////////////////Кадр 5////////////////////////////////////////  
  BasicScenarios[1].BeforeDelay[4]=5;                                           // Задержка до
  BasicScenarios[1].NumberOfStep[4]=ScenLedOn;                                  // Включить лампочку
  BasicScenarios[1].Parametr1[4]=0;                                             // Адрес лампочки        
  BasicScenarios[1].AfterDelay[4]=0;                                           // Задержка после

//////////////////////////////////Кадр 6////////////////////////////////////////  
  BasicScenarios[1].BeforeDelay[5]=5;                                          // Задержка до
  BasicScenarios[1].NumberOfStep[5]=ScenLedOff;                                 // Выключить лампочку
  BasicScenarios[1].Parametr1[5]=0;                                             // Адрес лампочки        
  BasicScenarios[1].AfterDelay[5]=0;                                           // Задержка после
 
////////////////////Сценарий включения основного света в ванной/////////////////  
  BasicScenarios[0].Name=MainLightStart;
  
  BasicScenarios[0].Active=false;
  BasicScenarios[0].TimerStep=0;
  BasicScenarios[0].Position=0;
  BasicScenarios[0].Frame=0;
//////////////////////////////////Кадр 1////////////////////////////////////////  
  BasicScenarios[0].BeforeDelay[0]=10;                                           // Задержка до
  BasicScenarios[0].NumberOfStep[0]=ScenLedOn;                                  // Включить лампочку
  BasicScenarios[0].Parametr1[0]=0;                                             // Адрес лампочки        
  BasicScenarios[0].AfterDelay[0]=1;                                           // Задержка после

//////////////////////////////////Кадр 2////////////////////////////////////////  
  BasicScenarios[0].BeforeDelay[1]=10;                                          // Задержка до
  BasicScenarios[0].NumberOfStep[1]=ScenLedOff;                                 // Выключить лампочку
  BasicScenarios[0].Parametr1[1]=0;                                             // Адрес лампочки        
  BasicScenarios[0].AfterDelay[1]=0;                                           // Задержка после

//////////////////////////////////Кадр 3////////////////////////////////////////  
  BasicScenarios[0].BeforeDelay[2]=1;                                            // Задержка до
  BasicScenarios[0].NumberOfStep[2]=0;                                          // Пустое действие
  BasicScenarios[0].Parametr1[2]=0;                                             // Адрес лампочки        
  BasicScenarios[0].AfterDelay[2]=0;                                           // Задержка после
////////////////////////////////////////////////////////////////////////////////  
#endif 

#ifdef RooomRooomBoard 
//////////////////////////////Тестовый сценарий/////////////////////////////////  
  BasicScenarios[0].Name=TestDiodOnOff;
  
  BasicScenarios[0].Active=false;
  BasicScenarios[0].TimerStep=0;
  BasicScenarios[0].Position=0;
  BasicScenarios[0].Frame=0;
//////////////////////////////////Кадр 1////////////////////////////////////////  
  BasicScenarios[0].BeforeDelay[0]=10;                                          // Задержка до
  BasicScenarios[0].NumberOfStep[0]=ScenRelayOn;                                // Включить лампочку
  BasicScenarios[0].Parametr1[0]=0;                                             // Адрес реле       
  BasicScenarios[0].AfterDelay[0]=1;                                            // Задержка после

//////////////////////////////////Кадр 2////////////////////////////////////////  
  BasicScenarios[0].BeforeDelay[1]=10;                                          // Задержка до
  BasicScenarios[0].NumberOfStep[1]=ScenRelayOff;                               // Выключить лампочку
  BasicScenarios[0].Parametr1[1]=1;                                             // Адрес реле        
  BasicScenarios[0].AfterDelay[1]=0;                                            // Задержка после

//////////////////////////////////Кадр 3////////////////////////////////////////  
  BasicScenarios[0].BeforeDelay[2]=1;                                           // Задержка до
  BasicScenarios[0].NumberOfStep[2]=0;                                          // Пустое действие
  BasicScenarios[0].Parametr1[2]=0;                                             // Адрес реле        
  BasicScenarios[0].AfterDelay[2]=0;                                            // Задержка после
//////////////////////////////////////////////////////////////////////////////// 
  
////////////////////////////Сценарий включения света////////////////////////////  
  BasicScenarios[1].Name=MainLightStart;
  
  BasicScenarios[1].Active=false;
  BasicScenarios[1].TimerStep=0;
  BasicScenarios[1].Position=0;
  BasicScenarios[1].Frame=0;
//////////////////////////////////Кадр 1////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[0]=1;                                          // Задержка до
  BasicScenarios[1].NumberOfStep[0]=ScenRelayOn;                                // Включить реле
  BasicScenarios[1].   Parametr1[0]=1;                                          // Адрес реле        
  BasicScenarios[1].  AfterDelay[0]=1;                                          // Задержка после

//////////////////////////////////Кадр 2////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[1]=100;                                         // Задержка до
  BasicScenarios[1].NumberOfStep[1]=ScenRelayOn;                                // Выключить реле
  BasicScenarios[1].   Parametr1[1]=2;                                          // Адрес реле        
  BasicScenarios[1].  AfterDelay[1]=1;                                          // Задержка после
  
//////////////////////////////////Кадр 3////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[2]=100;                                         // Задержка до
  BasicScenarios[1].NumberOfStep[2]=ScenRelayOn;                                // Включить реле
  BasicScenarios[1].   Parametr1[2]=3;                                          // Адрес реле        
  BasicScenarios[1].  AfterDelay[2]=1;                                          // Задержка после

//////////////////////////////////Кадр 4////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[3]=100;                                         // Задержка до
  BasicScenarios[1].NumberOfStep[3]=ScenRelayOn;                                // Выключить реле
  //////////////////////////////////////////////////////////////
  //BasicScenarios[1].NumberOfStep[3]=0;                                // Выключить реле
  /////////////////////////////////////////////////////////////
  BasicScenarios[1].   Parametr1[3]=4;                                          // Адрес реле        
  BasicScenarios[1].  AfterDelay[3]=1;                                          // Задержка после
  
//////////////////////////////////Кадр 5////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[4]=100;                                         // Задержка до
  BasicScenarios[1].NumberOfStep[4]=ScenRelayOn;                                // Включить реле
  BasicScenarios[1].   Parametr1[4]=5;                                          // Адрес реле        
  BasicScenarios[1].  AfterDelay[4]=1;                                          // Задержка после

//////////////////////////////////Кадр 6////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[5]=100;                                         // Задержка до
  BasicScenarios[1].NumberOfStep[5]=ScenRelayOn;                                // Выключить реле
  BasicScenarios[1].   Parametr1[5]=6;                                          // Адрес реле        
  BasicScenarios[1].  AfterDelay[5]=1;                                          // Задержка после
  
//////////////////////////////////Кадр 7////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[6]=100;                                         // Задержка до
  BasicScenarios[1].NumberOfStep[6]=ScenRelayOn;                                // Включить реле
  BasicScenarios[1].   Parametr1[6]=7;                                          // Адрес реле        
  BasicScenarios[1].  AfterDelay[6]=1;                                          // Задержка после

//////////////////////////////////Кадр 8////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[7]=100;                                         // Задержка до
  BasicScenarios[1].NumberOfStep[7]=ScenRelayOn;                                // Выключить реле
  BasicScenarios[1].   Parametr1[7]=8;                                          // Адрес реле        
  BasicScenarios[1].  AfterDelay[7]=1;                                          // Задержка после  
  
//////////////////////////////////Кадр 9////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[8]=100;                                          // Задержка до
  BasicScenarios[1].NumberOfStep[8]=ScenRelayOn;                                // Пустое действие
  BasicScenarios[1].   Parametr1[8]=9;                                          // Адрес лампочки        
  BasicScenarios[1].  AfterDelay[8]=0;                                          // Задержка после

//////////////////////////////////Кадр 10////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[9]=100;                                         // Задержка до
  BasicScenarios[1].NumberOfStep[9]=ScenRelayOn;                                // Выключить реле
  BasicScenarios[1].   Parametr1[9]=10;                                         // Адрес реле        
  BasicScenarios[1].  AfterDelay[9]=1;                                          // Задержка после  

//////////////////////////////////Кадр 11////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[10]=100;                                        // Задержка до
  BasicScenarios[1].NumberOfStep[10]=ScenRelayOn;                               // Выключить реле
  BasicScenarios[1].   Parametr1[10]=11;                                        // Адрес реле        
  BasicScenarios[1].  AfterDelay[10]=1;                                         // Задержка после  
  
//////////////////////////////////Кадр 12////////////////////////////////////////  
  BasicScenarios[1]. BeforeDelay[12]=100;                                       // Задержка до
  BasicScenarios[1].NumberOfStep[12]=0;                                         // Пустое действие
  BasicScenarios[1].   Parametr1[12]=1;                                         // Адрес лампочки        
  BasicScenarios[1].  AfterDelay[12]=1;                                         // Задержка после
////////////////////////////////////////////////////////////////////////////////   

////////////////////////////Сценарий выключения света///////////////////////////  
  BasicScenarios[2].Name=MainLightStop;
  
  BasicScenarios[2].Active=false;
  BasicScenarios[2].TimerStep=0;
  BasicScenarios[2].Position=0;
  BasicScenarios[2].Frame=0;
//////////////////////////////////Кадр 1////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[0]=1;                                          // Задержка до
  BasicScenarios[2].NumberOfStep[0]=ScenRelayOff;                               // Включить реле
  BasicScenarios[2].   Parametr1[0]=1;                                          // Адрес реле        
  BasicScenarios[2].  AfterDelay[0]=1;                                          // Задержка после

//////////////////////////////////Кадр 2////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[1]=100;                                         // Задержка до
  BasicScenarios[2].NumberOfStep[1]=ScenRelayOff;                               // Выключить реле
  BasicScenarios[2].   Parametr1[1]=2;                                          // Адрес реле        
  BasicScenarios[2].  AfterDelay[1]=1;                                          // Задержка после
  
//////////////////////////////////Кадр 3////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[2]=100;                                         // Задержка до
  BasicScenarios[2].NumberOfStep[2]=ScenRelayOff;                                // Включить реле
  BasicScenarios[2].   Parametr1[2]=3;                                          // Адрес реле        
  BasicScenarios[2].  AfterDelay[2]=1;                                          // Задержка после

//////////////////////////////////Кадр 4////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[3]=100;                                         // Задержка до
  BasicScenarios[2].NumberOfStep[3]=ScenRelayOff;                               // Выключить реле
  BasicScenarios[2].   Parametr1[3]=4;                                          // Адрес реле        
  BasicScenarios[2].  AfterDelay[3]=1;                                          // Задержка после
  
//////////////////////////////////Кадр 5////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[4]=100;                                         // Задержка до
  BasicScenarios[2].NumberOfStep[4]=ScenRelayOff;                               // Включить реле
  BasicScenarios[2].   Parametr1[4]=5;                                          // Адрес реле        
  BasicScenarios[2].  AfterDelay[4]=1;                                          // Задержка после

//////////////////////////////////Кадр 6////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[5]=100;                                         // Задержка до
  BasicScenarios[2].NumberOfStep[5]=ScenRelayOff;                               // Выключить реле
  BasicScenarios[2].   Parametr1[5]=6;                                          // Адрес реле        
  BasicScenarios[2].  AfterDelay[5]=1;                                          // Задержка после
  
//////////////////////////////////Кадр 7////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[6]=100;                                         // Задержка до
  BasicScenarios[2].NumberOfStep[6]=ScenRelayOff;                                // Включить реле
  BasicScenarios[2].   Parametr1[6]=7;                                          // Адрес реле        
  BasicScenarios[2].  AfterDelay[6]=1;                                          // Задержка после

//////////////////////////////////Кадр 8////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[7]=100;                                         // Задержка до
  BasicScenarios[2].NumberOfStep[7]=ScenRelayOff;                               // Выключить реле
  BasicScenarios[2].   Parametr1[7]=8;                                          // Адрес реле        
  BasicScenarios[2].  AfterDelay[7]=1;                                          // Задержка после  
  
//////////////////////////////////Кадр 9////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[8]=100;                                          // Задержка до
  BasicScenarios[2].NumberOfStep[8]=ScenRelayOff;                               // Пустое действие
  BasicScenarios[2].   Parametr1[8]=9;                                          // Адрес лампочки        
  BasicScenarios[2].  AfterDelay[8]=1;                                          // Задержка после

//////////////////////////////////Кадр 10////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[9]=100;                                         // Задержка до
  BasicScenarios[2].NumberOfStep[9]=ScenRelayOff;                               // Выключить реле
  BasicScenarios[2].   Parametr1[9]=10;                                         // Адрес реле        
  BasicScenarios[2].  AfterDelay[9]=1;                                          // Задержка после  

//////////////////////////////////Кадр 11////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[10]=100;                                        // Задержка до
  BasicScenarios[2].NumberOfStep[10]=ScenRelayOff;                              // Выключить реле
  BasicScenarios[2].   Parametr1[10]=11;                                        // Адрес реле        
  BasicScenarios[2].  AfterDelay[10]=1;                                         // Задержка после  
  
//////////////////////////////////Кадр 12////////////////////////////////////////  
  BasicScenarios[2]. BeforeDelay[12]=1;                                         // Задержка до
  BasicScenarios[2].NumberOfStep[12]=0;                                         // Пустое действие
  BasicScenarios[2].   Parametr1[12]=0;                                         // Адрес лампочки        
  BasicScenarios[2].  AfterDelay[12]=0;                                         // Задержка после
//////////////////////////////////////////////////////////////////////////////// 
  
  
#endif
  
}

void ScenarioAction(void)
{
if(ScenarioTimerMainCount==0)
  {
  for(int i=0;i<BasicScenariosCount;i++)                                        // Пробегаемся по базовым сценариям
    {
    if(BasicScenarios[i].Active==true)                                          // Если сценарий активен
      {
      switch (BasicScenarios[i].Position)                                       // Проверяем позицию в кадре сценария                      
        {
        case 0:                                                                 // Выполняется начальная задержка
          {
          if(BasicScenarios[i].TimerStep>0)                                     // Если счетчик задержки еще тикает
            {BasicScenarios[i].TimerStep--;}                                    // Убавить счетчик на шаг
          else                                                                  // Если нет
            {BasicScenarios[i].Position=1;};                                    // Выставить позицию выполнения команды
          break;
          } 
        case 1:                                                                 // Выполняется команда
          {

////////////////////////////////////////////////////////////////////////////////
          DoIT(BasicScenarios[i].NumberOfStep[BasicScenarios[i].Frame], BasicScenarios[i].Parametr1[BasicScenarios[i].Frame]);  
////////////////////////////////////////////////////////////////////////////////            
          BasicScenarios[i].Position=2;                                         // Выставить позицию выполнения задержки после команды
          BasicScenarios[i].TimerStep=BasicScenarios[i].AfterDelay[BasicScenarios[i].Frame];// Задать значение задержки после действия, соответствующее текущему кадру
          break;
          }
        case 2:                                                                 // Выполняется конечная задержка
          { 
          if(BasicScenarios[i].TimerStep>0)                                     // Если таймер задержки еще тикает
            {BasicScenarios[i].TimerStep--;}                                    // Убавить значение таймера
          else
            {
            BasicScenarios[i].Frame++;                                          // Перейти к следующему кадру
            if(BasicScenarios[i].NumberOfStep[BasicScenarios[i].Frame]>0)       // Если действие в следующем кадре не нулевое
              {
              BasicScenarios[i].TimerStep=BasicScenarios[i].AfterDelay[BasicScenarios[i].Frame];
              }
            else                                                                // Иначе
              {
              BasicScenarios[i].Active=false;                                   // Останавливаем сценарий
              BasicScenarios[i].TimerStep=BasicScenarios[i].BeforeDelay[BasicScenarios[i].Frame];     // Выставляем таймер для последующего пуска сценария
              BasicScenarios[i].Frame=0;                                        // Выставляем стартовый кадр
              };
            BasicScenarios[i].Position=0;
            };
          break;
          };    
        };        
      };
    };
  ScenarioTimerMainCount=ScenarioTimerMax; 
  };
}
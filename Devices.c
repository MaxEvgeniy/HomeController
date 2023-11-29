#include "Devices.h"
#include "cmsis_os2.h"
#include "stm32f1xx_hal.h"

uint8_t DelayForButtons=2;                                                      // Пауза опроса кнопки для подавления дребезга
uint8_t State1;                                                                 // Первое состояние кнопки
uint8_t State2;                                                                 // Второе состояние кнопки

void LedOn (Led LedLamp)                                                        
{
HAL_GPIO_WritePin(LedLamp.Port,LedLamp.Pin,GPIO_PIN_SET);                       
};

void LedOff (Led LedLamp)                                                       
{
HAL_GPIO_WritePin(LedLamp.Port,LedLamp.Pin,GPIO_PIN_RESET);                       
};

void LedToggle (Led LedLamp)                                                    
{
HAL_GPIO_TogglePin(LedLamp.Port,LedLamp.Pin);                       
};

uint8_t ReadButton (Button ButKey)                                              // Считать кнопку
{
uint8_t ResState;                                                               // Первое состояние, второе состояние, результирующее состояние 

ResState=ButtonIsNoPress;

if(HAL_GPIO_ReadPin(ButKey.Port,ButKey.Pin)==GPIO_PIN_SET)                      // Если пин активен
  {State1=ButtonIsPress;}                                                       // Состояние кнонки "нажата"
  else
  {State1=ButtonIsNoPress;};                                                    // Состояние кнопки "не нажата"

   osDelay(DelayForButtons);                                                    // Задержка для подавления дребезга
   
if(HAL_GPIO_ReadPin(ButKey.Port,ButKey.Pin)==GPIO_PIN_SET)                     // Если пин активен
  {State2=ButtonIsPress;
    osDelay(1); 
  }                                                       // Состояние кнонки "нажата"
  else
  {State2=ButtonIsNoPress;};                                                    // Состояние кнопки "не нажата"
 
if(State1==ButtonIsPress && State2==ButtonIsPress){ResState=ButtonIsPress;}   
   
return ResState;
};

void RelayOn (Relay RelaySwitch)                                                        
{
//HAL_GPIO_WritePin(RelaySwitch.Port,RelaySwitch.Pin,GPIO_PIN_SET);  
HAL_GPIO_WritePin(RelaySwitch.Port,RelaySwitch.Pin,GPIO_PIN_RESET);  
};

void RelayOff (Relay RelaySwitch)                                                       
{
//HAL_GPIO_WritePin(RelaySwitch.Port,RelaySwitch.Pin,GPIO_PIN_RESET);  
HAL_GPIO_WritePin(RelaySwitch.Port,RelaySwitch.Pin,GPIO_PIN_SET);  
};

void RelayToggle (Relay RelaySwitch)                                                    
{
HAL_GPIO_TogglePin(RelaySwitch.Port,RelaySwitch.Pin);                       
};

bool ReadMovingSensor (MovingSensor MovSensor)
{
bool ResState=false;                                                            // Результирующее состояние 
if(HAL_GPIO_ReadPin(MovSensor.Port,MovSensor.Pin)==GPIO_PIN_SET)                // Если пин активен
  {ResState=true;};                                                             // Состояние кнонки "нажата"
return ResState;
};

bool ReadProximitySensor (ProximitySensor ProxSensor)                           // Считать датчик приближения
{
bool ResState=false;                                                            // Результирующее состояние 
if(HAL_GPIO_ReadPin(ProxSensor.Port,ProxSensor.Pin)==GPIO_PIN_SET)              // Если пин активен
  {ResState=true;};                                                             // Состояние кнонки "нажата"
return ResState;
};
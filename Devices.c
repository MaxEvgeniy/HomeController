#include "Devices.h"
#include "cmsis_os2.h"
#include "stm32f1xx_hal.h"

uint8_t DelayForButtons=2;                                                      // ����� ������ ������ ��� ���������� ��������
uint8_t State1;                                                                 // ������ ��������� ������
uint8_t State2;                                                                 // ������ ��������� ������

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

uint8_t ReadButton (Button ButKey)                                              // ������� ������
{
uint8_t ResState;                                                               // ������ ���������, ������ ���������, �������������� ��������� 

ResState=ButtonIsNoPress;

if(HAL_GPIO_ReadPin(ButKey.Port,ButKey.Pin)==GPIO_PIN_SET)                      // ���� ��� �������
  {State1=ButtonIsPress;}                                                       // ��������� ������ "������"
  else
  {State1=ButtonIsNoPress;};                                                    // ��������� ������ "�� ������"

   osDelay(DelayForButtons);                                                    // �������� ��� ���������� ��������
   
if(HAL_GPIO_ReadPin(ButKey.Port,ButKey.Pin)==GPIO_PIN_SET)                     // ���� ��� �������
  {State2=ButtonIsPress;
    osDelay(1); 
  }                                                       // ��������� ������ "������"
  else
  {State2=ButtonIsNoPress;};                                                    // ��������� ������ "�� ������"
 
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
bool ResState=false;                                                            // �������������� ��������� 
if(HAL_GPIO_ReadPin(MovSensor.Port,MovSensor.Pin)==GPIO_PIN_SET)                // ���� ��� �������
  {ResState=true;};                                                             // ��������� ������ "������"
return ResState;
};

bool ReadProximitySensor (ProximitySensor ProxSensor)                           // ������� ������ �����������
{
bool ResState=false;                                                            // �������������� ��������� 
if(HAL_GPIO_ReadPin(ProxSensor.Port,ProxSensor.Pin)==GPIO_PIN_SET)              // ���� ��� �������
  {ResState=true;};                                                             // ��������� ������ "������"
return ResState;
};
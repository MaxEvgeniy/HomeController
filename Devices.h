#ifndef DEVICES_H
#define DEVICES_H

#include "main.h"
#include "stdint.h"    
#include "stdbool.h"

#include "TasksForAll.h"

////////////////////////////////////�������� �����//////////////////////////////////
typedef struct                                                                  // �������� ����� � ������
{
uint8_t Address;                                                                // ����� �����  (������ ���� ��������)
uint8_t Name;                                                                   // ��� ����� (����� �����������)
uint8_t State;                                                                  // C�������� �����
}Board;

enum BoardStates                                                                // ������ ��������� �����
{
BoardOnLine=0x01,                                                               // ����� � ����, �������� ���������
BoardStateUnknown,                                                              // ��������� ����� �� �����������
BoardOffLine,                                                                   // ����� ���������
BoardInAlarm,                                                                   // ����� � ��������� �������
BoardError                                                                      // ����� � ��������� ������
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////����������//////////////////////////////////
typedef struct                                                                  // �������� ����������
{
uint8_t Address;                                                                // ����� ��������
uint16_t Pin;                                                                   // ��� ��������
GPIO_TypeDef* Port;                                                             // ���� ��������
}Led;

enum LedStates                                                                  // ������ ��������� ����������
{
LedIsOn=0x01,                                                                   // ��������� �������
LedIsOff,                                                                       // ��������� ��������
LedUnknown                                                                      // ��������� ���������� ����������
};

void LedOn (Led LedLamp);                                                        // �������� ���������
void LedOff (Led LedLamp);                                                       // ��������� ���������
void LedToggle (Led LedLamp);                                                    // ����������� ���������
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////������//////////////////////////////////////
typedef struct                                                                  // �������� ������
{
uint8_t Address;                                                                // ����� ������
uint16_t Pin;                                                                   // ��� ������
GPIO_TypeDef* Port;                                                             // ���� ������
uint8_t State;                                                                  // ��������� ������
uint16_t HotPointTime;                                                          // ������� ������� �� ����������� �����
uint8_t HotPoint;                                                               // ������� ���������� ����������� �����
bool FirstPointState;                                                           // ��������� ������ ��� ����������� ������ ����������� �����
bool SecondPointState;                                                          // ��������� ������ ��� ����������� ������ ����������� �����
bool FinalPointState;                                                           // ��������� ������ ��� ����������� ��������� ����������� �����
uint8_t Result;                                                                 // �������������� ��������� ������

uint8_t ShortClickScenario;                                                     // ����� �������� �� ��������� �������  
uint8_t ButtonLongPressScenario;                                                // ����� �������� �� �������� ������� 
uint8_t DoubleClickScenario;                                                    // ����� �������� �� �������� ������� 
uint8_t ButtonHoldScenari;                                                      // ����� �������� �� ��������� 
}Button;

enum ButtonStates                                                               // ������ ��������� ������
{
ButtonIsPress=0x01,                                                             // ������ ������
ButtonIsNoPress,                                                                // ������ �� ������
};

enum ButtonResults                                                              // ������ �������������� ��������� ������
{
ButtonUp=0x01,                                                                  // ������ �� ����������                        
ButtonShortClick,                                                               // �������� �������
ButtonLongPress,                                                                // ������� �������
ButtonDoubleClick,                                                              // ������� �������
ButtonHold,                                                                     // �����������
};

uint8_t ReadButton (Button ButKey);                                             // ������� ������
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////����////////////////////////////////////////
typedef struct                                                                  // �������� ����
{
uint8_t Address;                                                                // ����� ����
uint16_t Pin;                                                                   // ��� ����
GPIO_TypeDef* Port;                                                             // ���� ����
uint8_t State;                                                                  // ��������� ����
}Relay;

enum RelayStates                                                                // ������ ��������� ������
{
RelayDisabled=0x01,                                                             // ���� ����������
RelayEnabled,                                                                   // ���� ��������
};

void RelayOn (Relay RelaySwitch);                                               // �������� ����
void RelayOff (Relay RelaySwitch);                                              // ���������� ����
void RelayToggle (Relay RelaySwitch);                                           // ����������� ����
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////������ ��������/////////////////////////////
typedef struct                                                                  // �������� ������� ��������
{
uint8_t Address;                                                                // ����� ������� ��������
uint16_t Pin;                                                                   // ��� ������� ��������
GPIO_TypeDef* Port;                                                             // ���� ������� ��������
}MovingSensor;

bool ReadMovingSensor (MovingSensor MovSensor);                                 // ������� ������ ��������
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////������ �����������/////////////////////////////
typedef struct                                                                  // �������� ������� �����������
{
uint8_t Address;                                                                // ����� ������� �����������
uint16_t Pin;                                                                   // ��� ������� �����������
GPIO_TypeDef* Port;                                                             // ���� ������� �����������
}ProximitySensor;

bool ReadProximitySensor (ProximitySensor ProxSensor);                          // ������� ������ �����������
////////////////////////////////////////////////////////////////////////////////

#endif

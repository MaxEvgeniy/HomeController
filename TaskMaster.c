#include "TaskMaster.h"
#include "TasksForAll.h"
#include "Devices.h"
#include "main.h"


extern Led Leds[4];

extern uint8_t MessageToTransmit[16];  
extern uint16_t Timer2Ticks;   
extern uint16_t Timer2TicksOLD;   
extern uint8_t MessageToTransmitStatus;

extern bool MessageInBox;                                                        // ”казатель на полученное сообщение
extern Board Boards[2];

void TaskMasterInit (void)
{ 

Leds[0].Address=1;  
Leds[0].Pin=Led1_Pin;
Leds[0].Port=Led1_GPIO_Port; 

Leds[1].Address=2;  
Leds[1].Pin=Led2_Pin;
Leds[1].Port=Led2_GPIO_Port; 

Leds[2].Address=3;  
Leds[2].Pin=Led3_Pin;
Leds[2].Port=Led3_GPIO_Port; 

Leds[3].Address=4;  
Leds[3].Pin=Led4_Pin;
Leds[3].Port=Led4_GPIO_Port; 

LedOff(Leds[0]);
LedOff(Leds[1]);
LedOff(Leds[2]);
LedOff(Leds[3]);

////////////////////////////////////////////////////////////////////////////////
BME280_Init();
////////////////////////////////////////////////////////////////////////////////

}

void TaskMasterDrive (void)
{ 
////////////////////////////////////////////////////////////////////////////////  
//if (Boards[0].State==BoardOnLine){LedOn(Leds[0]);}else{LedOff(Leds[0]);};
//if (Boards[1].State==BoardOnLine){LedOn(Leds[1]);}else{LedOff(Leds[1]);};
//if (Boards[2].State==BoardOnLine){LedOn(Leds[2]);}else{LedOff(Leds[2]);};
////////////////////////////////////////////////////////////////////////////////
  
//////////////////////////////////////////////////////////////////////////////// 
/*
if (Timer2Ticks==0 && MessageToTransmitStatus==NoMessage)  
  {  
  Timer2Ticks=Timer2TicksMax;  
  CommandConstructor (NetMaster,TaskMaster,InformationGroup,NoAnswer,0,0,0,0,0,0,0,0,0,0,0,0);// ќтвет: нет исход¤щих сообщений
  ////////////////////////////////////////////////////////////////////////////////
  LedToggle(Leds[2]);  
////////////////////////////////////////////////////////////////////////////////
  };
*/  

}
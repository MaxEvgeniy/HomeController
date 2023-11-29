#include "NetMaster.h"
#include "TasksForAll.h"
#include "Devices.h"
#include "main.h"

extern uint8_t MessageToTransmit[16];  
extern uint16_t Timer2Ticks; 
extern uint8_t MessageToTransmitStatus;
extern Led Leds[1];
extern Board Boards[2];
extern uint8_t BoardsCount; 

uint8_t QueueCount=0;                                                           // —четчик опрошенных плат        

void NetMasterInit(void)
{ 
Leds[0].Address=1;  
Leds[0].Pin=Led1_Pin;
Leds[0].Port=Led1_GPIO_Port; 

LedOff(Leds[0]);
Timer2Ticks=1;
}

void NetMasterDrive(void)
{ 
if (Timer2Ticks==0 && MessageToTransmitStatus==NoMessage)  
  {  
  Timer2Ticks=Timer2TicksMax;
  QueueCount++;
  //if (QueueCount>=BoardsCount-1){QueueCount=0;};  
  if (QueueCount>=BoardsCount-1){QueueCount=0;};  
  if (QueueCount==0)
    {
    CommandConstructor(NetMaster,TaskMaster,AsksGroup,IsHaveMessage,0,0,0,0,0,0,0,0,0,0,0,0);
    };  
  if (QueueCount==1)
    {
    CommandConstructor(NetMaster,BathLighter,AsksGroup,IsHaveMessage,0,0,0,0,0,0,0,0,0,0,0,0);
    }; 
  if (QueueCount==2)
    {
    CommandConstructor(NetMaster,RooomRooom,AsksGroup,IsHaveMessage,0,0,0,0,0,0,0,0,0,0,0,0);
    }; 
  };  
}
#include "BathLighter.h"
#include "TasksForAll.h"
#include "Scenarios.h"
#include "main.h"

extern uint8_t MyName;

extern Button Buttons[4];                                                       // ������ ������
extern uint8_t ButtonsCount;                                                    // ���������� ����������� �� ����� 

extern Led Leds[1];                                                             // ������ �����������
extern Relay Relays[8];                                                         // ������ ����
extern MovingSensor MovingSensors[1];                                           // ������ �������� ��������
extern ProximitySensor ProximitySensors[2];                                     // ������ �������� ��������
extern Scenario BasicScenarios[10];                                             // �������� ����� ���������

uint8_t BathMainCountMax=100;                                                   // ������������ �������� ��������� ������� ��� ������ BathLighter (��� �������� � �������)
uint8_t BathMainCount=100;                                                      // �������� ������ ��� ������ BathLighter
uint8_t BathMainCountOLD=0;                                                     // ������ �������� ��������� ������� ��� ������ BathLighter

uint16_t MainLightTimerCount=0;                                                 // ������� ������� ������ ��������� ��������� � ��������
uint16_t MainLightTimerMax=1800;                                                // ������������ �������� �������� ������� ������ ��������� ��������� � ��������

uint16_t BigVentTimerCount=0;                                                   // ������� ������� ������ ������� ������� � ��������
uint16_t BigVentTimerMax=1800;                                                  // ������������ �������� �������� ������� ������ ������� ������� � ��������

uint16_t BoxLightTimerCount=0;                                                  // ������� ������� ������ ��������� � ������ � ��������
uint16_t BoxLightTimerMax=600;                                                  // ������������ �������� �������� ������� ������ ��������� � ������ � ��������

uint16_t MirrorLightTimerCount=0;                                               // ������� ������� ������ ��������� ������� � ��������
uint16_t MirrorLightTimerMax=1200;                                              // ������������ �������� �������� ������� ������ ��������� ������� � ��������

bool MainLightIndicator=false;                                                  // ������ �������� ���� ������� ��� ���
bool BoxLightIndicator=false;                                                   // ������ ���� � ������ ������� ��� ���
bool VentIndicator=false;                                                       // ������ ��������� �������� ��� ���
bool MirrorLightIndicator=false;                                                // ������ ��������� �������

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
////////////////////////////������ 1//////////////////////////////////////////// 
switch (Buttons[0].Result)                                                      // �������� ��������� ������                     
  {
  case ButtonShortClick:                                                        // �������� �������
    {
      if(BasicScenarios[0].Active==false){BasicScenarios[0].Active=true;};
      /*
    if(MainLightIndicator==false)                                               // ���� �������� ���� ��������
      {MainLightOn();}                                                          // �������� �������� ���� 
    else
      {MainLightOff();};                                                        // ��������� �������� ����
      */
    ButtonsReset(0);                                                            // �������� ��������� ������
    break;
    } 
  case ButtonLongPress:                                                         // ������� ������� 
    {
     if(BasicScenarios[0].Active==false){BasicScenarios[0].Active=true;};
      /*
    if(MainLightIndicator==false)                                                      // ���� �������� ���� ��������
      {MainLightOn();}                                                          // �������� �������� ���� 
    else
      {MainLightOff();};                                                        // ��������� �������� ����
      */
      ButtonsReset(0);                                                          // �������� ��������� ������
    break;
    }  
  case ButtonDoubleClick:                                                       // ������� �������
    {
     /* 
    if(VentIndicator==false)                                                           // ���� ������� ���������
      {VentOn();}                                                               // �������� �������
    else
      {VentOff();};                                                             // ��������� �������
*/
    ButtonsReset(0);                                                            // �������� ��������� ������
    break;
    }  
  case ButtonHold:                                                              // ��������� 
    {
    ButtonsReset(0);                                                            // �������� ��������� ������ 
    break;      
    } 
  default:                                                              
    {
                 //������ ����������;
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
if (BathMainCountOLD!=BathMainCount)                                            // ���� ������ �������� �������� �� ��������� � ����� 
  {  
  if (BathMainCount<=0)                                                         // ���� �������� ������� ���������- 
    {
    BathMainCount=BathMainCountMax;                                             // ��������� ������  
    
    if(MainLightTimerCount>0)                                                   // ���� ������� ������� ��������� ����� �������
      {
      MainLightTimerCount--;                                                    // ������� ��������
      if(MainLightTimerCount==0){MainLightOff();};                              // ���� ������ ������� � ����� ��������� ����
      };
    
    if(BigVentTimerCount>0)                                                     // ���� ������� ������� ������� ������� �������
      {
      BigVentTimerCount--;                                                      // ������� ��������
      if(BigVentTimerCount==0){VentOff();};                                     // ���� ������ ������� � ����� ��������� ������� �������     
      };
    
    if(BoxLightTimerCount>0)                                                    // ���� ������� ������� ����� � ������ �������
      {
      BoxLightTimerCount--;                                                     // ������� ��������
      if(BoxLightTimerCount==0){BoxLightOff();};                                // ���� ������ ������� � ����� ��������� ��������� ������      
      };
    
    if(MirrorLightTimerCount>0)                                                 // ���� ������� ������� ��������� ������� �������
      {
      MirrorLightTimerCount--;                                                  // ������� ��������
      if(MirrorLightTimerCount==0){MirrorLightOff();};                          // ���� ������ ������� � ����� ��������� ��������� ������� 
      }; 
    };
  
  BathMainCountOLD=BathMainCount;                                               // ����������� ������ � ����� ��������
  };
};

void MainLightOn (void)
{
LedOn(Leds[0]); 
/*  
MainLightTimerCount=MainLightTimerMax;                                          // ������ ������� ��������� ��������� �����
MainLightIndicator=true;                                                        // ������ ������, ��� ���� �������
RelayOn(Relays[0]);                                                             // �������� ���� 1
osDelay(200);                                                                   // �������� ��� ������ �������
RelayOn(Relays[1]);                                                             // �������� ���� 2
osDelay(200);                                                                   // �������� ��� ������ �������
RelayOn(Relays[2]);                                                             // �������� ���� 3
 */
}

void MainLightOff (void)
{
LedOff(Leds[0]);
/*
MainLightTimerCount=0;                                                          // ���� ������� ��������� ��������� �����
MainLightIndicator=false;                                                       // ������ ������, ��� ���� ��������  
RelayOff(Relays[0]);                                                            // ��������� ���� 1
RelayOff(Relays[1]);                                                            // ��������� ���� 2
RelayOff(Relays[2]);                                                            // ��������� ���� 3
*/
}

void VentOn (void)
{
BigVentTimerCount=BigVentTimerMax;                                              // ������ ������� ��������� �������
VentIndicator=true;                                                             // ������ ������, ��� ��������� ��������
RelayOn(Relays[3]);                                                             // �������� ���� 4
}

void VentOff (void)
{
BigVentTimerCount=0;                                                            // ���� ������� ��������� �������
VentIndicator=false;                                                            // ������ ������, ��� ��������� ���������
RelayOff(Relays[3]);                                                            // ��������� ���� 4
}

void BoxLightOn (void)
{
BoxLightTimerCount=BoxLightTimerMax;                                            // ������ ������� ��������� ��������� ������
BoxLightIndicator=true;                                                         // ������ ������, ��� ��������� ��������
RelayOn(Relays[4]);                                                             // �������� ���� 5
}

void BoxLightOff (void)
{
BoxLightTimerCount=0;                                                           // ���� ������� ��������� ��������� ������
BoxLightIndicator=false;                                                        // ������ ������, ��� ��������� ���������
RelayOff(Relays[4]);                                                            // ��������� ���� 5
}

void MirrorLightOn (void)
{
MirrorLightTimerCount=MirrorLightTimerMax;                                      // ������ ������� ��������� ��������� �������
MirrorLightIndicator=true;                                                      // ������ ������, ��� ��������� ��������
RelayOn(Relays[5]);                                                             // �������� ���� 6
}

void MirrorLightOff (void)
{
MirrorLightTimerCount=0;                                                        // ���� ������� ��������� ��������� �������
MirrorLightIndicator=false;                                                     // ������ ������, ��� ��������� ���������
RelayOff(Relays[5]);                                                            // ��������� ���� 6
}

void RunIndividualComands (uint8_t Command,uint8_t Parametr2,uint8_t Parametr3,uint8_t Parametr4,uint8_t Parametr5,uint8_t Parametr6,uint8_t Parametr7)// ��������� �������������� ������
{
switch (Command)                                                                // ��������� �������                       
    {
    case CommandLightOn:                                                        // ������� ��������� �����
      {
      MainLightOn();  
      break;
      }
    case CommandLightOff:                                                        // ������� ���������� �����
      {
      MainLightOff(); 
      break;
      } 
    case CommandVentOn:                                                        // ������� ��������� �����
      {
      VentOn();
      break;
      }
    case CommandVentOff:                                                        // ������� ���������� �����
      {
      VentOn(); 
      break;
      }       
    default:                                                                    // ���� ������� �� ������ �� � ���� �� �����
      {
      //������ ����������
      };
    }; 
};
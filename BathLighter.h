#ifndef BATHLIGHTER_H
#define BATHLIGHTER_H
#include "Devices.h"

enum BoardsComandsIndividual                                                    // ������� ������ ��� ���� �����
{
CommandLightOn=0x01,                                                            // ������� �� ��������� �����
CommandLightOff,                                                                // ������� �� ���������� �����
CommandVentOn,                                                                  // ������� �� ��������� �������
CommandVentOff                                                                  // ������� �� ���������� �������
};

enum BoardsComandsIndividuaAnswers                                              // ���������� ���������� �������������� ������
{
CommandExecuted=0x01,                                                           // ������� ���������
CommandNotExecuted,                                                             // ������� �� ���������
CommandError,                                                                   // ������ ���������� �������
};

void BathLighterInit(void);
void BathLighterDrive(void);
void ButtonsCheck (void);                                                       // �������� ��������� ������ � �������� ��� ����������� �������
void LightDrive (void);                                                         // ���������� ������    
void BathLighterReadSensors(void);                                              // ��� ���������� ������ ������ ������ � ��������
void MainLightOn (void);
void MainLightOff (void);
void BoxLightOn (void);                                                         // �������� ���� � ������
void BoxLightOff (void);                                                        // ��������� ���� � ������
void MirrorLightOn (void);                                                      // �������� ��������� �������
void MirrorLightOff (void);                                                     // ��������� ��������� �������
void VentOn (void);
void VentOff (void);
void RunIndividualComands (uint8_t Parametr1,uint8_t Parametr2,uint8_t Parametr3,uint8_t Parametr4,uint8_t Parametr5,uint8_t Parametr6,uint8_t Parametr7);// ��������� �������������� ������

#endif

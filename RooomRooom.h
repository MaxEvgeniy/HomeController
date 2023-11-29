#ifndef ROOOMROOOM_H
#define ROOOMROOOM_H
#include "Devices.h"

void RooomRooomInit (void);
void RooomRooomDrive (void);
void RooomRooomReadSensors(void);
void LightDrive (void);                                                         // Управлялка светом    
void MainLightOn (void);                                                        // Включение света
void MainLightOff (void);                                                       // Выключение света
void ButtonsCheck (void);                                                       // Проверка состояний кнопок и действие при регистрации нажатия
#endif
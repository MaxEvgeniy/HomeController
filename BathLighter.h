#ifndef BATHLIGHTER_H
#define BATHLIGHTER_H
#include "Devices.h"

enum BoardsComandsIndividual                                                    // Команды только для этой платы
{
CommandLightOn=0x01,                                                            // Команда на включение света
CommandLightOff,                                                                // Команда на выключение света
CommandVentOn,                                                                  // Команда на включение вытяжки
CommandVentOff                                                                  // Команда на выключение вытяжки
};

enum BoardsComandsIndividuaAnswers                                              // Результаты выполнения индивидуальных команд
{
CommandExecuted=0x01,                                                           // Команда выполнена
CommandNotExecuted,                                                             // Команда не выполнена
CommandError,                                                                   // Ошибка выполнения команды
};

void BathLighterInit(void);
void BathLighterDrive(void);
void ButtonsCheck (void);                                                       // Проверка состояний кнопок и действие при регистрации нажатия
void LightDrive (void);                                                         // Управлялка светом    
void BathLighterReadSensors(void);                                              // Для выполнения задачи чтения кнопок и датчиков
void MainLightOn (void);
void MainLightOff (void);
void BoxLightOn (void);                                                         // Включить свет в коробе
void BoxLightOff (void);                                                        // Выключить свет в коробе
void MirrorLightOn (void);                                                      // Включить подсветку зеркала
void MirrorLightOff (void);                                                     // Выключить подсветку зеркала
void VentOn (void);
void VentOff (void);
void RunIndividualComands (uint8_t Parametr1,uint8_t Parametr2,uint8_t Parametr3,uint8_t Parametr4,uint8_t Parametr5,uint8_t Parametr6,uint8_t Parametr7);// Обработка индивидуальных команд

#endif

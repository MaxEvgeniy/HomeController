#ifndef TASKSFORALL_H/*ИМЯ ЗАГОЛОВОЧНОГО ФАЙЛА_H*/
#define TASKSFORALL_H/*ИМЯ ЗАГОЛОВОЧНОГО ФАЙЛА_H*/

#include "stdint.h"    
#include "stdbool.h"
#include "Devices.h"

//#define NetMasterBoard                                                        // Администратор сети
//#define TaskMasterBoard                                                       // Связь с компом        
#define BathLighterBoard                                                      // Управление светом в ванной
//#define RooomRooomBoard                                                         // Управление светом в комнате

#define ReceiverOn HAL_GPIO_WritePin(ReceiverOn_GPIO_Port, ReceiverOn_Pin, GPIO_PIN_SET);// Вкл передатчика
#define ReceiverOff HAL_GPIO_WritePin(ReceiverOn_GPIO_Port, ReceiverOn_Pin, GPIO_PIN_RESET);// Выкл передатчика

enum NamesOfBoards
{
NetMaster=0x01,                                                                 // Администратор сети
TaskMaster,                                                                     // Рассылатель задач, связанный с компом
BathLighter,                                                                    // Управление светом в ванной
RooomRooom                                                                      // Управление светом в комнате
};

enum MessageToTransmitState                                                     // Статусы сообщения для передачи
{
NoMessage=0x01,                                                                 // Нет сообщений
MessageReady,                                                                   // Сообщение готово к передаче
MessageInTransmit                                                               // Сообщение передается
};

enum ComandsGroups                                                              // Перечень групп комманд
{
InformationGroup=0x01,                                                          // Группа информационных команд
AsksGroup,                                                                      // Группа вопросов
BoardsGroup,                                                                    // Группа команд для платы
LedsGroup,                                                                       // Группа команд для светодиодов
RelaysGroup                                                                     // Группа команд для светодиодов
};

enum InformationComandsGroup                                                    // Команды информационной группы
{
NoAnswer=0x01,                                                                  // Ответ "Нет сообщений"
YesAnswer,                                                                      // Ответ какой то еще
Equipment1Answer,                                                               // Список подключенного оборудования
};

enum AsksComandsGroup                                                           // Команды вопросной группы. Требуют ответа.
{
IsHaveMessage=0x01,                                                             // Вопрос "Есть ли сообщения"
Equipment1,                                                                     // Запрос информации о подключенном оборудовании часть 1
};

enum LedsComandsGroup                                                           // Команды для светодиодов
{
CommandLedOff=0x01,                                                             // Выключить светодиод
CommandLedOn,                                                                   // Включить светодиод
CommandLedToggle,                                                               // Переключить светодиод        
CommandLedState                                                                 // Спросить про состояние светодиода
};

enum RelaysComandsGroup                                                         // Команды для светодиодов
{
CommandRelayOff=0x01,                                                             // Выключить светодиод
CommandRelayOn,                                                                   // Включить светодиод
CommandRelayToggle,                                                               // Переключить светодиод        
CommandRelayState                                                                 // Спросить про состояние светодиода
};

enum BoardsComandsGroup                                                         // Команды для светодиодов
{
CommandBoardReset=0x01,                                                         // Команда на перезагрузку платы
CommandSetDateTime,                                                             // Команда на корректировку даты и времени на плате
CommandIndividual                                                               // Команда, принадлежащая конкретной плате
};

enum ScenarioTriggersType                                                       // Список возможных триггеров для сценария
{
TriggerButton=0x01,                                                             // Кнопка
TriggerMovingSensor,                                                            // Датчик движения
};

void Initialization (void);
void Drive(void);
void SendMessage(void);                                                         // Отправка сообщения                
void Listen(void);                                                              // Прослушивание сети
void DecodeMessage(uint8_t Message[16]);                                        // Декодирование сообщения
void CommandConstructor (uint8_t Author,uint8_t Correspondent,uint8_t GroupOfCommand,uint8_t Command,
                         uint8_t Parametr1,uint8_t Parametr2,uint8_t Parametr3,uint8_t Parametr4,
                         uint8_t Parametr5,uint8_t Parametr6,uint8_t Parametr7,uint8_t Parametr8,
                         uint8_t Parametr9,uint8_t Parametr10,uint8_t Parametr11,uint8_t Parametr12);// Конструктор сообщений
void Communication(void);                                                       // Для обмена сообщениями по сети
void TransmitFromUSB(void);                                     // Для передачи данных по USB
void ProcessIncomUSBMessage (void);                                             // Обработка сообщений, принятых по USB
void ReadSensors(void);                                                         // Чтение датчиков                         
void AskSolver (uint8_t Correspondent,uint8_t Question);                        // Отвечайка на вопросы 
void SetDateTime(uint8_t Hours,uint8_t Minutes,uint8_t Seconds,uint8_t WeekDay,uint8_t Month,uint8_t Date,uint8_t Year);// Установка даты и времени
void BoardTweaker (uint8_t Command,uint8_t Parametr1,uint8_t Parametr2,uint8_t Parametr3,uint8_t Parametr4,
                   uint8_t Parametr5,uint8_t Parametr6,uint8_t Parametr7,uint8_t Parametr8,
                   uint8_t Parametr9,uint8_t Parametr10,uint8_t Parametr11,uint8_t Parametr12);// Настройка параметров платы по команде
void LedsDrive(uint8_t CommandForLed,uint8_t Address);                          // Управление светодиодами
void RelaysDrive(uint8_t CommandForRelay,uint8_t Address);                        // Управление реле
void ButtonsListen (void);                                                      // Слушалка для кнопок
void ButtonsReset(uint8_t NumderOfButton);                                      // Сброс кнопки после регистрации нажатия
void DoIT(uint8_t NumOfAction, uint8_t Param1);                                 // Процедура расшифровки сценарного действия по коду

extern bool MessageUSBCome;                                                     // Индикатор наличия новых входящих сообщений от USB

#endif


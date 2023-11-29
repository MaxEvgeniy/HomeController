#include "TasksForAll.h"
#include "Scenarios.h"
#include "cmsis_os2.h"
#include "usb_device.h"
#include "usbd_customhid.h"

////////////////////////////////////////////////////////////////////////////////
#include "BME280.h"
////////////////////////////////////////////////////////////////////////////////

#ifdef NetMasterBoard
#include "NetMaster.h"
uint8_t MyName = NetMaster;
Led Leds[1]; // Массив диодов
uint8_t LedsCount = 0; // Количество светодиодов на плате
Button Buttons[1]; // Массив кнопок
uint8_t ButtonsCount = 0; // Количество светодиодов на плате
Relay Relays[1]; // Массив реле
uint8_t RelaysCount = 0; // Количество реле, подключенных к плате
MovingSensor MovingSensors[1]; // Массив датчиков движения
uint8_t MovingSensorsCount = 0; // Количество датчиков движения, подключенных к плате
ProximitySensor ProximitySensors[1]; // Массив датчиков приближения
uint8_t ProximitySensorsCount = 0; // Количество датчиков приближения, подключенных к плате
#endif

#ifdef TaskMasterBoard
#include "TaskMaster.h"
uint8_t MyName = TaskMaster;
Led Leds[4]; // Массив диодов
uint8_t LedsCount = 4; // Количество светодиодов на плате
Button Buttons[1]; // Массив кнопок
uint8_t ButtonsCount = 0; // Количество светодиодов на плате
Relay Relays[1]; // Массив реле
uint8_t RelaysCount = 0; // Количество реле, подключенных к плате
MovingSensor MovingSensors[1]; // Массив датчиков движения
uint8_t MovingSensorsCount = 0; // Количество датчиков движения, подключенных к плате
ProximitySensor ProximitySensors[1]; // Массив датчиков приближения
uint8_t ProximitySensorsCount = 0; // Количество датчиков приближения, подключенных к плате
#endif

#ifdef BathLighterBoard
#include "BathLighter.h"
uint8_t MyName = BathLighter;
Led Leds[1]; // Массив диодов
uint8_t LedsCount = 1; //0; // Количество светодиодов на плате
Button Buttons[4]; // Массив кнопок
uint8_t ButtonsCount = 4; // Количество светодиодов на плате
Relay Relays[8]; // Массив реле
uint8_t RelaysCount = 8; // Количество реле, подключенных к плате
MovingSensor MovingSensors[1]; // Массив датчиков движения
uint8_t MovingSensorsCount = 1; // Количество датчиков движения, подключенных к плате
ProximitySensor ProximitySensors[2]; // Массив датчиков приближения
uint8_t ProximitySensorsCount = 2; // Количество датчиков приближения, подключенных к плате
#endif

#ifdef RooomRooomBoard
#include "RooomRooom.h"
uint8_t MyName = RooomRooom;
Led Leds[1]; // Массив диодов
uint8_t LedsCount = 1; //0; // Количество светодиодов на плате
Button Buttons[1]; // Массив кнопок
uint8_t ButtonsCount = 1; // Количество светодиодов на плате
Relay Relays[11]; // Массив реле
uint8_t RelaysCount = 11; // Количество реле, подключенных к плате
MovingSensor MovingSensors[1]; // Массив датчиков движения
uint8_t MovingSensorsCount = 0; // Количество датчиков движения, подключенных к плате
ProximitySensor ProximitySensors[2]; // Массив датчиков приближения
uint8_t ProximitySensorsCount = 0; // Количество датчиков приближения, подключенных к плате
#endif

extern TIM_HandleTypeDef htim2; // Хендлер таймера 2
extern UART_HandleTypeDef huart1; // Хендлер UART 1
extern DMA_HandleTypeDef hdma_usart1_rx; // Хендлер передатчика
extern DMA_HandleTypeDef hdma_usart1_tx; // Хендлер приемника

extern USBD_HandleTypeDef hUsbDeviceFS; // Хендлер на USB устройство
extern uint8_t dataToReceive[16]; // Данные, приходящие с USB
extern RTC_HandleTypeDef hrtc; // Хендлер на счетчик времени
RTC_TimeTypeDef BoardTime = { 0 }; // Время на плате
RTC_DateTypeDef BoardDate = { 0 }; // Дата на плате

uint8_t MyAddress; // Мой адрес

uint16_t Timer2Ticks = 0; // Тики таймера 2
uint16_t Timer2TicksOLD = 0; // Старое значение тиков таймера 2 для блокировки повторного срабатывания

uint16_t TimeUSARTDMACount; // Счетчик паузы между считываниями из DMA для определения конца посылки
uint16_t TimeUSARTDMACountMax = 50; // Максимальная пауза межу считываниями из DMA для определения конца посылки
bool MessageUSBTransmitted = true; // Указатель нокончание передачи сообщения по USB


uint8_t MessageToTransmit[16]; // Контейнер для отправляемого сообщения USART

////////////////////////////////////////////////////////////////////////////////
uint8_t MessageToReceive[16]; // Контейнер для получаемого сообщения USART
uint8_t MessageToReceiveBuffer[16]; // Буфер для получаемого сообщения USART
uint8_t MessageFromUSATContainer[10][16]; // Хранилище присланных сообщений по USART
uint8_t USARTMessState[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // Статусы сообщений в контейнере для отправки по USB:
// 0- Пусто, 1-Не обработано, 2-Обработано, 3- Вновь записанное поверх неотправленного
uint8_t MessageFromUSARTContainerCursor = 0; // Указатель на позицию записи сообщения

bool MessageFromUSARTStorage = true; // Указатель на то что сообщение сохранено в хранилище
////////////////////////////////////////////////////////////////////////////////

uint8_t MessageReceivedUSB[16]; // Контейнер для получаемого сообщения по USB
uint8_t MessageTransmitUSB[16]; // Контейнер для отправляемого сообщения по USB
uint8_t HID_Transfer_Buffer[16]; // Контейнер для отправки данных по USB
uint8_t MessageToUSBContainer[10][16]; // Хранилище сообщений для отправки по USB
uint8_t USBMessState[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // Статусы сообщений в контейнере для отправки по USB:
// 0- Пусто, 1-Не отправлено, 2-Отправлено, 3- Вновь записанное поверх неотправленного
uint8_t MessageToUSBContainerCursor = 0; // Указатель на позицию записи сообщения

bool MessageToUSBStorage = true; // Указатель на то что сообщение сохранено в хранилище
uint16_t USBPausedCount; // Счетчик паузы для USB для стабильной передачи
uint16_t USBPausedMax = 100; // Максимальное значение сетчика паузы USB для стабильной передачи

extern bool USBIncomingBusy; // Индикатор процесса приема данных по USB

uint8_t MessageReceived[16]; // Полученное сообщение
uint16_t TimeToWaitAnswerMax = 400; // Время ожидания ответа корреспондента
uint16_t TimeToWaitAnswerCount = 0; // Время ожидания ответа корреспондента
uint8_t AddressWaitingBoard = 0; // Адрес платы, от которой ожидается ответ
bool NeedAnswer = false; // Флажок ожидания ответа корреспондента

uint8_t MessageToTransmitStatus = NoMessage; // Статус отправляемого сообщения
uint8_t MessageToReceiveStatus = NoMessage; // Статус принимаемого сообщения
bool TranslateIncomingToUSB = false; // Разрешение на трансляцию входящих сообщений через USB

Board Boards[4];
uint8_t BoardsCount = 4; // Количество плат в системе

uint8_t KeyBoardTimerMainCount = 0; // Основной таймер для опроса кнопок
uint8_t KeyBoardTimerMainCountOLD = 0; // Старое значение основного таймера
uint8_t KeyBoardTimerMainMax = 200; // Максимальное значение основного таймера

uint8_t KeyBoardTimerCount = 0; // Таймер для опроса кнопок
uint8_t KeyBoardTimerMax = 200; // Максимальное значение таймера опроса кнопок

uint8_t TimeFirstHotPoint = 10; // Количество тиков таймера для достижения первой контрольной точки относительно стартовой.
uint8_t TimeSecondHotPoint = 10; // Количество тиков таймера для достижения второй контрольной точки относительно первой.
uint8_t TimeFinalHotPoint = 10; // Количество тиков таймера для достижения последней контрольной точки относительно второй.

void ButtonsListen(void)
{
	uint8_t ButtonTest; // Для проверки состояния кнопок

	if (KeyBoardTimerMainCount == 0){KeyBoardTimerMainCount = KeyBoardTimerMainMax; }
	; // Если основной счетчик обнулился- выставляем максимум

	if (KeyBoardTimerMainCount != KeyBoardTimerMainCountOLD) // Если старое значение счетчика не совпадает с новым
	{
		KeyBoardTimerMainCountOLD = KeyBoardTimerMainCount; // Приравниваем старое значение с новым
		KeyBoardTimerCount++; // Увеличиваем локальный счетчик
		if (KeyBoardTimerCount > KeyBoardTimerMax){KeyBoardTimerCount = 0; }
		; // Если локальный счетчик зашкаливает- сбрасываем

		for (int i = 0; i < ButtonsCount; i++) // Перебор массива кнопок
		{
			if (Buttons[i].HotPointTime == 0) // Если счетчик времени до горячих точек обнулился
			{
				ButtonTest = ReadButton(Buttons[i]);
				if (ButtonTest == ButtonIsPress)
				{
					switch (Buttons[i].HotPoint) // Проверка на прохождение контрольных точек
					{
					case 0: // Ни одна точка не пройдена
						{
							Buttons[i].HotPoint = 1; // Стартовая точка пройдена
							Buttons[i].FirstPointState = false; // Первая точка- нет нажатия
							Buttons[i].SecondPointState = false; // Вторая точка- нет нажатия
							Buttons[i].FinalPointState = false; // Последняя точка- нет нажатия
							Buttons[i].HotPointTime = TimeFirstHotPoint; // Выставляем значение таймера до первой контрольной точки
							break;
						}
					case 1: // Пройдена только стартовая точка
						{
							Buttons[i].HotPoint = 2; // Пройдена первая точка
							Buttons[i].FirstPointState = true; // Первая точка- есть нажатие
							Buttons[i].HotPointTime = TimeSecondHotPoint; // Выставляем значение таймера до второй контрольной точки

							break;
						}
					case 2: // Пройдена первая точка
						{
							Buttons[i].HotPoint = 3; // Пройдена вторая точка
							Buttons[i].SecondPointState = true; // Вторая точка- есть нажатие
							Buttons[i].HotPointTime = TimeFinalHotPoint; // Выставляем значение таймера до последней контрольной точки

							break;
						}
					case 3: // Пройдена вторая точка
						{
							Buttons[i].HotPoint = 4; // Пройдена последняя точка
							Buttons[i].FinalPointState = true; // Последняя точка- есть нажатие
							if (Buttons[i].FirstPointState == false && Buttons[i].SecondPointState == false) {
								Buttons[i].Result = ButtonDoubleClick;
							}
							;
							if (Buttons[i].FirstPointState == true && Buttons[i].SecondPointState == false) {
								Buttons[i].Result = ButtonDoubleClick;
							}
							;
							if (Buttons[i].FirstPointState == true && Buttons[i].SecondPointState == true) {
								Buttons[i].Result = ButtonHold;
							}
							;
							if (Buttons[i].FirstPointState == false && Buttons[i].SecondPointState == true) {
								Buttons[i].Result = ButtonDoubleClick;
							}
							;
							break;
						}

					default: // Если команда не входит ни в одну из групп
						{
							//группа операторов;
						}
						;
					}
					;
				}
				else // Если клавиша не нажата
				{
					switch (Buttons[i].HotPoint) // Проверка на прохождение контрольных точек
					{
					case 1: // Пройдена только стартовая точка
						{
							Buttons[i].HotPoint = 2; // Пройдена первая точка
							Buttons[i].FirstPointState = false; // Первая точка- нет нажатия
							Buttons[i].HotPointTime = TimeSecondHotPoint; // Выставляем значение таймера до второй контрольной точки
							break;
						}
					case 2: // Пройдена первая точка
						{
							Buttons[i].HotPoint = 3; // Пройдена вторая точка
							Buttons[i].SecondPointState = false; // Вторая точка- нет нажатия
							Buttons[i].HotPointTime = TimeFinalHotPoint; // Выставляем значение таймера до последней контрольной точки
							break;
						}
					case 3: // Пройдена вторая точка
						{
							Buttons[i].HotPoint = 4; // Пройдена последняя точка
							Buttons[i].FinalPointState = false; // Последняя точка- нет нажатия
							if (Buttons[i].FirstPointState == false && Buttons[i].SecondPointState == false) {
								Buttons[i].Result = ButtonShortClick;
							}
							;
							if (Buttons[i].FirstPointState == true && Buttons[i].SecondPointState == false) {
								Buttons[i].Result = ButtonShortClick;
							}
							;
							if (Buttons[i].FirstPointState == true && Buttons[i].SecondPointState == true) {
								Buttons[i].Result = ButtonLongPress;
							}
							;
							if (Buttons[i].FirstPointState == false && Buttons[i].SecondPointState == true) {
								Buttons[i].Result = ButtonDoubleClick;
							}
							;
							break;
						}

					default:
						{
							//группа операторов;
						}
						;
					}
					;
				}
				;
			}
			else
			{
				Buttons[i].HotPointTime--; // Убавить счетчик ожидания горячей точки на 1
			}
			;
		}
		;
	}
	;
}

void ButtonsReset(uint8_t NumderOfButton)
{
	Buttons[NumderOfButton].Result = ButtonUp; // Кнопка в положении "отпущена"
	Buttons[NumderOfButton].HotPoint = 0; // Стартовая точка не пройдена
	Buttons[NumderOfButton].HotPointTime = 0; // Время до точки нулевое
	Buttons[NumderOfButton].FirstPointState = false; // Первая точка- нет нажатия
	Buttons[NumderOfButton].SecondPointState = false; // Вторая точка- нет нажатия
	Buttons[NumderOfButton].FinalPointState = false; // Последняя точка- нет нажатия
}

void LedsDrive(uint8_t LedAddress, uint8_t CommandForLed)
{
	for (int i = 0; i < LedsCount; i++) // Перебор массива светодиодов
	{
		if (LedAddress == Leds[i].Address) // Поиск нужного адреса
		{
			switch (CommandForLed) // Проверяем группу команды
			{
			case CommandLedOff: // Если команда на выключение
				{
					LedOff(Leds[i]); // Выключить светодиод;
					break;
				}
			case CommandLedOn: // Если команда на включение
				{
					LedOn(Leds[i]); // Включить светодиод
					break;
				}
			case CommandLedToggle: // Если команда на переключение
				{
					LedToggle(Leds[i]);
					break;
				}
			case CommandLedState: // Опрос состояния
				{
					//группа операторов
					break;
				}
			}
			;
		}
		;
	}
	;
}
;

void RelaysDrive(uint8_t RelayAddress, uint8_t CommandForRelay)
{
	for (int i = 0; i < RelaysCount; i++) // Перебор массива светодиодов
	{
		if (RelayAddress == Relays[i].Address) // Поиск нужного адреса
		{
			switch (CommandForRelay) // Проверяем группу команды
			{
			case CommandRelayOff: // Если команда на выключение
				{
					RelayOff(Relays[i]); // Выключить светодиод;
					break;
				}
			case CommandRelayOn: // Если команда на включение
				{
					RelayOn(Relays[i]); // Включить светодиод
					break;
				}
			case CommandRelayToggle: // Если команда на переключение
				{
					RelayToggle(Relays[i]);
					break;
				}
			case CommandRelayState: // Опрос состояния
				{
					//группа операторов
					break;
				}
			}
			;
		}
		;
	}
	;
}
;

void Initialization(void)
{
	Boards[0].Name = NetMaster; // Имя платы 1
	Boards[1].Name = TaskMaster; // Имя платы 2
	Boards[2].Name = BathLighter; // Имя платы 3
	Boards[3].Name = RooomRooom; // Имя платы 4

	for (int i = 0; i < BoardsCount; i++)
	{
		Boards[i].Address = i + 1; // Адрес первой платы
		if (Boards[i].Name == MyName)
		{
			Boards[i].State = BoardOnLine;
			MyAddress = Boards[i].Address;
		}
		else
		{Boards[i].State = BoardStateUnknown; }
		;
	}
	;

#ifdef NetMasterBoard
	NetMasterInit();
	TranslateIncomingToUSB = false;
#endif

#ifdef TaskMasterBoard
	TaskMasterInit();
	TranslateIncomingToUSB = true;
#endif

#ifdef BathLighterBoard
	BathLighterInit();
	TranslateIncomingToUSB = false;
	//Scenario TestScenario;
#endif

#ifdef RooomRooomBoard
	RooomRooomInit();
	TranslateIncomingToUSB = false;
#endif

	ScenariosInit();

	HAL_TIM_Base_Start_IT(&htim2); // Старт таймера 2

	ReceiverOff;
	NeedAnswer = false;
	MessageToTransmitStatus = NoMessage;
	MessageToReceiveStatus = NoMessage;
}

void Drive(void)
{
#ifdef NetMasterBoard
	NetMasterDrive();
#endif

#ifdef TaskMasterBoard
	TaskMasterDrive();
#endif

#ifdef BathLighterBoard
	BathLighterDrive();
#endif

#ifdef RooomRooomBoard
	RooomRooomDrive();
#endif

	if (TranslateIncomingToUSB == true && MessageUSBCome == true)
	{
		ProcessIncomUSBMessage();
	}
	;
	////////////////////////////////////////////////////////////////////////////////
	if (MessageToReceiveStatus == MessageReady) // Если есть необработанные сообщения
	{
		for (int i = 0; i < sizeof(USARTMessState); i++) // Пробегаемся по всем ячейкам хранилища сообщений
		{
			MessageToReceiveStatus = NoMessage;
			if (USARTMessState[i] == 1 || USARTMessState[i] == 3) // Проверка статуса хранящегося в ячейке сообщения
			{
				MessageFromUSARTContainerCursor = i;
				MessageToReceiveStatus = MessageReady;

				MessageToReceiveBuffer[0] = MessageFromUSATContainer[i][0];
				MessageToReceiveBuffer[1] = MessageFromUSATContainer[i][1];
				MessageToReceiveBuffer[2] = MessageFromUSATContainer[i][2];
				MessageToReceiveBuffer[3] = MessageFromUSATContainer[i][3];
				MessageToReceiveBuffer[4] = MessageFromUSATContainer[i][4];
				MessageToReceiveBuffer[5] = MessageFromUSATContainer[i][5];
				MessageToReceiveBuffer[6] = MessageFromUSATContainer[i][6];
				MessageToReceiveBuffer[7] = MessageFromUSATContainer[i][7];
				MessageToReceiveBuffer[8] = MessageFromUSATContainer[i][8];
				MessageToReceiveBuffer[9] = MessageFromUSATContainer[i][9];
				MessageToReceiveBuffer[10] = MessageFromUSATContainer[i][10];
				MessageToReceiveBuffer[11] = MessageFromUSATContainer[i][11];
				MessageToReceiveBuffer[12] = MessageFromUSATContainer[i][12];
				MessageToReceiveBuffer[13] = MessageFromUSATContainer[i][13];
				MessageToReceiveBuffer[14] = MessageFromUSATContainer[i][14];
				MessageToReceiveBuffer[15] = MessageFromUSATContainer[i][15];

				DecodeMessage(MessageToReceiveBuffer); // Обработать сообщение
				break;
			}
			;
		}
		;
	}
	;

	////////////////////////////////////////////////////////////////////////////////
	/*
	if (MessageToReceiveStatus==MessageReady) // Если сообщение принято
	{
	DecodeMessage(MessageToReceive); // Обработать сообщение
	};
	*/
	if (NeedAnswer == true && TimeToWaitAnswerCount <= 0) // Если ожидается ответ и время ожидания истекло
	{
		NeedAnswer = false; // Выйти из режима ожидания
		for (int i = 0; i < BoardsCount; i++) // Перебор адресов плат
		{
			if (Boards[i].Address == AddressWaitingBoard) // Если найден адрес молчащей платы
			{
				Boards[i].State = BoardOffLine; // Выставляем статус "Оффлайн"
				break;
			}
			;
		}
		;
	}
	;
	osDelay(1);

	////////////////////////////////////////////////////////////////////////////////
	ScenarioAction();
	////////////////////////////////////////////////////////////////////////////////
}

void SendMessage(void)
{
	ReceiverOn;
	osDelay(10);
	if (hdma_usart1_tx.State == HAL_DMA_STATE_READY)
	{
		HAL_UART_Transmit_DMA(&huart1, MessageToTransmit, sizeof(MessageToTransmit) - 1);
		hdma_usart1_tx.State = HAL_DMA_STATE_BUSY;
		MessageToTransmitStatus = MessageInTransmit;
	}
	;
	osDelay(1);
	/////////////////////////////////////////////////////////////////////////////////
	MessageToReceive[0] = 0;
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	//LedOff(Leds[0]);
	////////////////////////////////////////////////////////////////////////////////
}

void Listen(void)
{
	////////////////////////////////////////////////////////////////////////////////
	if (HAL_UART_Receive_DMA(&huart1, MessageToReceive, sizeof(MessageToReceive) - 1) == HAL_OK)// Если что то пришло по USART
	{
		MessageFromUSARTStorage = false; // Сообщение не сохранено в хранилище
		for (int i = 0; i < sizeof(USARTMessState); i++)
		{
			if (USARTMessState[i] == 0) // Проверка статуса хранящегося в ячейке сообщения
			{
				for (int j = 0; j < sizeof(MessageToReceive); j++) // Заполняем его
				{
					MessageFromUSATContainer[i][j] = MessageToReceive[j];
				}
				;
				USARTMessState[i] = 1; // Устанавливаем метку о наличии неотправленного сообщения
				MessageFromUSARTStorage = true; // Поднимаем флажок о сохранении сообщения
				MessageToReceiveStatus = MessageReady;
				break;
			}
			;
		}
		;

		if (MessageFromUSARTStorage != true) // Если все ячейки заняты
		{
			for (int i = 0; i < sizeof(USARTMessState); i++) // Пробегаемся по всем ячейкам хранилища сообщений
			{
				if (USARTMessState[i] == 2)
				{
					for (int j = 0; j < sizeof(MessageToReceive); j++) // Заполняем его
					{
						MessageFromUSATContainer[i][j] = MessageToReceive[j];
					}
					;
					//////////////////////////////////////////////////////////////////////
					if (i < sizeof(USARTMessState) - 1)
					{
						if (USARTMessState[i + 1] == 2){USARTMessState[i + 1] = 0; }
						;
					}
					else
					{
						if (USARTMessState[0] == 2){USARTMessState[0] = 0; }
						;
					}
					;
					//////////////////////////////////////////////////////////////////////
					USARTMessState[i] = 1; // Устанавливаем метку о наличии неотправленного сообщения
					MessageFromUSARTStorage = true; // Поднимаем флажок о сохранении сообщения
					MessageToReceiveStatus = MessageReady;
					break;
				}
				;
			}
			;
		}
		;
		///////////////////////////////////////////////////////////////////////
		if (MessageFromUSARTStorage != true) // Если все ячейки заняты
		{
			for (int i = 0; i < sizeof(USARTMessState); i++) // Пробегаемся по всем ячейкам хранилища сообщений
			{
				if (USARTMessState[i] == 1) // Проверка статуса хранящегося в ячейке сообщения
				{
					for (int j = 0; j < sizeof(MessageToReceive); j++) // Заполняем его
					{
						MessageFromUSATContainer[i][j] = MessageToReceive[j];
					}
					;
					USARTMessState[i] = 3; // Устанавливаем метку о наличии неотправленного сообщения
					MessageFromUSARTStorage = true; // Поднимаем флажок о сохранении сообщения
					MessageToReceiveStatus = MessageReady;
					break;
				}
				;
			}
			;
		}
		;

		if (MessageFromUSARTStorage != true) // Если все ячейки заняты
		{
			for (int j = 0; j < sizeof(MessageToReceive); j++) // Заполняем его
			{
				MessageFromUSATContainer[0][j] = MessageToReceive[j];
			}
			;
			USARTMessState[0] = 3; // Устанавливаем метку о наличии неотправленного сообщения
			MessageFromUSARTStorage = true; // Поднимаем флажок о сохранении сообщения
			MessageToReceiveStatus = MessageReady;
		}
		;
	}
	;
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	/*
	if (HAL_UART_Receive_DMA(&huart1,ReceiveBuffer,sizeof(ReceiveBuffer)-1)==HAL_OK)// Если что то пришло
	{
	for(int i=0;i<sizeof(ReceiveBuffer);i++){MessageToReceive[i]=ReceiveBuffer[i];};// Заполняем буферный массив
	};

	if (MessageToReceive[0]!=0) // Если первое значение не нулевое


	if(TranslateIncomingToUSB==true) // Если разрешена передача по USB
	{
	MessageToUSBStorage=false; // сообщение
	for(int i=0;i<sizeof(USBMessState);i++)
	{

	if (USBMessState[i]==0) // Проверка статуса хранящегося в ячейке сообщения
	{
	for(int j=0;j<sizeof(MessageToReceive);j++) // Заполняем его
	{
	MessageToUSBContainer[i][j]=MessageToReceive[j];
	};
	USBMessState[i]=1; // Устанавливаем метку о наличии неотправленного сообщения
	MessageToUSBStorage=true; // Поднимаем флажок о сохранении сообщения
	break;
	};
	};

	if(MessageToUSBStorage!=true) // Если все ячейки заняты
	{
	for(int i=0;i<sizeof(USBMessState);i++) // Пробегаемся по всем ячейкам хранилища сообщений
	{
	if (USBMessState[i]==2)
	{
	for(int j=0;j<sizeof(MessageToReceive);j++) // Заполняем его
	{
	MessageToUSBContainer[i][j]=MessageToReceive[j];
	};
	//////////////////////////////////////////////////////////////////////
	if (i<sizeof(USBMessState)-1)
	{
	if(USBMessState[i+1]==2){USBMessState[i+1]=0;};
	}
	else
	{
	if(USBMessState[0]==2){USBMessState[0]=0;};
	};
	//////////////////////////////////////////////////////////////////////
	USBMessState[i]=1; // Устанавливаем метку о наличии неотправленного сообщения
	MessageToUSBStorage=true; // Поднимаем флажок о сохранении сообщения
	break;
	};
	};
	};

	if(MessageToUSBStorage!=true) // Если все ячейки заняты
	{
	for(int i=0;i<sizeof(USBMessState);i++) // Пробегаемся по всем ячейкам хранилища сообщений
	{
	if (USBMessState[i]==1) // Проверка статуса хранящегося в ячейке сообщения
	{
	for(int j=0;j<sizeof(MessageToReceive);j++) // Заполняем его
	{
	MessageToUSBContainer[i][j]=MessageToReceive[j];
	};
	USBMessState[i]=3; // Устанавливаем метку о наличии неотправленного сообщения
	MessageToUSBStorage=true; // Поднимаем флажок о сохранении сообщения
	break;
	};
	};
	};

	if(MessageToUSBStorage!=true) // Если все ячейки заняты
	{
	for(int j=0;j<sizeof(MessageToReceive);j++) // Заполняем его
	{
	MessageToUSBContainer[0][j]=MessageToReceive[j];
	};
	USBMessState[0]=3; // Устанавливаем метку о наличии неотправленного сообщения
	MessageToUSBStorage=true; // Поднимаем флажок о сохранении сообщения
	};
	};
	MessageToReceiveStatus=MessageReady;

	}
	else
	{
	MessageToReceiveStatus=NoMessage;
	};

	*/
}

void AskSolver(uint8_t Correspondent, uint8_t Question)
{
	switch (Question) // Проверяем вопрос
	{
	case IsHaveMessage: // Есть ли сообщения?
		{
			if (MessageToTransmitStatus == MessageReady)
			{
				SendMessage();
			}
			else
			{
				CommandConstructor(MyName, Correspondent, InformationGroup, NoAnswer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // Ответ: нет исходящих сообщений
				SendMessage();
			}
			;
			break;
		}
		////////////////////////////////////////////////////////////////////////////////
	case Equipment1: // Есть ли сообщения?
		{
			CommandConstructor(MyName, Correspondent, InformationGroup, Equipment1Answer, LedsCount, ButtonsCount, RelaysCount, MovingSensorsCount, ProximitySensorsCount, 0, 0, 0, 0, 0, 0, 0); // Ответ: нет исходящих сообщений
			SendMessage();
			break;
		}
		////////////////////////////////////////////////////////////////////////////////
	default: // Если команда не входит ни в одну из групп
		{
			/*группа операторов*/
			;
		}
		;
	}
	;
}

void DecodeMessage(uint8_t Message[16])
{
	////////////////////////////////////////////////////////////////////////////////
	if (TranslateIncomingToUSB == true) // Если разрешена передача по USB
	{
		MessageToUSBStorage = false; // сообщение
		for (int i = 0; i < sizeof(USBMessState); i++)
		{

			if (USBMessState[i] == 0) // Проверка статуса хранящегося в ячейке сообщения
			{
				//for(int j=0;j<sizeof(Message);j++) // Заполняем его
				for (int j = 0; j < 16; j++) // Заполняем его
				{
					MessageToUSBContainer[i][j] = Message[j];
				}
				;
				USBMessState[i] = 1; // Устанавливаем метку о наличии неотправленного сообщения
				MessageToUSBStorage = true; // Поднимаем флажок о сохранении сообщения
				break;
			}
			;
		}
		;

		if (MessageToUSBStorage != true) // Если все ячейки заняты
		{
			for (int i = 0; i < sizeof(USBMessState); i++) // Пробегаемся по всем ячейкам хранилища сообщений
			{
				if (USBMessState[i] == 2)
				{
					//for(int j=0;j<sizeof(Message);j++) // Заполняем его
					for (int j = 0; j < 16; j++) // Заполняем его
					{
						MessageToUSBContainer[i][j] = Message[j];
					}
					;
					//////////////////////////////////////////////////////////////////////
					if (i < sizeof(USBMessState) - 1)
					{
						if (USBMessState[i + 1] == 2){USBMessState[i + 1] = 0; }
						;
					}
					else
					{
						if (USBMessState[0] == 2){USBMessState[0] = 0; }
						;
					}
					;
					//////////////////////////////////////////////////////////////////////
					USBMessState[i] = 1; // Устанавливаем метку о наличии неотправленного сообщения
					MessageToUSBStorage = true; // Поднимаем флажок о сохранении сообщения
					break;
				}
				;
			}
			;
		}
		;

		if (MessageToUSBStorage != true) // Если все ячейки заняты
		{
			for (int i = 0; i < sizeof(USBMessState); i++) // Пробегаемся по всем ячейкам хранилища сообщений
			{
				if (USBMessState[i] == 1) // Проверка статуса хранящегося в ячейке сообщения
				{
					//for(int j=0;j<sizeof(Message);j++) // Заполняем его
					for (int j = 0; j < 16; j++) // Заполняем его
					{
						MessageToUSBContainer[i][j] = Message[j];
					}
					;
					USBMessState[i] = 3; // Устанавливаем метку о наличии неотправленного сообщения
					MessageToUSBStorage = true; // Поднимаем флажок о сохранении сообщения
					break;
				}
				;
			}
			;
		}
		;

		if (MessageToUSBStorage != true) // Если все ячейки заняты
		{
			//for(int j=0;j<sizeof(Message);j++) // Заполняем его
			for (int j = 0; j < 16; j++) // Заполняем его
			{
				MessageToUSBContainer[0][j] = Message[j];
			}
			;
			USBMessState[0] = 3; // Устанавливаем метку о наличии неотправленного сообщения
			MessageToUSBStorage = true; // Поднимаем флажок о сохранении сообщения
		}
		;
	}
	;

	////////////////////////////////////////////////////////////////////////////////
	USARTMessState[MessageFromUSARTContainerCursor] = 2;

	for (int i = 0; i < BoardsCount; i++) // Перебор адресов плат
	{
		if (Boards[i].Address == Message[0]) // Если найден адрес отвечающей платы
		{
			if (Boards[i].State == BoardStateUnknown || Boards[i].State == BoardOffLine) // Если статус платы не ясен или она не подключена
			{
				////////////////////////////////////////////////////////////////////////////////
				// отправка сообщения о статусе платы ?
				////////////////////////////////////////////////////////////////////////////////
				Boards[i].State = BoardOnLine; // Выставляем статус "Онлайн"
			}
			;
			break; // Выход из перебора
		}
		;
	}
	;

	if (Message[1] == MyName) // Если команда для меня
	{
		switch (Message[2]) // Проверяем группу команды
		{
		case InformationGroup: // Группа информационных команд
			{
				//группа операторов
				break;
			}
		case AsksGroup: // Группа вопросов
			{
				AskSolver(Message[0], Message[3]); // Ответы на вопросы
				break;
			}
		case BoardsGroup: // Группа команд для платы
			{
				BoardTweaker(Message[3],
					Message[4],
					Message[5],
					Message[6],
					Message[7],
					Message[8],
					Message[9],
					Message[10],
					Message[11],
					Message[12],
					Message[13],
					Message[14],
					Message[15]);
				//группа операторов
				break;
			}
		case LedsGroup: // Группа команд для светодиодов
			{
				LedsDrive(Message[3], Message[4]);
				break;
			}
		case RelaysGroup: // Группа команд для светодиодов
			{
				RelaysDrive(Message[3], Message[4]);
				break;
			}
		default: // Если команда не входит ни в одну из групп
			{
				//группа операторов
			}
			;
		}
		;
		////////////////////////////////////////////////////////////////////////////
		// USARTMessState[MessageFromUSARTContainerCursor]=2;
		// MessageToReceiveStatus=NoMessage; // Сбросить статус сообщения
		////////////////////////////////////////////////////////////////////////////
	}
	else // Если команда не для меня
	{
		switch (Message[2]) // Проверяем группу команды
		{
		case InformationGroup: // Группа информационных команд
			{
				switch (Message[3]) // Проверяем команду
				{
				case NoAnswer: // Команда "Нет сообщений"
					{
						for (int i = 0; i < BoardsCount; i++) // Перебор адресов плат
						{
							if (Boards[i].Address == AddressWaitingBoard) // Если адрес отвечающей платы совпадает с адресом ожидания ответа
							{
								TimeToWaitAnswerCount = 0; // Остановить счетчик ожидания
								NeedAnswer = false; // Выйти из режима ожидания
							}
							;

						}
						;

						break;
					}
					;
				}
				;
				break;
			}
		case AsksGroup: // Группа вопросов
			{
				//группа операторов
				break;
			}
		case BoardsGroup: // Группа команд для платы
			{
				switch (Message[3]) // Проверяем команду
				{
				case CommandSetDateTime: // Команда корректировки времени и даты
					{
						SetDateTime(Message[4], Message[5], Message[6], Message[7], Message[8], Message[9], Message[10]); // Корректируем дату и время
					}
					;
					break;
				}
				;
				//группа операторов
				break;
			}
		case LedsGroup: // Группа команд для светодиодов
			{
				//группа операторов
				break;
			}
		default: // Если команда не входит ни в одну из групп
			{
				//группа операторов
			}
			;
		}
		;
		///////////////////////////////////////////////////////////////////////////
		// USARTMessState[MessageFromUSARTContainerCursor]=2;
		// MessageToReceiveStatus=NoMessage; // Сбросить статус сообщения
		////////////////////////////////////////////////////////////////////////////

	}
	;
	////////////////////////////////////////////////////////////////////////////////
	//for(int i=0;i<sizeof(MessageToReceive);i++){MessageToReceive[i]=0;}; // Обнулить сообщение
	//MessageToReceive[0]=0; // Обнулить сообщение
	//MessageToReceiveStatus=NoMessage; // Сбросить статус сообщения
	////////////////////////////////////////////////////////////////////////////////
}
;

void CommandConstructor(uint8_t Author,
	uint8_t Correspondent,
	uint8_t GroupOfCommand,
	uint8_t Command,
	uint8_t Parametr1,
	uint8_t Parametr2,
	uint8_t Parametr3,
	uint8_t Parametr4,
	uint8_t Parametr5,
	uint8_t Parametr6,
	uint8_t Parametr7,
	uint8_t Parametr8,
	uint8_t Parametr9,
	uint8_t Parametr10,
	uint8_t Parametr11,
	uint8_t Parametr12)
{
	MessageToTransmit[0] = Author;
	MessageToTransmit[1] = Correspondent;
	MessageToTransmit[2] = GroupOfCommand;
	MessageToTransmit[3] = Command;
	MessageToTransmit[4] = Parametr1;
	MessageToTransmit[5] = Parametr2;
	MessageToTransmit[6] = Parametr3;
	MessageToTransmit[7] = Parametr4;
	MessageToTransmit[8] = Parametr5;
	MessageToTransmit[9] = Parametr6;
	MessageToTransmit[10] = Parametr7;
	MessageToTransmit[11] = Parametr8;
	MessageToTransmit[12] = Parametr9;
	MessageToTransmit[13] = Parametr10;
	MessageToTransmit[14] = Parametr11;
	MessageToTransmit[15] = Parametr12;

	if (GroupOfCommand == AsksGroup) // Если команда относится к вопросной группе
	{
		NeedAnswer = true; // Ставим флажок ожидания ответа
		AddressWaitingBoard = Correspondent; // Запоминаем адрес корреспондента
	}
	;

	MessageToTransmitStatus = MessageReady; // Флажок о готовности сообщения
}

void Communication(void)
{

	if (TranslateIncomingToUSB == true)
	{
		if (USBPausedCount == 0)
		{
			USBPausedCount = USBPausedMax;
			for (int i = 0; i < sizeof(USBMessState); i++) // Пробегаемся по всем ячейкам хранилища сообщений
			{
				if (USBMessState[i] == 1 || USBMessState[i] == 3) // Проверка статуса хранящегося в ячейке сообщения
				{
					MessageToUSBContainerCursor = i;
					HID_Transfer_Buffer[0] = 3;
					HID_Transfer_Buffer[1] = MessageToUSBContainer[i][0];
					HID_Transfer_Buffer[2] = MessageToUSBContainer[i][1];
					HID_Transfer_Buffer[3] = MessageToUSBContainer[i][2];
					HID_Transfer_Buffer[4] = MessageToUSBContainer[i][3];
					HID_Transfer_Buffer[5] = MessageToUSBContainer[i][4];
					HID_Transfer_Buffer[6] = MessageToUSBContainer[i][5];
					HID_Transfer_Buffer[7] = MessageToUSBContainer[i][6];
					HID_Transfer_Buffer[8] = MessageToUSBContainer[i][7];
					HID_Transfer_Buffer[9] = MessageToUSBContainer[i][8];
					HID_Transfer_Buffer[10] = MessageToUSBContainer[i][9];
					HID_Transfer_Buffer[11] = MessageToUSBContainer[i][10];
					HID_Transfer_Buffer[12] = MessageToUSBContainer[i][11];
					HID_Transfer_Buffer[13] = MessageToUSBContainer[i][12];
					HID_Transfer_Buffer[14] = MessageToUSBContainer[i][13];
					HID_Transfer_Buffer[15] = MessageToUSBContainer[i][14];

					TransmitFromUSB();
					break;
				}
				;
			}
			;
		}
		;
	}
	;


	switch (MessageToTransmitStatus) // Статус отправляемого сообщения
	{
	case MessageReady: // Сообщение готово к передаче
		{
#ifdef NetMasterBoard
			if (NeedAnswer == false){SendMessage(); }
			;
#else
			//////////////////////////////////////////////////////////////////////////
			//SendMessage();
			//////////////////////////////////////////////////////////////////////////
			Listen();
#endif

			break;
		}
	case MessageInTransmit: // Если сообщение передается
		{
			if (hdma_usart1_tx.State == HAL_DMA_STATE_READY) // Если сообщение передалось
			{
				ReceiverOff; // Выключить передатчик
				MessageToTransmitStatus = NoMessage; // Сообщение отправлено
				if (NeedAnswer == true) // Если ожидаем ответ
				{
					TimeToWaitAnswerCount = TimeToWaitAnswerMax; // Запуск счетчика таймера ожидания ответа
				}
				;
			}
			break;
		}
	case NoMessage: // Если нет передаваемых сообщений
		{
			Listen();
			break;
		}
	default: // Если команда не входит ни в одну из групп
		{
			//группа операторов
		}
		;
	}
	;
}

void ProcessIncomUSBMessage(void)
{
	if (dataToReceive[0] != 0)
	{
		CommandConstructor(MyName,
			dataToReceive[1],
			dataToReceive[2],
			dataToReceive[3],
			dataToReceive[4],
			dataToReceive[5],
			dataToReceive[6],
			dataToReceive[7],
			dataToReceive[8],
			dataToReceive[9],
			dataToReceive[10],
			dataToReceive[11],
			dataToReceive[12],
			dataToReceive[13],
			dataToReceive[14],
			dataToReceive[15]); // Пересылка присланного сообщения
		MessageUSBCome = false;
	}
	;
}

void TransmitFromUSB(void)
{
	if (USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, HID_Transfer_Buffer, sizeof(HID_Transfer_Buffer) + 1) == USBD_OK)
	{
		USBMessState[MessageToUSBContainerCursor] = 2;
	}
	;
	USBPausedCount = USBPausedMax;
}

void ReadSensors(void)
{
#ifdef BathLighterBoard
	BathLighterReadSensors();
#endif

#ifdef TaskMasterBoard

	if (MessageUSBCome == true)
	{
		ProcessIncomUSBMessage();
	}
	;
#endif

#ifdef RooomRooomBoard
	RooomRooomReadSensors();
#endif
}

void DoIT(uint8_t NumOfAction, uint8_t Param1)
{

	switch (NumOfAction) // Проверяем команду
	{
	case ScenRelayOn:
		{
			for (int i = 0; i < RelaysCount; i++)
			{
				if (Relays[i].Address == Param1)
				{
					RelayOn(Relays[i]);
					break;
				}
				;
			}
			;
			break;
		}
	case ScenRelayOff:
		{
			for (int i = 0; i < RelaysCount; i++)
			{
				if (Relays[i].Address == Param1)
				{
					RelayOff(Relays[i]);
					break;
				}
				;
			}
			;
			break;
		}
	case ScenLedOn:
		{
			for (int i = 0; i < LedsCount; i++)
			{
				if (Leds[i].Address == Param1)
				{
					LedOn(Leds[i]);
					break;
				}
				;
			}
			;
			break;
		}
	case ScenLedOff:
		{
			for (int i = 0; i < LedsCount; i++)
			{
				if (Leds[i].Address == Param1)
				{
					LedOff(Leds[i]);
					break;
				}
				;
			}
			;
			break;
		}
	default:
		{
			//////////////////////
			break;
		}
		;
	}
	;

}


void SetDateTime(uint8_t Hours, uint8_t Minutes, uint8_t Seconds, uint8_t WeekDay, uint8_t Month, uint8_t Date, uint8_t Year)
{
	BoardTime.Hours = Hours;
	BoardTime.Minutes = Minutes;
	BoardTime.Seconds = Seconds;

	if (HAL_RTC_SetTime(&hrtc, &BoardTime, RTC_FORMAT_BCD) != HAL_OK)
	{
		Error_Handler();
	}
	;

	BoardDate.WeekDay = WeekDay;
	BoardDate.Month = Month;
	BoardDate.Date = Date;
	BoardDate.Year = Year;

	if (HAL_RTC_SetDate(&hrtc, &BoardDate, RTC_FORMAT_BCD) != HAL_OK)
	{
		Error_Handler();
	}
	;

}

void BoardTweaker(uint8_t Command,
	uint8_t Parametr1,
	uint8_t Parametr2,
	uint8_t Parametr3,
	uint8_t Parametr4,
	uint8_t Parametr5,
	uint8_t Parametr6,
	uint8_t Parametr7,
	uint8_t Parametr8,
	uint8_t Parametr9,
	uint8_t Parametr10,
	uint8_t Parametr11,
	uint8_t Parametr12)
{
	switch (Command) // Проверяем команду
	{
	case CommandBoardReset: // Если команда на сброс платы
		{
			//////////;
			break;
		}
	case CommandSetDateTime: // Команда корректировки времени и даты
		{
			SetDateTime(Parametr1, Parametr2, Parametr3, Parametr4, Parametr5, Parametr6, Parametr7);
			break;
		}
	case CommandIndividual: // Индивидуальная команда только для текущей платы
		{
			//////////////////////////////////////////////////////////////////////////RunIndividualComands(Parametr1,Parametr2,Parametr3,Parametr4,Parametr5,Parametr6,Parametr7);
			break;
		}
	default: // Если команда не входит ни в одну из групп
		{
			//группа операторов
		}
		;
	}
	;
}
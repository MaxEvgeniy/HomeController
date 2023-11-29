#include "GlobalHeader.h"
#include "main.h"

extern osMessageQueueId_t SongQueueHandle;
extern osEventFlagsId_t EventAlarmRunHandle;

extern const uint8_t ALARMSONG;

void AlarmDrive(void)
{
	osEventFlagsWait(EventAlarmRunHandle, ALARMMODESET, osFlagsWaitAny, osWaitForever);
	HAL_GPIO_WritePin(LightAlarm_GPIO_Port, LightAlarm_Pin, GPIO_PIN_SET); // Включить лампочку
		if (osMessageQueueGetCount (SongQueueHandle) == 0)
		{
			osMessageQueuePut(SongQueueHandle, &ALARMSONG, 0, 0);
		}
	osDelay(100); // Задержка, чтобы лампочка посветилась маленько.
	HAL_GPIO_WritePin(LightAlarm_GPIO_Port, LightAlarm_Pin, GPIO_PIN_RESET); // Выключить лампочку. На случай отмены тревоги
}

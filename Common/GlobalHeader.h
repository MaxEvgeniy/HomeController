#ifndef GLOBALHEADER
#define GLOBALHEADER
#include "cmsis_os2.h"
#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	uint16_t Frequency; // Требуемая частота звучания
	uint16_t Prescaler; // Предделитель для расчета ШИМа таймера
	uint16_t Period; // Период для расчета ШИМа таймера
	uint16_t Pulse; // Заполнение. Громкость 100% при заполнении на 50%
}Note; // Нота

#define BUZZERALARM		1
#define ALARMMODESET	2

void SensorDrive(void); // Чтение датчиков
void AlarmDrive(void); // Управление сиреной
void BuzzerDrive(void); // Управление пъезодинамиком
#endif

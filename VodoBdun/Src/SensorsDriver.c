#include "GlobalHeader.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os2.h"
#include "main.h"

uint16_t adc = 0; // Значение с АЦП
uint16_t adcOLD = 0; // Старое значение с ацп для отслеживания перехода

const uint16_t WaterThreshold = 3500; // Пороговое значение чувствительности датчика капель

extern ADC_HandleTypeDef hadc1;
extern osEventFlagsId_t EventAlarmRunHandle;

void SensorDrive(void)
{
	if (adc != adcOLD)
	{
		if (adc < WaterThreshold)
		{
			if (osEventFlagsGet(EventAlarmRunHandle) != ALARMMODESET)
			{
				osEventFlagsSet(EventAlarmRunHandle, ALARMMODESET); // Выставляем флаг тревоги
			} // Если флаг тревоги не установлен
		} // Если значение с АЦП миньше контрольного
		else
		{
			if (osEventFlagsGet(EventAlarmRunHandle) == ALARMMODESET)
			{
				osEventFlagsClear(EventAlarmRunHandle, ALARMMODESET); // Снимаем флаг тревоги
			} // Если флаг тревоги установлен
		} // Если значение с АЦП больше контрольного
		adcOLD = adc;
	} // Если значение с АЦП изменилось
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc, 2); // Запуск расчета АЦП
}

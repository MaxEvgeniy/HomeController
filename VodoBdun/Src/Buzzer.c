#include "GlobalHeader.h"
#include "main.h"

/*------------------------Список нот--------------------------*/
/*-Частота, предделитель, период, заполнение. Соответствует типу Note-*/
#define  Do			{ 2093, 0, 34400, 17200 }
#define  DoDiez		{ 2217, 0, 32469, 16235 }
#define  Re			{ 2349, 0, 30648, 15325 }
#define  ReDiez		{ 2489, 0, 28926, 14464 }
#define  Mi			{ 2637, 0, 27303, 13652 }
#define  Fa			{ 2793, 0, 25770, 12886 }
#define  FaDiez		{ 2960, 0, 24323, 12162 }
#define  Sol		{ 3136, 0, 22958, 11480 }
#define  SolDIez	{ 3332, 0, 21605, 10803 }
#define  La			{ 3440, 0, 20929, 10465 }
#define  LaDiez		{ 3729, 0, 19306, 9654 }
#define  Si			{ 3951, 0, 18223, 9112 }
#define  Pause		{ 0, 0, 0, 0 }
#define  EndNote	{ 2, 2, 2, 2 }

/*-Длительности нот-*/
#define  Dur1		4096
#define  Dur1_2		2048
#define  Dur1_4		1024
#define  Dur1_8		512
#define  Dur1_16	256
#define  Dur1_32	128
/*--------------------------------------------------------------------*/
const uint8_t ALARMSONG = 1; // Идентификатор мелодии тревоги

float x = 32.14;

void SoundSetPeriod(uint32_t period); // Установка параметров пьездинамика для воспроизведения ноты

Note AlarmSongNotes[] = {
	Do,
	Fa,
	Pause,
	Re,
	Sol,
	Pause,
	Mi,
	Si,
	Pause,
	EndNote
}; // Ноты мелодии тревоги...
uint16_t AlarmSongDuration[] = { 
	Dur1_16,
	Dur1_8,
	Dur1_32,
	Dur1_16,
	Dur1_8,
	Dur1_32,
	Dur1_16,
	Dur1_8,
	Dur1_32,
	Dur1
}; // Длительность нот мелодии тревоги...

Note *ActiveNote;
uint16_t ActiveSongNotesCount = 0;
uint8_t NumberOfSong;
uint16_t NoteDurationCount = 0;

bool BuzzerBusy = false;

extern osMessageQueueId_t SongQueueHandle;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;

void BuzzerDrive(void)
{
	TIM_OC_InitTypeDef sConfigOC;
	uint16_t MiddleDuration = 0;
	
	if (BuzzerBusy == false)
	{
		if (osMessageQueueGetCount(SongQueueHandle) > 0)
		{
			osMessageQueueGet(SongQueueHandle, &NumberOfSong, NULL, 0); // Чтение из очереди
			ActiveSongNotesCount = 0; // Обнуляем счетчик нот
			BuzzerBusy = true; // Ставим флажок проигрывания
			HAL_TIM_Base_Start_IT(&htim4); // запуск таймера
		} // Проверка очереди на проигрывание
	} // Если динамик не занят
	else
	{
		if (NoteDurationCount == 0)
		{
			switch (NumberOfSong)
			{
			case 1:
				{
					ActiveNote = &AlarmSongNotes[ActiveSongNotesCount];
					MiddleDuration = AlarmSongDuration[ActiveSongNotesCount]/2;
					break;
				} // Мелодия тревоги
			default:
				{
					break;
				} // Ошибка какая-то
			} // Определяем нужную мелодию
			
			if (ActiveNote->Frequency != (Note)EndNote.Frequency)
			{
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2); // Останавливаем генератор
				if (ActiveNote->Frequency != (Note)Pause.Frequency)
				{
					__HAL_TIM_SET_ICPRESCALER(&htim2, TIM_CHANNEL_2, ActiveNote->Prescaler);
					__HAL_TIM_SET_AUTORELOAD(&htim2, ActiveNote->Period);
					__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, ActiveNote->Pulse);
					
					HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2); // Старт генератора
				} // Если нет паузы
				
				NoteDurationCount = MiddleDuration;
				ActiveSongNotesCount = ActiveSongNotesCount + 1; // Увеличиваем счетчик отработанных нот на 1
			} // Если нет флажковой ноты окончания мелодии
			else
			{
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2); // Останавливаем генератор
				HAL_TIM_Base_Stop(&htim4); // Останавливаем таймер	
				ActiveSongNotesCount = 0; // Обнуляем счетчик нот
				MiddleDuration = 0; // Обнуляем промежуточный счетчик длительности звучания ноты
				NoteDurationCount = 0; // Обнуляем счетчик длительности звучания ноты
				BuzzerBusy = false; // Снимаем флажок проигрывания
			} // Если наткнулись на флажок конца мелодии
			
		} // Если счетчик длительности звучания ноты не активен
		else
		{
			osDelay(10); // Ждем...
		} // Если счетчик длительности звучания ноты активен
		
	} // Если динамик занят
}

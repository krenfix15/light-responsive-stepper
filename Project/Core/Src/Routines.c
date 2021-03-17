#include "main.h"
#include "cmsis_os.h"
#include "Routines.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern osSemaphoreId_t myBinarySemAnalogHandle;

uint16_t oAdcConvertedValue[10] = {0};

void RoutineInit()
{
	HAL_ADC_Start_DMA(&hadc1,&oAdcConvertedValue,10);
	HAL_TIM_Base_Start_IT(&htim2);
}

void Routine()
{

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	//osSemaphoreRelease(&myBinarySemAnalogHandle);
}

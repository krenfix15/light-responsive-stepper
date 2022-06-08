#include "main.h"
#include "cmsis_os.h"
#include "Routines.h"
#include "mxconstants.h"

extern ADC_HandleTypeDef hadc1;

extern ADC_HandleTypeDef hadc3;

extern TIM_HandleTypeDef htim2;

extern TIM_HandleTypeDef htim3;

extern osSemaphoreId_t myBinarySemAnalogHandle;

uint16_t oAdcConvertedValuePA0[NUMBER_OF_VALUES] = {0};
uint16_t oAdcConvertedValuePC1[NUMBER_OF_VALUES] = {0};

/***********************************************************//**
*
* \descriere RoutineInit
* - pornește DMA-ul pentru ADC-ul 1 și ADC-ul 3 pentru citirea valorilor analogice 
* și conversia lor la digital
* - pornește Timer-ul 1 și Timer-ul 3 pentru citire ciclică la fiecare tick de ceas
*
***************************************************************/
void RoutineInit()
{
	HAL_ADC_Start_DMA(&hadc1, &oAdcConvertedValuePA0, NUMBER_OF_VALUES);
	HAL_ADC_Start_DMA(&hadc3, &oAdcConvertedValuePC1, NUMBER_OF_VALUES);
	
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
}

void Routine()
{

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	//osSemaphoreRelease(&myBinarySemAnalogHandle);
}

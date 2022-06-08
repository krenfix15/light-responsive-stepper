#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "cmsis_os.h"
#include "main.h"
#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include "mxconstants.h"
#include "stm32f4xx_hal.h"
#include <gui_generated/controlscreen_screen/ControlScreenViewBase.hpp>

extern osSemaphoreId_t myBinarySemAnalogHandle;
extern uint16_t oAdcConvertedValuePA0[NUMBER_OF_VALUES];
extern uint16_t oAdcConvertedValuePC1[NUMBER_OF_VALUES];
extern int analogValuePA0_Graph, analogValuePC1_Graph;
Model::Model() : modelListener(0)
{

}

/***********************************************************//**
*
* \descriere tick
* - actualizează valoarea analogică recepționată de senzorii de lumină
* - se actualizează la fiecare tick de ceas
*
***************************************************************/
void Model::tick()
{
	if(myBinarySemAnalogHandle != NULL)
	{
		//if(osSemaphoreWait (myBinarySemAnalogHandle,100) == osOK)
		//{
		analogUpdatePA0();
		analogUpdatePC1();
		//}
	}
	
}

/***********************************************************//**
*
* \descriere moveStepperToRight
* - poziționează motorul pas cu pas înspre dreapta cu 32 pași (o rotație completă are 2048 pași)
* - aplică un curent pe fiecare pin la care este conectat motorul pas cu pas, alternativ
*
***************************************************************/
void Model::moveStepperToRight()
{
	for(int i = 0; i < NUMBER_OF_STEPS; i++)
	{
		HAL_GPIO_WritePin(PHASE1_GPIO_Port, PHASE1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(PHASE2_GPIO_Port, PHASE2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE3_GPIO_Port, PHASE3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE4_GPIO_Port, PHASE4_Pin, GPIO_PIN_RESET);

		HAL_Delay(DELAY_VALUE);

		HAL_GPIO_WritePin(PHASE1_GPIO_Port, PHASE1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE2_GPIO_Port, PHASE2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(PHASE3_GPIO_Port, PHASE3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE4_GPIO_Port, PHASE4_Pin, GPIO_PIN_RESET);

		HAL_Delay(DELAY_VALUE);

		HAL_GPIO_WritePin(PHASE1_GPIO_Port, PHASE1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE2_GPIO_Port, PHASE2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE3_GPIO_Port, PHASE3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(PHASE4_GPIO_Port, PHASE4_Pin, GPIO_PIN_RESET);

		HAL_Delay(DELAY_VALUE);

		HAL_GPIO_WritePin(PHASE1_GPIO_Port, PHASE1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE2_GPIO_Port, PHASE2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE3_GPIO_Port, PHASE3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE4_GPIO_Port, PHASE4_Pin, GPIO_PIN_SET);

		HAL_Delay(DELAY_VALUE);
	}
	HAL_Delay(750);
}

/***********************************************************//**
*
* \descriere moveStepperToLeft
* - poziționează motorul pas cu pas înspre stânga cu 32 pași (o rotație completă are 2048 pași)
* - aplică un curent pe fiecare pin la car e conectat motorul pas cu pas, alternativ
*
***************************************************************/
void Model::moveStepperToLeft()
{
	for(int i = 0; i < NUMBER_OF_STEPS; i++)
	{
		HAL_GPIO_WritePin(PHASE1_GPIO_Port, PHASE1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE2_GPIO_Port, PHASE2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE3_GPIO_Port, PHASE3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE4_GPIO_Port, PHASE4_Pin, GPIO_PIN_SET);

		HAL_Delay(DELAY_VALUE);

		HAL_GPIO_WritePin(PHASE1_GPIO_Port, PHASE1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE2_GPIO_Port, PHASE2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE3_GPIO_Port, PHASE3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(PHASE4_GPIO_Port, PHASE4_Pin, GPIO_PIN_RESET);

		HAL_Delay(DELAY_VALUE);

		HAL_GPIO_WritePin(PHASE1_GPIO_Port, PHASE1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE2_GPIO_Port, PHASE2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(PHASE3_GPIO_Port, PHASE3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE4_GPIO_Port, PHASE4_Pin, GPIO_PIN_RESET);

		HAL_Delay(DELAY_VALUE);

		HAL_GPIO_WritePin(PHASE1_GPIO_Port, PHASE1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(PHASE2_GPIO_Port, PHASE2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE3_GPIO_Port, PHASE3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PHASE4_GPIO_Port, PHASE4_Pin, GPIO_PIN_RESET);

		HAL_Delay(DELAY_VALUE);
	}
	
	HAL_Delay(750);
}

/***********************************************************//**
*
* \descriere analogUpdatePA0
* - actualizează valoarea analogică citită de senzorul de lumină conectat la pinul PA0
* - face o medie aritmetică de 10 valori (smoothing)
* - poziționează motorul pas cu pas înspre dreapta dacă valoarea citită de la senzorul de lumină 
* conectat la pinul PA0 e mai mare decât valoarea citită de la senzorul de lumină 
* conectat la pinul PC1
* - oprește rotația dacă valoarea e mai mare decât o anumită valoare "ANALOGIC_MAX_VALUE"
*
***************************************************************/
void Model::analogUpdatePA0()
{
	uint32_t sumPA0 = 0;

	for(int i = 0; i < NUMBER_OF_VALUES; i++)
	{
		sumPA0 += oAdcConvertedValuePA0[i];
	}

	modelListener->analogUpdatePA0(sumPA0 / NUMBER_OF_VALUES);
	analogValuePA0 = sumPA0 / NUMBER_OF_VALUES / ANALOG_CALIB_VALUE;
	
	analogValuePA0_Graph = analogValuePA0;
	
	if((isControlModeAuto == true) && 
	(analogValuePA0 - analogValuePC1) > ANALOGIC_DIFFERENCE && 
	(analogValuePA0 < ANALOGIC_MAX_VALUE))
	{
		moveStepperToRight();
	}
}

/***********************************************************//**
*
* \descriere analogUpdatePC1
* - actualizează valoarea analogică citită de senzorul de lumină conectat la pinul PC1
* - face o medie aritmetică de 10 valori
* - poziționează motorul pas cu pas înspre stânga dacă valoarea citită de la senzorul de lumină 
* conectat la pinul PC1 e mai mare decât valoarea citită de la senzorul de lumină 
* conectat la pinul PA0
* - oprește rotația dacă valoarea e mai mare decât o anumită valoare "ANALOGIC_MAX_VALUE"
*
***************************************************************/
void Model::analogUpdatePC1()
{
	uint32_t sumPC1 = 0;

	for(int i = 0; i < NUMBER_OF_VALUES; i++)
	{
		sumPC1 += oAdcConvertedValuePC1[i];
	}

	modelListener->analogUpdatePC1(sumPC1 / NUMBER_OF_VALUES);
	analogValuePC1 = sumPC1 / NUMBER_OF_VALUES / ANALOG_CALIB_VALUE;
	
	analogValuePC1_Graph = analogValuePC1;
	
	if((isControlModeAuto == true) && 
	(analogValuePC1 - analogValuePA0) > ANALOGIC_DIFFERENCE && 
	(analogValuePC1 < ANALOGIC_MAX_VALUE))
	{
		moveStepperToLeft();
	}
}

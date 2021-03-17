#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "cmsis_os.h"
#include "main.h"
#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/motorscreen_screen/MotorScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include "mxconstants.h"
#include "stm32f4xx_hal.h"

extern osSemaphoreId_t myBinarySemAnalogHandle;
extern uint16_t oAdcConvertedValue[10];

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	if(myBinarySemAnalogHandle != NULL)
	{
		//if(osSemaphoreWait (myBinarySemAnalogHandle,100) == osOK)
		//{
		analogUpdate();
		//}
	}
}

void Model::analogUpdate()
{
	touchgfx::Slider sliderRPM;
	uint32_t sum = 0;
	int rotationStep = 1;

	for(int i = 0;i < 10; i++)
	{
		sum+=oAdcConvertedValue[i];
	}

	modelListener->analogUpdate(sum/10);
	analogValue = sum/10;

	if(analogValue > 1650)
	{
		for(int i = 0; i<32; i++)
		{
			HAL_GPIO_WritePin(PHASE1_GPIO_Port,PHASE1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PHASE2_GPIO_Port,PHASE2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PHASE3_GPIO_Port,PHASE3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PHASE4_GPIO_Port,PHASE4_Pin, GPIO_PIN_RESET);

			HAL_Delay(2);

			HAL_GPIO_WritePin(PHASE1_GPIO_Port,PHASE1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PHASE2_GPIO_Port,PHASE2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PHASE3_GPIO_Port,PHASE3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PHASE4_GPIO_Port,PHASE4_Pin, GPIO_PIN_RESET);

			HAL_Delay(2);

			HAL_GPIO_WritePin(PHASE1_GPIO_Port,PHASE1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PHASE2_GPIO_Port,PHASE2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PHASE3_GPIO_Port,PHASE3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PHASE4_GPIO_Port,PHASE4_Pin, GPIO_PIN_RESET);

			HAL_Delay(2);

			HAL_GPIO_WritePin(PHASE1_GPIO_Port,PHASE1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PHASE2_GPIO_Port,PHASE2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PHASE3_GPIO_Port,PHASE3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PHASE4_GPIO_Port,PHASE4_Pin, GPIO_PIN_SET);

			HAL_Delay(2);
		}

		HAL_Delay(1000);

		rotationStep *= 2;

		if(rotationStep == 512)
		{
			for(int i = 0; i<512; i++)
			{
				HAL_GPIO_WritePin(PHASE1_GPIO_Port,PHASE1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PHASE2_GPIO_Port,PHASE2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PHASE3_GPIO_Port,PHASE3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PHASE4_GPIO_Port,PHASE4_Pin, GPIO_PIN_SET);

				HAL_Delay(2);

				HAL_GPIO_WritePin(PHASE1_GPIO_Port,PHASE1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PHASE2_GPIO_Port,PHASE2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PHASE3_GPIO_Port,PHASE3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(PHASE4_GPIO_Port,PHASE4_Pin, GPIO_PIN_RESET);

				HAL_Delay(2);

				HAL_GPIO_WritePin(PHASE1_GPIO_Port,PHASE1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PHASE2_GPIO_Port,PHASE2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(PHASE3_GPIO_Port,PHASE3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PHASE4_GPIO_Port,PHASE4_Pin, GPIO_PIN_RESET);

				HAL_Delay(2);

				HAL_GPIO_WritePin(PHASE1_GPIO_Port,PHASE1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(PHASE2_GPIO_Port,PHASE2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PHASE3_GPIO_Port,PHASE3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PHASE4_GPIO_Port,PHASE4_Pin, GPIO_PIN_RESET);

				HAL_Delay(2);
			}

			HAL_Delay(1000);
			rotationStep /= 512;
		}
	}
}

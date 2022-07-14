#include <gui/mainscreen_screen/MainScreenView.hpp>
#include "string.h"
#include "mxconstants.h"
#include "main.h"

int analogValuePA0_Graph = 0;
int analogValuePC1_Graph = 0;

MainScreenView::MainScreenView()
{

}

void MainScreenView::setupScreen()
{
    MainScreenViewBase::setupScreen();
}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
}

/***********************************************************//**
*
* \descriere analogUpdatePA0 
* - transmite datele preluate de senzorul de lumină conectat la pinul PA0
* către interfață
*
***************************************************************/
void MainScreenView::analogUpdatePA0(uint32_t value)
{
	memset(&textLightSensorPA0Buffer, 0, TEXTLIGHTSENSORPA0_SIZE);
	Unicode::snprintf(textLightSensorPA0Buffer, sizeof(textLightSensorPA0Buffer), "%d", value / ANALOG_CALIB_VALUE);
	textLightSensorPA0.invalidate();
}

/***********************************************************//**
*
* \descriere analogUpdatePA0 
* - transmite datele preluate de senzorul de lumină conectat la pinul PC1
* către interfață
*
***************************************************************/
void MainScreenView::analogUpdatePC1(uint32_t value)
{
	memset(&textLightSensorPC1Buffer, 0, TEXTLIGHTSENSORPC1_SIZE);
	Unicode::snprintf(textLightSensorPC1Buffer, sizeof(textLightSensorPC1Buffer), "%d", value / ANALOG_CALIB_VALUE);
	textLightSensorPC1.invalidate();
}

/***********************************************************//**
*
* \descriere handleTickEvent 
* - reîncarcă graficul cu puncte reprezentând diferența dintre valorile 
* citite de senzori
*
***************************************************************/
void MainScreenView::handleTickEvent()
{
	if(analogValuePC1 > analogValuePA0)
		dGraphSensors.addDataPoint(analogValuePC1 - analogValuePA0);
	else
		dGraphSensors.addDataPoint(analogValuePA0 - analogValuePC1);
}

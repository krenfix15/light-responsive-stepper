#include <gui/mainscreen_screen/MainScreenView.hpp>
#include "string.h"

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

void MainScreenView::analogUpdate(uint32_t value)
{
	memset(&textLightBuffer,0,TEXTLIGHT_SIZE);
	Unicode::snprintf(textLightBuffer,sizeof(textLightBuffer),"%d", value);
	textLight.invalidate();
}

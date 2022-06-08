#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

class MainScreenView : public MainScreenViewBase
{
public:
    MainScreenView();
	
    virtual ~MainScreenView() {}
	
    virtual void setupScreen();
	
    virtual void tearDownScreen();
	
    virtual void analogUpdatePA0(uint32_t value);
	
	virtual void analogUpdatePC1(uint32_t value);
	
	void handleTickEvent();
	
protected:
	int tickCounter;
};

#endif // MAINSCREENVIEW_HPP

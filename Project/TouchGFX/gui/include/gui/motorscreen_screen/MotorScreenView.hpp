#ifndef MOTORSCREENVIEW_HPP
#define MOTORSCREENVIEW_HPP

#include <gui_generated/motorscreen_screen/MotorScreenViewBase.hpp>
#include <gui/motorscreen_screen/MotorScreenPresenter.hpp>

class MotorScreenView : public MotorScreenViewBase
{
public:
    MotorScreenView();
    virtual ~MotorScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // MOTORSCREENVIEW_HPP

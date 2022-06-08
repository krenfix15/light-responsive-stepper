#ifndef CONTROLSCREENVIEW_HPP
#define CONTROLSCREENVIEW_HPP

#include <gui_generated/controlscreen_screen/ControlScreenViewBase.hpp>
#include <gui/controlscreen_screen/ControlScreenPresenter.hpp>

class ControlScreenView : public ControlScreenViewBase
{
public:
    ControlScreenView();
    virtual ~ControlScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // CONTROLSCREENVIEW_HPP

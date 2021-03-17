#ifndef MOTORSCREENPRESENTER_HPP
#define MOTORSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MotorScreenView;

class MotorScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MotorScreenPresenter(MotorScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~MotorScreenPresenter() {};

private:
    MotorScreenPresenter();

    MotorScreenView& view;
};

#endif // MOTORSCREENPRESENTER_HPP

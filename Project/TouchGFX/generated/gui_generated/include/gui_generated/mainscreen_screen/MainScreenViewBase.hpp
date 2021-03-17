/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MAINSCREENVIEWBASE_HPP
#define MAINSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class MainScreenViewBase : public touchgfx::View<MainScreenPresenter>
{
public:
    MainScreenViewBase();
    virtual ~MainScreenViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image bkg;
    touchgfx::Image imgStepper;
    touchgfx::Image logo;
    touchgfx::Button btnGoToMotorScreen;
    touchgfx::TextAreaWithOneWildcard textLight;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTLIGHT_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textLightBuffer[TEXTLIGHT_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<MainScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // MAINSCREENVIEWBASE_HPP

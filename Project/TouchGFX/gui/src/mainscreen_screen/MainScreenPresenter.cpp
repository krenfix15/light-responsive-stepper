#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

MainScreenPresenter::MainScreenPresenter(MainScreenView& v)
    : view(v)
{

}

void MainScreenPresenter::activate()
{

}

void MainScreenPresenter::deactivate()
{

}

void MainScreenPresenter::analogUpdatePA0(uint32_t value)
{
	view.analogUpdatePA0(value);
}

void MainScreenPresenter::analogUpdatePC1(uint32_t value)
{
	view.analogUpdatePC1(value);
}

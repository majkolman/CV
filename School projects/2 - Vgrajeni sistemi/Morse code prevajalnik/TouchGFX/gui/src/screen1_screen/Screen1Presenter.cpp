#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}
//klicemo funkcije za prikaz na zaslonu
void Screen1Presenter::updateText(int value)
{
	view.updateText(value);
}

void Screen1Presenter::updateMorse(int velikost)
{
	view.updateMorse(velikost);
}

void Screen1Presenter::updatePrevedeno(){
	view.updatePrevedeno();
};

void Screen1Presenter::updateTime(uint16_t value)
{
	view.updateTime(value);
}

void Screen1Presenter::updateTimeBetween(uint16_t value)
{
	view.updateTimeBetween(value);
}

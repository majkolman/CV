#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();


    //definicije uporabljenih funkcij
    virtual void function1();

    virtual void updateText(int value);
    virtual void updateMorse(int velikost);
    virtual void updatePrevedeno();
    virtual void updateTime(uint16_t value);
    virtual void updateTimeBetween(uint16_t value);
protected:
};

#endif // SCREEN1VIEW_HPP

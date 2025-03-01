/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen3_screen/Screen3ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen3ViewBase::Screen3ViewBase() :
    interaction1Counter(0)
{
    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    tiledImage1.setBitmap(touchgfx::Bitmap(BITMAP_GLASS_THEME_IMAGES_BACKGROUNDS_480X272_GRADIENT_LINES_ID));
    tiledImage1.setPosition(0, 0, 480, 272);
    tiledImage1.setOffset(0, 0);
    add(tiledImage1);

    textArea1.setXY(52, 88);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_R9V3));
    add(textArea1);
}

Screen3ViewBase::~Screen3ViewBase()
{

}

void Screen3ViewBase::setupScreen()
{
    transitionBegins();
}

void Screen3ViewBase::transitionBegins()
{
    //Interaction1
    //When screen transition begins delay
    //Delay for 1000 ms (60 Ticks)
    interaction1Counter = INTERACTION1_DURATION;
}

void Screen3ViewBase::handleTickEvent()
{
    if (interaction1Counter > 0)
    {
        interaction1Counter--;
        if (interaction1Counter == 0)
        {
                //Interaction2
                //When Interaction1 completed change screen to Screen1
                //Go to Screen1 with screen transition towards East
                application().gotoScreen1ScreenWipeTransitionEast();
        }
    }
}

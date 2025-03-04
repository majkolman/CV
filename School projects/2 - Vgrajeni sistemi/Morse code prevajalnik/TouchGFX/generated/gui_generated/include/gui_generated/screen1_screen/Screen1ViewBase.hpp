/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN1VIEWBASE_HPP
#define SCREEN1VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TiledImage.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/ButtonWithIcon.hpp>

class Screen1ViewBase : public touchgfx::View<Screen1Presenter>
{
public:
    Screen1ViewBase();
    virtual ~Screen1ViewBase();
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void function1()
    {
        // Override and implement this function in Screen1
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box2;
    touchgfx::TiledImage tiledImage1;
    touchgfx::TextAreaWithOneWildcard textArea1;
    touchgfx::TextAreaWithOneWildcard time;
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea3;
    touchgfx::TextArea textArea4;
    touchgfx::TextAreaWithOneWildcard timeBetween;
    touchgfx::TextArea textArea5;
    touchgfx::TextAreaWithOneWildcard morse;
    touchgfx::TextArea textArea6;
    touchgfx::TextAreaWithOneWildcard prevedenoText;
    touchgfx::ButtonWithLabel buttonWithLabel1;
    touchgfx::ButtonWithLabel buttonWithLabel2;
    touchgfx::ButtonWithIcon buttonWithIcon1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA1_SIZE = 36;
    touchgfx::Unicode::UnicodeChar textArea1Buffer[TEXTAREA1_SIZE];
    static const uint16_t TIME_SIZE = 10;
    touchgfx::Unicode::UnicodeChar timeBuffer[TIME_SIZE];
    static const uint16_t TIMEBETWEEN_SIZE = 10;
    touchgfx::Unicode::UnicodeChar timeBetweenBuffer[TIMEBETWEEN_SIZE];
    static const uint16_t MORSE_SIZE = 36;
    touchgfx::Unicode::UnicodeChar morseBuffer[MORSE_SIZE];
    static const uint16_t PREVEDENOTEXT_SIZE = 36;
    touchgfx::Unicode::UnicodeChar prevedenoTextBuffer[PREVEDENOTEXT_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen1ViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // SCREEN1VIEWBASE_HPP

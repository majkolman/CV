#include <gui/screen1_screen/Screen1View.hpp>

#include <string.h>
#include "stm32h7xx_hal.h"

extern uint8_t buffer[36];
extern int wait;
extern int maxvalue;
extern uint8_t beseda[36];
extern uint8_t prevedeno[36];
extern int reset;



void clearT(uint8_t t[]) {
	for (int i = 0; t[i] != 0; i++) {
		t[i] = 0;
	}
}


Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

//Text vnesen z UART-om prikazemo na zaslonu s tem da ga shranimo v Buffer besedilnega polja
void Screen1View::updateText(int value)
{
	for(int i = 0; i < maxvalue; i++){
		textArea1Buffer[i] = 0;
	}
	value--;
	while(value){
		textArea1Buffer[value] = buffer[value];
		value--;
	}
	textArea1Buffer[value] = buffer[value];
	textArea1.invalidate();
	wait = 0;
}

//vnesen morse shranimo v Buffer besedilnega polja
void Screen1View::updateMorse(int velikost)
{
	while(velikost){
		morseBuffer[velikost] = beseda[velikost];
		velikost--;
	}
	morseBuffer[velikost] = beseda[velikost];
	morse.invalidate();
}

//Preveden morse shranimo v Buffer besedilnega polja
void Screen1View::updatePrevedeno(){
	for(int i = 0; i < maxvalue; i++)prevedenoTextBuffer[i] = 0;
	for(int i = 0; prevedeno[i] != 0; i++){
		prevedenoTextBuffer[i] = prevedeno[i];
	}
	prevedenoText.invalidate();
}

//cas pritiska shranimo v Buffer
void Screen1View::updateTime(uint16_t value)
{
	Unicode::snprintf(timeBuffer, TIME_SIZE, "%d", value);
	time.invalidate();
}

//cas med pritiski shranimo v Buffer
void Screen1View::updateTimeBetween(uint16_t value)
{
	Unicode::snprintf(timeBetweenBuffer, TIMEBETWEEN_SIZE, "%d", value);
	timeBetween.invalidate();
}

//ko pritisnemo gumb Zbriši se klice ta funkcija
//nastavimo flag reset in zbrisemo vnesen morse in njegov prevod
void Screen1View::function1()
{
	reset = 1;
	clearT(beseda);
	clearT(prevedeno);
}





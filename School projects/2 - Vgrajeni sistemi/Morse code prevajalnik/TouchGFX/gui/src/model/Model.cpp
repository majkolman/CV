#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "stm32h7xx_hal.h"
extern __IO uint8_t wait;
extern int ind;
extern uint16_t timePressed;
extern uint16_t timeBetween;
extern int velikost;

Model::Model() : modelListener(0)
{

}

//vsak tick posodobimo zaslon
void Model::tick()
{
	if(wait)
	{
		wait = 0;
		modelListener->updateText(ind);
		ind = 0;
	}

	modelListener->updateMorse(velikost);
	modelListener->updatePrevedeno();

	modelListener->updateTime(timePressed);
	modelListener->updateTimeBetween(timeBetween);
}

#ifndef STATES_H
#define STATES_H

#include "main.h"
#include "graphics.h"

enum GameStates{
    STATE_NULL,
    STATE_INTRO,
    STATE_MENU,
    STATE_GAME_B,
    STATE_GAME_I,
    STATE_GAME_A,
    STATE_EXIT,
};

class CStates {

	public:

    virtual void handleEvents(void) = 0;
    virtual GameStates getNextState(void) = 0;
    virtual void Render(CGraphics*) = 0;

};

#endif

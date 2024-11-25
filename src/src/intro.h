#ifndef INTRO_H
#define INTRO_H

#include "main.h"
#include "graphics.h"
#include "gamestates.h"

class CIntro: public CStates {

	private:

		SDL_Surface* image; // CIntro Image

		GameStates nextState;

		SDL_Event events; // The event structure that will be used

	protected:

		void handleKeyboard();

	public:
		CIntro(CGraphics*);
		~CIntro();

    void handleEvents(void);
    GameStates getNextState(void){
			return nextState;
		}
    void Render(CGraphics*);

};

#endif

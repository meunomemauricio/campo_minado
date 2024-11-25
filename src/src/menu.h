#ifndef MENU_H
#define MENU_H

#include "main.h"
#include "graphics.h"
#include "gamestates.h"
#include "mbuttons.h"

/* Menu Buttons Number */
#define NMBUTTON						3

/* Menu Buttons Dimensions */
#define MBUTTONW						200
#define MBUTTONH						50
#define MBUTTONX						60

#define MBUTTONYB						80
#define MBUTTONYI						140
#define MBUTTONYA						200

using std::vector;

class CMenu : public CStates {

	private:

		CMenuButtons** buttons; // Buttons Array

		SDL_Surface* menuBkg; // CMenu Image
    SDL_Surface* mbuttons; // CMenu Button Images

    GameStates nextState;

    SDL_Event events; // The event structure that will be used

    int mouseY; // Mouse Coordinates Related to the array of buttons

	protected:

		void getMouseCoordinates(void);
		void handleMouse(void); // Handle mouse events
		void pressButton(void); // Press a Button Down
		void Click(void); // Clicks a Button when it's released

	public:
		CMenu(CGraphics*);
		~CMenu();

		void handleEvents();
		GameStates getNextState(void){
			return nextState;
		}
    void Render(CGraphics*);

};


#endif

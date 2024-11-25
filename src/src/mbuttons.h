#ifndef MBUTTONS_H
#define MBUTTONS_H

#include "main.h"

/* Menu Buttons Dimensions */
#define MBUTTONW						200
#define MBUTTONH						50

enum MenuButtons{
	MENU_BASIC,
	MENU_INTER,
	MENU_ADVANCED,
};

class CMenuButtons{

	private:

		SDL_Rect* dim;

		SDL_Rect* clip;

		MenuButtons value;

		bool pressed;

	public:
		CMenuButtons();
		~CMenuButtons();

		void setClip(void); //Set the button Clip
		void setDim(int,int,int,int); //Set the Buttom Dim
		void setValue(MenuButtons val){ //Sets the Button value
			value = val;
		}
		int getValue(void){ // Returns button Value
			return value;
		}
		SDL_Rect* getDim(void){ //Returns Button Dimensions
			return dim;
		}
		SDL_Rect* getClip(void){ //Returns the Clip
			return clip;
		}
		void pressDown(void){ // Press the button Down
			pressed = true;
		}
		void Unpress(void){ // Releases the button
			pressed = false;
		}

};

#endif

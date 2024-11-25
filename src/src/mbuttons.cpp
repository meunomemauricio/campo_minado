#include "mbuttons.h"

CMenuButtons::CMenuButtons(){

	pressed = false;

	dim = new SDL_Rect;

	clip = new SDL_Rect;

}

CMenuButtons::~CMenuButtons(){

	delete dim;
	delete clip;

}

void CMenuButtons::setDim(int x, int y, int w, int h){

	dim->x = x;
	dim->y = y;
	dim->w = w;
	dim->h = h;

}

void CMenuButtons::setClip(void){

	switch(value){

		case MENU_BASIC:
			clip->y = 0;
			break;

		case MENU_INTER:
			clip->y = (MBUTTONH);
			break;

		case MENU_ADVANCED:
			clip->y = (2*MBUTTONH);
			break;

	}

	if(pressed){
		clip->x = MBUTTONW;
	}
	else{
		clip->x = 0;
	}

	clip->w = MBUTTONW;
	clip->h = MBUTTONH;

}

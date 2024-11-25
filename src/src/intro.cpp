#include "intro.h"

CIntro::CIntro(CGraphics* graphics){

	graphics->setSize(320,320);

	image = CGraphics::loadImage("Arquivos/Intro.bmp");

	nextState = STATE_NULL;

}

CIntro::~CIntro(){
	SDL_FreeSurface( image );
}

void CIntro::handleEvents(void){

	while( SDL_PollEvent(&events) ){

    if(events.type == SDL_QUIT){ //If user trys to close the window
      nextState = STATE_EXIT;
    }

    handleKeyboard();

  }

}

void CIntro::handleKeyboard(void){

	Uint8 *keystates = SDL_GetKeyState( NULL );

  // If Enter is Pressed
  if((keystates[SDLK_RETURN]||keystates[SDLK_KP_ENTER])){

    nextState = STATE_MENU;

    //nextState = STATE_GAME; //Temp! While CMenu is under construction

  }

}

void CIntro::Render(CGraphics* graphics){

	CGraphics::applySurface(0,0, image, graphics->getScreen(), NULL);

}

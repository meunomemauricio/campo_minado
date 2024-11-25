#include "menu.h"

CMenu::CMenu(CGraphics* graphics){

	graphics->setSize(320,320);

	menuBkg = CGraphics::loadImage("Arquivos/Menu.bmp");
	mbuttons = CGraphics::loadImage("Arquivos/BotoesM.bmp");

	buttons = new CMenuButtons*[NMBUTTON];

	int i;

	for(i=0;i<NMBUTTON;i++){
		buttons[i] = new CMenuButtons;
	}

	buttons[0]->setValue(MENU_BASIC);
	buttons[1]->setValue(MENU_INTER);
	buttons[2]->setValue(MENU_ADVANCED);

	buttons[0]->setDim(MBUTTONX,MBUTTONYB,MBUTTONW,MBUTTONH);
	buttons[1]->setDim(MBUTTONX,MBUTTONYI,MBUTTONW,MBUTTONH);
	buttons[2]->setDim(MBUTTONX,MBUTTONYA,MBUTTONW,MBUTTONH);

	nextState = STATE_NULL;

	mouseY = 0;

}

CMenu::~CMenu(){

	int i;

	for(i=0;i<NMBUTTON;i++){
		delete buttons[i];
	}

	SDL_FreeSurface( menuBkg );
	SDL_FreeSurface( mbuttons );
}

void CMenu::handleEvents(void){

	while( SDL_PollEvent(&events) ){

    if(events.type == SDL_QUIT){ //If user trys to close the window
      nextState = STATE_EXIT;
    }

    handleMouse();

  }

}

void CMenu::getMouseCoordinates(void){

	int i;
	int x, y;

	x = events.button.x;
	y = events.button.y;

	mouseY = NMBUTTON;

	if((x > 60)&&(x < 260)){

		for(i=0;i<NMBUTTON;i++){

			if((y > buttons[i]->getDim()->y) &&
					(y < (buttons[i]->getDim()->y + buttons[i]->getDim()->h))){

				mouseY = i;
			}
		}
	}

}

void CMenu::handleMouse(void){

	switch(events.type){
  	case SDL_MOUSEMOTION:
  	case SDL_MOUSEBUTTONDOWN:

			if(SDL_GetMouseState(NULL, NULL)&(SDL_BUTTON(1))){
				pressButton();
			}

  		break;

  	case SDL_MOUSEBUTTONUP:

			if(events.button.button == SDL_BUTTON_LEFT){
				Click();
			}
  		break;
	}

}

void CMenu::pressButton(void){

  getMouseCoordinates();

	if(mouseY < NMBUTTON){
		buttons[mouseY]->pressDown();
	}

}

void CMenu::Click(void){

	getMouseCoordinates();

	if(mouseY < NMBUTTON){

		switch(buttons[mouseY]->getValue()){

		case MENU_BASIC:
			nextState = STATE_GAME_B;
			break;

		case MENU_INTER:
			nextState = STATE_GAME_I;
			break;

		case MENU_ADVANCED:
			nextState = STATE_GAME_A;
			break;

		}
	}

}

void CMenu::Render(CGraphics* graphics){

	CGraphics::applySurface(0,0, menuBkg, graphics->getScreen(),NULL);

	int i;

	for(i=0;i<NMBUTTON;i++){

		if(i != mouseY){
       buttons[i]->Unpress();
		}

		buttons[i]->setClip();

		CGraphics::applySurface(buttons[i]->getDim()->x,
														buttons[i]->getDim()->y,
														mbuttons,
														graphics->getScreen(),
														buttons[i]->getClip());

	}

}

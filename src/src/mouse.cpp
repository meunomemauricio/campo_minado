#include "game.h"

void CGame::clearButtonStates(void){

	int i,j;

	for(i=0; i < (bWidth); i++){
		for(j=0; j < (bHeight); j++){

			bMatrix.at((j*bWidth)+i).unHighLight();
			bMatrix.at((j*bWidth)+i).unPress();

		}
	}

}

void CGame::mouseMotion(void){

	Highlight();

	//If left or right button was pressed and dragged
	if(SDL_GetMouseState(NULL, NULL)&(SDL_BUTTON(1)|SDL_BUTTON(3))){
			pressButton();
	}

	//If middle button was pressed and dragged
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(2)){
			middlePress();
	}

}

void CGame::mousePress(void){

	switch(events.button.button){
		case SDL_BUTTON_LEFT:
		case SDL_BUTTON_RIGHT:
			pressButton();
			break;

		case SDL_BUTTON_MIDDLE:
			middlePress();
			break;
	}

}

void CGame::mouseRelease(void){

	//Handles the first move of the game.
	if(firstMove){
		doFirstMove();
	}

	else{

		switch(events.button.button){
			case SDL_BUTTON_LEFT: //If Left Button was Clicked
				getMouseCoordinates();
				Click(mouseX,mouseY);
				break;

			case SDL_BUTTON_RIGHT: //If Right Button was Clicked
				insertFlag();
				break;

			case SDL_BUTTON_MIDDLE: //If Middle Button was Clicked
				//getMouseCoordinates();
				//bMatrix[(mouseY*bWidth)+mouseX].unPress();
				middleClick();
				break;

		}

	}

}

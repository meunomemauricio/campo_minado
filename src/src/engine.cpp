#include "engine.h"

CEngine::CEngine(void){

  graphics = new CGraphics();

  currentState = new CIntro(graphics); //Starts aplication with the CIntro

  stateID = STATE_NULL;
	nextState = STATE_NULL;

}

CEngine::~CEngine(void){

  delete graphics;
  delete currentState;

  SDL_Quit();

}

void CEngine::Init(void){

  //Initiate SDL and log into file if an error ocurrs
  if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 ){
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
  }

  atexit (SDL_Quit); //Call SDL_Quit at program exit.

}

void CEngine::Start(void){

	graphics->setTitle("Campo Minado");

	//Main Loop
	while( stateID != STATE_EXIT ){

		currentState->handleEvents();

		nextState = currentState->getNextState();

		changeState();

		currentState->Render(graphics);

		SDL_Flip(graphics->getScreen());

	}

}

void CEngine::changeState(void){

	//If the state needs to be changed
	if( nextState != STATE_NULL )
	{

		if( nextState != STATE_EXIT )
		{
			delete currentState;
		}

		//Change the state
		switch( nextState )
		{
			case STATE_MENU:
				currentState = new CMenu(graphics);
				break;

			case STATE_GAME_B: // Game with Basic dificulty
				currentState = new CGame(graphics,STATE_GAME_B);
				break;

			case STATE_GAME_I: // Game with Intermediate dificulty
				currentState = new CGame(graphics,STATE_GAME_I);
				break;

			case STATE_GAME_A: // Game with Advanced dificulty
				currentState = new CGame(graphics,STATE_GAME_A);
				break;
		}

		stateID = nextState;

		//NULL the next state ID
		nextState = STATE_NULL;
	}

}

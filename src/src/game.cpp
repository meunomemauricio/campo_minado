#include "game.h"

CGame::CGame(CGraphics* graphics, GameStates l){

	buttons = CGraphics::loadImage("Arquivos/botoesG.bmp");
	framesImage = CGraphics::loadImage("Arquivos/Borda.bmp");

	setLevel(l); // Set the Game Level

	//set size to Board + Frame
	graphics->setSize((bWidth*BSIZE)+64,(bHeight*BSIZE)+80);

	setFrame(); // Draw the frame

	//Allocate memory for the board
	bMatrix.assign ((bWidth*bHeight),CGameCells());

	firstMove = true;

	gameOver = false;

	flagCount = 0;

	nextState = STATE_NULL;

	mouseX = 0;
	mouseY = 0;

	gameTimer = new CTimer; // Construct the timer

}

CGame::~CGame(){

	bMatrix.clear();

	SDL_FreeSurface( buttons );
	SDL_FreeSurface( frame );
	SDL_FreeSurface( framesImage );

	delete gameTimer;

}

void CGame::setLevel(GameStates l){

	level = l;

	switch(level){
		case STATE_GAME_B:

			mineNumber = 10;
			bWidth = 9;
			bHeight = 9;

			break;

		case STATE_GAME_I:

			mineNumber = 40;
			bWidth = 16;
			bHeight = 16;

			break;

		case STATE_GAME_A:

			mineNumber = 99;
			bWidth = 30;
			bHeight = 16;

			break;
	}

}

void CGame::handleEvents(void){

	while( SDL_PollEvent(&events) ){

		if(events.type == SDL_QUIT){ //If user trys to close the window
			nextState = STATE_EXIT;
		}

		handleMouse();
		handleKeyboard();

  }

}

void CGame::Render(CGraphics* graphics){

  SDL_Color textColor = { 255, 0, 0 };

  stringstream oss, oss2;
  string text;

	int i,j;

  CGraphics::applySurface(0,0,frame,graphics->getScreen(),NULL);

  for(i=0; i < (bWidth); i++){
    for(j=0; j < (bHeight); j++){

      bMatrix.at((j*(bWidth))+i).setClip();

      CGraphics::applySurface((i*BSIZE)+32,
															(j*BSIZE)+48,
															buttons,
															graphics->getScreen(),
															(bMatrix.at((j*(bWidth))+i).getClip()));
    }
  }

  oss << int(gameTimer->getTicks()/1000);
  text = oss.str();
  graphics->printMessage(((bWidth*BSIZE)/2)+40,11,text,textColor);

	oss2 << (mineNumber-flagCount);
  text = oss2.str();
  graphics->printMessage(((bWidth*BSIZE)/2)+40,26,text,textColor);

  SDL_Flip( graphics->getScreen() );

}

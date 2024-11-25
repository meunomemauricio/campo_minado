#include "game.h"

void CGame::putMines(void){

  int b, i , j;

  srand ((unsigned int) time(NULL));

	b = 0;

	do{
		i = ((rand() % bWidth ));
		j = ((rand() % bHeight ));

		if ((!bMatrix[(j*(bWidth))+i].isMine()) &&
          !((i == mouseX) && (j == mouseY))){

		  bMatrix[(j*(bWidth))+i].setValue(MINE);
			b++;

		}
	}while (b < mineNumber);

}

void CGame::fillBoard(void){

  int a, b, i, j;

	for(a=0; a < bWidth; a++){
		for(b=0; b < bHeight; b++){

      if(!bMatrix[(b*(bWidth))+a].isMine()){

        for(i=-1; i <= 1; i++){
          for(j=-1; j <= 1; j++){

            if(((a-i) >= 0) && ((a-i)<(bWidth))
                && ((b-j) >= 0) && ((b-j)<(bHeight))){

              if(bMatrix[((b-j)*(bWidth))+(a-i)].isMine()){
                bMatrix[(b*(bWidth))+a].increaseValue();
              }

            }
          }
        }
      }
      bMatrix[(b*(bWidth))+a].setClip();
		}
	}
}

int CGame::getAdjFlags(void){

	int i, j;
	int adjFlags = 0;

	for (i = -1; i <= 1 ; i++ ){
		for (j = -1; j <= 1 ; j++ ){

			if(((mouseX-i) >= 0) && ((mouseX-i)<(bWidth)) &&
					((mouseY-j) >= 0) && ((mouseY-j)<(bHeight))){

				if(bMatrix[(((mouseY-j))*bWidth)+(mouseX-i)].isFlag()){
					adjFlags++;
				}

			}

		}
	}

	return adjFlags;

}

void CGame::doFirstMove(void){
	putMines();
	fillBoard();
	firstMove  = false;
	getMouseCoordinates();
	Click(mouseX,mouseY);
	gameTimer->Start();
}


void CGame::getMouseCoordinates(void){

	int x,y;

	x = events.motion.x;
	y = events.motion.y;

	if((x >= 32) && (x <= (bWidth*BSIZE)+32) &&
			(y >= 48) && (y <= (bHeight*BSIZE)+48)){

		mouseX = ((x-32)/BSIZE);
		mouseY = ((y-48)/BSIZE);

		if(((mouseX > bWidth) && (mouseY > bHeight)) || (mouseX < 0 && mouseY < 0)){
			mouseX = bWidth;
			mouseY = bHeight;
		}

	}

}

void CGame::handleMouse(void){

	if(!gameOver){

		clearButtonStates();

		switch(events.type){

			case SDL_MOUSEMOTION:
				mouseMotion();
				break;

			case SDL_MOUSEBUTTONDOWN:
				mousePress();
				break;

			case SDL_MOUSEBUTTONUP:
				mouseRelease();
				break;
		}

  }

}

void CGame::handleKeyboard(void){

	Uint8 *keystates = SDL_GetKeyState( NULL );

  // If F2 is pressed
  if(keystates[SDLK_F2]){
  	nextState = level;
  }

	// If Esc is pressed
  if(keystates[SDLK_ESCAPE]){
  	nextState = STATE_MENU;
  }

	// If Game is over and Enter is pressed
	if(gameOver){
		if((keystates[SDLK_RETURN]||keystates[SDLK_KP_ENTER])){
			nextState = STATE_MENU;
		}
	}

}


void CGame::Click(int x, int y){

	if(x < bWidth && y < bHeight){

		if(!bMatrix[(y*bWidth)+x].isFlag()&&
					bMatrix[(y*bWidth)+x].isHidden()){

			switch(bMatrix[(y*bWidth)+x].getValue()){

				case MINE:
					bMatrix[(y*bWidth)+x].setLastClick();
					endGame(false); //Ends CGame with win = false.
					break;

				case EMPTY:
					bMatrix[(y*bWidth)+x].unHide();
					clickEmpty(x,y);
					break;

				default:
					bMatrix[(y*bWidth)+x].unHide();
					if(checkVictory()){
						endGame(true);
					}
					break;
			}

		}

	}

}

void CGame::Highlight(void){

  getMouseCoordinates();

  if(mouseX < bWidth && mouseY < bHeight){

		bMatrix[(mouseY*bWidth)+mouseX].highLight();
  }

}

void CGame::insertFlag(void){

  getMouseCoordinates();

  if(mouseX < bWidth && mouseY < bHeight){

		if(bMatrix[(mouseY*bWidth)+mouseX].isHidden()){

			if((!bMatrix.at((mouseY*bWidth)+mouseX).isFlag()) && (flagCount < mineNumber)){
				bMatrix[(mouseY*bWidth)+mouseX].setFlag(true);
				flagCount++;
			}

			else if(bMatrix[(mouseY*bWidth)+mouseX].isFlag()){
				bMatrix[(mouseY*bWidth)+mouseX].setFlag(false);
				flagCount--;
			}

		}

	}

}

void CGame::pressButton(void){

  getMouseCoordinates();

  if(mouseX < bWidth && mouseY < bHeight){

		bMatrix[(mouseY*bWidth)+mouseX].pressDown();
	}

}

void CGame::clickEmpty(int x,int y){

  int i, j;

  for (i = -1; i <= 1 ; i++ ){
  	for (j = -1; j <= 1 ; j++ ){

      if(((x-i) >= 0) && ((x-i)<(bWidth)) &&
          ((y-j) >= 0) && ((y-j)<(bHeight))){

        if(!((i == 0) && (j == 0)))
          Click((x-i),(y-j));
        }

      }

  	}
  }

void CGame::middlePress(void){

  getMouseCoordinates();

  if(mouseX < bWidth && mouseY < bHeight){

		int i, j;

		for (i = -1; i <= 1 ; i++ ){
			for (j = -1; j <= 1 ; j++ ){

				if(((mouseX+i) >= 0) && ((mouseX+i) < bWidth) &&
						((mouseY+j) >= 0) && ((mouseY+j) < bHeight)){

					if((bMatrix[((mouseY + j)*bWidth)+(mouseX + i)].isHidden()) &&
						 !(bMatrix[((mouseY + j)*bWidth)+(mouseX + i)].isFlag())){

						bMatrix[((mouseY + j)*bWidth)+(mouseX + i)].pressDown();

					}

				}

			}
		}

  }

}

void CGame::middleClick(void){

  getMouseCoordinates();

  if(mouseX < bWidth && mouseY < bHeight){

		if(bMatrix[(mouseY*bWidth)+mouseX].getValue() != EMPTY){

			int i, j;
			int adjFlags = 0;

			adjFlags = getAdjFlags();

			for (i = -1; i <= 1 ; i++ ){
				for (j = -1; j <= 1 ; j++ ){

					if(((mouseX-i) >= 0) && ((mouseX-i)<(bWidth)) &&
							((mouseY-j) >= 0) && ((mouseY-j)<(bHeight))){


						if((adjFlags == int(bMatrix[((mouseY)*bWidth)+(mouseX)].getValue()))){

							Click((mouseX-i),(mouseY-j));

						}

					}

				}
			}

		}
	}

}


bool CGame::checkVictory(void){

  int i,j;
  int unhiddenButtons = 0;

  for(i=0; i < (bWidth); i++){
    for(j=0; j < (bHeight); j++){

      if(!bMatrix[(j*bWidth)+i].isHidden()){
      	unhiddenButtons++;
      }

    }
  }

  if(unhiddenButtons == ((bWidth * bHeight) - mineNumber)){
    return true;
  }

  return false;

}

void CGame::endGame(bool win){

	gameTimer->Pause();

  int i,j;

  if(win){
    for ( i=0 ; i < bWidth ; i++ ){
      for ( j=0 ; j < bHeight ; j++ ){

        if (bMatrix[(j*bWidth)+i].isMine()){
          bMatrix[(j*bWidth)+i].setFlag(true);
          flagCount = mineNumber;
        }

      }
    }
  }

  else{

    for ( i=0 ; i < bWidth ; i++ ){
      for ( j=0 ; j < bHeight ; j++ ){

        if (bMatrix[(j*bWidth)+i].isMine()){
          bMatrix[(j*bWidth)+i].unHide();
        }

        if(bMatrix[(j*bWidth)+i].isFlag() && !bMatrix[(j*bWidth)+i].isMine()){
					bMatrix[(j*bWidth)+i].setWrongFlag();
					bMatrix[(j*bWidth)+i].unHide();
				}

      }
    }
  }

  gameOver = true;

}

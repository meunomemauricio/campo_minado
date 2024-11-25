#include "cells.h"

CGameCells::CGameCells(void){

  value = EMPTY;
  hidden = true;
  pressed = false;
  lastclick = false;
  flag = false;
  highlighted = false;
  wrongFlag = false;


  clip = new SDL_Rect();

}

CGameCells::~CGameCells(){
	delete clip;
}

void CGameCells::setFlag(bool f){
  	flag = f;
}

void CGameCells::setClip(void){

  if(hidden){
		if(flag){
			clip->x = (7*BSIZE);
			clip->y = BSIZE;
		}

		else if(pressed){ //Button is Pressed
			clip->x = (4*BSIZE);
			clip->y = BSIZE;
		}

		else if(highlighted){ // Button is Highlighted
			clip->x = (6*BSIZE);
			clip->y = BSIZE;
		}

		else{ // Button is just hidden.
			clip->x = (5*BSIZE);
			clip->y = BSIZE;
		}
  }

  else{

    switch(value){
      case EMPTY: //An empty cell
        clip->x = (4*BSIZE);
        clip->y = BSIZE;
        break;

      case MINE:
        if(lastclick){ // The mine that was steped
          clip->x = 0;
          clip->y = BSIZE;
        }
        else if(flag){ // A Mine that player was aware of (marked with flag)
          clip->x = (3*BSIZE);
          clip->y = BSIZE;
        }
        else{ // A Mine that was still Hidden
          clip->x = (2*BSIZE);
          clip->y = BSIZE;
        }
        break;

      default: // A cell with a number.
				if(wrongFlag){
        	clip->x = BSIZE;
					clip->y = BSIZE;
        }
        else{
					clip->x = ((value-1)*BSIZE);
					clip->y = 0;
        }
        break;

    }

  }

  clip->w = BSIZE;
  clip->h = BSIZE;
}

void CGameCells::unHighLight(void){
  highlighted = false;
  pressed = false;
}

void CGameCells::setWrongFlag(void){
	flag = false;
	wrongFlag = true;
}

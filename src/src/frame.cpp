#include "game.h"

void CGame::setFrame(void){

	SDL_Rect* clip = new SDL_Rect;

	//Init frame as an empty surface
	frame = SDL_CreateRGBSurface(SDL_SWSURFACE,
																(bWidth*BSIZE)+64,(bHeight*BSIZE)+80,
																BPP,0,0,0,0);

	placeSideFrames(clip);
	placeCornerFrames(clip);
	placeOtherFrames(clip);

	delete clip;

}

void CGame::placeCornerFrames(SDL_Rect* clip){

	clip->x = 0;
	clip->y = 0;
	clip->w = 32;
	clip->h = 48;

	CGraphics::applySurface(0,0,framesImage,frame, clip);

	clip->x = 320;
	clip->y = 0;
	clip->w = 32;
	clip->h = 48;

	CGraphics::applySurface((bWidth*BSIZE)+32,0,framesImage,frame, clip);

	clip->x = 0;
	clip->y = 48;
	clip->w = 32;
	clip->h = 32;

	CGraphics::applySurface(0,(bHeight*BSIZE)+48,framesImage,frame, clip);

	clip->x = 48;
	clip->y = 48;
	clip->w = 32;
	clip->h = 32;

	CGraphics::applySurface((bWidth*BSIZE)+32,(bHeight*BSIZE)+48,
														framesImage,frame, clip);

}

void CGame::placeSideFrames(SDL_Rect* clip){

	clip->x = 80;
	clip->y = 64;
	clip->w = 32;
	clip->h = 16;

	int i;

	for(i=0; i< bHeight; i++){ // Left Side
		CGraphics::applySurface(0,(48+i*16),framesImage,frame, clip);
	}

	clip->x = 80;
	clip->y = 48;
	clip->w = 32;
	clip->h = 16;

	for(i=0; i< bHeight; i++){ // Right Side
		CGraphics::applySurface((bWidth*BSIZE)+32,(48+i*16),framesImage,frame, clip);
	}

	clip->x = 32;
	clip->y = 0;
	clip->w = 16;
	clip->h = 48;

	for(i=0; i< bWidth; i++){ // Up Side
		CGraphics::applySurface((32+i*16),0,framesImage,frame, clip);
	}

	clip->x = 32;
	clip->y = 48;
	clip->w = 16;
	clip->h = 32;

	for(i=0; i< bWidth; i++){ // Down Side
		CGraphics::applySurface((32+i*16),(bHeight*BSIZE)+48,framesImage,frame, clip);
	}

}

void CGame::placeOtherFrames(SDL_Rect* clip){

	clip->x = 251;
	clip->y = 0;
	clip->w = 70;
	clip->h = 48;

	CGraphics::applySurface((bWidth*BSIZE)/2,0,framesImage,frame, clip);

}

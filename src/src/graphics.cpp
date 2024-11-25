#include "engine.h"

CGraphics::CGraphics(){

	//Initiate TTF
  if( TTF_Init() == -1 ){
		fprintf(stderr, "Unable to init TTF: %s\n", TTF_GetError());
		exit(1);
	}

	sWidth = 320;
	sHeight = 320;

	sTitle = "Campo Minado v1.0 - By Muthazem";

	screen = NULL;

	font = TTF_OpenFont( FONTLOCATION, 14 );
	if(!font) {
		fprintf(stderr, "Unable to Open Font: %s\n", TTF_GetError());
		exit(1);
	}

}

CGraphics::~CGraphics(){

	TTF_CloseFont(font);

}

SDL_Surface* CGraphics::loadImage( string filename ) {


	SDL_Surface* loadedImage = NULL;

	SDL_Surface* optimizedImage = NULL;

	loadedImage = SDL_LoadBMP(filename.c_str());

	if( loadedImage != NULL ){

		//Convert the image to the apropriate display format
		optimizedImage = SDL_DisplayFormat( loadedImage );

	}

	return loadedImage;
}

void CGraphics::setSize(int w,int h){

	sWidth = w;
	sHeight = h;

	screen = SDL_SetVideoMode(sWidth,
														sHeight,
														BPP,
														SDL_HWSURFACE);

	if( screen == NULL ){
		fprintf(stderr, "Unable to set up video: %s\n", SDL_GetError());
		exit(1);
	}

}

void CGraphics::setTitle( string title ){

	sTitle = title;
	SDL_WM_SetCaption(sTitle.c_str() , NULL );

}

void CGraphics::applySurface(int x, int y, SDL_Surface* source,
                    SDL_Surface* dest, SDL_Rect* clip = NULL){

    SDL_Rect offset; // Offset Retangle

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, clip, dest, &offset );
}

void CGraphics::eraseScreen(void){
  SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) );
}

void CGraphics::printMessage(int x, int y, string text, SDL_Color textColor){

	SDL_Surface* message = TTF_RenderText_Blended( font, text.c_str(), textColor );

	applySurface(x,y,message,screen, NULL);

	SDL_FreeSurface(message);

}

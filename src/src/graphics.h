#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "main.h"

/* Bits per Pixel */
#define FONTLOCATION				"Arquivos/HopferHornbook.ttf"

/* Bits per Pixel */
#define BPP									24

class CGraphics{

	private:

		string sTitle; //Window Title

	// Screen Dimentions
		int sWidth;
		int sHeight;

		SDL_Surface* screen; // Surface for the screen

		TTF_Font* font;

	public:
		CGraphics();
		~CGraphics();

		static SDL_Surface* loadImage(string); // Load a BMP file to a surface
		static void applySurface(int,int,SDL_Surface*,SDL_Surface*, SDL_Rect*);

		SDL_Surface* getScreen(void){ // Returns a pointer to the screen surface
			return screen;
		}

		void setSize(int,int); // Sets the size of the screen;
		void setTitle(string); // Sets the Window Title
		void eraseScreen(void); // Erase Screen to Black;
		void printMessage(int,int,string, SDL_Color); // Print a text to the screen

};

#endif

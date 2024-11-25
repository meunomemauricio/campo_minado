#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "gamestates.h"
#include "graphics.h"
#include "timer.h"
#include "cells.h"

using std::vector;

class CGame: public CStates {

	private:

    vector< CGameCells > bMatrix; // Board Matrix

    CTimer* gameTimer; // Creates a Timer for the Game

    GameStates level; // Stores the Level of the Game

    // Board Dimentions
    int bWidth;
    int bHeight;

    int mineNumber; // Number of mines in the board

    SDL_Surface* buttons; // Button Images
    SDL_Surface* framesImage; // Frame images
    SDL_Surface* frame; // Frame images

    int mouseX; // Mouse Coordinates
    int mouseY; // Related to the matrix cells!

    bool firstMove; // true if its the first move of the game.

    int flagCount; // Number of flags in the board.

    SDL_Event events; // The event structure that will be used

    GameStates nextState;

    bool gameOver; // True if game is over

	protected:

		void setLevel(GameStates); // Set the game to the right Level

	/* Actions */

    void putMines(void); // Sort the mines through the board
    void fillBoard(void); // Place the numbers in the board
    int getAdjFlags(void); // Return the number of adjacent flags to
																// mouseX & mouseY
		void doFirstMove(void); // Make the first move

    void getMouseCoordinates(void); //Coordinates related to the matrix cells!
    void handleMouse(void); // Call Functions related to mouse
    void handleKeyboard(void); // Call Functions related to Kboard

    void Click(int,int); // Clicks a Button
    void Highlight(void); // Highlight the button under the mouse
    void insertFlag(void); // Insert a Flag Button in the Board
    void pressButton(void); // Press a button
    void clickEmpty(int,int); //Show every button around an empty button
    void middlePress(void); // Handle Middle Button Press
    void middleClick(void); // Handle Middle Click

    bool checkVictory(void); // return True if the game is over
    void endGame(bool); // Ends the game

	/* Mouse */

		void clearButtonStates(void); // Clear Highlight and Pressed states.
		void mouseMotion(void); // Deals with the motion states
		void mousePress(void); //  Deals with what happens when you press the mouse
		void mouseRelease(void); // Deas with what happens when you release the mouse

	/* Frame */

		void setFrame(void); // Sets the game frame
		void placeSideFrames(SDL_Rect*); // Place the laterals os the frame
		void placeCornerFrames(SDL_Rect*); //
		void placeOtherFrames(SDL_Rect*);

	public:

		CGame(CGraphics* graphics, GameStates);
		~CGame();

    void handleEvents(void); // Handle input events
		GameStates getNextState(void){
			return nextState;
		}
    void Render(CGraphics*);

};


#endif

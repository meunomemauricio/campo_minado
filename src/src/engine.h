#ifndef ENGINE_H
#define ENGINE_H

#include "main.h"
#include "graphics.h"
#include "gamestates.h"
#include "intro.h"
#include "menu.h"
#include "game.h"


class CEngine{

  private:

    CGraphics* graphics;
    CStates* currentState;

		GameStates stateID;
		GameStates nextState;

  protected:

    void changeState(void); // Change the State if needed

  public:

    CEngine(void); // Constructor
    ~CEngine(void); // Destructor

    void Init(void); // Initiate CEngine

    void Start(void); // Start doing everything

};

#endif

#ifndef GCELLS_H
#define GCELLS_H

#include "main.h"

/* Board Matrix Characters */
#define EMPTY				        0
#define MINE				        'x'

/* Button Size */
#define BSIZE               16

class CGameCells {

  private:

    char value;

    bool hidden;

    bool pressed;

    bool flag;

    bool highlighted;

    bool wrongFlag; //true if it's a flag but placed incorretly

    SDL_Rect* clip;

    bool lastclick;

  public:

    CGameCells(void);
    ~CGameCells();

    void setValue(char v){ //Sets the button Value
			value = v;
		}
    char getValue(void){ // Returns the button Value
			return value;
		}
    void increaseValue(void){ //Button value++
			value++;
		}
    void setFlag(bool); //Set if a Button is a flag or not
    bool isFlag(void){ //Returns true if button is a flag
			return flag;
		}
    void unHide(void){ // Unhide button
			hidden = false;
		}
    bool isHidden(void){ // Returns true if button is hidden
			return hidden;
		}
    void setClip(void); // Set the clip of the button
    SDL_Rect* getClip(void){ //Returns the clip of the button
			return clip;
		}
    bool isMine(void){ // Returns true if button is a mine
			return (value == MINE);
		}
    void highLight(void){ //Highlights the button
			highlighted = true;
		}
    void unHighLight(void); // Unhighlights the button
    void pressDown(void){ // Press Button Down
			pressed = true;
		}
		void pressDown(int x, int y){ // Press Button Down
			pressed = true;
		}
    void unPress(void){ //Unpress a Button
			pressed = false;
		}
    void setLastClick(void){ //Sets a button as the last clicked
			lastclick = true;
		}
		void setWrongFlag(void);

};

#endif

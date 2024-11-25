#include "timer.h"

CTimer::CTimer(void){

	initialTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;

}

void CTimer::Start(void){

	started = true;

	paused = false;

	initialTicks = SDL_GetTicks();

}

void CTimer::Stop(void){

	started = false;

	paused = false;

}

void CTimer::Pause(){

	if( ( started == true ) && ( paused == false ) )
	{
		//Pause the timer
		paused = true;

		//Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - initialTicks;
	}

}

void CTimer::Unpause(){

	if( paused == true )
	{
		paused = false;

		//Reset the starting ticks
		initialTicks = SDL_GetTicks() - pausedTicks;

		pausedTicks = 0;
	}

}

int CTimer::getTicks(void){

	if( started == true )
	{
		if( paused == true )
		{
			//Return the number of ticks when the the timer was paused
			return pausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			return SDL_GetTicks() - initialTicks;
		}
	}

	return 0;
}

#ifndef CTIMER_H
#define CTIMER_H

#include "main.h"

class CTimer{

	private:

		int initialTicks; // The clock time when the timer started

		int pausedTicks; // The ticks stored when the timer was paused

		bool paused; // The timer status
		bool started;

	public:

		CTimer(void);

		// Clock Actions
		void Start(void);
		void Stop(void);
		void Pause(void);
		void Unpause(void);

		int getTicks(void); // Gets the timer's time

		// Checks the status of the timer
		bool isStarted(void){
			return started;
		}
		bool isPaused(void){
			return paused;
		}

};

#endif

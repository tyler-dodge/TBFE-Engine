#include "tbfe/misc/Timer.h"
Timer::Timer()
{
  //Initialize the variables
  startTicks = 0;
  pausedTicks = 0;
  paused = false;
  started = false;
};

//The various clock actions
void Timer::Start()
{
  //Start the timer
  started = true;
  
  //Unpause the timer
  paused = false;
  
  //Get the current clock time
  startTicks = SDL_GetTicks();
};

//Gets the timer's time
int Timer::GetTicks()
{
  //If the timer is running
  if( started == true )
    {
      //If the timer is paused
      if( paused == true )
	{
	  //Return the number of ticks when the timer was paused
	  return pausedTicks;
	}
      else
	{
	  //Return the current time minus the start time
	  return SDL_GetTicks() - startTicks;
	}
    }
  
  //If the timer isn't running
  return 0;
};

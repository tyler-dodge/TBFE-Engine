#ifndef Timer_L
#define Timer_L
#include "SDL/SDL.h"
//I did not write this
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();
    void Start();
    int GetTicks();
    
};
#endif

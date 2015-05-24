// Timer.h

#ifndef TIMER_H
#define TIMER_H

class Timer
{
// Methods
public:
   Timer();
   ~Timer();

   // This returns the number of milliseconds since this object was created.
   float timeSinceCreation();

   // This method returns the number of milliseconds that have passed since it was last called.
   float timeSinceLastFrame();

// Data
private:
   // This stores the time of that last call to timeSinceLastFrame().
   float m_timeOfLastCall;
};

#endif

// Input.h

#ifndef INPUT_H
#define INPUT_H

#include <SDL/SDL.h>

class Input
{
// Methods
public:
   Input();
   ~Input();

   // Call this before any other methods
   void readInput();
   


   bool* getInput();
   bool* getSlowInput();   
   int menuInput();
   
   void clearKeys();


   // Check this each frame
   bool windowClosed();

// Data
private:
   SDL_Event m_event;
   SDL_Event m_slowevent;

   bool m_keysHeld[323];
   bool m_keysHit[323];
   bool m_windowClosed;
};

#endif

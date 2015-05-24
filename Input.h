// Input.h

#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

class Input
{
// Methods
public:
   Input();
   ~Input();

   // Call this before any other methods
   void readInput();

   bool* getInput();

   // Check this each frame
   bool windowClosed();

// Data
private:
   SDL_Event m_event;
   bool m_keysHeld[323];
   bool m_windowClosed;
};

#endif

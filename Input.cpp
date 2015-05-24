// Input.cpp

#include "Input.h"

Input::Input()
{
   m_windowClosed = false;

   // Make sure all the keys are set to false.
   for (int i = 0; i < 323; i++)
   {
      m_keysHeld[i] = false;
   }
}

Input::~Input()
{
}

void Input::readInput()
{
   if (SDL_PollEvent(&m_event))
   {
      if (m_event.type == SDL_QUIT)
      {
         m_windowClosed = true;
      }

      if (m_event.type == SDL_KEYDOWN)
      {
         m_keysHeld[m_event.key.keysym.sym] = true;
      }

      if (m_event.type == SDL_KEYUP)
      {
         m_keysHeld[m_event.key.keysym.sym] = false;
      }
   }
}

bool* Input::getInput()
{
   return m_keysHeld;
}

bool Input::windowClosed()
{
   return m_windowClosed;
}

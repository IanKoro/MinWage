// Input.cpp

#include "Input.h"
#include "main.h"

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
         m_keysHit[m_event.key.keysym.sym] = false;
      }

      if (m_event.type == SDL_KEYUP)
      {
         m_keysHeld[m_event.key.keysym.sym] = false;
         m_keysHit[m_event.key.keysym.sym] = true;
      }
   }
}



bool* Input::getInput()
{
   return m_keysHeld;
}

bool* Input::getSlowInput()
{
   return m_keysHit;
}


int Input::menuInput()
{

  	SDL_Event menuEvent;

	
	while (inMenu)
	{
	
		if (SDL_PollEvent(&menuEvent))
		{
			if (menuEvent.type == SDL_QUIT)
			{
				inMenu = false;
			}
      
         if (menuEvent.type == SDL_KEYDOWN)
         {
            SDLKey keyPressed = menuEvent.key.keysym.sym;
      
            switch (keyPressed)
            {
               case SDLK_ESCAPE:
                  inMenu = false;
                  break;
               case SDLK_UP:
                  inMenu = false;
                  break;
               case SDLK_DOWN:
                  inMenu = false;
                  break;
            }
		 }
		}
	}
	inMenu = false;
}

void Input::clearKeys()
{
	int i = 0;
	for (i = 0; i < 323; i++)
	{
		m_keysHeld[i] = false;
		m_keysHit[i] = false;
	}
}


bool Input::windowClosed()
{
   return m_windowClosed;
}

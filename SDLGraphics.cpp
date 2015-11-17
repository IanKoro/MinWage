// SDLGraphics.cpp

#include "SDLGraphics.h"
#include "main.h"
#include "mapobjs.h"

SDLGraphics::SDLGraphics(int windowWidth, int windowHeight,
                         const char* windowTitle,
                         int bgR, int bgG, int bgB)
{
   SDL_Init(SDL_INIT_VIDEO);

   TTF_Init();

   m_screen = SDL_SetVideoMode(windowWidth, windowHeight,
                               0, SDL_HWSURFACE | SDL_DOUBLEBUF);

   SDL_WM_SetCaption(windowTitle, 0);

   setBackgroundColor(bgR, bgG, bgB);
}

SDLGraphics::~SDLGraphics()
{
   TTF_Quit();
   SDL_Quit();
}

SDL_Surface* SDLGraphics::loadBitmap(const char* bitmapFileName,
                                     int transparentRed, int transparentGreen, int transparentBlue)
{
   SDL_Surface* bitmap = SDL_LoadBMP(bitmapFileName);

   SDL_SetColorKey(bitmap,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(bitmap->format, transparentRed, transparentGreen, transparentBlue));

   return bitmap;
}

void SDLGraphics::closeBitmap(SDL_Surface* bitmap)
{
   SDL_FreeSurface(bitmap);
}

void SDLGraphics::beginScene()
{
   // Clear the screen
   SDL_FillRect(m_screen,
                NULL,
                SDL_MapRGB(m_screen->format, m_backgroundColorRed,
                                             m_backgroundColorGreen,
                                             m_backgroundColorBlue));
}

// This just displays the scene.
void SDLGraphics::endScene()
{
   SDL_Flip(m_screen);
}

void SDLGraphics::drawSprite(SDL_Surface* imageSurface,
                             int srcX, int srcY,
                             int dstX, int dstY,
                             int width, int height)
{
   SDL_Rect srcRect;
   srcRect.x = srcX;
   srcRect.y = srcY;
   srcRect.w = width;
   srcRect.h = height;

   SDL_Rect dstRect;
   dstRect.x = dstX;
   dstRect.y = dstY;
   dstRect.w = width;
   dstRect.h = height;

   SDL_BlitSurface(imageSurface, &srcRect, m_screen, &dstRect);
}

void SDLGraphics::drawText(const char* string,
                           int size,
                           int x, int y,
                           int fR, int fG, int fB,
                           int bR, int bG, int bB)
{
	TTF_Font* font = TTF_OpenFont("fonts/Amatic-Bold.ttf", size);
	
	//else{font = TTF_OpenFont("fonts/arial.ttf", size);}
   SDL_Color foregroundColor = { fR, fG, fB };
   SDL_Color backgroundColor = { bR, bG, bB };

   SDL_Surface* textSurface = TTF_RenderText_Shaded(font, string,
                                                    foregroundColor, backgroundColor);

   SDL_Rect textLocation = { x, y, 0, 0 };

   SDL_BlitSurface(textSurface, NULL, m_screen, &textLocation);

   SDL_FreeSurface(textSurface);

   TTF_CloseFont(font);
}

void SDLGraphics::setBackgroundColor(int r, int g, int b)
{
   m_backgroundColorRed = r;
   m_backgroundColorGreen = g;
   m_backgroundColorBlue = b;
}

int drawSpiral(int numPts, int delayTime)
{
	
	    // (dirX, dirY) is a vector - direction in which we move right now
    int dirX = 1;
    int dirY = 0;
    // length of current segment
    int segment_length = 1;

    // current position (i, j) and how much of current segment we passed
    int i = 10;
    int j = 7;
    
    int k = 0;

    game_graphics->drawSprite(blackTile, 0, 0, i * 32, j * 32, 32, 32);
    game_graphics->endScene();
    
    int segment_passed = 0;
    for (k = 0; k < numPts; ++k) {
        // make a step, add 'direction' vector (dirX, dirY) to current position (i, j)
        i += dirX;
        j += dirY;
        ++segment_passed;
        SDL_Delay(delayTime);
        game_graphics->drawSprite(blackTile, 0, 0, i * 32, j * 32, 32, 32);
        game_graphics->endScene();
        printf("%d %d\n", i, j);

        if (segment_passed == segment_length) {
            // done with current segment
            segment_passed = 0;

            // 'rotate' directions
            int buffer = dirX;
            dirX = -dirY;
            dirY = buffer;

            // increase segment length if necessary
            if (dirY == 0) {
                ++segment_length;
            }
        }
    }
	
	return 0;
	
}


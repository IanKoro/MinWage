minwage:	main.cpp
	g++ `sdl-config --cflags --libs` -lSDL_ttf SDL_collide.cpp SDLGraphics.cpp Input.cpp Timer.cpp mapobjs.cpp gameobjs.cpp main.cpp -o minwage

clean:
	rm minwage

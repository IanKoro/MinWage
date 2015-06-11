minwage:	main.cpp
	g++ `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf SDL_collide.cpp indoors.cpp SDLGraphics.cpp menuclass.cpp Input.cpp Timer.cpp mapobjs.cpp gameobjs.cpp main.cpp -o minwage

clean:
	rm minwage

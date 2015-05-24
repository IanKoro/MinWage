minwage:	main.cpp
	g++ `sdl-config --cflags --libs` -lSDL_ttf SDLGraphics.cpp Input.cpp Timer.cpp mapobjs.cpp gameobjs.cpp main.cpp -o minwage

clean:
	rm minwage

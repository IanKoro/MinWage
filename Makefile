CC=g++
CFLAGS=-c -Wall -g
SDLOPTS=`sdl-config --cflags --libs` -lSDL_image -lSDL_ttf

LDFLAGS=
SOURCES= SDL_collide.cpp characters.cpp maps.cpp indoors.cpp inventory.cpp indoorPlayer.cpp SDLGraphics.cpp menuclass.cpp Input.cpp Timer.cpp mapobjs.cpp gameobjs.cpp makeMap.cpp main.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=minwage

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(SDLOPTS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f minwage *.o

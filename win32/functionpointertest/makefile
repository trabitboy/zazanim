
SDL_HOME = 	C:
CC= C:/mingw/bin/g++



##### sdl2 win settings
SDL_INCLUDE = -I$(SDL_HOME)/SDL2-2.0.3/i686-w64-mingw32/include/SDL2 -I$(SDL_HOME)/SDL2_mixer-2.0.0/i686-w64-mingw32/include/SDL2 -I$(SDL_HOME)/SDL2_image-2.0.0/i686-w64-mingw32/include/SDL2 
SDL_LINK = -L$(SDL_HOME)/SDL2-2.0.3/i686-w64-mingw32/lib -L$(SDL_HOME)/SDL2_mixer-2.0.0/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -L$(SDL_HOME)/SDL2_image-2.0.0/i686-w64-mingw32/lib  
MFLAGS = -DSDL2GLB=1
CFLAGS =  $(SDL_INCLUDE) -gdwarf-2 -s  -c -fmessage-length=0 $(MFLAGS)

main.o: 
	$(CC) $(CFLAGS) main.cpp
exe: main.o 
	$(CC) -otest.exe main.o  $(SDL_LINK)

cleano:
	rm *.o
cleanexe: cleano
	rm *.exe

run: cleanexe exe
	./test.exe
	



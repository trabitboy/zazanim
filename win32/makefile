#SDL_HOME = R:/perso/tmp
#CC= R:/perso/tmp/MinGW/bin/g++

#the latest has dependency on path, switching it that way doesn't work
#SDL_HOME = R:/perso/tmp
#CC= R:/perso/latestmingw/bin/g++

SDL_HOME = C:\Users\thomas\cpp_libs\SDL2-2.0.5
SDL_MIXER_HOME = C:\Users\thomas\cpp_libs

CC= /cygdrive/c/Users/thomas/MinGW3leg/bin/g++


##### SDL1 
#SDL_INCLUDE=-I$(SDL_HOME)/SDL_mixer-1.2.11/include -I$(SDL_HOME)/SDL-1.2.14/include/SDL
#SDL_LINK = -L$(SDL_HOME)/SDL_mixer-1.2.11/lib -L$(SDL_HOME)/SDL-1.2.14/lib -lmingw32 -lSDLmain -lSDL -lopengl32 -lSDL_mixer 
# MFLAGS = 
#MFLAGS = -DNOMUSIC=1
#CFLAGS =  $(SDL_INCLUDE) -gdwarf-2 -s  -c -fmessage-length=0 $(MFLAGS)
#BLIT_PATH=../src


##### sdl2 win settings
SDL_INCLUDE = -I$(SDL_HOME)/i686-w64-mingw32/include/SDL2 -I$(SDL_MIXER_HOME)/SDL2_mixer-2.0.1/i686-w64-mingw32/include/SDL2  
SDL_LINK = -L$(SDL_HOME)/i686-w64-mingw32/lib -L$(SDL_MIXER_HOME)/SDL2_mixer-2.0.1/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer 
MFLAGS = -DSDL2GLB=1
CFLAGS =  $(SDL_INCLUDE) -gdwarf-2 -s  -c -fmessage-length=0 $(MFLAGS)
BLIT_PATH=../src/sdl2


### minimal sdl2 win32 setting no sdl mixer or image settings
# SDL_INCLUDE = -I$(SDL_HOME)/SDL2-2.0.3/i686-w64-mingw32/include/SDL2  
# SDL_LINK = -L$(SDL_HOME)/SDL2-2.0.3/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2    
# MFLAGS = -DSDL2GLB=1 -DNOMUSIC=1
# BLIT_PATH=../src/sdl2
# CFLAGS =  $(SDL_INCLUDE) -g -s  -c -fmessage-length=0 $(MFLAGS)
################ config end


###### RASPI DEBIAN
#CC=g++ 
#SDL_INCLUDE = `sdl2-config --cflags`
##SDL_LINK = `sdl2-config --libs`
#SDL_LINK =`sdl2-config --libs` -lSDL2_image -lSDL2_mixer
##MFLAGS = -DSDL2GLB=1 -DNOMUSIC=1 -DRASPI=1
#MFLAGS = -DSDL2GLB=1 -DRASPI=1
#BLIT_PATH=../src/sdl2
#CFLAGS = $(SDL_INCLUDE) -g -s -c -fmessage-length=0 $(MFLAGS) 



clean:
	rm *.o ./zaza.exe


#### tests
logtest.o: 
	$(CC) $(CFLAGS) ../src/util/logtest.cpp

tlog: logtest.o Log.o
	$(CC)  -o../tlog.exe logtest.o Log.o $(SDL_LINK)


tinyxmltest.o:  
	$(CC) $(CFLAGS) ../src/test/tinyxmltest.cpp

txml: tinyxmltest.o Log.o tinyxml.o tinystr.o tinyxmlerror.o tinyxmlparser.o
	$(CC)  -o../txml.exe tinyxmltest.o Log.o tinystr.o tinyxmlerror.o tinyxmlparser.o tinyxml.o $(SDL_LINK)

### examples
t_tmtd.o:
	$(CC) $(CFLAGS) ../src/maputil/test_tmtd.cpp

t_tmtd: Log.o t_tmtd.o tilemapwithtiledefs.o blitsdl.o Point.o TileMap.o tiledef.o slashrfix.o
	$(CC)  -o../t_tmtd.exe Log.o test_tmtd.o tilemapwithtiledefs.o blit.o Point.o TileMap.o tiledef.o slashrfix.o $(SDL_LINK)


### test
tqueue.o:
	$(CC) $(CFLAGS) ../jni/src/tqueue.cpp



###THE REAL MEAT 
testrtex.o:
	$(CC) $(CFLAGS) ../jni/src/testrtex.cpp
testsimple.o:
	$(CC) $(CFLAGS) ../jni/src/testsimple.cpp
testmodifytexture.o:
	$(CC) $(CFLAGS) ../jni/src/testmodifytexture.cpp
treadpix.o: 
	$(CC) $(CFLAGS) ../jni/src/treadpix.cpp
testfbreadpix.o: 
	$(CC) $(CFLAGS) ../jni/src/testfbreadpix.cpp
testcvsalpha.o: 
	$(CC) $(CFLAGS) ../jni/src/testcvsalpha.cpp
gpupaintpoc.o: 
	$(CC) $(CFLAGS) ../jni/src/gpupaintpoc.cpp
testsw.o: 
	$(CC) $(CFLAGS) ../jni/src/testsw.cpp
testsurfaccess.o: 
	$(CC) $(CFLAGS) ../jni/src/testsurfaccess.cpp
handleinput.o: 
	$(CC) $(CFLAGS) ../jni/src/handleinput.cpp
gpuopaquertpoc.o: 
	$(CC) $(CFLAGS) ../jni/src/gpuopaquertpoc.cpp

traj.o: 
	$(CC) $(CFLAGS) ../jni/src/traj.cpp

composebrush.o: 
	$(CC) $(CFLAGS) ../jni/src/composebrush.cpp

gputransparentrtpoc.o: 
	$(CC) $(CFLAGS) ../jni/src/gputransparentrtpoc.cpp

floodfill.o:
	$(CC) $(CFLAGS) ../jni/src/floodfill.cpp

timecodes.o:
	$(CC) $(CFLAGS) ../jni/src/timecodes.cpp

cleanartifacts.o:
	$(CC) $(CFLAGS) ../jni/src/cleanartifacts.cpp


main.o: 
	$(CC) $(CFLAGS) ../jni/src/main.cpp
exe: main.o testcvsalpha.o testsimple.o testmodifytexture.o treadpix.o gpupaintpoc.o testsw.o gpuopaquertpoc.o testsurfaccess.o handleinput.o testfbreadpix.o gputransparentrtpoc.o traj.o composebrush.o floodfill.o timecodes.o cleanartifacts.o
	$(CC) -ozaza.exe main.o testcvsalpha.o testsimple.o testmodifytexture.o treadpix.o gpupaintpoc.o testsw.o gpuopaquertpoc.o testsurfaccess.o handleinput.o testfbreadpix.o gputransparentrtpoc.o traj.o composebrush.o floodfill.o timecodes.o cleanartifacts.o $(SDL_LINK)

cleano:
	rm *.o
cleanexe: cleano
	rm *.exe

run:cleanexe  exe
	./zaza.exe

### test to make sure api actually working UNCLEAR
SDL_test_common.o: 
	$(CC) $(CFLAGS) ../jni/src/SDL_test_common.c
testrendertarget.o: 
	$(CC) $(CFLAGS) ../jni/src/testrendertarget.c
trp: testrendertarget.o SDL_test_common.o
	$(CC) -otrp.exe testrendertarget.o SDL_test_common.o $(SDL_LINK)



### treadpix custom ( bken I guess )
trpix: treadpix.o 
	$(CC) -orpix.exe treadpix.o $(SDL_LINK)


//in this poc, the save of a frame takes 3s on note 3 neo,
// so we maintain a dirty flag and only save what we paint
#include "SDL_mixer.h"

struct{
	SDL_Texture * tx;
	Mix_Chunk * snd;
	// if a wav file is loaded, on save of the project we need to 
	// rename it with correct index
	Uint16 wavFileNumberOnDisk;

	bool dirty;
	bool shifted;
	char loadedfrom[256]; //we need the initial file name if just a move 
	Uint16 timecode; //default 1, number of frames of duration ( in global fps)
}typedef Tex;

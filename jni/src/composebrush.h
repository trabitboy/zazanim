#include "SDL.h"
struct myRgb{

	Uint8 r;
	Uint8 g;
	Uint8 b;
};

SDL_Surface * composeBrushWithAlpha(Uint16 radius,Uint16 alphaborder, myRgb targetColor, Uint16 alpha);

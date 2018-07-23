#include "stdio.h"
#include "globstruct.h"
#include "composebrush.h"

// //TODO clearly not sure toCompose is freed
//TODO border alpha not used 
//TODO pb with alpha blending on andro ( is done on black )
// struct Sprite * composeBrushWithAlpha(Uint16 radius, myRgb targetColor, Uint16 alpha) {
SDL_Surface * composeBrushWithAlpha(Uint16 radius,Uint16 alphaborder, myRgb targetColor, Uint16 alpha) {

	Uint32 rmask, gmask, bmask, amask;

	//legacy from before port ?
	if (radius > 128) {
		return 0;
	}

//is it necesarry ?
	
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00; amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface * toCompose = SDL_CreateRGBSurface(SDL_SWSURFACE, radius*2, radius*2, 32,
			rmask, gmask, bmask, amask);

	Uint8 r_full, g_full, b_full, a_full;
	r_full = targetColor.r;
	g_full = targetColor.g;
	b_full = targetColor.b;
	LOGD("about to compose surf for %d %d %d \n",r_full,g_full,b_full);

	a_full =
		alpha;
//		127;

	Uint8 r_transp, g_transp, b_transp, a_transp;
	r_transp = 0;
	g_transp = 0;
	b_transp = 0;
	a_transp = 0;

	Uint32 border = SDL_MapRGBA(toCompose->format, r_full, g_full, b_full,
			a_full/2);

	
	Uint32 color = SDL_MapRGBA(toCompose->format, r_full, g_full, b_full,
			a_full);
	Uint32 transp = SDL_MapRGBA(toCompose->format, r_transp, g_transp,
			b_transp, a_transp);

// //	printf("color in hex: %x\n", color);

	int i, j;
	for (j = 0; j < radius * 2; j++) {
		for (i = 0; i < radius * 2; i++) {
			// //
			// //       /|
			// //   c  / | b
			// //     /  |
			// //    -----
			// //       a
			// //  lower left is circle center,
			// // we want to calculate c^2
			// //            x c  - x p
			// // a^2 = ( radius - i) ^2
			// // b^2 = ( radius - j) ^2
			// // c^2 = a^2 + c^2


			// //FALSE coordinates are false ( MIRACLE it works )
			int squareDistToCtr = (radius - i) * (radius - i) + (radius - j)
					* (radius - j);
			int squareRadius = radius * radius;
			if (squareDistToCtr < squareRadius) {
			
				*((Uint32 *) toCompose->pixels + j * toCompose->pitch / 4 + i)
						= color;
			} else {
				*((Uint32 *) toCompose->pixels + j * toCompose->pitch / 4 + i)
						= transp;
			}
//			printf(" %x ;", *((Uint32 *) toCompose->pixels + j
//					* toCompose->pitch / 4 + i));
		}
//		printf("\n");

		//TODO second pass to do an x pixels border that is half alph

	}

	// return AllocSpriteFromSurface(toCompose);
	return toCompose;
}

#include "SDL.h"
#include "globstruct.h"
#include "stdio.h"
namespace testsurfaccess{

//STATUS: the log in the console doesn't match the pattern,
// which means I do not access the surface pixels in the correct way


//for some reason 32 bit bmp with alpha are not ARGB or RGBA,
//answer : BGRA for 32 BITS? alpha mask info is wrong

// //tyr to convert so 

//for 24 bits, test

// test
	SDL_Window * window= NULL;
	SDL_Renderer * renderer= NULL;


void testsurfaccess(){
	//for mobile where we don't pre know the screen size
	int sw=0;
	int sh=0;

	SDL_CreateWindowAndRenderer(
	SCRWDTH,SCRHGTH,
	0, &window, &renderer) ;
		SDL_Surface * testsurf = SDL_LoadBMP(
					"testr32.bmp"
					//"testr24.bmp"
		);

	LOGD("zzn surf r %08X g %08X  b %08X pitch %d  \n",
	testsurf->format->Rmask,
	testsurf->format->Gmask,
	testsurf->format->Bmask,
	testsurf->pitch);
	int i,j;
	
	// LOGD("uint 32 cursing \n");
	// Uint32 * tmp32 = (Uint32 * )testsurf->pixels;

	// for( j=0;j<16;j++){
		// for( i=0;i<16;i++){
		// LOGD("%d ",tmp[j*16+i +1]);
		
		// }
		// LOGD("\n ");
	// }
	
	
	
	Uint8 * tmp = (Uint8 * )testsurf->pixels;

	LOGD("uint 8 cursing \n");
	
	for( j=0;j<16;j++){
		for( i=0;i<16;i++){
		LOGD("%d ",
		tmp[4*(j*16+i) 
		 // 32 bit b ?
		]);
		
		}
		LOGD("\n ");
	}

	LOGD("2nd slot \n");
	
	for( j=0;j<16;j++){
		for( i=0;i<16;i++){
		LOGD("%d ",
		tmp[4*(j*16+i) 
		 // 32 bit g ?
		 +1
		]);
		
		}
		LOGD("\n ");
	}


	LOGD("3rd spot\n");
	for( j=0;j<16;j++){
		for( i=0;i<16;i++){
		LOGD("%d ",
		tmp[4*(j*16+i) 
		+2 // 32 bit r
		]);
		
		}
		LOGD("\n ");
	}

		
	//to be replaced by buffer
	SDL_FreeSurface( testsurf);

		
		
	}

}
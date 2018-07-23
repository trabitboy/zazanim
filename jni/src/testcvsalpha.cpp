//TODO compose brush instead of loading it , square
//TODO assert that readpixels doesn't work on brush if not render target
// > and that it works if tex init as render target 
//TODO create brush SRC with SDL_TEXTURE_STREAMING
// to compose 0 alpha , blit on canvas an check result
//TODO how to do a canvas with 0 alpha ?
// CAN't seem to do a render target with 0 alpha so far even if brush has alpha not FF
//BlendMode does nothing
// is blittin from alpha 0 ok?
// check alpha of cvs after brush rtotex to check transparency preserved

#include "SDL.h"
#include "stdio.h"
#include "string.h"

#include "globstruct.h"
//TODO put this in header
// #ifdef __ANDROID_API__
// #include <android/log.h>
// #define  LOG_TAG    "main"
// #define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
// #endif


// #ifndef __ANDROID_API__
// #define LOGD(...) printf(__VA_ARGS__)

// #endif

// mTexture = SDL_CreateTexture( gRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height );

// int main( int argc, char* args[] ){
void testcvsalpha(){
//create window and renderer
SDL_Window * window= NULL;
SDL_Renderer * renderer= NULL;
 
// SDL_Window * window= NULL;
// SDL_Renderer * renderer= NULL;
// if(
SDL_CreateWindowAndRenderer(32, 32, 0, &window, &renderer) ;
// < 0)
	// exit(2);

    // // SDL_Surface * brushSurf = SDL_LoadBMP("icon.bmp");
    // SDL_Texture * brush  = SDL_CreateTextureFromSurface(renderer, brushSurf);
	// SDL_FreeSurface( brushSurf);
	
	//TODO change texture streaming 
	SDL_Texture * brush  = SDL_CreateTexture( 
								renderer, 
								SDL_PIXELFORMAT_RGBA8888, 
								SDL_TEXTUREACCESS_STREAMING,
								// SDL_TEXTUREACCESS_TARGET, 
								32, 
								8 
								);

	//TODO blend mode to set cvs blit alpha ?
								
								
	//TODO compose with array of bytes
	// SDL_SetRenderTarget(renderer, brush);
	// SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );		
	   // SDL_Rect brushRect = 
		// {8,8,
	   // 16,16};

	// SDL_RenderFillRect( renderer, &brushRect );
    // SDL_RenderPresent(renderer);

	void* mPixels;
	int mPitch;
	//LOCK DOES NOTHING ON SDL_TEXTURE_TARGET >> branch in 2 different tests
    SDL_LockTexture( brush, NULL, &mPixels, &mPitch );
	//blit like a mad man
	LOGD("pitch %d\n",mPitch);
	Uint32 size = 32*8; //intentionally a fouth
	int i;
	for(i=0;i<size;i++){
	((Uint8 *)mPixels)[i*4]=16;
	((Uint8 *)mPixels)[i*4+1]=0;
	((Uint8 *)mPixels)[i*4+2]=0;
	((Uint8 *)mPixels)[i*4+3]=128;
	}
	SDL_UnlockTexture( brush );
	//TODO shouldn't I free the void * ?
	
	
	
	SDL_Texture * cvs = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 32,32 );

//r to tex on this tex with primitive
	SDL_SetRenderTarget(renderer, cvs);
	//TODO maybe try fillrect to force SDL_BLENDMODE_NONE
	SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0x00 );
	// SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer);
	
	   SDL_Rect destRect = 
		{0,0,
	   32,8};
	// SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );		
	// SDL_RenderFillRect( renderer, &destRect );
	//not sure blend mode changes anything
	SDL_SetTextureBlendMode(brush,SDL_BLENDMODE_NONE);
	SDL_RenderCopy(renderer,brush,NULL,&destRect);
	
	//render on scrin
	SDL_SetRenderTarget(renderer,NULL);
	   SDL_Rect dispRect = 
		{0,0,
		32,32};
	SDL_RenderCopy(renderer, cvs, NULL, &dispRect);
    SDL_RenderPresent(renderer);
		
		LOGD("brush content \n");
    SDL_LockTexture( brush, NULL, &mPixels, &mPitch );
	//blit like a mad man
	LOGD("pitch %d\n",mPitch);
	// Uint32 size = 32*32;
	// int i;
	for(i=0;i<size;i++){
	LOGD("brsh %08x" ,((Uint32 *)mPixels)[i]);
	}
	SDL_UnlockTexture( brush );
	
	
//get pixels of modified texture 
		LOGD("zzn cvs content\n");
		SDL_SetRenderTarget(renderer,
		cvs
		// brush
		);
		//works on win 32, on android coordinates seem 90°
		// Uint32 p;
		
		int pwidth=8;
		int pheight=8;

		SDL_Surface * sshot=SDL_CreateRGBSurface(0,pwidth,pheight,32,0XFF000000,0X00FF0000,0X0000FF00,0X000000FF);
		
		Uint32 p[pwidth*pheight];
		SDL_Rect pick={
		// 15,15,
		// 2,1
		0,4,
		// 1,1
		pwidth,pheight
		};
        SDL_RenderReadPixels(renderer, &pick, SDL_PIXELFORMAT_RGBA8888, 
		// p, // array is pointer 
		// &p, //integer I pass address
		// sizeof(p)
		// 2
		sshot->pixels,
		pwidth
		*4 //length of line in octets
		);
		
		
		// int i;
		int j;
		// *pheight
		for(j=0;j<pheight;j++){
			LOGD("zzn");
			for(i=0;i<pwidth;i++){
				// printf("size of P %d\n",sizeof(p) );
				// LOGD("thomas Blended pixel: 0x%8.8X", 
				// p[j*pwidth+i]
				// // p
				// );
				LOGD("zzn %08X", 
				// p
				// p[j*pwidth+i]
				((Uint32 *)sshot->pixels)[j*pwidth+i]
				);
			}
			LOGD("\n");
		}

		//blit to console successful, let's try to save to file
	char pathAndName[256];
	strcpy(pathAndName,"./");
	#ifdef __ANDROID_API__
	//overriding with android sensible default
	strcpy(pathAndName, 
	// SDL_AndroidGetInternalStoragePath()
	SDL_AndroidGetExternalStoragePath()
	);
	// strcpy(pathAndName,"/storage/extSdCard");
	strcat(pathAndName,"/");
	#endif
	strcat(pathAndName,"testsave.bmp");
	LOGD("zzn %s\n",pathAndName);
		
	SDL_SaveBMP(sshot,pathAndName);
		
	//TODO try in separate file
	//additional test to try to compose a transparent canvas through 
	// a clear 
	// SDL_SetRenderTarget(renderer,
	// cvs
	// // brush
	// );
	// SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	// SDL_RenderClear(renderer);
	// // SDL_RenderPresent(renderer);
        // SDL_RenderReadPixels(renderer, &pick, SDL_PIXELFORMAT_RGBA8888, 
		// // p, // array is pointer 
		// // &p, //integer I pass address
		// // sizeof(p)
		// // 2
		// sshot->pixels,
		// pwidth
		// *4 //length of line in octets
		// );

		// for(j=0;j<pheight;j++){
			// LOGD("zzn");
			// for(i=0;i<pwidth;i++){
				// // printf("size of P %d\n",sizeof(p) );
				// // LOGD("thomas Blended pixel: 0x%8.8X", 
				// // p[j*pwidth+i]
				// // // p
				// // );
				// LOGD("clr %08X", 
				// // p
				// // p[j*pwidth+i]
				// ((Uint32 *)sshot->pixels)[j*pwidth+i]
				// );
			// }
			// LOGD("\n");
		// }


	SDL_FreeSurface(sshot);
		
//loop waiting for quit
    Uint8 done = 0;
    SDL_Event event;
    while(!done)
    {
        /* Wait for events */
        SDL_WaitEvent(&event);
        do {
					if( event.type == SDL_QUIT )
					{
						done = true;
					}
        } while (SDL_PollEvent(&event));
	}
	LOGD("thomas quitting\n");
	SDL_DestroyTexture(cvs);
	//TODO free brush
//clean up
    // exit(0); not from sdl then?
	// return 0;
}

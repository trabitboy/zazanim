#include "testmodifytexture.h"

//BROKEN AS OF RENDERER WINDOW REFACTOR


//OK creating blank texture and filling it AFTER creation
// blit a smaller brush
//do it where surface is touched 
//OK put the tablet horizontal locked
//display 3 frames, 2 onions
//load
//save
//STILL SLOW put render directly in event loop, to flush as it comes
//OK try paint with render to tex
//TODO split tex stream poc and rtotex poc
//TODO test save of rtotex poc ( just blit to console ) with :
// SDL_RenderReadPixels(SDL_Renderer*   renderer,
                         // const SDL_Rect* rect,
                         // Uint32          format,
                         // void*           pixels,
                         // int             pitch)
// simple one pixel test of SDL_RenderReadPixels(
// do a small test from scratch as no understandable test in SDL src
						 

//simple render test
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "globstruct.h"

#define BRSHWDTH 8

   SDL_Surface* canvasSurf;


void canvasCreate(SDL_Renderer *renderer,SDL_Texture * cvs,SDL_Texture * prevlightTex){
 
    /* Load the sprite image */
    canvasSurf = SDL_LoadBMP("sample.bmp");

    /* Create texture from the image */
	//let's try to fill the tex manually as an exercise
    prevlightTex = SDL_CreateTextureFromSurface(renderer, canvasSurf);
	SDL_SetTextureBlendMode(prevlightTex,SDL_BLENDMODE_BLEND);
	
	
	cvs = 
	SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, CVSWDTH, CVSHGTH );
	void* mPixels;
	int mPitch;
	//LOCK DOES NOTHING ON SDL_TEXTURE_TARGET >> branch in 2 different tests
    SDL_LockTexture( cvs, NULL, &mPixels, &mPitch );
	//blit like a mad man
	printf("pitch %d\n",mPitch);
	Uint32 size = CVSHGTH *CVSWDTH *4;
	int i;
	for(i=0;i<size;i++){
	((Uint8 *)mPixels)[i]=255;
	}
	SDL_UnlockTexture( cvs );


	
}



// SLOOOOWWW on 720p canvas
void paintDlUplTex(Uint16 x,Uint16 y,SDL_Texture * cvs){
	void* mPixels;
	int mPitch;
	
	//let's do the offset afterwards
	
	//check boundaries
	if(x<(CVSWDTH-BRSHWDTH)&&y<(CVSHGTH-BRSHWDTH)){
	//let's blit 32 x 32

		SDL_LockTexture( cvs, NULL, &mPixels, &mPitch );
		// Uint32 size = CVSHGTH *CVSWDTH; //intentionally fourth of screen
		int i;
		int j;
		for(j=y;j<(y+BRSHWDTH);j++){
			for(i=x;i<(x+BRSHWDTH);i++){
				Uint32 pixelOffset;
				pixelOffset=(i+j*CVSWDTH)*4;
				((Uint8 *)mPixels)[pixelOffset]=255;
				((Uint8 *)mPixels)[pixelOffset+1]=0;
				((Uint8 *)mPixels)[pixelOffset+2]=0;
				((Uint8 *)mPixels)[pixelOffset+3]=255;
			}
		}
		SDL_UnlockTexture( cvs );
	
	}
	
	


}

SDL_Rect gScreenRect = { 0, 0, 0, 0 };

void render(SDL_Renderer * renderer,SDL_Texture * cvs,SDL_Texture * prevlightTex){
				// //Reset render target
				SDL_SetRenderTarget( renderer, NULL );
        /* Draw a gray background */
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        
        // draw(window, renderer, sprite);
   SDL_Rect destRect = {XORIG, YORIG, CVSWDTH, CVSHGTH};
    /* Blit the sprite onto the screen */
    SDL_RenderCopy(renderer, cvs, NULL, &destRect);
    //normally not to be done every blit just testing
	
	SDL_SetTextureAlphaMod( prevlightTex ,25);
	SDL_RenderCopy(renderer, prevlightTex, NULL, &destRect);
	
        /* Update the screen! */
        SDL_RenderPresent(renderer);

}

//not working, see shorter test in treadpix
void renderTargetSaveCanvas(){
	// SDL_SetRenderTarget(renderer,cvs);
	// // SDL_Surface *sshot = SDL_CreateRGBSurface(0, CVSWDTH, CVSHGTH, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	// Uint32 * pixels =(Uint32 *) malloc (4*CVSWDTH*CVSHGTH);
	// int pitch=4*CVSWDTH;
	// printf("bef rt\n");
	// SDL_RenderReadPixels(renderer, NULL, NULL, 
	// // sshot->pixels, sshot->pitch
	// pixels,pitch
	// );
	// printf("read rt success\n " );
	// free(pixels);
	// // SDL_SaveBMP(sshot, "screenshot.bmp");
	// // SDL_FreeSurface(sshot);
}


void testmodifytexture()
{
SDL_Window * window= NULL;
SDL_Renderer * renderer= NULL;
SDL_Texture * cvs = NULL;
SDL_Texture * prevlightTex = NULL;

	
    if(SDL_CreateWindowAndRenderer(960, 720, 0, &window, &renderer) < 0)
        exit(2);

	SDL_DisplayMode displayMode;
	if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
	{
		gScreenRect.w = displayMode.w;
		gScreenRect.h = displayMode.h;
	}

		
	canvasCreate(renderer,cvs,prevlightTex);

    // Sprite sprite = LoadSprite("sample.bmp", renderer);
    // if(sprite.texture == NULL)
        // exit(2);

	printf("about to draw\n");
	// paintTexToTex
	// (256,256);
	render(renderer,cvs,prevlightTex);
	// renderTargetSaveCanvas();
    /* Main render loop */
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
					//Window event
					// else if( event.type == SDL_WINDOWEVENT )
					// {
						// //Window resize/orientation change
						// if( event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED )
						// {
							// //Get screen dimensions
							// gScreenRect.w = event.window.data1;
							// gScreenRect.h = event.window.data2;
							
							// //Update screen
							// SDL_RenderPresent( gRenderer );
						// }
					// }
					//Touch down
					else if( event.type == SDL_FINGERDOWN )
					{
						Uint16 x = event.tfinger.x * gScreenRect.w -XORIG;
						Uint16 y = event.tfinger.y * gScreenRect.h -YORIG;
						// LOGD("thomas finger down ");
						paintDlUplTex
						// paintTexToTex
						(x,y,cvs);
						render(renderer,cvs,prevlightTex);

						// currentTexture = &gTouchDownTexture;
						// display=false;
					}
					//Touch motion
					else if( event.type == SDL_FINGERMOTION )
					{
						// touchLocation.x = event.tfinger.x * gScreenRect.w;
						// touchLocation.y = event.tfinger.y * gScreenRect.h;
						Uint16 x = event.tfinger.x * gScreenRect.w -XORIG;
						Uint16 y = event.tfinger.y * gScreenRect.h -YORIG;
						// LOGD("thomas finger motion ");
						paintDlUplTex
						// paintTexToTex
						(x,y,cvs);
						render(renderer,cvs,prevlightTex);
						// currentTexture = &gTouchMotionTexture;
						// // display=false;
					}
					//Touch release
					else if( event.type == SDL_FINGERUP )
					{
						// touchLocation.x = event.tfinger.x * gScreenRect.w;
						// touchLocation.y = event.tfinger.y * gScreenRect.h;
						// LOGD("thomas finger up");
						// display=true;
						// currentTexture = &gTouchUpTexture;
					}
			// if(event.type == SDL_QUIT 
			// )
            // {
                // done = 1;
            // }else if(	event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN ){
				// testpaint(32,32);
			// }
        } while (SDL_PollEvent(&event));
        
		
		//TODO put render directly in event loop, to flush as it comes
		// render();
		
    }

	printf("out of input loop\n");
	

	// SDL_DestroyTexture(brushTex);
	SDL_DestroyTexture(cvs);
	SDL_DestroyTexture(prevlightTex);
	SDL_FreeSurface(canvasSurf);
    exit(0);
}
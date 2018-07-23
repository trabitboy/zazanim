#include "gpupaintpoc.h"
#include "stdio.h"
#include "stdlib.h"

#include "SDL.h"
#include "globstruct.h"
SDL_Texture * gppBrush= NULL;
//to paint canvas white ( SDL_UpdateTexture not working on render target ? )
SDL_Texture * gppBgBrush;
SDL_Texture * gppCvs = NULL;
SDL_Window * gppWindow= NULL;
SDL_Renderer * gppRenderer= NULL;
	float buttonZoom=1; // preinit for windows?


//white canvas
//DONE support size
//DONE WORKS define different size win32 (640 480) / check clear not black
//DONE button to switch color/eraser
//TODO can't happen to make a transparent bg 
//blitting pixel data of canvas shows it is 255 alpha,
//even if gppBrush painting works
//> try to compose initial canvas directly with byte arry / 0s to set alpha
// load 2 images from files and make them -1 and +1 and display them
// work on an array of 10 SDL_Texture * ( 10 frames in video mem )
// transparency
// next 
// previous
// load
// save
//if def win / andro / SDL_Touch / SDL_Mouse
//test SDL MOUSE EMU on android ( supposed to work )
//MIGHT BE A PROBLEM LATER ( multitouch zoom )
// play back from buffer of 2bpp images / uncompress
//either surface 
// or texture streaming ( check speed )
//SDL audio recording
//TODO after testing, line draw ?
//display 3 frames, 2 onions
//buttons on the side for next, previous, add , play
//load
//save
//TODO ( nth ) modularize init render and save ( pluggable choice )
//TODO sound grab / play test 
//TODO samsung multi screen support

	//just to restore build
	int sw=0;
	int sh=0;


//for some reason doesn't work on android in this context, whereas worked in rto tex test
//suspicion that gles2 on android clears view when render target changes
void renderbuttons(SDL_Renderer * gppRenderer){
	// SDL_SetRenderTarget(gppRenderer,NULL);
	   SDL_Rect dispRect = 
		// {0,0,
		// 1280,720};
		{BTN_ERASER_UL_X,BTN_ERASER_UL_Y,
		BTN_BASE_W,BTN_BASE_W};
		// SDL_SetRenderDrawColor( gppRenderer, 0xFF, 0x00, 0x00, 0xFF );		
		// SDL_RenderFillRect( gppRenderer, &dispRect );
		//test with bg gppBrush
		SDL_RenderCopy(gppRenderer, gppBgBrush, NULL, &dispRect);
		// SDL_RenderPresent(gppRenderer);


}


void gpprendergpupoc(SDL_Renderer * gppRenderer,SDL_Texture * gppCvs){
	SDL_SetRenderTarget(gppRenderer,NULL);
	   SDL_Rect dispRect = 
		// {0,0,
		// 1280,720};
		{XORIG,YORIG,
		CVSWDTH,CVSHGTH};
	SDL_RenderCopy(gppRenderer, gppCvs, NULL, &dispRect);
	renderbuttons(gppRenderer);
    SDL_RenderPresent(gppRenderer);


}
/**
button state
*/
	bool erase =false;


bool checkButtonColl(int x,int y){
	if( 
		x < (BTN_ERASER_UL_X+BTN_BASE_W)
		&& x > BTN_ERASER_UL_X
		&&	y < (BTN_ERASER_UL_Y+BTN_BASE_W)
		&& y > BTN_ERASER_UL_Y
	){
		LOGD("zzn button toggle\n");
		erase=! erase;
		return true;
	}
	return false;
}




void gpppaintCanvas(int x, int y,SDL_Renderer * gppRenderer,SDL_Texture * tgt,SDL_Texture * with){

		SDL_SetRenderTarget( gppRenderer, tgt );
	   SDL_Rect destRect = 
	   {x, y,
	   32,32};
	   SDL_RenderCopy(gppRenderer, with, NULL, &destRect);

}

void gpppaintHandlingUI(int x, int y,SDL_Renderer * gppRenderer){
						if(erase){
							gpppaintCanvas
							(x,y,gppRenderer,gppCvs,gppBgBrush);						
						}else{
							gpppaintCanvas
							(x,y,gppRenderer,gppCvs,gppBrush);
						}
}

//suspicion that non render target texture don't work
//works on win 32, on android coordinates seem 90°
void testTexToConsole(SDL_Texture * tex,int h){
		SDL_SetRenderTarget(gppRenderer,tex); 
		//TODO destroy surface
		int pwidth=32;
		int pheight=32;

		SDL_Surface * sshot=SDL_CreateRGBSurface(0,pwidth,pheight,32,0XFF000000,0X00FF0000,0X0000FF00,0X000000FF);
		
		Uint32 p[pwidth*pheight];
		SDL_Rect pick={
		// 15,15,
		// 2,1
		0,h,
		// 1,1
		pwidth,pheight
		};
        SDL_RenderReadPixels(gppRenderer, &pick, SDL_PIXELFORMAT_RGBA8888, 
		// p, // array is pointer 
		// &p, //integer I pass address
		// sizeof(p)
		// 2
		sshot->pixels,
		pwidth
		*4 //length of line in octets
		);
		
		
		int i;
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
				LOGD(
				// "zzn %d", 
				"zzn %08X", 
				// p
				// p[j*pwidth+i]
				((Uint32 *)sshot->pixels)[j*pwidth+i]
				);
			}
			LOGD("\n");
		}





}



void gpupaintpoc(){
	LOGD("zzn logcat test\n");


//needed for tablet <> pc equivalence
		    // }	else if (event.type == SDL_MOUSEBUTTONDOWN) {
				// if (event.button.button == SDL_BUTTON_LEFT) {
					// log() << "mouse cl x:" << event.button.x << endl;
					// log() << "mouse cl y:" << event.button.y << endl;

					// newPressLeftClick=1;
					// leftClick=1;
					// xclick=event.button.x;
					// yclick=event.button.y;
				// }
		    // }else if (event.type == SDL_MOUSEBUTTONUP) {
				// if (event.button.button == SDL_BUTTON_LEFT) {

					// leftClick=0;
					// clickConsumedFlag=0;
				// }
		    // }else if (event.type == SDL_MOUSEMOTION) {

				// if (leftClick) {
					// xclick=event.button.x;
					// yclick=event.button.y;
				// }
		    // }




// if(
SDL_CreateWindowAndRenderer(
// 1280, 720, 
SCRWDTH,SCRHGTH,
0, &gppWindow, &gppRenderer) ;
// < 0)
	// exit(2);

    SDL_Surface * gppBrushSurf = SDL_LoadBMP(
				// "iconalpha.bmp"
				"gppBrush32.bmp"
	);
    gppBrush  = SDL_CreateTextureFromSurface(gppRenderer, gppBrushSurf);
	SDL_FreeSurface( gppBrushSurf);

    SDL_Surface * bgSurf = SDL_LoadBMP(
				// "iconalpha.bmp"
				"bg32.bmp"
	);
    gppBgBrush  = SDL_CreateTextureFromSurface(gppRenderer, bgSurf);
	SDL_FreeSurface( bgSurf);

	
	//TODO create white texture
	//the update texture tings dosn't work at all , 
	// do it using blit of small white tex ( argh )
	// Uint32 size = 1280 *720 *4;
	// void * pixels = malloc(size);
	// int i;
	// for(i=0;i<size;i++){
	// ((Uint8 *)pixels)[i]=255;
	// }	
	gppCvs = SDL_CreateTexture( gppRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
	// 1280,720
	CVSWDTH,CVSHGTH
	);

	//creating a white pixels array to whiten the canvas
	// SDL_UpdateTexture(gppCvs,NULL,pixels,1280*4);
	// free(pixels);
	
	//TODO extract canvas clear
	// gpppaintCanvas(200,300,gppRenderer,gppCvs,gppBgBrush);
	int xt,yt;
	xt=
	// 1280
	CVSWDTH
	/32;
	yt=
	// 720
	CVSHGTH
	/32;
	int i,j;
	for(j=0;j<yt;j++){
		for(i=0;i<xt;i++){
			gpppaintCanvas(i*32,j*32,gppRenderer,gppCvs,gppBgBrush);
		}
	}
	
	//end canvas clear
	gpppaintCanvas
	(0,0,gppRenderer,gppCvs,gppBrush);

	//not pushing it in render gpu poc ( perf ? ) NOT WORKING RIGHT NOW
	SDL_SetRenderTarget(gppRenderer,NULL);
	
	SDL_SetRenderDrawColor(gppRenderer, 0x0F, 0x0F, 0x0F, 0xFF);
	SDL_RenderClear(gppRenderer);
    SDL_RenderPresent(gppRenderer);
	//in case set render target clears ops?
	gpprendergpupoc(gppRenderer,gppCvs);
	// renderbuttons(gppRenderer);
	LOGD("zzn canvas line\n");
	testTexToConsole(gppCvs,0);
	LOGD("zzn gppBrush line\n");
	testTexToConsole(gppBrush,0);
	

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
					else if( event.type == SDL_FINGERDOWN || event.type == SDL_FINGERMOTION )
					{
						Uint16 x = event.tfinger.x *
						SCRWDTH
						//CVSWDTH	
						// -XORIG
						;
						Uint16 y = event.tfinger.y * 
						SCRHGTH
						// 720
						// CVSHGTH
						// -YORIG
						;
						
						
						
						if(event.type == SDL_FINGERDOWN ){
							if(!checkButtonColl(x,y)){
								gpppaintHandlingUI(x-XORIG,y-YORIG,gppRenderer);
							
							}
						}else if(event.type == SDL_FINGERMOTION){
							gpppaintHandlingUI(x-XORIG,y-YORIG,gppRenderer);
						}
						
						// if(erase){
							// gpppaintCanvas
							// (x,y,gppRenderer,gppCvs,gppBgBrush);						
						// }else{
							// gpppaintCanvas
							// (x,y,gppRenderer,gppCvs,gppBrush);
						// }
						gpprendergpupoc(gppRenderer,gppCvs);

					}

        } while (SDL_PollEvent(&event));
		gpprendergpupoc(gppRenderer,gppCvs);
	}
	LOGD("zzn quitting\n");
	SDL_DestroyTexture(gppCvs);
	SDL_DestroyTexture(gppBrush);
	SDL_DestroyTexture(gppBgBrush);
}
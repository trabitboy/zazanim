#include "testsw.h"
#include "stdio.h"
#include "SDL.h"
#include "globstruct.h"


//load previous and after frames, blit them with 25% alpha
//TODO
//load current and blit
// mouse support ( define with if def )
// when blitting brush, blitting also to the source surface
// refresh only every nth ms ( configurable via define )
// measure draw cycle 
// measure render

void testswblit(){
	//just to restore build
	int sw=0;
	int sh=0;


	SDL_Window * win = NULL;
	SDL_Surface * screen = NULL;

	SDL_Surface * bgBrush = NULL;
	SDL_Surface * brsh = NULL;
	SDL_Surface * previous = NULL;
	SDL_Surface * next = NULL;
	SDL_Surface * current = NULL;

	
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("sw test",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	SCRWDTH,
	SCRHGTH,
	SDL_WINDOW_SHOWN);
	
	Uint32 r,g,b,a;
	int bpp;
	r=0;g=0;b=0;a=0;bpp=0;
	
	
	SDL_PixelFormatEnumToMasks( 
		SDL_GetWindowPixelFormat(win),
		&bpp,
		&r,
		&g,
		&b,
		&a
		);
	
	LOGD("zzn r %08X g %08X  b %08X  \n",r,g,b);
	
	screen = SDL_GetWindowSurface(win);

	bgBrush = SDL_LoadBMP("bg32.bmp");

	brsh = SDL_LoadBMP("brush32.bmp");

	current = SDL_LoadBMP("current.bmp");
	
	previous = SDL_LoadBMP("previous.bmp");
	
	next = SDL_LoadBMP("next.bmp");
	
	
	LOGD("zzn screen surf %d  %d  \n",screen->w,screen->h);


	
	int xm=10;
	int ym=10;
	xm=CVSWDTH/32;
	ym=CVSHGTH/32;
	LOGD("zzn xm ym %d  %d  \n",xm,ym);
	int i,j;
	// SDL_Rect dstrct={0,0,0,0};
	
	for(j=0;j<ym;j++){
		for(i=0;i<xm;i++){
		SDL_Rect dstrct={XORIG+i*32,YORIG+j*32,32,32};
		SDL_BlitSurface(bgBrush,NULL,screen,&dstrct);
		
		}
	}
	
	SDL_Rect dstrct={XORIG,YORIG,640,480};
	SDL_BlitSurface(current,NULL,screen,&dstrct);
	SDL_BlitSurface(previous,NULL,screen,&dstrct);
	SDL_BlitSurface(next,NULL,screen,&dstrct);
	
	SDL_Rect brrct={XORIG,YORIG,32,32};
	SDL_BlitSurface(brsh,NULL,screen,&brrct);
	
	
	SDL_UpdateWindowSurface(win);
	
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
						
						//blitting on current src
						SDL_Rect dstrct1={x-XORIG,y-YORIG,32,32};
						//TODO not sure calculation is correct, 
						// add preview of current result
						SDL_BlitSurface(brsh,NULL,screen,&dstrct1);						
						
						
						//blitting on screen
						SDL_Rect dstrct2={x-XORIG,y-YORIG,32,32};
						SDL_BlitSurface(brsh,NULL,screen,&dstrct2);
						SDL_UpdateWindowSurface(win);
					}

        } while (SDL_PollEvent(&event));
	}

	
	// SDL_Delay(5000);
	SDL_FreeSurface(current);
	SDL_FreeSurface(next);
	SDL_FreeSurface(previous);
	SDL_FreeSurface(bgBrush);
	SDL_FreeSurface(brsh);
	
	
	SDL_DestroyWindow(win);
	
	SDL_Quit();
	
}
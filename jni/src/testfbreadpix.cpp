//test fb read pixels to identify pb on gles2 target

#include "SDL.h"
#include "stdio.h"
#include "string.h"

#include "globstruct.h"

namespace testfbreadpix{

	void testfbreadpix(){
	//create window and renderer
	SDL_Window * window= NULL;
	SDL_Renderer * renderer= NULL;
	 
	SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) ;
		
		// SDL_Texture * brush  = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 32, 32 );
		// SDL_SetRenderTarget(renderer, brush);
		// SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );		
		   // SDL_Rect brushRect = 
			// {4,4,
		   // 24,24};

		// SDL_RenderFillRect( renderer, &brushRect );
		// SDL_RenderPresent(renderer);
		
	//get pixels of render to fb 
			SDL_SetRenderTarget(renderer,
			NULL
			);
		   SDL_Rect fbrect = 
			{16,16,
		   608,448};
		SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );		
		SDL_RenderFillRect( renderer, &fbrect );
		// SDL_RenderCopy( renderer,brush,NULL, &fbrect );
		SDL_RenderPresent(renderer);
			
			int pwidth=640;
			int pheight=480;

			SDL_Surface * sshot=SDL_CreateRGBSurface(0,pwidth,pheight,32,0XFF000000,0X00FF0000,0X0000FF00,0X000000FF);
			
			Uint32 p[pwidth*pheight];
			SDL_Rect pick={
			0,0,
			pwidth,pheight
			};
			SDL_RenderReadPixels(renderer, &pick, SDL_PIXELFORMAT_RGBA8888, 
			sshot->pixels,
			pwidth
			*4 //length of line in octets
			);
			
			
			int i;
			int j;
			// *pheight
			// for(j=0;j<pheight;j++){
				// LOGD("zzn");
				// for(i=0;i<pwidth;i++){
					// LOGD("zzn %08X", 
					// ((Uint32 *)sshot->pixels)[j*pwidth+i]
					// );
				// }
				// LOGD("\n");
			// }

			//blit to console successful, let's try to save to file
		char pathAndName[256];
		strcpy(pathAndName,"./");
		#ifdef __ANDROID_API__
		//overriding with android sensible default
		strcpy(pathAndName, 
		SDL_AndroidGetExternalStoragePath()
		);
		strcat(pathAndName,"/");
		#endif
		strcat(pathAndName,"testfbreadpix.bmp");
		LOGD("zzn %s\n",pathAndName);
			
		SDL_SaveBMP(sshot,pathAndName);
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
		
		// SDL_DestroyTexture(brush);
		
		LOGD("thomas quitting\n");
	}
	
}
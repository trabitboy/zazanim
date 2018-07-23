//test render to tex read pixels from render target in the simplest possible scenario ( small tex )
// load small canvas with pattern
// blit with tex and not primitive
//TODO sdl2.0.3 patch sdl_gles2.c to remove upside down
// output small tex to console
// save as surface

// setRenderTarget doesn't change read pixels target on windows dx
//but on android ( gles2 it works )

//alspha of render target is for another test


// V/SDL     ( 9063): pixel format RGB_565
// V/SDL     ( 9063): Window size:1920x1080
// D/SensorManager( 9063): registerListener :: 0, MPU6500 Acceleration Sensor, 20000, 0,
// I/SDL     ( 9063): SDL_Android_Init()
// I/SDL     ( 9063): SDL_Android_Init() finished!
// W/Adreno-EGLSUB( 9063): <SwapBuffers:1352>: Invalid native buffer. Failed to queueBuffer
// W/Adreno-EGLSUB( 9063): <updater_thread:428>: native buffer is NULL
// W/Adreno-EGLSUB( 9063): <SwapBuffers:1352>: Invalid native buffer. Failed to queueBuffer
// W/Adreno-EGLSUB( 9063): <updater_thread:428>: native buffer is NULL
// D/zzn     ( 9063): zzn brush content
// V/SDL     ( 9063): onWindowFocusChanged(): true




#include "SDL.h"
#include "stdio.h"
#include "string.h"

#include "globstruct.h"



namespace treadpix{

	bool save = false;

	SDL_Window * window= NULL;
	SDL_Renderer * renderer= NULL;
SDL_Texture * cvs=NULL;

	void attemptSave(){
	//READ RENDER PIXEL
	// win32 reads fb whatever the setting
	//gles saves rt
	//get pixels of modified texture 
			LOGD("zzn brush content\n");
			SDL_SetRenderTarget(renderer,
			NULL //trying null on adreno note 3 ( like desktop )
			// cvs
			);
			
			int pwidth=1920;
			int pheight=1080;

			SDL_Surface * sshot=SDL_CreateRGBSurface(0,pwidth,pheight,32,0XFF000000,0X00FF0000,0X0000FF00,0X000000FF);
			
			Uint32 p[pwidth*pheight];
			SDL_Rect pick={
			// 15,15,
			// 2,1
			0,0,
			// 1,1
			pwidth,pheight
			};
			SDL_RenderReadPixels(renderer, &pick, SDL_PIXELFORMAT_RGBA8888, 
			// sshot->pixels,
			p,
			pwidth
			*4 //length of line in octets
			);
			
			
			// int i;
			// int j;
			// // *pheight
			// for(j=0;j<pheight;j++){
				// // LOGD("zzn");
				// for(i=0;i<pwidth;i++){
					// // printf("size of P %d\n",sizeof(p) );
					// // LOGD("thomas Blended pixel: 0x%8.8X", 
					// // p[j*pwidth+i]
					// // );
					// // LOGD("zzn %08X", 
					// // ((Uint32 *)sshot->pixels)[j*pwidth+i]
					// // );
				// }
				// LOGD("\n");
			// }

			//blit to console successful, let's try to save to file
		if(save){
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
		strcat(pathAndName,"testreadpix.bmp");
		LOGD("zzn %s\n",pathAndName);
			
		SDL_SaveBMP(sshot,pathAndName);
		SDL_FreeSurface(sshot);
		}
	
	}


	//on pc render readpixels just reads the frame buffer, no matter what
	void treadpix(){
	//create window and renderer
	 
	SDL_CreateWindowAndRenderer(1920, 1080, 32, &window, &renderer) ;
		
		//creating a RT canvas
		cvs = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1920,1080 );

		SDL_SetRenderTarget(renderer, cvs);
		SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );		
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

		SDL_Rect greenRect = 
			{0,0,
			768,768};
		SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );		
		SDL_RenderFillRect( renderer, &greenRect );

		SDL_RenderPresent(renderer);
		
		//now we blit the brush to it to see if alpha is taken in account
		// SDL_Rect destRect = 
			// {0,0,
		   // 128,128};
		// SDL_RenderCopy(renderer,brush,NULL,&destRect);
		
		//render on scrin
		//if the clear with alpha of the brush was successful,
		//we should see a bit of green below the red square, not black
		//WIN32 works, brush has alpha
		//ANDRO GLES2 works, brush has alpha		
		SDL_SetRenderTarget(renderer,NULL);
		
		SDL_SetRenderDrawColor( renderer, 0x00,0x00, 0x00, 0x00 );		
		SDL_RenderClear(renderer);
		
		   SDL_Rect dispRect = 
			{0,0,
			1920,1080};
		SDL_RenderCopy(renderer, cvs, NULL, &dispRect);


		SDL_RenderPresent(renderer);

		attemptSave();
		
			
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

	
}
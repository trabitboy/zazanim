#include "testsimple.h"

//simple render test
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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



#include "SDL.h"

typedef struct Sprite
{
    SDL_Texture* texture;
    Uint16 w;
    Uint16 h;
} Sprite;

/* Adapted from SDL's testspriteminimal.c */
Sprite LoadSprite(const char* file, SDL_Renderer* renderer)
{
    Sprite result;
    result.texture = NULL;
    result.w = 0;
    result.h = 0;
    
    SDL_Surface* temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(file);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return result;
    }
    result.w = temp->w;
    result.h = temp->h;

    /* Create texture from the image */
    result.texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!result.texture) {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return result;
    }
    SDL_FreeSurface(temp);

    return result;
}

void draw(SDL_Window *window, SDL_Renderer* renderer, const Sprite sprite)
{
    int w, h;

    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect destRect = {w/2 - sprite.w/2, h/2 - sprite.h/2, sprite.w, sprite.h};
    /* Blit the sprite onto the screen */
    SDL_RenderCopy(renderer, sprite.texture, NULL, &destRect);
}

void testsimple()
{
    // SDL_Window *window;
    // SDL_Renderer *renderer;
SDL_Window * window= NULL;
SDL_Renderer * renderer= NULL;

    if(SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) < 0)
        exit(2);

    Sprite sprite = LoadSprite("sample.bmp", renderer);
    if(sprite.texture == NULL)
        exit(2);

	bool display;
	display=true;
		
	LOGD("prout\n");
    /* Main render loop */
    Uint8 done = 0;
    SDL_Event event;
    while(!done)
    {
        /* Wait for events */
        SDL_WaitEvent(&event);
        do {
		
							//User requests quit
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
						// touchLocation.x = event.tfinger.x * gScreenRect.w;
						// touchLocation.y = event.tfinger.y * gScreenRect.h;
						LOGD("thomas finger down");
						// currentTexture = &gTouchDownTexture;
						display=false;
					}
					//Touch motion
					else if( event.type == SDL_FINGERMOTION )
					{
						// touchLocation.x = event.tfinger.x * gScreenRect.w;
						// touchLocation.y = event.tfinger.y * gScreenRect.h;
						LOGD("thomas finger motion");
						// currentTexture = &gTouchMotionTexture;
						display=false;
					}
					//Touch release
					else if( event.type == SDL_FINGERUP )
					{
						// touchLocation.x = event.tfinger.x * gScreenRect.w;
						// touchLocation.y = event.tfinger.y * gScreenRect.h;
						LOGD("thomas finger up");
						display=true;
						// currentTexture = &gTouchUpTexture;
					}

		
	    // if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN
               // || event.type == SDL_FINGERDOWN)
            // {
				// LOGD("thomas exit");
                // done = 1;
            // }
        } while (SDL_PollEvent(&event));
        
        
        /* Draw a gray background */
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        
		if(display==true){
        draw(window, renderer, sprite);
		}
	
        /* Update the screen! */
        SDL_RenderPresent(renderer);
    }

    exit(0);
}
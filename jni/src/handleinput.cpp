#include "handleinput.h"
#include "SDL.h"
//globstrcut mandatorily after sdl or ifdef fails
#include "stdio.h"
#include "globstruct.h"

SDL_Event event;


void cleaninput(input *to_clean){
			to_clean->endofpress=false;
			to_clean->kright=false;
			to_clean->kleft=false;
			if(to_clean->newpress){
			  to_clean->newpress=false;

			  LOGD("zzn newpress cleaned");
			}
			to_clean->pressed=false;
}

//android version
#ifdef __ANDROID_API__
void handleinput(input *to_populate,bool blocking){
  //otherwise newpress never cleaned
  cleaninput(to_populate);
  int sw,sh;
	sw=to_populate->sw;
	sh=to_populate->sh;
			to_populate->endofpress=false;
			to_populate->newpress=false;
			to_populate->pressed=false;
			if(blocking){
				SDL_WaitEvent(&event);
			}else{
				SDL_PollEvent(&event);
			}
				
			do {
						//we don't track finger up ( maybe we should )
						if( event.type == SDL_QUIT )
						{
							to_populate->quit = true;
						}
						else if( event.type == SDL_FINGERDOWN || event.type == SDL_FINGERMOTION )
						{
							to_populate->pressed=true;
						
							to_populate->x = event.tfinger.x *
							SCRWDTH
							;
							to_populate->y = event.tfinger.y * 
							SCRHGTH
							;
							
							if(event.type == SDL_FINGERDOWN){
								LOGD("SDL zzn newpress %d %d ",to_populate->x,to_populate->y);
								to_populate->newpress=true;
							}else{
							  LOGD("SDL zzn move %d %d ",to_populate->x,to_populate->y);

							}

						}
						else if( event.type == SDL_FINGERUP)
						{
							to_populate->endofpress=true;
							LOGD("zzn end of press, finger up \n");
						}
						else if( event.type == SDL_KEYDOWN)
						{
						  LOGD("zzn key pressed \n");
						  //TODO use volume up to toggle buttons displayed or not
							if(event.key.keysym.sym==SDLK_VOLUMEUP){
								LOGD("zzn volume up \n");
								
							}
							// // if()
							// to_populate->endofpress=true;
						}

			} while (SDL_PollEvent(&event));


}
#endif


//desktop / win version
#ifndef __ANDROID_API__
bool released =true;

void handleinput(input *to_populate,bool blocking){
			//cleaning new press ( if we come back here it has already 
			// been processed )
			to_populate->newpress=false;
			to_populate->endofpress=false;
			// to_populate->kright=false;
			// to_populate->kleft=false;

			// cleaninput(to_populate);
			
			if(blocking){
				SDL_WaitEvent(&event);
			}else{
				SDL_PollEvent(&event);
			}
			do {
						//we don't track finger up ( maybe we should )
				if( event.type == SDL_QUIT )
				{
					to_populate->quit = true;
				}

				if(event.type == SDL_KEYDOWN){
				  if (event.key.keysym.sym==SDLK_RIGHT){
				    to_populate->kright=true;
					LOGD("right pressed\n");
				  }else if (event.key.keysym.sym==SDLK_LEFT){
				    to_populate->kleft=true;
					LOGD("left pressed\n");
				  }

				}else if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (event.button.button == SDL_BUTTON_LEFT) {
						// LOGD( "mouse cl x: %d\n" , event.button.x );
						// LOGD( "mouse cl y: %d\n" , event.button.y );
						if(released==true){
							to_populate->newpress=true;
							released=false; // on win32 newpress not reliable otherwise
							LOGD("not released flag set\n");
						}
						to_populate->pressed=true;
						to_populate->x=event.button.x;
						to_populate->y=event.button.y;
					}
				}else if (event.type == SDL_MOUSEBUTTONUP) {
					if (event.button.button == SDL_BUTTON_LEFT) {
						to_populate->pressed=false;
						released=true;
						to_populate->endofpress=true;
						LOGD("released flag set\n");
					}
				}else if (event.type == SDL_MOUSEMOTION) {

					if (to_populate->pressed) {
						to_populate->x=event.button.x;
						to_populate->y=event.button.y;
					}
				}
						
						
						
						
			} while (SDL_PollEvent(&event));


}
#endif

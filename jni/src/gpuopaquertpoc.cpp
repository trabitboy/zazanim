

//**************  GENERAL BENCHMARKING ***************
#define BENCH true

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "SDL.h"
//globstrcut mandatorily after sdl or ifdef fails
#include "globstruct.h"
#include "handleinput.h"

//create previous and next from surface 
//to streaming access texture

//load in tmp texture and blit current on rt
// time the operation

//TODO look at tex compression
//TODO scale canvas to screen ( other rtotex ? ) ( just blit coordinates on render ? )

// input manager ( updates struct with coords, newpress, pressinprogress, zoom, quantity_of_zoom )
// mouse input manager
// to cover the mouse / touch difference  

// load 10 surf and practice moving within the anim
//feed current slot and compose rt canvas with it on scroll
// compose current avec alpha 255
//save modifs on slot change to surf 
//TODO sdl read pixels doesn't work with render target on windows, check on simple unit test
//work around using framebuffer implemented
// read from fb doesn't work on andro but read from tex works ( inverted )
// draw gfx buttons
// save surfaces to files 
// next 
// previous
// play
// save
// save all surfaces on button
//done android lookup is not correct,
//load and save should be in data folder

//TODO copy colors other than blue on toggle
//WIP eraser toggle
//TODO play button ( state / classes )
//do with function pointer
//TODO poc render from surf, streaming to texture
// TODO perf logs , on ifdef
//do it as macro
// download from gpu seems very slow

//done save

//TODO flick gadget




namespace opaqueRTPOC{
	//just to restore build
	int sw=0;
	int sh=0;

	//quick zoom test
	float zoom=1;
		float buttonZoom=1; // preinit for windows?


	SDL_Texture * buttons=NULL;

	SDL_Texture * brush= NULL;

	
	//all the picture slotss
	//hardcoded at the mo
	SDL_Surface * project[DFLT_FRAME_NMBER];
	
	//the 3 slots we are working on
	//onion skin
	SDL_Texture * previous = NULL;
	//current to blit on RT cvs on change slot
	SDL_Texture * current = NULL;
	//onion skin
	SDL_Texture * next = NULL;
	//render target of brush
	//( we can't upload pixels directly )
	//and blit result will be opaque ( rt for some reason )
	SDL_Texture * cvs = NULL;

	
	SDL_Window * window= NULL;
	SDL_Renderer * renderer= NULL;

	Sint16 nb_edit_slot=1; //sensible dflt
	

	void initprojectframes(){
		//preinit
		int i;
		for(i=0;i<DFLT_FRAME_NMBER;i++){
			project[i]=NULL;
			
		}
		
		
		//TODO on android when app installed, data is erased, loading from template in apk would be cool 
		//if null ( it probably doesn't work now )
		LOGD("zzn load begin \n");
		char path[256];
		strcpy(path,"./");
		#ifdef __ANDROID_API__
		//overriding with android sensible default
		strcpy(path, 
		SDL_AndroidGetExternalStoragePath()
		);
		// strcpy(pathAndName,"/storage/extSdCard");
		strcat(path,"/");
		#endif
		LOGD("zzn %s\n",path);

		char file[256];
		
		strcpy(file,path);
		strcat(file,"frame0.bmp");
		LOGD("zzn %s\n",file);
		project[0] = SDL_LoadBMP(
					file
		);
		strcpy(file,path);
		strcat(file,"frame1.bmp");
		LOGD("zzn %s\n",file);
		project[1] = SDL_LoadBMP(
					file
		);
		strcpy(file,path);
		strcat(file,"frame2.bmp");
		LOGD("zzn %s\n",file);
		project[2] = SDL_LoadBMP(
					file
		);
		strcpy(file,path);
		strcat(file,"frame3.bmp");
		LOGD("zzn %s\n",file);
		project[3] = SDL_LoadBMP(
					file
		);
		strcpy(file,path);
		strcat(file,"frame4.bmp");
		LOGD("zzn %s\n",file);
		project[4] = SDL_LoadBMP(
					file
		);
		LOGD("zzn data load end \n");
		
		//on android data folder is destroyed on uninstall so we
		//add this workaround to load from assets
		if(
			project[0]==NULL
			||project[1]==NULL
			||project[2]==NULL
			||project[3]==NULL
			||project[4]==NULL
		
		){
			LOGD("zzn one surf null we try to get template from assets andro \n");
			project[0] = SDL_LoadBMP(
					 "frame0.bmp"
			);
			project[1] = SDL_LoadBMP(
					 "frame1.bmp"
			);
			project[2] = SDL_LoadBMP(
					 "frame2.bmp"
			);
			project[3] = SDL_LoadBMP(
					 "frame3.bmp"
			);
			project[4] = SDL_LoadBMP(
					 "frame4.bmp"
			);
		
		}
	
	}

	void saveProjectFrames(){
		LOGD("zzn save begin \n");
		
		char path[256];
		strcpy(path,"./");
		#ifdef __ANDROID_API__
		//overriding with android sensible default
		strcpy(path, 
		SDL_AndroidGetExternalStoragePath()
		);
		// strcpy(pathAndName,"/storage/extSdCard");
		strcat(path,"/");
		#endif
		LOGD("zzn %s\n",path);

		char file[256];
		
		strcpy(file,path);
		strcat(file,"frame0.bmp");
		LOGD("zzn %s\n",file);
		SDL_SaveBMP(project[0],file);
		strcpy(file,path);
		strcat(file,"frame1.bmp");
		LOGD("zzn %s\n",file);
		SDL_SaveBMP(project[1],file);
		strcpy(file,path);
		strcat(file,"frame2.bmp");
		LOGD("zzn %s\n",file);
		SDL_SaveBMP(project[2],file);
		strcpy(file,path);
		strcat(file,"frame3.bmp");
		LOGD("zzn %s\n",file);
		SDL_SaveBMP(project[3],file);
		strcpy(file,path);
		strcat(file,"frame4.bmp");
		LOGD("zzn %s\n",file);
		SDL_SaveBMP(project[4],file);
		LOGD("zzn save end \n");
	}
	
	//intended to be called only from rgpupoc
	void renderbuttons(){
		// SDL_SetRenderTarget(renderer,NULL);
		   SDL_Rect dispRect = 
			{BTN_NXT_UL_X,BTN_NXT_UL_Y,
			64,256};
	   SDL_Rect clipRect = 
			{0,0,
			BTN_BASE_W,BTN_BASE_W};

		SDL_RenderCopy(renderer,
		buttons, 
		// &clipRect,
		NULL,
		&dispRect
		);
		// SDL_RenderPresent(renderer);
	
	
	
	}
	

	//we pass buttons as parameter,
	//as on gles target rt change clears screen
	void rendergpupoc(SDL_Renderer * renderer,SDL_Texture * cvs,bool buttons){
		SDL_SetRenderTarget(renderer,NULL);
		   SDL_Rect dispRect = 
			// {0,0,
			// 1280,720};
			{XORIG,YORIG,
			CVSWDTH*zoom,CVSHGTH*zoom};
		SDL_RenderCopy(renderer, cvs, NULL, &dispRect);
		//for onion skinning
		SDL_RenderCopy(renderer, previous, NULL, &dispRect);
		SDL_RenderCopy(renderer, next, NULL, &dispRect);
		
		if(buttons)renderbuttons();
		
		SDL_RenderPresent(renderer);


	}

	void saveRTCanvasToSurf();

	void testSaveTexUsingFrameBuffer();
	
	void paintCanvas(int x, int y,SDL_Renderer * renderer,SDL_Texture * tgt,SDL_Texture * with){

			Uint8 ret=SDL_SetRenderTarget( renderer, tgt );
			//DEBUG
			// LOGD("zzn painting set render targ :%d \n",ret);
		   SDL_Rect destRect = 
		   {x, y,
		   32,32};
		   SDL_RenderCopy(renderer, with, NULL, &destRect);

		   // saveRTCanvasToSurf();
		   // testSaveTexUsingFrameBuffer();
	}

	void paintHandlingUI(int x, int y,SDL_Renderer * renderer){
								paintCanvas
								(x,y,renderer,cvs,brush);
	}


	//we do this only one time
	//not at slot change
	void allocateTextures(){
		previous = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		CVSWDTH,CVSHGTH
		);
		SDL_SetTextureBlendMode(previous,SDL_BLENDMODE_BLEND);
		current = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		CVSWDTH,CVSHGTH
		);
		SDL_SetTextureBlendMode(current,SDL_BLENDMODE_BLEND);
		next = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		CVSWDTH,CVSHGTH
		);
		SDL_SetTextureBlendMode(next,SDL_BLENDMODE_BLEND);
	
	}

	
	void changeOneSlot(
						SDL_Surface * src,
						SDL_Texture * tgt,
						Uint8 alpha
		){
		void* mPixels;
		int mPitch;
		
		//let's check tex pixel format
		Uint32 t_fmt=0;
		SDL_QueryTexture(tgt,&t_fmt,NULL,NULL,NULL);
		printf("tgt t_fmt%d \n",t_fmt);
		Uint32 r,g,b,a;
		int bpp;
		r=0;g=0;b=0;a=0;bpp=0;
		SDL_PixelFormatEnumToMasks( 
			t_fmt,
			&bpp,
			&r,
			&g,
			&b,
			&a
			);
		
		LOGD("zzn tgttex r %08X g %08X  b %08X  \n",r,g,b);
		//even though it seems rgba,
		//testing below shows that it is a b g r
		
		SDL_LockTexture( tgt, NULL, &mPixels, &mPitch );
		//blit like a mad man
		printf("prev pitch %d\n",mPitch);
		Uint32 size = CVSHGTH *CVSWDTH;
		int i;
		
		Uint8 just_tranp=
		// 32
		// 64
		alpha
		// 255
		;
		
		Uint8 surf_r,surf_g,surf_b,onion_a;
		// size * 4 Uint8 slots
		// rgba > argb from surf ( dunno why sdl loader gives argb )
		for(i=0;i<size;i++){
		
		//as seen in test surf access, order is bgra for bmp32,
		//whatever the masks say
		surf_b=((Uint8 *)src->pixels)[4*i];
		surf_g=((Uint8 *)src->pixels)[4*i+1];
		surf_r=((Uint8 *)src->pixels)[4*i+2];
		//we dont need a
		if(surf_b==0 && surf_g==0 && surf_r==0){
			onion_a=0;
		}else{
			onion_a=just_tranp;
		
		}
		// for some reason locked pixels is abgr
		
		//a ( TODO should be 0 if all other is 0 )
		((Uint8 *)mPixels)[4*i]= 
		//debug
		// 32;
		// 255;
		onion_a;
		//b
		((Uint8 *)mPixels)[4*i+1]=
		// 128;
		// 0;
		// 255;
		surf_b;
		//g
		((Uint8 *)mPixels)[4*i+2]=
		surf_g;
		// 0;
		// 255;
		//r in locked tex 
		((Uint8 *)mPixels)[4*i+3]=
		surf_r;
		// 0;
		// 255;
		}
		SDL_UnlockTexture( tgt );	
		
	}
	
	//TODO current should be 255 alpha
	//fill the 3 slots with the data ( no allocation )
	// might save from render target to surf?
	//THIS DOES NOT SAVE EDITS ON THE RENDER TARGETS
	void changeSlots(
						SDL_Surface * _prev,
						SDL_Surface * _current,
						SDL_Surface * _next
						
						){
		if(_prev != NULL){
			changeOneSlot(_prev,previous,64);
		}
		changeOneSlot(_current,current,255);	
		
		if(_next != NULL){
			changeOneSlot(_next,next,64);
		}
	}
	
	void freeprojectframes(){
		int i;
		for(i=0;i<DFLT_FRAME_NMBER;i++){
			SDL_FreeSurface(project[i]);
		}
	}

	
	//WORKAROUND render target doesn't seem to work to read pixels ( on dx at least ),
	//clearing and rendering on frame buffer, then saving
	//BUG: on android gles, has a margin on the left
	void testSaveTexUsingFrameBuffer(){
	
	Uint32 bench = SDL_GetTicks();
	
	//old school
			SDL_SetRenderTarget(renderer,NULL);
//on android the bg is not cleared on target change
//TODO test
		SDL_SetRenderDrawColor(renderer,0X00,0X00,0X00,0X00);
		SDL_RenderClear(renderer);
			
		   SDL_Rect dispRect = 
			{0,0,
			CVSWDTH,CVSHGTH};
		SDL_RenderCopy(renderer, cvs, NULL, &dispRect);
		SDL_RenderPresent(renderer);
		int pwidth=CVSWDTH;
		int pheight=CVSHGTH; 
		
		Uint32 p[pwidth*pheight];
		SDL_Rect pick={
		0,
		0,
		pwidth,pheight
		};
		
		//core dump if no prealloc 
		void * readpixels= malloc (4*CVSWDTH*CVSHGTH);
		
        SDL_RenderReadPixels(renderer, &pick, SDL_PIXELFORMAT_RGBA8888, 
		readpixels,
		pwidth
		*4 //length of line in octets
		);		
		
		int i;
		int j;
		
		
		//readpixels > 0 is A
		
		
		//TODO put pixels in the right place in surf
		//WIP brute force try
		//from load test surf is BGRA
		for(j=0;j<pheight;j++){
			// // LOGD("zzn");
			for(i=0;i<pwidth;i++){
				//WIP still having no fricking idea of the pixel format 
				//without testing
				//surf is 
				//b in surf
				((Uint8*)project[nb_edit_slot]->pixels)[ 4*(pwidth*j+i)]=
				((Uint8 *)readpixels)[4*(pwidth*j+i)
				 +1
				];
				// 255; // debug to identify blue // indeed blue in surf
				
				
				//g in surf
				// ((Uint8*)project[nb_edit_slot]->pixels)[ 4*(pwidth*j+i)+1]=
				// // ((Uint8 *)readpixels)[4*(pwidth*j+i)+1];
				// 255; // debug to identify green // indeed green in surf

				//r in surf
				// ((Uint8*)project[nb_edit_slot]->pixels)[ 4*(pwidth*j+i)+2]=
				// ((Uint8 *)readpixels)[4*(pwidth*j+i)];
				// 255; // debug to identify red // indeed red in surf
			
				
			}
			// LOGD("\n");
		}

		//DEBUG TEST 
		// SDL_SaveBMP(project[nb_edit_slot],"test.bmp");
		
		
		free(readpixels);

		bench=SDL_GetTicks()-bench;
		LOGD("zzn save from fb ms %d \n",bench);
		
	}
	
	
	
	
	
	//TODO flag to invert for gles target
	//when changing slot we need to copy back from gpu
	void saveRTCanvasToSurf(){
		//set render target DOESN'T WORK in this context on dx 
		//read pixels grabs from fb instead, but gles seems to work
		
		Uint32 bench = SDL_GetTicks();

		
		Uint8 ret=SDL_SetRenderTarget(renderer,
		cvs
		);
		LOGD("zzn readpix set render targ :%d \n",ret);

		
		
		int pwidth=CVSWDTH;
		int pheight=CVSHGTH; 
		
		Uint32 p[pwidth*pheight];
		SDL_Rect pick={
		0,
		// XORIG, //render target is set to cvs, BUG SEE ABOVE 
		//but if we don't use the offset copy is offset ( makes no sense )
		0,
		pwidth,pheight
		};
		
		//core dump if no prealloc 
		void * readpixels= malloc (4*CVSWDTH*CVSHGTH);
		
        SDL_RenderReadPixels(renderer, &pick, SDL_PIXELFORMAT_RGBA8888, 
		readpixels,
		pwidth
		*4 //length of line in octets
		);
		
		
		int i;
		int j;
		
		
		//readpixels > 0 is A
		
		
		//TODO put pixels in the right place in surf
		//WIP brute force try
		//from load test surf is BGRA
		for(j=0;j<pheight;j++){
			// // LOGD("zzn");
			for(i=0;i<pwidth;i++){
				//WIP still having no fricking idea of the pixel format 
				//without testing
				//surf is 
				//b in surf
				((Uint8*)project[nb_edit_slot]->pixels)[ 4*(pwidth*j+i)]=
				((Uint8 *)readpixels)[4*(pwidth*j+i)
				 +1
				];
				// 255; // debug to identify blue // indeed blue in surf
				
				
				//g in surf
				// ((Uint8*)project[nb_edit_slot]->pixels)[ 4*(pwidth*j+i)+1]=
				// // ((Uint8 *)readpixels)[4*(pwidth*j+i)+1];
				// 255; // debug to identify green // indeed green in surf

				//r in surf
				// ((Uint8*)project[nb_edit_slot]->pixels)[ 4*(pwidth*j+i)+2]=
				// ((Uint8 *)readpixels)[4*(pwidth*j+i)];
				// 255; // debug to identify red // indeed red in surf
			
				
			}
			// LOGD("\n");
		}

		//DEBUG TEST 
		// SDL_SaveBMP(project[nb_edit_slot],"test.bmp");
		
		
		free(readpixels);

		bench=SDL_GetTicks()-bench;
		LOGD("zzn save from fb ms %d \n",bench);

		
	}
	
	//set texture slots on edit position,
	//then preparing RT cvs
	void setEditSlot(int nb){
		//TODO validation that nb is possible
		LOGD("setting edit slot %d \n",nb);
		if( nb<0){
			LOGD("no back possible");
			return;
		}
		
		if(nb>(DFLT_FRAME_NMBER-1)){ //for 10 frames, max nb possible is 9
			LOGD("no fwd possible");
			return;		
		}
		
		SDL_Surface * pot_prev=NULL;
		if(nb-1>=0)pot_prev=(project[nb-1]);
		SDL_Surface * pot_next=NULL;
		if(nb+1<=DFLT_FRAME_NMBER-1){
			pot_next=(project[nb+1]);
		}
		
		changeSlots(
		pot_prev,
		project[nb],
		pot_next
		);

		//we blit current to prepare canvas
		SDL_SetRenderTarget(renderer,cvs);
		SDL_SetRenderDrawColor(renderer,0X00,0X00,0X00,0X00);
		SDL_RenderClear(renderer);
	   SDL_Rect dispRect = 
			// {0,0,
			// 1280,720};
			{0,0,
			CVSWDTH,CVSHGTH};
		SDL_RenderCopy(renderer, current, NULL, &dispRect);
		//for onion skinning
		SDL_RenderPresent(renderer);

		
		
	}

bool checkButtonColl(int x,int y){
	LOGD("zzn checking buttons\n");
	if( 
		x < (BTN_NXT_UL_X+BTN_BASE_W)
		&& x > BTN_NXT_UL_X
		&&	y < (BTN_NXT_UL_Y+BTN_BASE_W)
		&& y > BTN_NXT_UL_Y
	){
		LOGD("zzn button next\n");
		//TODO validation two times so far
		int tgt = nb_edit_slot+1;
		if(tgt>(DFLT_FRAME_NMBER-1)){ //for 10 frames, max nb possible is 9
			LOGD("no fwd possible for edit slot %d\n",tgt);
			return true;		
		}else{
			//WIP DEBUG save rt to surf
			
			#ifndef __ANDROID_API__
			testSaveTexUsingFrameBuffer();
			#endif
			
			#ifdef __ANDROID_API__
			saveRTCanvasToSurf();
			#endif
			
			// saveRTCanvasToSurf();
			setEditSlot(tgt);
			nb_edit_slot=tgt;
		}

		
		// erase=! erase;
		return true;
	}else 	if( 
		x < (BTN_PREV_UL_X+BTN_BASE_W)
		&& x > BTN_PREV_UL_X
		&&	y < (BTN_PREV_UL_Y+BTN_BASE_W)
		&& y > BTN_PREV_UL_Y
	){
		LOGD("zzn button back\n");
		int tgt = nb_edit_slot-1;
		if(tgt<0){ //for 10 frames, min nb possible is 1
			LOGD("no back possible for edit slot %d\n",tgt);
			return true;		
		}else{

			#ifndef __ANDROID_API__
			testSaveTexUsingFrameBuffer();
			#endif
			
			#ifdef __ANDROID_API__
			saveRTCanvasToSurf();
			#endif

			setEditSlot(tgt);
			nb_edit_slot=tgt;
		}
		
	}else 	if( 
		x < (BTN_SAVE_UL_X+BTN_BASE_W)
		&& x > BTN_SAVE_UL_X
		&&	y < (BTN_SAVE_UL_Y+BTN_BASE_W)
		&& y > BTN_SAVE_UL_Y
	){
		LOGD("zzn save clicked\n");
		saveProjectFrames();
	}
		
	
	
	
	return false;
}
	
	
	
	//main test
	void gpuopaquertpoc(){
		LOGD("zzn logcat test\n");

	zoom=((float) SCRHGTH) / ((float)CVSHGTH);
		

	SDL_CreateWindowAndRenderer(
	SCRWDTH,SCRHGTH,
	0, &window, &renderer) ;
		//test data, will be replaced by buffer of surfaces
		//TODO I would compose the tex myself to be sure
		//of alpha
			// SDL_Surface * previousSurf = SDL_LoadBMP(
					// "previous.bmp"
		// );
	
	initprojectframes();
	
	//this info is wrong ( masks ), see testsurf access
	// LOGD("zzn prevsurf r %08X g %08X  b %08X pitch %d \n",
	// previousSurf->format->Rmask,
	// previousSurf->format->Gmask,
	// previousSurf->format->Bmask,
	// previousSurf->pitch);
	
		allocateTextures();
		cvs = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		// 1280,720
		CVSWDTH,CVSHGTH
		);
		//on note 8 the tex returned is not zeroed,tentative fix
		SDL_SetRenderTarget(renderer,cvs);
		SDL_SetRenderDrawColor(renderer,0X00,0X00,0X00,0X00);
		SDL_RenderClear(renderer);

		setEditSlot(nb_edit_slot);

		SDL_Surface * brushSurf = SDL_LoadBMP(
					"brush32.bmp"
		);
		brush  = SDL_CreateTextureFromSurface(renderer, brushSurf);
		SDL_FreeSurface( brushSurf);

		SDL_Surface * buttonsSurf = SDL_LoadBMP(
					"buttons.bmp"
		);
		buttons  = SDL_CreateTextureFromSurface(renderer, buttonsSurf);
		SDL_FreeSurface( buttonsSurf);
		
		
		//end canvas clear
		//for test without doing anything
		paintCanvas
		(0,0,renderer,cvs,brush);

		//not pushing it in render gpu poc ( perf ? ) NOT WORKING RIGHT NOW
		//in case set render target clears ops?
		rendergpupoc(renderer,cvs,true);

		// renderbuttons();
		
		// Uint8 done = 0;
		// SDL_Event event;
		
		//we pass it to the system defined input handler
		input polled;
		polled.quit=false;//toget in the while
		polled.pressed=false;//init 
		
		bool noPaint=false;
		while(!
			polled.quit
		// done
		)
		{
			handleinput(&polled,true);
			/* Wait for events */
			// SDL_WaitEvent(&event);
			// do {
				noPaint=false;
						// if( event.type == SDL_QUIT )
						// {
							// done = true;
						// }
						// else if( event.type == SDL_FINGERDOWN || event.type == SDL_FINGERMOTION )
						// {
							// Uint16 x = event.tfinger.x *
							// SCRWDTH
							// ;
							// Uint16 y = event.tfinger.y * 
							// SCRHGTH
							// ;
							
							// if(event.type == SDL_FINGERDOWN){
							if(polled.newpress){
								LOGD("zzn checking buttons\n");
								noPaint=checkButtonColl(polled.x,polled.y);
							}
							// }
								//normaly should not take place in certain case, clean up
							if(polled.pressed && !noPaint){
								paintHandlingUI( 
									(polled.x-XORIG)/zoom, (polled.y-YORIG)/zoom,renderer);
								rendergpupoc(renderer,cvs,true);
							}
							

						// }

			// } while (SDL_PollEvent(&event));
			
			//150624 disabled for test
			//needed when coming back from save fb
			// renderbuttons();
			rendergpupoc(renderer,cvs,true);
		}
		LOGD("zzn quitting\n");
		SDL_DestroyTexture(buttons);	
		SDL_DestroyTexture(cvs);
		SDL_DestroyTexture(brush);
		SDL_DestroyTexture(previous);
		SDL_DestroyTexture(current);
		SDL_DestroyTexture(next);

		//to be replaced by buffer
		// SDL_FreeSurface( previousSurf);
		freeprojectframes();
		
	}

}//ns end


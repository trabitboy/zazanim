

//TODO reintegrate java stub with history handling  ( twice event freq )


//WIP bug on eraser fill/ fill empty color/kill color > just on android note 8> note 4 is fine
// fill of empty color is fine, check erase in fill / kill color before work? 

//only on note 8 , seems on select colors single "dither" pixels are added as if 16bit 


// add 0 frames support on timecodes ( to skip work frames on playback export)
//with decoration

// WIP simple tool to remove all occurences of one color in pic 
// (to remove sketches in clearer color )
//new mode for pick mode
//WIP code ready, put in UI


//paste under in "paste bit",
// in conjunction with behind flag ?

//paste under in paste postiion


//background > load list of images named bgXXX.bmp
//each image is displayed until new bg
//drawing on bg is the pb

// simple but useful -> paint below, useful for coloring and fill
// -do switch to paint below
// - on switch create/clear tex
// -if paint below, flag to paint on this tex
// - flag to render also this tex if paint below
// - when to commit / reset surf to normal render tex ? probably on pen up
// DONE tested on win, with flag, no interface,
// TODO test POC on android


//TODO optional bg layer

//TODO fillmode scroll buttons
//TODO simple x surfs undo on current frame would be cool to debug color

//TEST wav cut paste as there is some logic to move on save 


//BUG rename / shift of wav not working on android
// check if link with paste range
//use C as marker for initial wav
//new button in settings to paste wav ( knowing that not perfect due to frame order)
//171111 still, after some days, wav still shifted

//BUG fill of clear color sometimes makes dithered pattern at least on android
//171111 also happens with normal color

//TODO decoration if frame is covered by sound playback

//TEST fill mode with clear color if eraser enabled
// works on windows, test workaround on android note 4 note 8


//2 fingers zoom / zoom
// -- first keyboard events, joystick
//PB SDL2 app crashes when bt keyboard on, or off

//TODO deco when sound on frame
//TODO erase all wavs on save and resave them with correct number ? keep track of intial number and move to new ?
// rename wavs on save and reset metacounter
//TODO copy of sound metadata around when inserting/ contracting


//WIP chose clear color
// parameterize clear color on load if metadata file present,
// otherwise use white as default

//TODO add button to pick clear color from palette
// should resave and reload to make alpha in the gpu texs consistent

//TODO if clear color changed, 
// save all frames REPLACING CLEAR COLOR IN SURFS WITH NEW and situation should be ok
// > surfs on android and win saved using brute force approach ( clear /light table color is on gpu and copied )
// > flag should be passed to copy back function to replace old clear color with new clear color
// > all frames should be recomposed from files/ or reuploaded?  ( risky !!!!!!! )


// if clear color is changed, on save, update clear color , then reload


//TODO enable fill with clear color

//TODO change buffer surf to rgb 24 as we never use alpha

//WIP palette screen loading bmp from ressource
//add user interface button for palette (no more pick right now)
//had to keep surf to pick colors because copy back from video memory doesn4t work on android 
// (slightly different tex creation from frames ?)

//WIP dodonpachi draw tool
// refactoring of edit loop
// display cursor
// move cursor
//paint by moving
// dodonpachi mode toggle in settings
//dodonpachi mode paint toggle displayed on main edit



//undo using paint surf merged in certain conditions,
// or keep several older surfs ? (easier, more versatile, less code to plug )
// could be ( undo buffer , number of frame ) in a stack
// that way cross frame possible ( rotating buffer )



//transparency for current picture

// load playback rate from file / configure screen?

//do new poc with only 3 tex for previous next current, test perf

//WIP shadow inputs on android
//trying to revert to base sdl java activity
//- base sdl activity shows fantom touch on color pick
//- look at event code, log better handle input
// there is several move that are consumed after execution of color pick
// check if end of newpress correctly handled
//fixed but qa then revert to patched activity

// WIP , pythom, update backup script to centralize on dropbox ( with png )
//png support to load save


// tentative antialiased brush mode :
// draw non antialiased and post process like round eraser on release touch


//on windows changing frame corrupts pic when round eraser is set > work around in place

//stable ! during qa week:
//test current version on pi

//cut up in unit tests


// test operation to delete file again ( once very stable )

//load 8bit surface ( to be able to choose palette on device in grafx2 )

//test units on android and windows and pi

//WIP save 24bpp only 


//WIP sound
//TODO move sound references when shifting
//for each frame load, load wave if there is one 
//on playback , trigger if there is one on frame start
//TODO python scripts to merge wav and mp4s using ffmpeg
//TENTATIVE maybe storyboard view where sound clips can be movedata
// colored bars



//DONE cut alpha as blending wrong on android
//pasting white below could be a solution but then overlap of 2 transparents would be impossible

//idea: objectify state to open several projects at once

//TODO frame delete ( wrong order of treatment and SDL del file option )

//DONE stop play anywhere

//DONE play from anywhere



//**************  GENERAL BENCHMARKING ***************
#define BENCH true

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "Tex.h"
#include "timecodes.h"
//globstrcut mandatorily after sdl or ifdef fails
//#include "cJSON.h"
#include "globstruct.h"
#include "handleinput.h"
#include "traj.h"
#include "composebrush.h"
#include "state.h"
#include "floodfill.h"
#include "cleanartifacts.h"

#ifdef __ANDROID_API__
#include "../SDL/include/SDL_opengles2.h"
#endif
#include <fstream>
#include <iostream>
using namespace std;

//PRIORITIES:

// delete button test > the save shift order treatment works for add but not for delete
// ( every shifted from delete is copied from last frame )
//TODO save delete in reverse order, IN PUSH BUTTON 
// zzn save clicked
// zzn save begin
// zzn ./
// begin save report
// zzn last presumed index 6
// frame 5 is a shift from ./frame006.bmp
// src fwp ./frame006.bmp
// tgt fwp ./frame005.bmp
// frame 4 is a shift from ./frame005.bmp
// src fwp ./frame005.bmp
// tgt fwp ./frame004.bmp
// frame 3 is a shift from ./frame004.bmp
// src fwp ./frame004.bmp
// tgt fwp ./frame003.bmp
// frame 2 is a shift from ./frame003.bmp
// src fwp ./frame003.bmp
// tgt fwp ./frame002.bmp
// zzn save finished,about to regenerate metadata


//TODO blending is not correct on android if brush is transparent,
//blending seems to be done with black instead of white
//TO TEST we copy to a streaming tex, then blit to rt tex ; maybe clean with white transp rt first?
//already cleaned before blit !!!!

//TODO HIDE delete bug, more testing ( consecutive deletes killed the project )



//WIP brush composed with semi alpha on border

// interpolate on/off setting
//HACK just pasting range after selection would be easier to begin with


//decoration for sel begin, sel , sel end


//TODO  delete range
// > same code for delete one and range


//this poc allocates all frames in video memory,
//hungry but no scroll pb on android
// ( it probably was due to a local buffer alloc in save / push streaming tex, could be avoided now )

namespace gputransparentrtpoc{

	//proto
	void resetUndo();
    void initedit();
	void rendergpupoc(SDL_Renderer * renderer,
		bool buttons,bool renderCursor);
	bool checkButtonColl(int x,int y);


	//folder of the current project
	char projectPath[512];

	//proto
	Uint16 cb=0;
	Uint16 ce=0;


	//WIP transparent color is parameterizable now
	Uint8 clearR=CL_R;
	Uint8 clearG=CL_G;
	Uint8 clearB=CL_B;
	
	
	//for mobile where we don't pre know the screen size
	int sw=0;
	int sh=0;
	int xorig=0; // init from screen size and zoom
	
	//brush color, change before realloc
	myRgb col;



	//render position of the canvas, computed only one time
	SDL_Rect cvsDispRect;



		//we don't want to allocate this every loop
		//we pass it to the system defined input handler
		input polled;


	//quick zoom test
	float zoom=1; //canvas
	float buttonZoom=1; // preinit for windows?

	//flag for BEHIND paint mode
	bool BEHIND=false;
	
	//WIP this is used to determine initial texture size, but scale is actually used by gadget
	Uint16 brushRadius= 
						// 8
						// 16
						 16 //we init at max, then we only change clipping
						;

	Uint16 brushScale=16;
						
	SDL_Texture * buttons=NULL;

	SDL_Texture * brush= NULL;

	SDL_Texture * eraser= NULL;
	
	SDL_Texture * roundEraser= NULL;
	
	
	//NO ALLOC just holds current brush
	SDL_Texture * activeBrush=NULL;
	
	//32bpp, used when geting data back from gpu
	SDL_Surface * bufferSurf=NULL;

	//palette texture for color pick screen
	//she loading code takes 24 and 32
	SDL_Texture * palette=NULL;
	SDL_Surface * paletteSurface=NULL;
	
	//TODO 24bpp, to always save 24bpp for simplicity
	SDL_Surface * saveSurf=NULL;
	
	
	//buffer for intermediary blits between 2 events
	Blit interpolated[MAX_BLITS];
	
	//rts, can't manipulate directly
	Tex project[MAX_FRAME_NMBER];

	//streaming access, use to initially fill the rts
	SDL_Texture * tmp=NULL;

	//behind paint mode
	SDL_Texture * pane=NULL;
	
	//undo buffer on which pane is pasted
	const Uint8 undoDepth=3;
	SDL_Texture * undoBuf[undoDepth];
	Sint8 currentUndoBuf=0;//this changes as we paint
	Sint8 currentUndoDepth=0;//how many steps undo can go back
	
	// ONLY POINTERS  ( points to buffer )
	//onion skin
	SDL_Texture * previous = NULL;
	//current 
	SDL_Texture * current = NULL;
	//onion skin
	SDL_Texture * next = NULL;

	//copy src
	SDL_Texture * copy_src=NULL;
	
	SDL_Window * window= NULL;
	SDL_Renderer * renderer= NULL;

	Sint16 nb_edit_slot=1; //sensible dflt

	
		//curses project frames until a NULL is found
	int frameNumber(){
			int ret=0;
	
			int i;
			for(i=0;i<MAX_FRAME_NMBER;i++){
				if(project[i].tx==NULL){
					
					break;
				}else{
					ret++;
				}
			}
			LOGD("zzn last presumed index %d \n",ret);
			
			return ret;
	}	

	
	void loadsurftostreamingtex(
						SDL_Surface * src,
						SDL_Texture * tgt,
						bool takeSrcAlpha,
						Uint8 alpha
		);
	void blittexoncleanrt(SDL_Renderer * renderer,SDL_Texture * tgt,SDL_Texture * src);	

	//mutualized to be usable for undo buffer creation
	SDL_Texture * createFrameTexture(){
				SDL_Texture * ret=SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
												CVSWDTH,CVSHGTH);
				//TODO we should maybe clear to white transparent, so that after blending from
				// the tmp tex, blend will be ok with "bg"
												
				SDL_SetTextureBlendMode(ret,SDL_BLENDMODE_BLEND);
				
				SDL_SetRenderTarget( renderer, ret );
			
			//tentatively commented as doesn't work on android gles2
			//reactivated to remove garbled graphics on note8 andro 4
			//spaghetti : was not working to paste content on target after white clean up ( on note 3 neo andro 5)
			//( round brush ), but necessary when loading one note 8 andro 4 ( clear render target with square not working there ? )
			//TODO externalise both functions
			
			//this block doesn't work on note 3 and is necessary on note 8!!!!
			
			SDL_SetRenderDrawColor(renderer,
			
			// CL_R,CL_G,CL_B,
			clearR,clearG,clearB,
			0X00);
			SDL_RenderClear(renderer);

			return ret;
		
	}
	
	//TODO refactor and replace with one buffer surf
	void loadprojectsurfs(){
		int j;
		for(j=0;j<MAX_FRAME_NMBER;j++){
			project[j].tx=NULL;
			project[j].dirty=false;
			project[j].shifted=false;
			project[j].timecode=1;
			project[j].snd=NULL;
			project[j].wavFileNumberOnDisk=0;
			strcpy(project[j].loadedfrom,"\0");
		}
	
		//all the picture slotss
		//hardcoded at the mo
		//TODO will not be kept once uploaded to texs
		SDL_Surface * loadedsurf;
		//preinit
		loadedsurf=NULL;
		// }
		LOGD("zeroed surf * : %d\n",loadedsurf);
		
		//if null ( it probably doesn't work now )
		LOGD("zzn load begin \n");

		char file[256];
		
		char num[4]="";


		//we need this tmp as technical artifact
		LOGD("about to allocate tex\n");
		tmp = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		CVSWDTH,CVSHGTH
		);
		SDL_SetTextureBlendMode(tmp,SDL_BLENDMODE_BLEND);

		int i;
		for( i= 0;i<MAX_FRAME_NMBER;i++){
			LOGD("before load surf %d  :  %d \n",i,loadedsurf);

			strcpy(file,projectPath);
			strcat(file,"frame");
			
			strcpy(num,"");
			
			// snprintf(num,sizeof(num),"%d",i);
			sprintf(num,"%03d",i);

			strcat(file,num);
			strcat(file,".bmp");
			LOGD("zzn %s\n",file);
			loadedsurf = SDL_LoadBMP(
						file
			);
			//extra check to add a default frame on android
			if(loadedsurf==NULL){
				if(i==0||i==1||i==2){
				//TODO should use append frame
					LOGD("zzn one surf null we try to get template from assets andro \n");
					loadedsurf = SDL_LoadBMP( //android, will look in apk
							 // "frame0.bmp"
							 "template.bmp"
					);
					LOGD("zzn dflt data load end \n");
					project[i].dirty=true; //this is gonna be a new frame
					LOGD("zzn %i dirty create from template \n");
				}
			
			}


			LOGD("loaded surf %d  :  %d \n",i,loadedsurf);
			if(loadedsurf==NULL){
			
				LOGD("zzn loaded %d is null so not existing or error \n",i);
				break;
			}else{
				LOGD("zzn %d exists, is loaded \n",i);
				//insert logic here
				LOGD("zzn %d exists, allocate texture \n",i);
				
				project[i].tx=createFrameTexture();
				//extract for undo buff rotation
				// project[i].tx=SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
												// CVSWDTH,CVSHGTH);
				// //TODO we should maybe clear to white transparent, so that after blending from
				// // the tmp tex, blend will be ok with "bg"
												
				// SDL_SetTextureBlendMode(project[i].tx,SDL_BLENDMODE_BLEND);
				
									// Uint8 ret=SDL_SetRenderTarget( renderer, project[i].tx );
			
			//tentatively commented as doesn't work on android gles2
			//reactivated to remove garbled graphics on note8 andro 4
			//spaghetti : was not working to paste content on target after white clean up ( on note 3 neo andro 5)
			//( round brush ), but necessary when loading one note 8 andro 4 ( clear render target with square not working there ? )
			//TODO externalise both functions
			
			//this block doesn't work on note 3 and is necessary on note 8!!!!
			
			// SDL_SetRenderDrawColor(renderer,
			
			// // CL_R,CL_G,CL_B,
			// clearR,clearG,clearB,
			// 0X00);
			// SDL_RenderClear(renderer);

				
				
				
				loadsurftostreamingtex(loadedsurf,tmp,false,255);		
				blittexoncleanrt(renderer,project[i].tx,tmp);		

				if(sizeof(file)>256)LOGD("WARN path too long for metadata\n");
				strcpy(project[i].loadedfrom,file);
				
				//default case that can be overwritten
				project[i].timecode=1;
				
			}
			LOGD("about to see if there is a sound trigger for this frame");
			strcpy(file,projectPath);
			strcat(file,"frame");
			
			strcpy(num,"");
			
			// snprintf(num,sizeof(num),"%d",i);
			sprintf(num,"%03d",i);

			strcat(file,num);
			strcat(file,".wav");
			project[i].snd=Mix_LoadWAV( 
			// "slash.wav"
				file
			);
			project[i].wavFileNumberOnDisk=i;
		LOGD("sound trigger for frame %d is %d \n",i,project[i].snd);

			
		}

		LOGD("about to free tmp surf for tex load\n");
		
		SDL_FreeSurface(loadedsurf);
		
		
		
	}

		void saveSlotToFile(int slot, char * file);//proto


	//patch move files because we dunno how to rename through SDL on android 
	void movefile(char * srcfilewithpath, char * targetfilewithpath ){
		//TODO implement
		SDL_Surface * tomove = SDL_LoadBMP(srcfilewithpath);
		SDL_SaveBMP(tomove,targetfilewithpath);
		SDL_FreeSurface( tomove );
	}

//extracted to migrate to new save
void saveFrame(char * path, int idx){
		char file[256];
		
		char num[4]="";
			if(project[idx].tx!=NULL){
				strcpy(file,path);
				strcat(file,"frame");
				strcpy(num,"");
				// itoa(i,num,10);//careful, magic é
				// snprintf(num,sizeof(num),"%d",idx);
				sprintf(num,"%03d",idx);
				strcat(file,num);
				strcat(file,".bmp");
				LOGD("zzn %s\n",file);
				saveSlotToFile(idx,file);
			}else{
				//polluting logs
				// LOGD("zzn no tex for index %d \n",idx);
			}


}
	

	//testing if stack is the pb on save crash
	char newsrc[256];
	
	//the distinction between move dirty and untouched is because save from gpu 
	//has terrible performance on android
	void saveReport( char * path,bool save ){
		LOGD("begin save report\n");
		//first shifted, because we should not overwrite possible moves
		int i;
		
		//TODO shift needs to be detected in the other direction 
		// ( from last frame to first )
		//otherwise the 
		int max = frameNumber();
		
		char srcfwp[256];
		char tgtfwp[256];
		char num[4];
	
		for( i= max-1;i>=0;i--){
				if(project[i].shifted==true){
					if(project[i].dirty==false){
						LOGD("frame %d is a shift from %s\n",i,project[i].loadedfrom);
						strcpy(srcfwp,project[i].loadedfrom);
						LOGD("src fwp %s \n",srcfwp);
						strcpy(tgtfwp,path);
						strcat(tgtfwp,"frame");
						// strcat(tgtfwp, //num
						snprintf(num,sizeof(num),"%03d",i);
						strcat(tgtfwp,num);
						
						strcat(tgtfwp,".bmp");
						LOGD("tgt fwp %s \n",tgtfwp);
						if(save){
							movefile(srcfwp,tgtfwp);
							project[i].shifted=false;
							//original file reset globally later
						}
					
					}else{
						//dirty = true, shifted but modified
						LOGD("frame %d is a shift but dirty, will be picked up second pass\n",i);
					}
					//because if we shift, then paint, we need a complete save
				}
		}

		//then we track dirty frames ( created, or edited )
		for( i= 0;i<max;i++){
				if(project[i].dirty==true){
					//because if we shift, then paint, we need a complete save
					LOGD("frame %d is a new full save \n",i);
					if(save){
						saveFrame(path,i);
						//frame is not dirty anymore
						project[i].dirty=false;
					}
				}
		}

		LOGD("zzn save finished,about to regenerate metadata \n");

		LOGD("zzn using path %s\n",path);
		// all graphics is saved we reset metadata such as original file
		for( i= 0;i<max;i++){

			//composing new "loadedfrom"
			strcpy(newsrc,path);
			strcat(newsrc,"frame");

			//TODO append num
			snprintf(num,sizeof(num),"%03d",i);
			strcat(newsrc,num);
			
			strcat(newsrc,".bmp");
			LOGD("frame %d new src %s \n",i,newsrc);
			
			strcpy(project[i].loadedfrom,newsrc);

			
		}
		
		LOGD("end regenerate metadata after save \n");

		
	}

	//prototype
	void saveTranspCol();

	void moveWavsAround(){
		//reversing not to overwrite wavs by accident
		for(Sint16 i=(frameNumber()-1);i>=0;i--){
			LOGD("checking tex %d \n",i);
			if(project[i].snd !=NULL && i!=project[i].wavFileNumberOnDisk){

							//snprintf(num,sizeof(num),"%03d",i);
				char num[4];
				//we need to compose both file names and move files around
				char oldw[512];
				strcpy(oldw,projectPath);
				strcat(oldw,"frame");
				snprintf(num,sizeof(num),"%03d",project[i].wavFileNumberOnDisk);
				strcat(oldw,num);
				strcat(oldw,".wav");
				

				char neww[512];
				strcpy(neww,projectPath);
				strcat(neww,"frame");
				snprintf(num,sizeof(num),"%03d",i);
				strcat(neww,num);
				strcat(neww,".wav");

				LOGD("%s to be renamed %s \n",oldw,neww);

				rename(oldw,neww);

				//rename done , we need to reset index
				project[i].wavFileNumberOnDisk=i;
				
				
			}
		}
	}

	void saveProjectFrames(){
		LOGD("zzn save begin \n");


		saveReport(projectPath,
		// false //for debugging
		true // we cache save !!!!!
		);

		moveWavsAround();


		saveTimeCodes(projectPath,project,frameNumber());
		//saveTranspCol();
		LOGD("zzn save end \n");
	}
	
	//intended to be called only from rgpupoc
	void renderbuttons(){
	   SDL_Rect dispRect = 
			{BTN_NXT_UL_X,BTN_NXT_UL_Y,
			BTN_BASE_W,BTN_BASE_W};
	   SDL_Rect clipRect = 
			{TOFF_NXT_X,TOFF_NXT_Y,
			64,64};

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);

		dispRect.x=BTN_PREV_UL_X;
		dispRect.y=BTN_PREV_UL_Y;
		clipRect.x=TOFF_PREV_X;
		clipRect.y=TOFF_PREV_Y;
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);

		dispRect.x=BTN_SAVE_UL_X;
		dispRect.y=BTN_SAVE_UL_Y;
		clipRect.x=TOFF_SAVE_X;
		clipRect.y=TOFF_SAVE_Y;
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);

		
		dispRect.x=BTN_ERASER_UL_X;
		dispRect.y=BTN_ERASER_UL_Y;
		
		if(activeBrush==roundEraser){
			clipRect.x=TOFF_ROUND_ERASER_X;
			clipRect.y=TOFF_ROUND_ERASER_Y;
		}else if(BEHIND==true){
			clipRect.x=TOFF_CANCEL_X;
			clipRect.y=TOFF_CANCEL_Y;
		}else if(activeBrush==brush){
			clipRect.x=TOFF_BRUSH_X;
			clipRect.y=TOFF_BRUSH_Y;
		}
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);

		dispRect.x=BTN_PLAY_UL_X;
		dispRect.y=BTN_PLAY_UL_Y;
		// clipRect.x=TOFF_PLAY_X;
		// clipRect.y=TOFF_PLAY_Y;
		clipRect.x=TOFF_FILL_X;
		clipRect.y=TOFF_FILL_Y;
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);
		
		dispRect.x=BTN_ADD_UL_X;
		dispRect.y=BTN_ADD_UL_Y;
		clipRect.x=TOFF_ADD_X;
		clipRect.y=TOFF_ADD_Y;
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);

		dispRect.x=BTN_FLR_UL_X;
		dispRect.y=BTN_FLR_UL_Y;
		clipRect.x=TOFF_FLR_X;
		clipRect.y=TOFF_FLR_Y;
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);

		dispRect.x=BTN_FLG_UL_X;
		dispRect.y=BTN_FLG_UL_Y;
		clipRect.x=TOFF_FLG_X;
		clipRect.y=TOFF_FLG_Y;
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);
		
		dispRect.x=BTN_COPY_UL_X;
		dispRect.y=BTN_COPY_UL_Y;
		clipRect.x=TOFF_COPY_X;
		clipRect.y=TOFF_COPY_Y;
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);

		dispRect.x=BTN_PASTE_UL_X;
		dispRect.y=BTN_PASTE_UL_Y;
		clipRect.x=TOFF_PASTE_X;
		clipRect.y=TOFF_PASTE_Y;
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);

		
		
		dispRect.x=BTN_SETTINGS_UL_X;
		dispRect.y=BTN_SETTINGS_UL_Y;
		clipRect.x=TOFF_SETTINGS_X;
		clipRect.y=TOFF_SETTINGS_Y;
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);

		dispRect.x=BTN_UNDO_UL_X;
		dispRect.y=BTN_UNDO_UL_Y;
		clipRect.x=TOFF_UNDO_X;
		clipRect.y=TOFF_UNDO_Y;
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);
		
		
		int i,offset;
		//adding decorations if time code !=1
		offset=BTN_BASE_W /4;
		dispRect.w=offset;
		dispRect.h=offset;
		if(project[nb_edit_slot].timecode!=1){
			for(i=0;i<project[nb_edit_slot].timecode;i++){
				dispRect.x=BTN_BASE_W+i*offset;
				dispRect.y=0;
				clipRect.x=TOFF_SETTINGS_X;
				clipRect.y=TOFF_SETTINGS_Y;
				SDL_RenderCopy(renderer,
				buttons, 
				&clipRect,
				&dispRect
				);
				
			}
		}
		
		// decorate if in selection range
		if(nb_edit_slot <=ce  && nb_edit_slot >= cb ){
			
			dispRect.w=BTN_BASE_W /4;
			dispRect.h=offset;
			dispRect.x=DEC_CR_UL_X;
			dispRect.y=DEC_CR_UL_Y;
			clipRect.x=TOFF_CR_X;
			clipRect.y=TOFF_CR_Y;
			SDL_RenderCopy(renderer,
			buttons, 
			&clipRect,
			&dispRect
			);
		}
		
		// decorate if in sound starts at this frame
		if( project[nb_edit_slot].snd!=NULL ){
		//TODO display and add globstruct variable
			dispRect.w=BTN_BASE_W /4;
			dispRect.h=BTN_BASE_W /4;
			dispRect.x=DEC_SND_UL_X;
			dispRect.y=DEC_SND_UL_Y;
			clipRect.x=TOFF_SND_X;
			clipRect.y=TOFF_SND_Y;
			SDL_RenderCopy(renderer,
			buttons, 
			&clipRect,
			&dispRect
			);
		}

	}
	

	void redWaitScreen(){
		SDL_SetRenderTarget(renderer,NULL);
		SDL_SetRenderDrawColor(renderer,0XFF,0X00,0X00,0XFF);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	
	}
	
	
	void lightTableDrawCalls(){
		SDL_SetRenderDrawColor(renderer,
		clearR,clearG,clearB,
		// CL_R,CL_G,CL_B,
		//not sure if the define is used for render target,
		// 0XF0,0XF0,0XF0, but then we see the gray below the light table :p
		0X00);
		// LOGD(" DBG ltdc, clear color %d %d %d \n",clearR,clearG,clearB );

		SDL_RenderClear(renderer);
		
		//for onion skinning
		SDL_SetTextureAlphaMod(previous,32);
		SDL_RenderCopy(renderer, previous, NULL, &cvsDispRect);
		SDL_SetTextureAlphaMod(next,32);
		SDL_RenderCopy(renderer, next, NULL, &cvsDispRect);
		
		if(BEHIND){
		    SDL_RenderCopy(renderer, pane, NULL, &cvsDispRect);
			// LOGD("rendering behind \n");
			
		}
		
		SDL_SetTextureAlphaMod(project[nb_edit_slot].tx,255);
		SDL_RenderCopy(renderer, project[nb_edit_slot].tx, NULL, &cvsDispRect);

		if(!BEHIND){ //normal mode, we paint on a glass pane until stylus released
		    SDL_RenderCopy(renderer, pane, NULL, &cvsDispRect);
			// LOGD("rendering behind \n");
			
		}
	
	}
	
	void saveRTCanvasToSurf(int slot);

	void testSaveTexUsingFrameBuffer();

	//used in copy paste
	void rtcopy(SDL_Renderer * renderer,SDL_Texture * tgt,SDL_Texture * src,Uint16 xoff, Uint16 yoff,float xScale,float yScale, SDL_Rect * optionalClip){
			Uint8 ret=SDL_SetRenderTarget( renderer, tgt );
			SDL_SetTextureAlphaMod(src,255);
			
		   SDL_Rect destRect = 
		   {xoff, yoff,
		   CVSWDTH,CVSHGTH
		   };
			//quick idiot proof
			if(optionalClip!=NULL){
						 destRect.w=  optionalClip->w;
		   destRect.h=optionalClip->h;

				if(xScale>0)destRect.w=destRect.w*xScale;
				if(yScale>0)destRect.h=destRect.h*yScale;
		   
			}

		   SDL_RenderCopy(renderer, 
		   src, 
		   // NULL, 
		   optionalClip,
		   &destRect);	
		   SDL_RenderPresent(renderer);
	}
	

	void testClearRT(SDL_Renderer * renderer,SDL_Texture * tgt){
			Uint8 ret=SDL_SetRenderTarget( renderer, tgt );
			SDL_SetRenderDrawColor(renderer,
			
			// 0X00,0X00,0X00,
			CL_R,CL_G,CL_B,
			0X00);
			SDL_RenderClear(renderer);

		   SDL_RenderPresent(renderer);
	}

	void clearRenderTargetWithSquareEraser(SDL_Texture * tgt);
	
	void blittexoncleanrt(SDL_Renderer * renderer,SDL_Texture * tgt,SDL_Texture * src){



			Uint8 ret=SDL_SetRenderTarget( renderer, tgt );
			

			
		   SDL_Rect destRect = 
		   {0, 0,
		   CVSWDTH,CVSHGTH};
		   SDL_RenderCopy(renderer, src, NULL, &destRect);	
		   SDL_RenderPresent(renderer);
	}
	
	
	void paintCanvas(Blit * points,SDL_Renderer * renderer,SDL_Texture * tgt,SDL_Texture * with){

			Uint8 ret=SDL_SetRenderTarget( renderer, tgt );
			//DEBUG
			// LOGD("zzn painting set render targ :%d \n",ret);
			int i;
			for(i=0;i<MAX_BLITS;i++){
				if(points[i].xbl==-1 && points[i].ybl==-1){
					break;
				}else{
					//TODO bufferize dest rect ? ( perf )
				   SDL_Rect destRect = 
				   {
				   //HACK 151222 correction to center pain
				   points[i].xbl - brushScale/2,
				   points[i].ybl- brushScale/2,
				   // 2*brushRadius,
				   // 2*brushRadius
					//WIP
				   brushScale,
				   brushScale
				   }; //TODO needs to be computed from radius
				   SDL_RenderCopy(renderer, with, NULL, &destRect);
				}
			}
	}

	
	SDL_Texture * toPaintTo=NULL;
	//interpolating events at this stage
	void paintHandlingUI(int prevxc,int prevyc,int xc, int yc,SDL_Renderer * renderer){
	
		// if(BEHIND){
			toPaintTo=pane;
		// }else{
	
		 // toPaintTo=current;
		// }
		// else behind
	
		//TODO interpolate events if applicable, and do all the blits in one render target change below
		calculateTraj(interpolated,prevxc,prevyc,xc,yc);						
		
								paintCanvas
								(interpolated,renderer,
								toPaintTo,
								activeBrush
								);
	}



	
	void loadsurftostreamingtex(
						SDL_Surface * src,
						SDL_Texture * tgt,
						bool takeSrcAlpha,
						Uint8 alpha
		){ //take src alpha added for round eraser clean up ( we fill with alpha 0 sometimes)
			
		LOGD("zzn src surf depth: %d \n",src->format->BitsPerPixel);
		Uint8 srfBpp=src->format->BitsPerPixel;
			
			
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
		
		LOGD("zzn src tex depth :%d\n",bpp);
		LOGD("zzn tgttex r %08X g %08X  b %08X  \n",r,g,b);
		//even though it seems rgba,
		//testing below shows that it is a b g r
		
		SDL_LockTexture( tgt, NULL, &mPixels, &mPitch );
		//blit like a mad man
		printf("prev pitch %d\n",mPitch);
		Uint32 size = CVSHGTH *CVSWDTH;
		Uint32 i;
		
		Uint8 just_tranp=
		// 32
		// 64
		alpha
		// 255
		;
		
		//TODO add multiplicator on load to get both 32 and 24 ( factor 4 or 3 )
		
		Uint8 srfGap=0;
		if(srfBpp==32){
			srfGap=4;
		}else if(srfBpp==24){
			srfGap=3;
		}else if(srfBpp==8){
			LOGD("compatibility 8bpp load");
			srfGap=1;
		}else{
			LOGD("zzn probably will crash");
		}

		if(srfGap==4 && takeSrcAlpha){
			LOGD("bitdepth ok we take src alpha");
		}
		
		Uint8 surf_r,surf_g,surf_b,onion_a;
		// size * 4 Uint8 slots
		for(i=0;i<size;i++){
		
		//as seen in test surf access, order is bgra for bmp32,
		//whatever the masks say
		if(srfGap==3 || srfGap==4){
		surf_b=((Uint8 *)src->pixels)[srfGap*i];
		surf_g=((Uint8 *)src->pixels)[srfGap*i+1];
		surf_r=((Uint8 *)src->pixels)[srfGap*i+2];
		}else if(srfGap==1){
			//8bit bmp
			SDL_PixelFormat * fmt;
			SDL_Color *color;
			Uint8 index;
			fmt=src->format;
			SDL_LockSurface(src);
			//index= surface->pixels[]
			//WIP
		}
		
		//we dont need a

		// if(surf_b==CL_B && surf_g==CL_G && surf_r==CL_R){
		if(surf_b==clearB && surf_g==clearG && surf_r==clearR){
			onion_a=0;
			//this is a workaround so that blending of the brush is correct
			// surf_b=25;
			// surf_g=255;
			// surf_r=255;
		}else{
			onion_a=just_tranp;		
		}

		//TODO differentiate function for 24bpp and 32bpp
		//if surf 32 we can copy alpha
		if(srfGap==4 && takeSrcAlpha){
			onion_a = ((Uint8 *)src->pixels)[srfGap*i+3];
			
		}

		// for some reason locked pixels is abgr
		
		//a ( TODO should be 0 if all other is 0 )
		((Uint8 *)mPixels)[4*i]= 
		onion_a;
		//b
		((Uint8 *)mPixels)[4*i+1]=
		surf_b;
		//g
		((Uint8 *)mPixels)[4*i+2]=
		surf_g;
		//r in locked tex 
		((Uint8 *)mPixels)[4*i+3]=
		surf_r;
		}
		SDL_UnlockTexture( tgt );	
		
	}
	
	

	
	//WORKAROUND render target doesn't seem to work to read pixels ( on dx at least ),
	//clearing and rendering on frame buffer, then saving
	//BUG: on android gles, doesn't work
	void texToBufferSurfUsingFB(
		SDL_Texture * tex
	){
	
	LOGD("tex to buffer surf using fb /n");
	Uint32 bench = SDL_GetTicks();
	
		SDL_SetRenderTarget(renderer,NULL);
		SDL_SetRenderDrawColor(renderer,
		// CL_R,CL_G,CL_B,
		clearR,clearG,clearB,
		0XFF);
		SDL_RenderClear(renderer);
			
		   SDL_Rect dispRect = 
			{0,0,
			CVSWDTH,CVSHGTH};
			//we fiddle with it when scrolling
//			project[slot].tx
			SDL_SetTextureAlphaMod(
			tex
			,255);
//		project[slot].tx
		SDL_RenderCopy(renderer,
		tex
		, NULL, &dispRect);
		SDL_RenderPresent(renderer);
		
		
		
		int pwidth=CVSWDTH;
		int pheight=CVSHGTH; 
		
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
		//guess is read PIX ABGR , because we read with byte and endianess
		//TODO we do not know , as copying other than blue doesn't work,
		//TODO do color brush and small unit test
		
		//TODO put pixels in the right place in surf
		//WIP brute force try
		//from load test surf is BGRA
		for(j=0;j<pheight;j++){
			// // LOGD("zzn");
			for(i=0;i<pwidth;i++){
				//b in surf				
				((Uint8 *)bufferSurf->pixels)[ 4*(pwidth*j+i)]=
				((Uint8 *)readpixels)[4*(pwidth*j+i)
				 +1
				];
				// g in surf
				((Uint8 *)bufferSurf->pixels)[ 4*(pwidth*j+i)+1]=
				 ((Uint8 *)readpixels)[4*(pwidth*j+i)+2];

				//r in surf
				 ((Uint8 *)bufferSurf->pixels)[ 4*(pwidth*j+i)+2]=
				 ((Uint8 *)readpixels)[4*(pwidth*j+i)+3];
				//a in surf
				//we only translate alpha to transp on gpu side otherwise too hard to debug graphically
				 ((Uint8 *)bufferSurf->pixels)[ 4*(pwidth*j+i)+3]=255;
				
			}
		}
		free(readpixels);
		bench=SDL_GetTicks()-bench;
		LOGD("zzn copy from fb to surf ms %d \n",bench);

		

		
	}
	
	
	//TODO refac to take tex ref
	//proto
	void texToBufferSurfUsingRT(
		SDL_Texture * tex
	);

	void copyTextureToBufferSurf(SDL_Texture * tex){
			#ifndef __ANDROID_API__
			texToBufferSurfUsingFB(
			tex
			);
			#endif
			
			#ifdef __ANDROID_API__
			texToBufferSurfUsingRT(
			tex
			);
			#endif
	
	}

	
	//ahem plat independant entrypoing
	void copyTexToBufferSurf(int slot){
		copyTextureToBufferSurf(project[slot].tx);
	}

	
	
	//somehow on direct3d pb detected on copy tex to buff
	void saveSlotToBufferSurf(int slot){
		
			SDL_SetRenderTarget(renderer,NULL);
			SDL_SetRenderDrawColor(renderer,0XFF,0X00,0X00,0XFF);
			SDL_RenderClear(renderer);
			SDL_SetTextureAlphaMod(project[slot].tx,255);
			SDL_RenderCopy(renderer, project[slot].tx, NULL, &cvsDispRect);
			
			
			SDL_RenderPresent(renderer);
	

			copyTexToBufferSurf( slot);
		
	}
	
	
	void saveSlotToFile(int slot,char * file){
	
			saveSlotToBufferSurf(slot);
			
			//previous operation only copies to buffersurf "singleton"
			LOGD("zzn read pix done from gpu, attempting save \n");
			SDL_SaveBMP(
				bufferSurf
				,file);

			
	}
	
	
	
	
	void texToBufferSurfUsingRT(
		SDL_Texture * tex
//		int slot
	){
		//set render target DOESN'T WORK in this context on dx 
		//read pixels grabs from fb instead, but gles seems to work
		
		Uint32 bench = SDL_GetTicks();

		
//		project[slot].tx
		Uint8 ret=SDL_SetRenderTarget(renderer,
		tex
		);
		LOGD("zzn readpix set render targ (0 is normal ) :%d \n",ret);
		
		
		Uint32 pwidth=CVSWDTH;
		Uint32 pheight=CVSHGTH; 

		SDL_Rect pick={
		0,
		// XORIG, //render target is set to cvs, BUG SEE ABOVE 
		//but if we don't use the offset copy is offset ( makes no sense )
		0,
		pwidth,pheight
		};


		LOGD("zzn thomas bef malloc");

		//core dump if no prealloc 
		void * readpixels= malloc (4*CVSWDTH*CVSHGTH);


		LOGD("zzn malloc done, about to read rendered pixels \n");
		// #ifdef __ANDROID_API__
		// LOGD("zzn SPECIAL READ PIXELS ");
		// glReadPixels(0, 0,CVSWDTH,CVSHGTH,
						   // GL_RGBA, GL_UNSIGNED_BYTE, readpixels);
		// #else
        SDL_RenderReadPixels(renderer, &pick, SDL_PIXELFORMAT_RGBA8888, 
		readpixels,
		pwidth
		*4 //length of line in octets
		);
		// #endif
		
		
		Uint32 i;
		Uint32 j;
		
		
		//readpixels > 0 is A
		LOGD("zzn render read pixels done \n" );
		
		//TODO put pixels in the right place in surf
		//WIP brute force try
		//from load test surf is BGRA
		for(j=0;j<pheight;j++){
			// // LOGD("zzn");
			for(i=0;i<pwidth;i++){
				//WIP still having no fricking idea of the pixel format 
				//without testing
				//surf is 
				
				//HACK ANDRO 5 on note 3 neo, LT pixels saved as black, trying to differentiate
				//them through alpha
				bool colorkey=false;
				if(((Uint8 *)readpixels)[4*(pwidth*j+i)]==0){
					//this is a light table transparent pixel
					colorkey=true;
				}
			
				if(colorkey==false){
				//b in surf
					((Uint8 *)bufferSurf->pixels)[ 4*(pwidth*j+i)]=
					((Uint8 *)readpixels)[4*(pwidth*j+i)
					 +1
					];
					// 255; // debug to identify blue // indeed blue in surf
					
					
					//g in surf
					// ((Uint8*)loadedsurfs[
					// slot
					// ]
					((Uint8 *)bufferSurf->pixels)[ 4*(pwidth*j+i)+1]=
					((Uint8 *)readpixels)[4*(pwidth*j+i)+2];
					// 255; // debug to identify green // indeed green in surf

					//r in surf
					// ((Uint8*)loadedsurfs[
					// slot
					// ]
					((Uint8 *)bufferSurf->pixels)[ 4*(pwidth*j+i)+2]=
					((Uint8 *)readpixels)[4*(pwidth*j+i)+3];
					// 255; // debug to identify red // indeed red in surf
				}else{
					//andro 5 patch for texture transp pixels
					((Uint8 *)bufferSurf->pixels)[ 4*(pwidth*j+i)]=clearB;
					((Uint8 *)bufferSurf->pixels)[ 4*(pwidth*j+i)+1]=clearG;
					((Uint8 *)bufferSurf->pixels)[ 4*(pwidth*j+i)+2]=clearR;
				
				}
					
				//TL 151101 setting preventively ( was always right value in buffersurf )
				((Uint8 *)bufferSurf->pixels)[ 4*(pwidth*j+i)+3]= 255;
				
				
			}
			// LOGD("\n");
		}
		free(readpixels);

		bench=SDL_GetTicks()-bench;
		LOGD("zzn copy from fb to surf ms %d \n",bench);
	
		
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
		
		if(
		// nb>(DFLT_FRAME_NMBER-1)
			nb>(MAX_FRAME_NMBER-1)
			||project[nb].tx==NULL
		){ 
			LOGD("no fwd possible");
			return;		
		}
		
		// SDL_Surface 
		// loadedsurfs
		SDL_Texture * pot_prev=NULL;
		if(nb-1>=0){
			pot_prev=(project[nb-1].tx);
		}
		// SDL_Surface 
			// loadedsurfs
		SDL_Texture * pot_next=NULL;
		if(nb+1<=MAX_FRAME_NMBER-1){
			pot_next=(project[nb+1].tx);
		}
		
		// changeSlots(
		// pot_prev,
		// loadedsurfs[nb],
		// pot_next
		// );

		previous=pot_prev;
		next=pot_next;
		current=project[nb].tx;
		

//we edit in place in the tex now 
		
		//we blit current to prepare canvas
		// SDL_SetRenderTarget(renderer,cvs);
		// SDL_SetRenderDrawColor(renderer,0X00,0X00,0X00,0X00);
		// SDL_RenderClear(renderer);
	   // SDL_Rect dispRect = 
			// // {0,0,
			// // 1280,720};
			// {0,0,
			// CVSWDTH,CVSHGTH};
		// SDL_RenderCopy(renderer, current, NULL, &dispRect);
		// //for onion skinning
		// SDL_RenderPresent(renderer);

		
		
	}

//TODO 
void toggleEraser(){
	//simple slot change
	if(activeBrush==brush && BEHIND==false){
		    BEHIND=false;
			activeBrush=roundEraser;
	}else if(activeBrush==roundEraser){
		//activeBrush=eraser;
		// activeBrush=brush;
		activeBrush=brush;
		BEHIND=true;
	}else if(BEHIND==true){
		activeBrush=brush;
		BEHIND=false;
	}

}	
	
void appendframe(int pos);	
void init_play();
	
	void initFlick(bool left);
	
	
	//should be in .h really
	void settings();
	
	
	
	void	removeAllClearColorAlphaInBufferSurf(){
		int i,j;
		//CVSWDTH,CVSHGTH
		for(j=0;j<CVSHGTH;j++){
			for(i=0;i<CVSWDTH;i++){
				
				if(
				((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)]==clearB
				&&
				((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+1]==clearG
				&&
				((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+2]==clearR
				&&
				((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+3]!=0
				){
					//clear color found and alpha not 0
					((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+3]=0;
					
				}
			}
		}
	}

	//work around to clear transparency after use of clear color round eraser full alpha
	void clearCurrentOfClearColorFullAlphaPixels(){
		
		//let s try to reset buffer surf (from one call to the next there seems to be a 'memory')
		int i,j;
		//CVSWDTH,CVSHGTH
		for(j=0;j<CVSHGTH;j++){
			for(i=0;i<CVSWDTH;i++){				
					//clear color found and alpha not 0
					((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+0]=0;
					((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+1]=0;
					((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+2]=0;
					((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+3]=255;
			}
		}
		
		
		//for some reason on direct 3D, on second call copy tex only gives non white areas from penultimate frame,
		// we hijack save slot as it works fine (BROWN TAPE FIX)
		copyTexToBufferSurf(nb_edit_slot);
		//saveSlotToBufferSurf(nb_edit_slot);
		
		
		//WINDOWS DEBUG
		LOGD("ctex debug.bmp SAVE");
		SDL_SaveBMP(
				bufferSurf
				,"debug.bmp");
		
		//at this point all white is 255 on windows (patch to copytex buffer surf, and debug save is ok)
		
		removeAllClearColorAlphaInBufferSurf();
		
		
		loadsurftostreamingtex(
							bufferSurf,
							tmp,
							true,
							255
			);
			
		clearRenderTargetWithSquareEraser(project[nb_edit_slot].tx);			
		blittexoncleanrt(renderer,project[nb_edit_slot].tx,tmp);		
		project[nb_edit_slot].dirty=true;
	}
	
	
	//needs renderer to be init
	void composeEraser(){
			//square eraser, bg 0 alpha
		
			eraser=SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
											64,64);
			SDL_SetTextureBlendMode(eraser,SDL_BLENDMODE_NONE);
			SDL_SetRenderTarget(renderer,eraser);
			//this is a try, I blit without blend mode hoping to erase
			SDL_SetRenderDrawColor(renderer,
			// CL_R,CL_G,CL_B
			clearR,clearG,clearB
			,0X00);
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
	
			//round eraser, pastes clear color with alpha 255,
			//needs work around to fill clear color with alpha 0 afterwards
			myRgb eraserCol;
			// eraserCol.r=CL_R;
			// eraserCol.g=CL_G;
			// eraserCol.b=CL_B;
			eraserCol.r=clearR;
			eraserCol.g=clearG;
			eraserCol.b=clearB;
			
			SDL_Surface * brushSurf = 
			composeBrushWithAlpha(brushRadius,ALPHA_BORDER, eraserCol, GLOBAL_ALPHA);
			roundEraser  = SDL_CreateTextureFromSurface(renderer, brushSurf);
			SDL_FreeSurface( brushSurf);

	
	}
	
	// it was written just to add at the end
	//TODO the surf part will disappear on refactor
	void fillslotfromtemplate(int nb){
		LOGD(" fill slot from template %d \n",nb);
	
		SDL_Surface * tmpsurf=NULL;
	
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
		strcat(file,
		"template.bmp"
		);
		LOGD("zzn %s\n",file);
		// loadedsurfs[nb] 
		tmpsurf= SDL_LoadBMP(
					file
		);
		LOGD("loaded template : %d \n",
		// loadedsurfs[nb]
		tmpsurf		);
	
	
		//allocate streaming tex
		LOGD("zzn creating tex at offset nb %d \n",nb);
		project[nb].tx=SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
										CVSWDTH,CVSHGTH);
		project[nb].dirty=true; //created from template so fully new								
		project[nb].timecode=1;
		LOGD(" slot %d dirty from creation \n");
		SDL_SetTextureBlendMode(project[nb].tx,SDL_BLENDMODE_BLEND);

		LOGD("zzn load surf to streaming tex \n");
		loadsurftostreamingtex(
		// loadedsurfs[nb]
		tmpsurf,tmp,false,255);		
		
		LOGD("zzn about to blit tex on new project frame \n");
		
					Uint8 ret=SDL_SetRenderTarget( renderer, project[nb].tx );
			
			//tentatively commented as doesn't work on android gles2
			//reactivated to remove garbled graphics on note8 andro 4
			//spaghetti : was not working to paste content on target after white clean up ( on note 3 neo andro 5)
			//( round brush ), but necessary when loading one note 8 andro 4 ( clear render target with square not working there ? )
			//TODO externalise both functions
			
			//this block doesn't work on note 3 and is necessary on note 8!!!!
			
			SDL_SetRenderDrawColor(renderer,
			
			// CL_R,CL_G,CL_B,
			clearR,clearG,clearB,
			0X00);
			SDL_RenderClear(renderer);

		
		
		blittexoncleanrt(renderer,project[nb].tx,tmp);		
		LOGD("zzn slot %d filled \n",nb);
		SDL_FreeSurface(tmpsurf);
	}

	// //seems to have pb on android 5 note 3 neo ( garbled pixels )
	// void clearstreamingtex(SDL_Texture * streaming){
			// void* mPixels;
		// int mPitch;
		
		// //let's check tex pixel format
		// Uint32 t_fmt=0;
		// SDL_QueryTexture(streaming,&t_fmt,NULL,NULL,NULL);
		// printf("tgt t_fmt%d \n",t_fmt);
		// Uint32 r,g,b,a;
		// int bpp;
		// r=0;g=0;b=0;a=0;bpp=0;
		// SDL_PixelFormatEnumToMasks( 
			// t_fmt,
			// &bpp,
			// &r,
			// &g,
			// &b,
			// &a
			// );
		
		// LOGD("zzn tgttex r %08X g %08X  b %08X  \n",r,g,b);
		// //even though it seems rgba,
		// //testing below shows that it is a b g r
		
		// SDL_LockTexture( streaming, NULL, &mPixels, &mPitch );
		// //blit like a mad man
		// printf("prev pitch %d\n",mPitch);
		// Uint32 size = CVSHGTH *CVSWDTH;
		// int i;
		
		
		// for(i=0;i<size;i++){

			// //TODO quick hack,
			// //should be put in line with define
		
		// ((Uint8 *)mPixels)[4*i]= 0;
		// ((Uint8 *)mPixels)[4*i+1]=0;
		// ((Uint8 *)mPixels)[4*i+2]=0;
		// ((Uint8 *)mPixels)[4*i+3]=0;
		// }
		// SDL_UnlockTexture( streaming );	

	// }

	//fill slot android 5 ( corruption on previous method )
	void initslot(int nb){
		LOGD(" init tx slot %d \n",nb);
		LOGD("zzn creating tex at offset nb %d \n",nb);
		project[nb].tx=SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
										CVSWDTH,CVSHGTH);
		project[nb].dirty=true; //created from template so fully new								
		project[nb].snd=NULL;
		project[nb].wavFileNumberOnDisk=0;
		project[nb].timecode=1;
		LOGD(" slot %d dirty from creation \n");

		// LOGD("clear streaming tex \n");
		// clearstreamingtex(tmp);
		
		// LOGD("zzn about to blit tex on new project frame \n");
		// blittexoncleanrt(renderer,project[nb].tx,tmp);		

		SDL_SetTextureBlendMode(project[nb].tx,SDL_BLENDMODE_BLEND);

		
		//trying alternative to init slot without garbledpix
			// SDL_SetRenderTarget(renderer,project[nb].tx);
			// //this is a try, I blit without blend mode hoping to erase
			// SDL_SetRenderDrawColor(renderer,
			// // 0X00,0X00,0X00
			// CL_R,CL_G,CL_B
			// ,0X00);
			// SDL_RenderClear(renderer);
			// SDL_RenderPresent(renderer);
		
		//WIP trying without init at all
		
		//apparently initing right now doesn't work,
		//but eraser will work later
		
		LOGD("zzn slot %d filled \n",nb);
	}

	
	
	// needs to work with array of Tex to keep dirty flag
	//create a null slot at index and shifts what is >=
	
	//TODO update timecodes
	void createNullSlot(int existing){
			Tex buf[MAX_FRAME_NMBER];
			int i;
			for( i=0;i<MAX_FRAME_NMBER;i++){
				buf[i].tx=NULL;
				buf[i].dirty=false;
				buf[i].shifted=false;
				buf[i].timecode=1;
				strcpy(buf[i].loadedfrom,"\0");
				buf[i].snd=NULL;
				buf[i].wavFileNumberOnDisk=0;
			}
			//buf ready to use
	
			int init_nb=frameNumber();
			
			for( i=0; i< init_nb;i++){
				if(i<existing){
					//TODO just copy
					buf[i].tx=project[i].tx;
					buf[i].dirty=project[i].dirty;
					buf[i].shifted=project[i].shifted;
					buf[i].timecode=project[i].timecode;
					strcpy(buf[i].loadedfrom,project[i].loadedfrom);
					buf[i].snd=project[i].snd;
					buf[i].wavFileNumberOnDisk=project[i].wavFileNumberOnDisk;

					LOGD("copying %d project to buf \n",i);
				}else{
					//TODO copy at i+1 to keep 'existing' slot at NULL
					buf[i+1]=project[i];
					buf[i+1].dirty=project[i].dirty;
					buf[i+1].shifted=true;
					buf[i+1].timecode=project[i].timecode;
					strcpy(buf[i+1].loadedfrom,project[i].loadedfrom);
					buf[i+1].snd=project[i].snd;
					buf[i+1].wavFileNumberOnDisk=project[i].wavFileNumberOnDisk;
					
					LOGD("copying %d project to buf %d \n",i,(i+1));
				}
			}
			
			//now we need to copy back on to project[]
			for(i=0 ; i< (init_nb+1);i++){ //we copy the added slot
				project[i].tx=buf[i].tx;
				project[i].dirty=buf[i].dirty;
				project[i].shifted=buf[i].shifted;
				project[i].timecode=buf[i].timecode;
				strcpy(project[i].loadedfrom,buf[i].loadedfrom);
				project[i].snd=buf[i].snd;
				project[i].wavFileNumberOnDisk=buf[i].wavFileNumberOnDisk;
			}
			//project should be with a null slot at existing now
	}

	//WIP not tested
	void contract(int pos){
		LOGD("about to contract pos %d \n",pos);
		Uint16 nbFramesBefore = frameNumber();
	
	LOGD("dealloc frame %d \n",pos);
		SDL_DestroyTexture(project[pos].tx);
		project[pos].tx=NULL;

	//is easier than add , we might just be able to copy in the same list
		// for(
		Uint16 i;
		for( i=(pos+1);i<nbFramesBefore;i++){
			LOGD("copying frame %d to %d \n",i, (i-1));
			//copy i to i-1, alter shift status
				project[i-1].tx=project[i].tx;
				project[i-1].dirty=project[i].dirty;
				project[i-1].shifted=true;
				strcpy(project[i-1].loadedfrom,project[i].loadedfrom);
		}
		//nullify the last slot as we reduced by one 
		Uint16 lastBefore=nbFramesBefore-1;
		project[lastBefore].tx=NULL;
		LOGD("slot %d nullified \n",lastBefore);
	}
	
	//WIP
	//we deallocate the tex at given slot and metadata 
	// void deallocframe(int pos){
		// }
	
	//in test
	void deleteOneFrame(int pos){
		// deallocframe(pos);
		contract(pos);
	}
	
	//as render clear doesn't work on android 5 gles
	void clearRenderTargetWithSquareEraser(SDL_Texture * tgt){
		
				Uint8 ret=SDL_SetRenderTarget( renderer, tgt );
				   SDL_Rect destRect = 
				   {
				   // x, y,
					0,0,
				   // 2*brushRadius,
				   // 2*brushRadius
					//WIP
				   640,
				   480
				   }; 
				   SDL_RenderCopy(renderer, eraser, NULL, &destRect);

	}
	
	//allocate and adds frame 
	void appendframe(int pos)
	{
	
			// get nb frames
			int frm_nb= frameNumber();

			//we need to check we do not append after MAX_FRAME
			if(frm_nb>=MAX_FRAME_NMBER){
				LOGD("we can't append, max frame number reached \n");
				return;
			}
			
			//TODO check i is frames+1 max
			//frm_nb still ok because appending supported
			if(pos > frm_nb ){
				LOGD("zzn append not possible here");
				return;
			}
			
			// if below frames + 1,
			// shift all frames in array to create a NULL slot
			if( pos < (frm_nb+1) ){
				LOGD(" shifting to create null slot\n");
				createNullSlot(pos);
			}else{
				LOGD("append at end of anim\n");
			}
	
			// fill NULL SLOT
			//TODO surf updated not consistently
			// fillslotfromtemplate(pos);
			initslot(pos);
			//dirty hack : if pixel corruption persists ,
			//erasing with tool is ok, simulate that on whole new tex 
			//( brrrrrrrrrrrrrrrrrr.... )


	 clearRenderTargetWithSquareEraser(project[pos].tx)			;
				// Uint8 ret=SDL_SetRenderTarget( renderer, project[pos].tx );
				   // SDL_Rect destRect = 
				   // {
				   // // x, y,
					// 0,0,
				   // // 2*brushRadius,
				   // // 2*brushRadius
					// //WIP
				   // 640,
				   // 480
				   // }; 
				   // SDL_RenderCopy(renderer, eraser, NULL, &destRect);

			#ifdef DIRTYNOTEHACK
			
			#endif
	}
	
	

		// typedef void (*statefunc)() ;
	
	// //current state func
	// statefunc mode=0;

	
	//************ PLAY STATE VARIABLES
	
	// Uint32 plyTimer=0;
	//DEFAULT shooting for 5 fps
	Uint32 frameTime=0;
	//index of currently displayed frame
	Uint32 disp_nb=0;
	//state transition from edit to play mode
	//state transition play end to edit mode
	
	void edit();
	
	void play_to_edit(){
		setEditSlot(disp_nb);
		nb_edit_slot=disp_nb;

	
		initedit();
	}



	//*******************************
	
	
	//proto
	void render_playback(int nb);



	/******** FLICK MODE *******************/
	Uint32 flick_nb=0;
	Uint32 lfn;
	
	bool leftMode;
	//TODO test input on press, end of press
	void flickMode(){
		//we get out of flick mode when press is released
	
	
		
		//we adapt nb edit mode relative to where the flick touch is
		//the screen with is NB_FLICK frames
		
		// //WIP we determine offset from the right 
		int offset;
		int flx=polled.x;
		
		if(leftMode ){
			offset=flx;
		}else{
			offset = SCRWDTH-flx;
		}
		int slotwidth= SCRWDTH/NB_FLICK ;
		//screen represents NB_FLICK slots ( last to the right is current )
		int nbslot= offset/slotwidth;
	
		int tgt;
		
		if(leftMode){
			tgt= flick_nb+nbslot;
		}else{
			tgt= flick_nb-nbslot;
		}
		
		if( tgt<0){tgt=0;}
		if(tgt>(lfn-1)){tgt=lfn-1;}
		
		LOGD("flx %d offset %d nb slot %d  computed tgt %d\n",flx,offset,nbslot,tgt);
		// LOGD("computed tgt %d\n",tgt);

		//is it too slow to do it all the time ?
		setEditSlot(tgt);
		nb_edit_slot=tgt;
		
		//TODO adapt flick_nb
		render_playback(
			nb_edit_slot
		// flick_nb
		);
	
		//TODO click drag detect
		handleinput(&polled,
		// true //has been blocking for most of the dev
		false //for some reason on android, we don't get pen up event, so trying busy wait
		);

		//only test release at the mo
		if(polled.pressed==false){
			//we render gpu poc one time with buttons cause edit mode input blocking
			rendergpupoc(renderer,
			true,false);
			initedit();
			return;
		}

	
	
	}


	//TODO we only do flick from right at the mo
	void initFlick(bool left){
		leftMode=left;
		//flick nb is the reference from which we flick
		flick_nb=nb_edit_slot;
		mode = flickMode;
		lfn=frameNumber();

	}

	
		//to be mutualized with color change
	//works with global
	void composeBrushInVideoMemory(){
		if(brush!=0){
			LOGD("cleaning brush tex\n");
			SDL_DestroyTexture(brush);
			LOGD("cleaning brush success\n");
		}
		
		SDL_Surface * brushSurf = 
			composeBrushWithAlpha(brushRadius,ALPHA_BORDER, col, GLOBAL_ALPHA);
		brush  = SDL_CreateTextureFromSurface(renderer, brushSurf);
		SDL_FreeSurface( brushSurf);
	}

	
	/** color pick state 
	just waiting for a click and exiting reallocating brush **/

  bool fillmode;
	myRgb picked;
	
	//TODO replacement android version modeled on save
	void pickInRTAndro(Uint16 x, Uint16 y){
	
	}
	
	//TODO works with offset on android ?
	//TODO this might work differently on android and win/d3d ( see save define )
	//same mechanism as on save, but this save doesn't work for andro
	void pickInCanvasD3D(Uint16 x, Uint16 y){
	//old school
			SDL_SetRenderTarget(renderer,NULL);
//on android the bg is not cleared on target change
		SDL_SetRenderDrawColor(renderer,
		// CL_R,CL_G,CL_B,
		clearR,clearG,clearB,
		0X00);
		SDL_RenderClear(renderer);
			
		   SDL_Rect dispRect = 
			{0,0,
			CVSWDTH,CVSHGTH};
			//we fiddle with it when scrolling
			SDL_SetTextureAlphaMod(project[nb_edit_slot].tx,255);
		SDL_RenderCopy(renderer, 
		project[nb_edit_slot].tx
		, NULL, &dispRect);
		SDL_RenderPresent(renderer);
		int pwidth=1;
		int pheight=1; 
		
		SDL_Rect pick={
		x,
		y,
		pwidth,pheight
		};
		
		//core dump if no prealloc 
		void * readpixels= malloc (4);
		
        SDL_RenderReadPixels(renderer, &pick, SDL_PIXELFORMAT_RGBA8888, 
		readpixels,
		SCRWDTH
		// CVSWDTH
		*4 //length of line in octets WRONG wz read fb which is wider
		);		
		
		
				picked.b=
				((Uint8 *)readpixels)[1];
	
				picked.g=
				 ((Uint8 *)readpixels)[2];
				 picked.r=
				 ((Uint8 *)readpixels)[3];
			
		free(readpixels);
		LOGD("zzn color pick from fb  %d %d %d \n",picked.r,picked.g,picked.b);
	}
	
	//TODO doesn't work ( random location ) workaround elsewhere
	void pickInCanvasAndro(Uint16 x, Uint16 y){
		Uint8 ret=SDL_SetRenderTarget(renderer,
		project[nb_edit_slot].tx
		);
		LOGD("zzn pick color in rt canvas set render targ (0 is normal ) :%d \n",ret);
		
		
		Uint32 pwidth=
		1;
		// CVSWDTH;
		Uint32 pheight=
		1;
		// CVSHGTH; 

		SDL_Rect pick={
		0,
		// XORIG, //render target is set to cvs, BUG SEE ABOVE 
		//but if we don't use the offset copy is offset ( makes no sense )
		0,
		pwidth,pheight
		};


		LOGD("zzn thomas bef malloc");

		//core dump if no prealloc 
		void * readpixels= malloc (4*pwidth*pheight
		// CVSWDTH*CVSHGTH
		);


		LOGD("zzn malloc done, about to read rendered pixels \n");
		// #ifdef __ANDROID_API__
		// LOGD("zzn SPECIAL READ PIXELS ");
		// glReadPixels(0, 0,CVSWDTH,CVSHGTH,
						   // GL_RGBA, GL_UNSIGNED_BYTE, readpixels);
		// #else
        SDL_RenderReadPixels(renderer, &pick, SDL_PIXELFORMAT_RGBA8888, 
		readpixels,
		// pwidth
		CVSWDTH
		*4 //length of line in octets
		);
		// #endif
		picked.b=
		((Uint8 *)readpixels)[1];

		picked.g=
		 ((Uint8 *)readpixels)[2];
		 picked.r=
		 ((Uint8 *)readpixels)[3];
			
		free(readpixels);
		LOGD("zzn color pick from fb  %d %d %d \n",picked.r,picked.g,picked.b);
	
	}

//unclettering event loop
  void executeFill(Uint16 x, Uint16 y){
			    //call flood fill
			    LOGD("flood fill " );
			copyTexToBufferSurf(nb_edit_slot);
				
				
			    myRgba replacecol;
				if(activeBrush==roundEraser){
					LOGD("round eraser selected,we fill with clear color \n");
					replacecol.b=clearB;
					replacecol.g=clearG;
					replacecol.r=clearR;
				//if we need to substract, we need to blit with 0 alpha some sections, so on a tex with alpha 0 everywhere
					//dunno how to do that on non streaming so for this special case reallocate ?
					// SDL_DestroyTexture(rdr,project[nb_edit_slot].tx);
					// SDL_CreateTexture
				Uint8 ret=SDL_SetRenderTarget( renderer, project[nb_edit_slot].tx );
				SDL_SetRenderDrawColor(renderer,
			
			// CL_R,CL_G,CL_B,
			clearR,clearG,clearB,
			0X00);
			SDL_RenderClear(renderer);



				}else{
					replacecol.b=col.b;
					replacecol.g=col.g;
					replacecol.r=col.r;
				}
				
					replacecol.a=255; //todo might change if we can flood lt color
				
			    //DEBUG TEST
			    Uint8 * pix =(Uint8 *) bufferSurf->pixels;
			    noRecFloodFill(  pix,  x,  y,  replacecol );
			    //SDL_SaveBMP(bufferSurf,"dbgfill.bmp");

				//TODO if round eraser hack we should be able to upload different alpha
				loadsurftostreamingtex(
									bufferSurf,
									tmp,
									// ROUNDERASERHACK,
									false,
									255
					);
			
				blittexoncleanrt(renderer,project[nb_edit_slot].tx,tmp);		
				project[nb_edit_slot].dirty=true;

  }



	void saveFramesChangingLightTableColor(myRgb *newLTcol){
		//TODO see list of tasks beginning of file
		
		
	}


  
	//TODO replace this sh#t with enum :p
	//are we picking from palette pick
	bool paletteMode=true;
	bool changeLightTableColor=true;
    bool cleanColor=true;
  
   void cleanPixelsOfBufferSurf(myRgb * picked){
	    int i,j;
		for(j=0;j<CVSHGTH;j++){
			for(i=0;i<CVSWDTH;i++){
				//WIP if statement on pix color

				if(
				 ((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)]==picked->b
				 &&
				 ((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+1]==picked->g
				 &&
				 ((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+2]==picked->r
				 
				){
					//b
					((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)]=clearB;
					// g in surf
					((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+1]=clearG;

					//r in surf
					((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+2]=clearR;
					//A in surf
					((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+3]=0;
				}
			}
		}
	   
   }
  
	void pickMode(){
		
		picked.r=0;
		picked.g=0;
		picked.b=0;
	
		SDL_SetRenderTarget(renderer,NULL);
		//to simplify to begin with, we just display surf
		   SDL_Rect dispRect = 
			{0,0,
			// {xorig,YORIG,
			CVSWDTH*zoom,CVSHGTH*zoom};
			// CVSWDTH,CVSHGTH};
		SDL_SetRenderDrawColor(renderer,
		// CL_R,CL_G,CL_B,
		clearR,clearG,clearB,
		0X00);
		SDL_RenderClear(renderer);
		
		if(paletteMode){
			SDL_RenderCopy(renderer, palette, NULL, &dispRect);			
		}else{
			SDL_SetTextureAlphaMod(project[nb_edit_slot].tx,255);
			SDL_RenderCopy(renderer, project[nb_edit_slot].tx, NULL, &dispRect);
		}

		// we need to display a cancel button to go out
		SDL_Rect clipRect = 
			{0,0,
			0,0};

		   
			
	   clipRect.x = TOFF_CANCEL_X;
	   clipRect.y = TOFF_CANCEL_Y;
	   clipRect.w = 64;
	   clipRect.h = 64;
		dispRect.x=PP_CANCEL_UL_X;
		dispRect.y=PP_CANCEL_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

			SDL_RenderCopy(renderer,
			buttons, 
			&clipRect,
			&dispRect
			);

		
		SDL_RenderPresent(renderer);
	
		handleinput(&polled,
				true // blocking should be ok
			);
		if(polled.newpress){
			LOGD("get pick TODO andro \n");
			if( 
				polled.x < (PP_CANCEL_UL_X+BTN_BASE_W)
				&& polled.x > PP_CANCEL_UL_X
				&&	polled.y < (PP_CANCEL_UL_Y+BTN_BASE_W)
				&& polled.y > PP_CANCEL_UL_Y
				){
				
				// mode=settings;
				initedit();
				return;
			}
			Uint16 xpick = polled.x/zoom;
			Uint16 ypick = polled.y/zoom;
			LOGD("zzn computed pick %d %d \n",xpick, ypick);


  		  if( fillmode){

		    executeFill(xpick,ypick);
			return;
		    //WIP we add an exit button
		    // initedit();
		  }else{


			
			//
			// picked.r=CL_R;
			// picked.g=CL_G;
			// picked.b=CL_B;
			picked.r=clearR;
			picked.g=clearG;
			picked.b=clearB;

			//WIP andro version not working on less than full tex,
			//workaround
			
			//TODO palette treatment
			if(paletteMode){
				// pb on android
				//				copyTextureToBufferSurf(palette);
				//pick color directly in palette
				picked.b=((Uint8 *)paletteSurface->pixels)[ 3*(CVSWDTH*ypick+xpick)];
				// g in surf
				picked.g=((Uint8 *)paletteSurface->pixels)[ 3*(CVSWDTH*ypick+xpick)+1];

				//r in surf
				 picked.r=((Uint8 *)paletteSurface->pixels)[ 3*(CVSWDTH*ypick+xpick)+2];
			
			}else if(cleanColor){
				//pick color in picture
				copyTexToBufferSurf(nb_edit_slot);
				picked.b=((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*ypick+xpick)];
				// g in surf
				picked.g=((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*ypick+xpick)+1];

				//r in surf
				 picked.r=((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*ypick+xpick)+2];

				 
				// char debugsave[512];
				// strcpy(debugsave,projectPath);
				// strcat(debugsave,"beforeclean.bmp");
				// LOGD("%s \n",debugsave);
				
				// SDL_SaveBMP(bufferSurf,debugsave);
				//we need to clean all pixels of this color in buffer surf
				cleanPixelsOfBufferSurf(&picked);

				// strcpy(debugsave,projectPath);
				// strcat(debugsave,"afterclean.bmp");
				// LOGD("%s \n",debugsave);
				// SDL_SaveBMP(bufferSurf,debugsave);
				// // SDL_SaveBMP(bufferSurf,"afterclean.bmp");
				
				clearRenderTargetWithSquareEraser(project[nb_edit_slot].tx);
				loadsurftostreamingtex(bufferSurf,tmp,true,255);
				blittexoncleanrt(renderer,project[nb_edit_slot].tx,tmp);		
				project[nb_edit_slot].dirty=true;
				
				//WORKAROUND it seems there are clear color pixels with full alpha
				//we run it as a workaround
				clearCurrentOfClearColorFullAlphaPixels();
				 

			}else{
				//pick color in picture
				copyTexToBufferSurf(nb_edit_slot);
				picked.b=((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*ypick+xpick)];
				// g in surf
				picked.g=((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*ypick+xpick)+1];

				//r in surf
				 picked.r=((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*ypick+xpick)+2];
			}
			

			
			LOGD("zzn result of pick %d %d %d \n",picked.r,picked.g,picked.b);
			
			
			//result is in global
			//rule : we dunno select light table color
			// if( picked.r==CL_R
			// && picked.g==CL_G
			// && picked.b==CL_B
			if( picked.r==clearR
			&& picked.g==clearG
			&& picked.b==clearB
			){
				LOGD("light table color picked , skipping \n");
				initedit();
			}else{
			    LOGD("not LT color, we change to it ");

				col.r=picked.r;
				col.g=picked.g;
				col.b=picked.b;
				composeBrushInVideoMemory();
				activeBrush=brush;
				LOGD("after compose brush video memory \n");
				
				//WIP / FROZEN not implemented yet
				if(changeLightTableColor){
					LOGD("change light table color \n");
					saveFramesChangingLightTableColor(&picked);
				}
				
				
				//was painful navigation
				// mode=settings;
				cleaninput(&polled);
				LOGD("brush color changed going to edit \n");
				initedit();
			}
		    }
		}
		
	}

  
  
	//*******************************
	
	//anim play back doesnot onion skin
	void render_playback(int frame){
		SDL_SetRenderTarget(renderer,NULL);
		   SDL_Rect dispRect = 
			{xorig,YORIG,
			CVSWDTH*zoom,CVSHGTH*zoom};
		SDL_SetRenderDrawColor(renderer,
		// CL_R,CL_G,CL_B,
		clearR,clearG,clearB,
		0X00);
		SDL_RenderClear(renderer);
		
		
		SDL_SetTextureAlphaMod(project[frame].tx,255);
		SDL_RenderCopy(renderer, project[frame].tx, NULL, &dispRect);
		
		
		SDL_RenderPresent(renderer);
	}
	
	//statefunc for anim play back > stops play back on newpress
	//TODO maybe optim for battery
	//TODO play timing is off because of no vsync probably
	Uint32 last=0;
	Uint32 now=0;
	Uint32 elapsed=0;
	// Uint16 stopinhib=0;

	
	void play_anm(){
		LOGD("play loop\n");
		last=now;
		now=SDL_GetTicks();
	
	
		handleinput(&polled,
				//true //has been blocking for most of the dev
				false
			);

		// LOGD("play anm\n");
		render_playback(disp_nb);

		
		
		if(last!=0){
			//means we are past first time
			elapsed+=(now-last);
			
			//hackish work around for touchy event
			// if(stopinhib>0){
				// if(elapsed<=stopinhib){
					// stopinhib-=elapsed;
				// }else{
					// stopinhib==0;
				// }
			// }
			
			if( elapsed < project[disp_nb].timecode*frameTime){
				SDL_Delay(frameTime);
			}else{
				//frame time elapsed
				//is this safe :) ?
				
				//TODO if time code different from one, multiple of frame time to be checked
				LOGD("frame %d elapsed \n",disp_nb);
				
				elapsed= elapsed-project[disp_nb].timecode*frameTime;
				disp_nb++;
				LOGD("checking new frame %d sound \n",disp_nb);
				
				if(project[disp_nb].tx==NULL){
					//woops no more frame , flipbook finished
					disp_nb=0;
					play_to_edit();
				}else{
					//we trigger sound if exists
					if(project[disp_nb].snd!=NULL){
						LOGD("triggering sound frame %d \n",disp_nb);
						Mix_PlayChannel( -1, project[disp_nb].snd, 0 );
					}

				}
				
			}
			
		}
		
		// if( plyTimer>frameTime){
			// plyTimer=0;
		// }
		
		//TODO doesn't work on android
		//seems the new press is triggered in a too touchy way
		//TODO add couple ms of inhib in android handle input
		
		//we poll an invisible button at the upper left of display to stop playback
		//( workaround of click "remanence")
		
		 if(
		 polled.newpress==true){
			// LOGD("newpress detected\n");
			// //escaping ( to edit probably )
			// //NOT WORKING we paint anyway
			// cleaninput(&polled);
			if(polled.x<BTN_BASE_W&&polled.y<BTN_BASE_W){
				play_to_edit();
			}
			
		 }
		
	}

	void init_play(){
		LOGD("initplay negating newpress\n");
		polled.newpress=false; // so that not immediately consumed a second time
		last=0;now=0;elapsed=0;
		mode = play_anm;
		frameTime=
		PB_TIME
		;
		// stopinhib=25; // half a sec
		disp_nb=
		// 0;
		nb_edit_slot;
	}

	//*** COPY CLIP SELECTION MODE 
	void pastePosition();
	
	SDL_Rect copy_clip_rect={0,0,0,0};
	
	bool cc_ul=true; //we start by setting upper left clipping point
	
	// we display the copy source and click drag to sel a part of it
	void copy_clip(){
	
		SDL_SetRenderTarget(renderer,NULL);
		SDL_RenderClear(renderer);
	   SDL_Rect dispRect ;
		SDL_Rect clipRect; //for buttons sprite sheet
	   
	   dispRect.x=cvsDispRect.x
	   ;
	   dispRect.y=cvsDispRect.y
	   ;
	   dispRect.w=cvsDispRect.w;
	   dispRect.h=cvsDispRect.h;
		SDL_SetTextureAlphaMod(copy_src,255);

		SDL_RenderCopy(renderer,
		copy_src, 
		NULL,
		&dispRect
		);
			
		// }
	
		//TODO we should display markers for the limits of the clipping
		//TODO should be compensated by zoom
		dispRect.x=cvsDispRect.x+copy_clip_rect.x*zoom;
		dispRect.y=cvsDispRect.y+copy_clip_rect.y*zoom;
		dispRect.w=BTN_BASE_W/8;
		dispRect.h=BTN_BASE_W/8;

		clipRect.x=TOFF_TGTUL_X;
		clipRect.y=TOFF_TGTUL_Y;
		clipRect.w=32;
		clipRect.h=32;
		SDL_RenderCopy(renderer,
		buttons, 
		// NULL,
		&clipRect,
		&dispRect
		);

		dispRect.x=cvsDispRect.x+(copy_clip_rect.x+copy_clip_rect.w)*zoom;
		dispRect.y=cvsDispRect.y+(copy_clip_rect.y+copy_clip_rect.h)*zoom;
		dispRect.w=BTN_BASE_W/8;
		dispRect.h=BTN_BASE_W/8;

		clipRect.x=TOFF_TGTDR_X;
		clipRect.y=TOFF_TGTDR_Y;
		clipRect.w=32;
		clipRect.h=32;
		SDL_RenderCopy(renderer,
		buttons, 
		// NULL,
		&clipRect,
		&dispRect
		);


		
		//blitting an exit button
		dispRect.x=CC_EXIT_UL_X;
		dispRect.y=CC_EXIT_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		clipRect.x=TOFF_VALIDATE_X;
		clipRect.y=TOFF_VALIDATE_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);
		
		
		SDL_RenderPresent(renderer);

		handleinput(&polled,
		true // blocking 
		// false
		);

		
		//we get the click and scale before returning to paste position
		if(polled.newpress){
			//TODO add exit button
			if(
				polled.x < (CC_EXIT_UL_X+BTN_BASE_W)
				&& polled.x > CC_EXIT_UL_X
				&&	polled.y < (CC_EXIT_UL_Y+BTN_BASE_W)
				&& polled.y > CC_EXIT_UL_Y
			){
				LOGD("exiting copyclip ");
				mode=pastePosition;
				return;
			}else 
			if( //small ajustment on x
				polled.x < (cvsDispRect.x+cvsDispRect.w)
				// && polled.x > cvsDispRect.x
				// && polled.x > cvsDispRect.x
				&&	polled.y < (cvsDispRect.y+cvsDispRect.h)
				&& polled.y > cvsDispRect.y
			){
				
				if(polled.x <= cvsDispRect.x){
					polled.x=cvsDispRect.x;
					//we should be able to easily select things overlaping the left border 
				}

				//click is in canvas , we have boolean to alternate between the 2 coordinates points to set
				Uint16 xcvsCoord,ycvsCoord;
				Uint16 tx,ty;
				tx=polled.x - cvsDispRect.x;
				ty = polled.y - cvsDispRect.y;
				LOGD("tx ty before zoom scale %d %d \n" , tx,ty);
				xcvsCoord=tx/zoom;
				ycvsCoord=ty/zoom;
				LOGD("x y in canvas %d %d \n" , xcvsCoord,ycvsCoord);
				
				//TODO we should click first and second new press and set markins accordingly
				if(cc_ul){
					copy_clip_rect.x=xcvsCoord;
					copy_clip_rect.y=ycvsCoord;
				    LOGD("adapting markers ul x y %d %d \n",copy_clip_rect.x,copy_clip_rect.y );
					
					// let s adapt width if we are end of the screen (seems to be problematic other wise)
					if(copy_clip_rect.x +copy_clip_rect.w>CVSWDTH){
						copy_clip_rect.w=CVSWDTH-copy_clip_rect.x;
						LOGD("width ajusted to %d \n",copy_clip_rect.w);
					}
					
					cc_ul=false;
				}else{

					if(xcvsCoord>copy_clip_rect.x&&ycvsCoord>copy_clip_rect.y){
						copy_clip_rect.w=xcvsCoord-copy_clip_rect.x;
						copy_clip_rect.h=ycvsCoord-copy_clip_rect.y;
						LOGD("adapting markers w h %d %d \n",copy_clip_rect.w,copy_clip_rect.h );
					}
					cc_ul=true;
				}
			
			}

		}
	
	}

  //** TIME CODE MODE

//TODO add init method
// store current timecode in local slot and apply only on exit
Uint16 timecode=0;

void initTimeCodeMode(){
	timecode=project[nb_edit_slot].timecode;
}

  // screen to set time code for frame : first half with one icon for frames / sec, second half for full seconds , different icon
	void timeCodeMode(){
		SDL_SetRenderTarget(renderer,NULL);
		SDL_RenderClear(renderer);
	   SDL_Rect dispRect, clipRect ;

	   //exit button
	   clipRect.x = TOFF_VALIDATE_X;
	   clipRect.y = TOFF_VALIDATE_Y;
	   clipRect.w = 64;
	   clipRect.h = 64;
		dispRect.x=TC_CANCEL_UL_X;
		dispRect.y=TC_CANCEL_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);
	   

	   //apply to multiple
	   clipRect.x = TOFF_MULTIPLE_X;
	   clipRect.y = TOFF_MULTIPLE_Y;
	   clipRect.w = 64;
	   clipRect.h = 64;
		dispRect.x=TC_MULTIPLE_UL_X;
		dispRect.y=TC_MULTIPLE_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);




	   //default button
	   // clipRect.x = TOFF_CANCEL_X;
	   // clipRect.y = TOFF_CANCEL_Y;
	   // clipRect.w = 64;
	   // clipRect.h = 64;
		// dispRect.x=TC_DEFAULT_UL_X;
		// dispRect.y=TC_DEFAULT_UL_Y;
		// dispRect.w=BTN_BASE_W;
		// dispRect.h=BTN_BASE_W;

		// SDL_RenderCopy(renderer,
		// buttons, 
		// &clipRect,
		// &dispRect
		// );
	   
	   //LATER full seconds row
	   
	
		//'frames"  row
		int maxcol;
		
		//should be define
		maxcol=TC_CLICK_W / ( 64 * buttonZoom);
		
		int i,col,row;
		col=0;row=0;
		for(i=0;i<timecode;i++){
			
			
			
		   clipRect.x = TOFF_TCODE_X;
		   clipRect.y = TOFF_TCODE_Y;
		   clipRect.w = 64;
		   clipRect.h = 64;
			dispRect.x=TC_CLICK_UL_X+buttonZoom*64*col;
			dispRect.y=TC_CLICK_UL_Y+buttonZoom*64*row;
			dispRect.w=BTN_BASE_W;
			dispRect.h=BTN_BASE_W;

			SDL_RenderCopy(renderer,
			buttons, 
			&clipRect,
			&dispRect
			);
				
			col++;
			
			//if we are further than max col,
			// we need to go below
			if( col>=maxcol){
				col=0;
				row++;
			}
			
		}
	
		SDL_RenderPresent(renderer);

		handleinput(&polled,
		true // blocking 
		// false
		);





		//we get the click and scale before returning to paste position
		if(polled.newpress){
			if( 
				polled.x < (TC_CANCEL_UL_X+BTN_BASE_W)
				&& polled.x > TC_CANCEL_UL_X
				&&	polled.y < (TC_CANCEL_UL_Y+BTN_BASE_W)
				&& polled.y > TC_CANCEL_UL_Y
			   
			){
				project[nb_edit_slot].timecode=timecode;
				//DEBUG going bac to settings for the mo
				mode=settings;
				return;
			}else
			if( 
				polled.x < (TC_MULTIPLE_UL_X+BTN_BASE_W)
				&& polled.x > TC_MULTIPLE_UL_X
				&&	polled.y < (TC_MULTIPLE_UL_Y+BTN_BASE_W)
				&& polled.y > TC_MULTIPLE_UL_Y
			   
			){
				int i;
				for( i=cb;i<=ce;i++){
					project[i].timecode=timecode;
				}
				//DEBUG going bac to settings for the mo
				mode=settings;
				return;
			// }else
			// if( 
				// polled.x < (TC_DEFAULT_UL_X+BTN_BASE_W)
				// && polled.x > TC_DEFAULT_UL_X
				// &&	polled.y < (TC_DEFAULT_UL_Y+BTN_BASE_W)
				// && polled.y > TC_DEFAULT_UL_Y			   
			// ){
				// //TODO put back default
			}else if(
				polled.x < (TC_CLICK_UL_X+TC_CLICK_W)
				&& polled.x > TC_CLICK_UL_X
			){
				//compute row and col of the click to set tc
				Uint16 tx=polled.x - TC_CLICK_UL_X;
				Uint16 ty=polled.y - TC_CLICK_UL_Y;
				Uint16 computedCol= tx / (BTN_BASE_W);
				Uint16 computedRow= ty / (BTN_BASE_W);
				Uint16 computedTC=computedCol+computedRow*maxcol;
				LOGD("computed click TC %d \n",computedTC);
				timecode=computedTC;
				//project[nb_edit_slot].timecode=computedTC;
			}
				
		}
	}
  
	
	
	//**** SCALE SELECTION MODE
	
	//should be done after sub selection/ clipping for interop
	float xScale=1;
	float yScale=1;
	
	void scaleSelection(){
		SDL_SetRenderTarget(renderer,NULL);
		SDL_RenderClear(renderer);
		// rendergpupoc(renderer,false);
		// // lightTableDrawCalls();
	   SDL_Rect dispRect ;

	   
	   dispRect.x=cvsDispRect.x
	   // +xpaste*zoom
	   ;
	   dispRect.y=cvsDispRect.y
	   // +ypaste*zoom
	   ;
	   dispRect.w=copy_clip_rect.w;
	   dispRect.h=copy_clip_rect.h;
	// if(copy_src!=NULL){
		SDL_SetTextureAlphaMod(copy_src,255);

		SDL_RenderCopy(renderer,
		copy_src, 
		&copy_clip_rect,
		// NULL,
		// &cvsDispRect
		&dispRect
		);
			
		// }
	
		SDL_RenderPresent(renderer);

		handleinput(&polled,
		true // blocking 
		// false
		);

		//we get the click and scale before returning to paste position
		if(polled.newpress){
			if(
				polled.x < (cvsDispRect.x+cvsDispRect.w)
				&& polled.x > cvsDispRect.x
				&&	polled.y < (cvsDispRect.y+cvsDispRect.h)
				&& polled.y > cvsDispRect.y
			){
				LOGD("calculating scale factor \n" );
				Uint16 tx,ty;
				tx=polled.x - cvsDispRect.x;
				ty = polled.y - cvsDispRect.y;
				
				xScale=((float)tx)/((float)copy_clip_rect.w);
				yScale=((float)ty)/((float)copy_clip_rect.h);
				
				LOGD("zoom factors %f %f \n",xScale,yScale);
				LOGD("we discard y and set xscale \n");
				yScale=xScale;

				
				// LOGD("tx ty before zoom scale %d %d \n" , tx,ty);
				// xpaste=tx/zoom;
				// ypaste=ty/zoom;
				// LOGD("xpaste ypaste before zoom scale %d %d \n" , xpaste, ypaste );
				
				
				//TODO scale must be changed several times before exiting
				LOGD("exiting scale selection");
				mode=pastePosition;
			}

		}
	}
	
	//********* PASTE POSITION MODE ****************
	Uint16 xpaste=0;
	Uint16 ypaste=0;
	
	void render_pastePosition(){
		//TODO render light table then paste layer and button
		SDL_SetRenderTarget(renderer,NULL);
		// rendergpupoc(renderer,false);
		lightTableDrawCalls();
		   SDL_Rect dispRect ;
		SDL_Rect clipRect = 
			{0,0,
			0,0};

		   
		   dispRect.x=cvsDispRect.x+xpaste*zoom;
		   dispRect.y=cvsDispRect.y+ypaste*zoom;
		   dispRect.w=copy_clip_rect.w*zoom*xScale;
		   dispRect.h=copy_clip_rect.h*zoom*yScale;
		// if(copy_src!=NULL){
			SDL_SetTextureAlphaMod(copy_src,255);

			SDL_RenderCopy(renderer,
			copy_src, 
			// NULL,
			&copy_clip_rect,
			// &cvsDispRect
			&dispRect
			);
			
		// }
			
	   clipRect.x = TOFF_CANCEL_X;
	   clipRect.y = TOFF_CANCEL_Y;
	   clipRect.w = 64;
	   clipRect.h = 64;
		dispRect.x=PP_CANCEL_UL_X;
		dispRect.y=PP_CANCEL_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

			SDL_RenderCopy(renderer,
			buttons, 
			&clipRect,
			&dispRect
			);

	   // SDL_Rect
	   clipRect.x = TOFF_VALIDATE_X;
	   clipRect.y = TOFF_VALIDATE_Y;
	   clipRect.w = 64;
	   clipRect.h = 64;
			// {,,
			// 64,64};
		dispRect.x=PP_VALIDATE_UL_X;
		dispRect.y=PP_VALIDATE_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

			SDL_RenderCopy(renderer,
			buttons, 
			&clipRect,
			&dispRect
			);

	//TODO icon
	   clipRect.x = TOFF_SUBSELECT_X;
	   clipRect.y = TOFF_SUBSELECT_Y;
	   clipRect.w = 64;
	   clipRect.h = 64;
			// {,,
			// 64,64};
		dispRect.x=PP_COPYCLIP_UL_X;
		dispRect.y=PP_COPYCLIP_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

			SDL_RenderCopy(renderer,
			buttons, 
			&clipRect,
			&dispRect
			);

		//TODO icon
	   // SDL_Rect
	   clipRect.x = TOFF_SCALE_X;
	   clipRect.y = TOFF_SCALE_Y;
	   clipRect.w = 64;
	   clipRect.h = 64;
			// {,,
			// 64,64};
		dispRect.x=PP_SCALE_UL_X;
		dispRect.y=PP_SCALE_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

			SDL_RenderCopy(renderer,
			buttons, 
			&clipRect,
			&dispRect
			);
			
		
		SDL_RenderPresent(renderer);

	}

	
	//TODO track new press to position paste
	//TODO track commit button press
	void pastePosition(){
		// LOGD("paste position loop \n");
		render_pastePosition();
		
		handleinput(&polled,
		true // blocking 
		// false
		);


		if(polled.newpress){
			if( 
				polled.x < (PP_CANCEL_UL_X+BTN_BASE_W)
				&& polled.x > PP_CANCEL_UL_X
				&&	polled.y < (PP_CANCEL_UL_Y+BTN_BASE_W)
				&& polled.y > PP_CANCEL_UL_Y
				){
				
				mode=settings;
				return;
			}else 
			if( 
				polled.x < (PP_SCALE_UL_X+BTN_BASE_W)
				&& polled.x > PP_SCALE_UL_X
				&&	polled.y < (PP_SCALE_UL_Y+BTN_BASE_W)
				&& polled.y > PP_SCALE_UL_Y
				){
				LOGD("setting scale selection\n");
				mode = scaleSelection;
				return;
			}else	
			if( 
				polled.x < (PP_COPYCLIP_UL_X+BTN_BASE_W)
				&& polled.x > PP_COPYCLIP_UL_X
				&&	polled.y < (PP_COPYCLIP_UL_Y+BTN_BASE_W)
				&& polled.y > PP_COPYCLIP_UL_Y
				){
				mode = copy_clip;
				return;
			}else	
			if( 
				polled.x < (PP_VALIDATE_UL_X+BTN_BASE_W)
				&& polled.x > PP_VALIDATE_UL_X
				&&	polled.y < (PP_VALIDATE_UL_Y+BTN_BASE_W)
				&& polled.y > PP_VALIDATE_UL_Y
				){
				//pasting for good
				LOGD("paste with offset \n");
				rtcopy(renderer,
						current,
						copy_src,
						xpaste,ypaste,
						xScale,yScale,
						&copy_clip_rect
						);
				project[nb_edit_slot].dirty=true;
				LOGD("frame %d marked dirty \n",nb_edit_slot);
				
				
			}else
			if(
				polled.x < (cvsDispRect.x+cvsDispRect.w)
				&& polled.x > cvsDispRect.x
				&&	polled.y < (cvsDispRect.y+cvsDispRect.h)
				&& polled.y > cvsDispRect.y
			){
				LOGD("moving frame to paste position \n" );
				//TODO compute new position of pasted selection
				Uint16 tx,ty;
				tx=polled.x - cvsDispRect.x;
				ty = polled.y - cvsDispRect.y;
				LOGD("tx ty before zoom scale %d %d \n" , tx,ty);
				xpaste=tx/zoom;
				ypaste=ty/zoom;
				LOGD("xpaste ypaste before zoom scale %d %d \n" , xpaste, ypaste );
				
			}
		}
		
	}
	
	

  
	//state of edit mode
	int xc,yc; //good candidate to keep last value in case of not newpress?
	int prevxc,prevyc; //init on new press ?
	//TO CHECK if a new press is out of canvas, does it draw ?
	bool incanvas;
  //bool noPaint;
	//statefunc for edit ( most complex )
        bool painting=false;

	  
	 void initBehind();
	  
	void commitBehind(){
		//we blit current on behind, then clear current and copy behind on it
		SDL_SetRenderTarget(renderer,pane);
		SDL_SetTextureAlphaMod(current,255);
		SDL_RenderCopy(renderer, current, NULL, NULL);
		
		clearRenderTargetWithSquareEraser(current);
		SDL_SetRenderTarget(renderer,current);
		SDL_RenderCopy(renderer, pane, NULL, NULL);
		
		// SDL_SetRenderTarget(renderer,behind);
		clearRenderTargetWithSquareEraser(pane);
		
	}
	  
	  
	// on stylus up
	void commitAbove(){

		//we blit current on undo buffer to keep it
		LOGD("filling %d \n",currentUndoBuf);
		clearRenderTargetWithSquareEraser(undoBuf[currentUndoBuf]);
		SDL_SetRenderTarget(renderer,undoBuf[currentUndoBuf]);
		SDL_SetTextureAlphaMod(current,255);
		SDL_RenderCopy(renderer, current, NULL, NULL);

		
		currentUndoDepth+=1;
		if(currentUndoDepth>=undoDepth)currentUndoDepth=undoDepth;
		LOGD("cur undo depth%d\n",currentUndoDepth);
		
		//house keeping undo slots
		currentUndoBuf+=1;
		if(currentUndoBuf>=undoDepth)currentUndoBuf=0;
		LOGD("next undo buf%d\n",currentUndoBuf);
	
		
		// clearRenderTargetWithSquareEraser(current);
		SDL_SetRenderTarget(renderer,current);
		SDL_RenderCopy(renderer, pane, NULL, NULL);
		
		// SDL_SetRenderTarget(renderer,behind);
		clearRenderTargetWithSquareEraser(pane);
		
		
		
		
	}

	  
		// TODO clean up and comment the mess
	void directDraw(input * pol){
						//decouple event loop from polled, as events in dodonpachi mode 
				//will be indirect
						//classical you touch I paint
				
				

				//WIP weakness we need to persist painting state from new press to end press
				// right now after new press consumed in other states, paints a bit on coming back
							if(pol->newpress){
								LOGD("win dbg: new press prev xc yc reset\n");
								//first event for this potential line
								prevxc=-1;prevyc=-1;
								//TODO with this fix the draw operation segfaults
								xc=-1;yc=-1; //otherwise archiving will restore prev xc yc
								// endless line pb
								// LOGD("zzn checking buttons\n");
								//state managment in there, not cool
								painting=!checkButtonColl(pol->x,pol->y);
							}
								//normaly should not take place in certain case, clean up
							if(pol->pressed && painting){
							
								//TODO normally should be done when in canvas
								//archiving previously polled event
								prevxc=xc;
								prevyc=yc;
						
								//transfo to canvas coords
								// if not in canvas coordinate,
								//do not set dirty flag
								xc=(pol->x-xorig)/zoom;
								yc=(pol->y-YORIG)/zoom;
							
								incanvas=false; //default
								if( (xc>=0 && xc<=CVSWDTH)
									&&
									(yc>=0 && yc<=CVSHGTH)  ){
									incanvas=true;
								}else{
									LOGD("zzn move or click not in canvas \n");
	
									//restoring backup not to let negative values here
									xc=prevxc;
									yc=prevyc;
								}
							
								//to begin interpolate only with draw that begins in canvas?
								if(incanvas){
									//dirty flag for save
									if( project[nb_edit_slot].dirty==false){
										project[nb_edit_slot].dirty=true;
										LOGD(" frame %d dirty from paint \n ",nb_edit_slot);
									}
									
									
									
									paintHandlingUI(
										prevxc,
										prevyc,
										xc 
										, yc,renderer);
									rendergpupoc(renderer,
									true,false);
								}
							}

							if(pol->endofpress && painting){
							  painting=false;
							  if(activeBrush==roundEraser){
								 LOGD("zzn clearing white from round eraser \n ");
								 clearCurrentOfClearColorFullAlphaPixels();
							  }
							  
							  if(BEHIND){
								  //we need to merge behind with current canvas when painting brush up
								  //lets blit current on behind and make it current
								  //TODO
								  commitBehind();
								  
								  //then reinit behind (clean or reallocation)
								  // initBehind();
							  }else{
								  
								  commitAbove();
								  
							  }
							}

	}


//dodonpaint variables	
	bool dodonpaint=false;
	bool ddpendown=true;
	bool ddpenjustdownmsg=false;
	//ddp mode variables
	Uint16 xcursor,ycursor,prevxtouch,prevytouch;
	Sint16 deltax,deltay;
	Uint16 xtouch,ytouch;

	//TODO simplify, use only variables for that mode (stop sharing with direct draw)
//TODO reset point of origin if finger outside of canvas / button coll, as it kills navigation of cursor it seems
	void dodonpachiDraw(input * pol){
				//decouple event loop from polled, as events in dodonpachi mode 
				//will be indirect

						prevxtouch=xtouch;
						prevytouch=ytouch;
						
						xtouch=pol->x;
						ytouch=pol->y;
			
						//we calculate a delta to move the cursor pos
						deltax=xtouch-prevxtouch;
						deltay=ytouch-prevytouch;

						if(pol->newpress){
							//means we reset our handle
							deltax=0;
							deltay=0;
						}
						
						xcursor+=deltax;
						ycursor+=deltay;
				//WIP weakness we need to persist painting state from new press to end press
				// right now after new press consumed in other states, paints a bit on coming back
							if(pol->newpress){
								if(checkButtonColl(xtouch,ytouch)){
									LOGD("dodon button coll, return \n");
									return;
								}
							}
								//normaly should not take place in certain case, clean up
							if(pol->pressed && ddpendown){
							
								//TODO normally should be done when in canvas
								//archiving previously polled event
								prevxc=xc;
								prevyc=yc;
						
						
								//transfo to canvas coords
								// if not in canvas coordinate,
								//do not set dirty flag
								xc=(xcursor-xorig)/zoom;
								yc=(ycursor-YORIG)/zoom;
							
								incanvas=false; //default
								if( (xc>=0 && xc<=CVSWDTH)
									&&
									(yc>=0 && yc<=CVSHGTH)  ){
									incanvas=true;
								}else{
									LOGD("zzn move or click not in canvas \n");
	
									//restoring backup not to let negative values here
									xc=prevxc;
									yc=prevyc;
								}
							
								//to begin interpolate only with draw that begins in canvas?
								if(incanvas){
									//dirty flag for save
									if( project[nb_edit_slot].dirty==false){
										project[nb_edit_slot].dirty=true;
										LOGD(" frame %d dirty from paint \n ",nb_edit_slot);
									}
									
									
									if(ddpenjustdownmsg){
										//first draw not a line, to avoid drawing from last pen up
										prevxc=xc;
										prevyc=yc;
										ddpenjustdownmsg=false; //msg consumed
									}
									
									paintHandlingUI(
										prevxc,
										prevyc,
										xc 
										, yc,renderer);
									rendergpupoc(renderer,
									true,dodonpaint);
								}
							}

							if(pol->endofpress && ddpendown){
							  if(activeBrush==roundEraser){
								 LOGD("zzn clearing white from round eraser \n ");
								 clearCurrentOfClearColorFullAlphaPixels();
								 ddpendown=false;
							  }
							}
	}

	
  void initedit(){
	//direct draw setup
	painting=false;
	  
		//for dodonpaint
		ddpendown=false;
	  prevxtouch=128*zoom+XORIG;
	  prevytouch=128*zoom+YORIG;
	  xtouch=128*zoom+XORIG;
	  ytouch=128*zoom+YORIG;
	  
	  xcursor=128;
	  ycursor=128;



      mode=edit;

	  }
	
	
Uint16 copy_frame_nb=-1;
	
	
void toNextFrame(){
		
		resetUndo();
		
		int tgt = nb_edit_slot+1;
		//we cycle to first frame
		if( 
			tgt>(MAX_FRAME_NMBER-1)	||	project[tgt].tx==NULL
		){ 
			LOGD("we cycle to first frame %d\n",tgt);
			tgt=0;
		}
			
		setEditSlot(tgt);
		nb_edit_slot=tgt;

}


void toPreviousFrame(){
		
		resetUndo();
		
		//changing behavior , <0, we get to last
		
		int tgt = nb_edit_slot-1;
		if(tgt<0){ 
			LOGD("zzn move to last frame %d\n",tgt);
			
			tgt=frameNumber()-1;
		}
		setEditSlot(tgt);
		nb_edit_slot=tgt;

	
}


void resetUndo(){
	currentUndoBuf=0;
	currentUndoDepth=0;
	
}

//undo
void unstackundo(){
	if(currentUndoDepth>0){
		LOGD("unstacking \n");
		currentUndoDepth-=1;
		LOGD("new undo depth %d \n",currentUndoDepth);
		currentUndoBuf-=1;
		if(currentUndoBuf<0)currentUndoBuf=undoDepth-1;
		
		LOGD("restoring slot %d \n",currentUndoBuf);
		SDL_Texture * tmp= undoBuf[currentUndoBuf];
		undoBuf[currentUndoBuf]=project[nb_edit_slot].tx;
		project[nb_edit_slot].tx=tmp;
		current=tmp;
		LOGD("undo done\n");
		
	}
	
}
	
//returns true if click consumed ( no paint )
bool checkButtonColl(int x,int y){
	LOGD("zzn checking buttons\n");
	if( 
		x < (BTN_SETTINGS_UL_X+BTN_BASE_W)
		&& x > BTN_SETTINGS_UL_X
		&&	y < (BTN_SETTINGS_UL_Y+BTN_BASE_W)
		&& y > BTN_SETTINGS_UL_Y
	){
		LOGD("zzn settings screen \n");
		mode=settings;
		return true;
	}else if( 
		x < (BTN_ADD_UL_X+BTN_BASE_W)
		&& x > BTN_ADD_UL_X
		&&	y < (BTN_ADD_UL_Y+BTN_BASE_W)
		&& y > BTN_ADD_UL_Y
	){
		LOGD("zzn btn add \n");
		appendframe(nb_edit_slot+1);
		return true;
	}else if( 
		x < (BTN_FLR_UL_X+BTN_BASE_W)
		&& x > BTN_FLR_UL_X
		&&	y < (BTN_FLR_UL_Y+BTN_BASE_W)
		&& y > BTN_FLR_UL_Y
	){
		resetUndo();
		initFlick(false);
		return true;
	}else if( 
		x < (BTN_FLG_UL_X+BTN_BASE_W)
		&& x > BTN_FLG_UL_X
		&&	y < (BTN_FLG_UL_Y+BTN_BASE_W)
		&& y > BTN_FLG_UL_Y
	){
	
		initFlick(true);
		return true;
	}else if( 
		x < (BTN_PLAY_UL_X+BTN_BASE_W)
		&& x > BTN_PLAY_UL_X
		&&	y < (BTN_PLAY_UL_Y+BTN_BASE_W)
		&& y > BTN_PLAY_UL_Y
	){
		LOGD("fill button pressed going to pick screen \n");
		fillmode=true;
		paletteMode=false;
		cleanColor=false;
		mode=pickMode;
		return true;
	
		// init_play();
		// return true;
	}else if( 
		x < (BTN_COPY_UL_X+BTN_BASE_W)
		&& x > BTN_COPY_UL_X
		&&	y < (BTN_COPY_UL_Y+BTN_BASE_W)
		&& y > BTN_COPY_UL_Y
	){
		// //HACK to test
		ddpendown=!ddpendown;
		ddpenjustdownmsg=ddpendown;		
						
		//to not have ghost lines 
		LOGD("ddpendown %d \n",ddpendown);
		
		
	
		//set copy slot
		copy_frame_nb=nb_edit_slot;
		copy_src=project[nb_edit_slot].tx;
		LOGD("copy slot set to : %d %d \n",copy_frame_nb,copy_src);
		return true;
	}else if( 
		x < (BTN_UNDO_UL_X+BTN_BASE_W)
		&& x > BTN_UNDO_UL_X
		&&	y < (BTN_UNDO_UL_Y+BTN_BASE_W)
		&& y > BTN_UNDO_UL_Y
	){
		unstackundo();
		return true;
	}else if( 
		x < (BTN_PASTE_UL_X+BTN_BASE_W)
		&& x > BTN_PASTE_UL_X
		&&	y < (BTN_PASTE_UL_Y+BTN_BASE_W)
		&& y > BTN_PASTE_UL_Y
	){
		if(copy_src!=NULL){
			if(BEHIND){
				LOGD("pasting behind \n");
				clearRenderTargetWithSquareEraser(pane);
				rtcopy(renderer,
						// project[nb_edit_slot].tx,
						pane,
						copy_src,
						0,0,0,0,NULL);
				rtcopy(renderer,
						// project[nb_edit_slot].tx,
						pane,
						current,
						0,0,0,0,NULL);
				//now we need to swap
				clearRenderTargetWithSquareEraser(current);
				rtcopy(renderer,
						// project[nb_edit_slot].tx,
						current,
						pane,
						0,0,0,0,NULL);
				clearRenderTargetWithSquareEraser(pane);
				
						
				project[nb_edit_slot].dirty=true;
				LOGD("frame %d marked dirty \n",nb_edit_slot);
				
			}else{
				LOGD("pasting to frame \n");
				rtcopy(renderer,
						// project[nb_edit_slot].tx,
						current,
						copy_src,
						0,0,0,0,NULL);
				project[nb_edit_slot].dirty=true;
				LOGD("frame %d marked dirty \n",nb_edit_slot);
			}
		}else{
			LOGD(" no copyslot set \n");
		}
		return true;
	}else if( 
		x < (BTN_NXT_UL_X+BTN_BASE_W)
		&& x > BTN_NXT_UL_X
		&&	y < (BTN_NXT_UL_Y+BTN_BASE_W)
		&& y > BTN_NXT_UL_Y
	){
		LOGD("zzn button next\n");
		
		toNextFrame();
		
		// int tgt = nb_edit_slot+1;
		// //we cycle to first frame
		// if( 
			// tgt>(MAX_FRAME_NMBER-1)	||	project[tgt].tx==NULL
		// ){ 
			// LOGD("we cycle to first frame %d\n",tgt);
			// tgt=0;
		// }
			
		// setEditSlot(tgt);
		// nb_edit_slot=tgt;

		return true;
	}else 	if( 
		x < (BTN_PREV_UL_X+BTN_BASE_W)
		&& x > BTN_PREV_UL_X
		&&	y < (BTN_PREV_UL_Y+BTN_BASE_W)
		&& y > BTN_PREV_UL_Y
	){
		LOGD("zzn button back\n");
		

		toPreviousFrame();
		// //changing behavior , <0, we get to last
		
		// int tgt = nb_edit_slot-1;
		// if(tgt<0){ 
			// LOGD("zzn move to last frame %d\n",tgt);
			
			// tgt=frameNumber()-1;
		// }
		// setEditSlot(tgt);
		// nb_edit_slot=tgt;
		return true;
	}else 	if( 
		x < (BTN_SAVE_UL_X+BTN_BASE_W)
		&& x > BTN_SAVE_UL_X
		&&	y < (BTN_SAVE_UL_Y+BTN_BASE_W)
		&& y > BTN_SAVE_UL_Y
	){
		LOGD("zzn save clicked\n");
		saveProjectFrames();
		LOGD("zzn returned from frames save \n");
		return true;
	}else 	if( 
		x < (BTN_ERASER_UL_X+BTN_BASE_W)
		&& x > BTN_ERASER_UL_X
		&&	y < (BTN_ERASER_UL_Y+BTN_BASE_W)
		&& y > BTN_ERASER_UL_Y
	){
		LOGD("zzn toggle erase clicked\n");
		
		//testClearRT(renderer,project[nb_edit_slot].tx);
		toggleEraser();
		return true;
	}
		
	
	
	
	return false;
}


	void kshortcuts(input * keys){
		if(keys->kleft){
			LOGD("kshort left \n");
			toNextFrame();
		}else if(keys->kright){
			LOGD("kshort right\n");
			toPreviousFrame();
		}
	}

	void edit( ){
				//first so that we get a render before blocking for input
				rendergpupoc(renderer
				,true,dodonpaint);
	
	
				handleinput(&polled,
				true //has been blocking for most of the dev
				//false
				);
				
				kshortcuts(&polled);
				
				if(dodonpaint){
					dodonpachiDraw(&polled);
				}else{
					 directDraw(&polled);
				}
				
	}

	
	//we pass buttons as parameter,
	//as on gles target rt change clears screen
	void rendergpupoc(SDL_Renderer * renderer,
		bool buttons,bool renderCursor){
		SDL_SetRenderTarget(renderer,NULL);

		lightTableDrawCalls();
		
		
		if(buttons)renderbuttons();
		
		if(renderCursor){
				   SDL_Rect destRect = 
				   {
				   //code duplication from paint
				   xcursor - brushScale/2,
				   ycursor- brushScale/2,
				   // 2*brushRadius,
				   // 2*brushRadius
					//WIP
				   brushScale,
				   brushScale
				   }; //TODO needs to be computed from radius
				   SDL_RenderCopy(renderer, activeBrush, NULL, &destRect);

			
		}
		
		
		SDL_RenderPresent(renderer);

		//debug for note 3 neo flicker
		//LOGD("zzn render gpu poc\n");

	}

	
	
	//**********  SETTINGS PANE   *********************
	
	Uint16 brushDispY=0;
//moved up for proto
//	Uint16 cb=0;
//	Uint16 ce=0;
	
	void render_settings(){
		SDL_SetRenderTarget(renderer,NULL);
		   SDL_Rect dispRect = 
			{xorig,YORIG,
			CVSWDTH*zoom,CVSHGTH*zoom};
		SDL_SetRenderDrawColor(renderer,0XFF,0XFF,0XFF,0XFF);
		SDL_RenderClear(renderer);

		


	   SDL_Rect clipRect = 
			{TOFF_DELETE_X,TOFF_DELETE_Y,
			64,64};
		dispRect.x=BTN_DELETE_UL_X;
		dispRect.y=BTN_DELETE_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		if(DEL_ENABLED){
			SDL_RenderCopy(renderer,
			buttons, 
			&clipRect,
			// NULL,
			&dispRect
			);
		}
		
		clipRect.x=TOFF_CB_X;
		clipRect.y=TOFF_CB_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_CB_UL_X;
		dispRect.y=BTN_CB_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);

		//brush size
		// SDL_SetRenderDrawColor(renderer,0XFF,0XFF,0XFF,0X00);
		// dispRect.x=0;
		// dispRect.y=0;
		// dispRect.w=SLDR_BRSH_WDTH;
		// dispRect.h=SLDR_BRSH_HGHT;
		// SDL_RenderDrawRect(renderer,&dispRect);
		
		// //we consider 64 max brush scale
		//TODO magic number for max brush scale
		brushDispY=((float)brushScale/(float)64)*SLDR_BRSH_HGHT;
		dispRect.x=0;
		dispRect.y=brushDispY-32;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;
		clipRect.x=TOFF_NXT_X;
		clipRect.y=TOFF_NXT_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		// SDL_RenderDrawRect(renderer,&dispRect);
		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);
		
		
		
		clipRect.x=TOFF_PLAY_X;
		clipRect.y=TOFF_PLAY_Y;
		// clipRect.x=TOFF_FILL_X;
		// clipRect.y=TOFF_FILL_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_FILL_UL_X;
		dispRect.y=BTN_FILL_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);
		
		
		
		
		clipRect.x=TOFF_CE_X;
		clipRect.y=TOFF_CE_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_CE_UL_X;
		dispRect.y=BTN_CE_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);

		clipRect.x=TOFF_PASTEBIT_X;
		clipRect.y=TOFF_PASTEBIT_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_PASTEBIT_UL_X;
		dispRect.y=BTN_PASTEBIT_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		&dispRect
		);

		clipRect.x=TOFF_PR_X;
		clipRect.y=TOFF_PR_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_PR_UL_X;
		dispRect.y=BTN_PR_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);
		
		clipRect.x=TOFF_PIP_X;
		clipRect.y=TOFF_PIP_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_PIP_UL_X;
		dispRect.y=BTN_PIP_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);

		//time code
		clipRect.x=TOFF_TCODE_X;
		clipRect.y=TOFF_TCODE_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_TCODE_UL_X;
		dispRect.y=BTN_TCODE_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);
		
		
		//paste position
		clipRect.x=TOFF_PP_X;
		clipRect.y=TOFF_PP_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_PP_UL_X;
		dispRect.y=BTN_PP_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);

		//palette
		clipRect.x=TOFF_PALETTE_X;
		clipRect.y=TOFF_PALETTE_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_PALETTE_UL_X;
		dispRect.y=BTN_PALETTE_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);
		
		//del color
		clipRect.x=TOFF_DELETECOLOR_X;
		clipRect.y=TOFF_DELETECOLOR_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_DELETECOLOR_UL_X;
		dispRect.y=BTN_DELETECOLOR_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);
		
		//ddp
		clipRect.x=TOFF_DDP_X;
		clipRect.y=TOFF_DDP_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_DDP_UL_X;
		dispRect.y=BTN_DDP_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);
		//MOV WAV
		clipRect.x=TOFF_MOVEWAV_X;
		clipRect.y=TOFF_MOVEWAV_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_MOVEWAV_UL_X;
		dispRect.y=BTN_MOVEWAV_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);
		//clear artifact
		clipRect.x=TOFF_CLEAR_ARTIFACTS_X;
		clipRect.y=TOFF_CLEAR_ARTIFACTS_Y;
		clipRect.w=64;
		clipRect.h=64;
		
		dispRect.x=BTN_CLEAR_ARTIFACTS_UL_X;
		dispRect.y=BTN_CLEAR_ARTIFACTS_UL_Y;
		dispRect.w=BTN_BASE_W;
		dispRect.h=BTN_BASE_W;

		SDL_RenderCopy(renderer,
		buttons, 
		&clipRect,
		// NULL,
		&dispRect
		);
		//render current brush
		
		dispRect.x=BTN_BASE_W;
		dispRect.y=SCRHGTH-(Uint16)brushScale*zoom;
		dispRect.w=(Uint16)brushScale*zoom;
		dispRect.h=(Uint16)brushScale*zoom;

						   

		
		SDL_RenderCopy(renderer,
		activeBrush, 
		NULL,
		&dispRect
		);
		//workaround for slight alpha
		SDL_RenderCopy(renderer,
		activeBrush, 
		NULL,
		&dispRect
		);

		
		SDL_RenderPresent(renderer);

	}


	// only move info in memory, the wav is renamed on project save
	void logicalmovewav(){
		// 
		if (copy_frame_nb<0){
			LOGD("no copy frame \n");
			return;
		}

		if(project[copy_frame_nb].snd==NULL){
			LOGD(" no sound to copy \n");
			return;
		}

		if(copy_frame_nb>nb_edit_slot){
			LOGD("with save order not sure that making frame earlier in time is 100p100 \n");
			return;
		}

		project[nb_edit_slot].snd=project[copy_frame_nb].snd;
		project[nb_edit_slot].wavFileNumberOnDisk=project[copy_frame_nb].wavFileNumberOnDisk;
		project[copy_frame_nb].wavFileNumberOnDisk=0;
		project[copy_frame_nb].snd=NULL;
		LOGD("successful logical copy of slot %d to %d \n",copy_frame_nb,nb_edit_slot);
		
	}

	
	
	void clearCurrentOfSinglePixels(){
				copyTexToBufferSurf(nb_edit_slot);
				 
				// char debugsave[512];
				// strcpy(debugsave,projectPath);
				// strcat(debugsave,"beforeclean.bmp");
				// LOGD("%s \n",debugsave);
				
				// SDL_SaveBMP(bufferSurf,debugsave);

				myRgba replaceCol;
				replaceCol.r=clearR;
				replaceCol.g=clearG;
				replaceCol.b=clearB;
				replaceCol.a=0;
				
				
				noRecCleanArtifacts((Uint8 *)bufferSurf->pixels,replaceCol);				
				
				// strcpy(debugsave,projectPath);
				// strcat(debugsave,"afterclean.bmp");
				// LOGD("%s \n",debugsave);
				// SDL_SaveBMP(bufferSurf,debugsave);
				// // SDL_SaveBMP(bufferSurf,"afterclean.bmp");
				
				clearRenderTargetWithSquareEraser(project[nb_edit_slot].tx);
				loadsurftostreamingtex(bufferSurf,tmp,true,255);
				blittexoncleanrt(renderer,project[nb_edit_slot].tx,tmp);		
				project[nb_edit_slot].dirty=true;
				
				//WORKAROUND it seems there are clear color pixels with full alpha
				//we run it as a workaround
				clearCurrentOfClearColorFullAlphaPixels();
		
		
	}
	
	
	//statefunc for settings > sliders
	
	void settings(){
		render_settings();
		
		handleinput(&polled,
				true // blocking should be ok
				//false
			);


		//handle settings click
						
		if(polled.newpress){
		//if click on slider no exit
			if(
				polled.x < (SLDR_BRSH_WDTH)
				&& polled.x > 0
				&&	polled.y < (SLDR_BRSH_HGHT)
				&& polled.y > 0
			){
				//TODO update brush radius
				LOGD("y click as int %d \n",polled.y);
				float t1=polled.y;
				LOGD("y click as float %f \n",t1);
				float t2=SLDR_BRSH_HGHT;
				LOGD("sldr hght as float %f \n",t2);
				Uint16 radius=
				(t1/t2)*64 ; //64 is max brush scale , 128 to 256 fails on win???
				// ((float)polled.y/(float)SLDR_BRSH_HGHT);
				LOGD("new brushscale %d \n",radius);
				if ( radius==0){
					LOGD("non zero to prevent crash? \n ");
					radius=1;
					
				}
				brushScale=radius;
				
				//this more logical method was abandoned on a suspicion of crash
				//crash on lots of resizes still there !
				
				//TODO reallocate brush from compose
				// brushRadius=radius;
				// SDL_DestroyTexture(brush);
				// SDL_Surface * brushSurf = 
					// // SDL_LoadBMP("brush32.bmp");
					// composeBrushWithAlpha(
					// // brushRadius
					// radius
					// ,ALPHA_BORDER
					// , col, GLOBAL_ALPHA);
				// LOGD("zzn new brush surf composed %d \n",brushSurf);
				// brush  = SDL_CreateTextureFromSurface(renderer, brushSurf);
				// SDL_FreeSurface( brushSurf);
				// LOGD("zzn brush newly allocated %d \n ",brush);
				// activeBrush=brush;
			}else
			if( 
				polled.x < (BTN_FILL_UL_X+BTN_BASE_W)
				&& polled.x > BTN_FILL_UL_X
				&&	polled.y < (BTN_FILL_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_FILL_UL_Y
			   
			){
				// LOGD("fill button pressed going to pick screen \n");
				// fillmode=true;
				// paletteMode=false;
					// mode=pickMode;
					// return;
				resetUndo();
				init_play();
				return ;
				
			}else
			if( 
				polled.x < (BTN_DDP_UL_X+BTN_BASE_W)
				&& polled.x > BTN_DDP_UL_X
				&&	polled.y < (BTN_DDP_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_DDP_UL_Y
			   
			){
				dodonpaint=!dodonpaint;
				LOGD("dodon paint %d\n",dodonpaint);
				initedit();
				return;
			}else
			if( 
				polled.x < (BTN_PASTEBIT_UL_X+BTN_BASE_W)
				&& polled.x > BTN_PASTEBIT_UL_X
				&&	polled.y < (BTN_PASTEBIT_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_PASTEBIT_UL_Y
			   
			){
				LOGD("pastebit  \n");
				rtcopy(renderer,
						current,
						copy_src,
						copy_clip_rect.x,copy_clip_rect.y,
						1,1,
						&copy_clip_rect
						);
				project[nb_edit_slot].dirty=true;
				
				
				initedit();
				return;
			}else
			if( 
				polled.x < (BTN_CLEAR_ARTIFACTS_UL_X+BTN_BASE_W)
				&& polled.x > BTN_CLEAR_ARTIFACTS_UL_X
				&&	polled.y < (BTN_CLEAR_ARTIFACTS_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_CLEAR_ARTIFACTS_UL_Y
			   
			){
				LOGD("clear artifacts  \n");
				//WIP insert call with correct color and eraser check
				myRgba param;
				param.r=clearR;
				param.g=clearG;
				param.b=clearB;
//WIP dl of the texture needs to be made
//				noRecClearArtifacts();
				clearCurrentOfSinglePixels();
				project[nb_edit_slot].dirty=true;
				initedit();
				return;
			}else
			if( 
				polled.x < (BTN_MOVEWAV_UL_X+BTN_BASE_W)
				&& polled.x > BTN_MOVEWAV_UL_X
				&&	polled.y < (BTN_MOVEWAV_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_MOVEWAV_UL_Y
			   
			){
				LOGD("MOVE WAV \n");
				logicalmovewav();
				return;
			}else
			if( 
				polled.x < (BTN_PALETTE_UL_X+BTN_BASE_W)
				&& polled.x > BTN_PALETTE_UL_X
				&&	polled.y < (BTN_PALETTE_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_PALETTE_UL_Y
			   
			){
				LOGD("palette button pressed going to palette screen \n");
				fillmode=false;
				cleanColor=false;
				paletteMode=true;
					mode=pickMode;
					return;
			}else
			if( 
				polled.x < (BTN_DELETECOLOR_UL_X+BTN_BASE_W)
				&& polled.x > BTN_DELETECOLOR_UL_X
				&&	polled.y < (BTN_DELETECOLOR_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_DELETECOLOR_UL_Y
			   
			){
				LOGD("del color button pressed going to pick screen \n");
				fillmode=false;
				paletteMode=false;
				cleanColor=true;
					mode=pickMode;
					return;
				
			}else
			if( 
				polled.x < (BTN_TCODE_UL_X+BTN_BASE_W)
				&& polled.x > BTN_TCODE_UL_X
				&&	polled.y < (BTN_TCODE_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_TCODE_UL_Y
			   
			){
				LOGD("tcode button pressed going to tcode screen \n",nb_edit_slot);
					initTimeCodeMode();
					mode=timeCodeMode;
					return;
				
			}else
			if( 
				polled.x < (BTN_DELETE_UL_X+BTN_BASE_W)
				&& polled.x > BTN_DELETE_UL_X
				&&	polled.y < (BTN_DELETE_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_DELETE_UL_Y
				&& DEL_ENABLED
			){
				LOGD("delete button pressed slot %d \n",nb_edit_slot);
				deleteOneFrame(nb_edit_slot);
				
			}else
			if( 
				polled.x < (BTN_CB_UL_X+BTN_BASE_W)
				&& polled.x > BTN_CB_UL_X
				&&	polled.y < (BTN_CB_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_CB_UL_Y
			){
				LOGD("cb button pressed slot %d \n",nb_edit_slot);
				cb=nb_edit_slot;
			}else
			if( 
				polled.x < (BTN_CE_UL_X+BTN_BASE_W)
				&& polled.x > BTN_CE_UL_X
				&&	polled.y < (BTN_CE_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_CE_UL_Y
			){
				LOGD("ce button pressed slot %d \n",nb_edit_slot);
				ce=nb_edit_slot;
			}else
			if( 
				polled.x < (BTN_PIP_UL_X+BTN_BASE_W)
				&& polled.x > BTN_PIP_UL_X
				&&	polled.y < (BTN_PIP_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_PIP_UL_Y
			){
					LOGD("color picker pressed\n");
					fillmode=false;
					cleanColor=false;
					paletteMode=false;
					mode=pickMode;
					return;
			}else
			if( 
				polled.x < (BTN_PP_UL_X+BTN_BASE_W)
				&& polled.x > BTN_PP_UL_X
				&&	polled.y < (BTN_PP_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_PP_UL_Y
			){
				mode=pastePosition;
				return;
			}else
			if( 
				polled.x < (BTN_PR_UL_X+BTN_BASE_W)
				&& polled.x > BTN_PR_UL_X
				&&	polled.y < (BTN_PR_UL_Y+BTN_BASE_W)
				&& polled.y > BTN_PR_UL_Y
			){
				LOGD("pr button pressed slot %d,currenb cb %d ce %d \n",nb_edit_slot,cb,ce);
				
				//TODO so far only after range selection
				
				if(nb_edit_slot<=ce
					&& cb <= nb_edit_slot){
					LOGD(" paste range inside sel not possible \n" );
					return;
				}
				
				// pasting after sel
				if(nb_edit_slot>ce){
					if(cb<=ce){
						int i;
						for(int i=ce;i>=cb;i--){
							appendframe(nb_edit_slot);
							// TODO copy correct to buff ( descending)
							// TODO paste in created
							// TODO logs, to test
							LOGD("copying %d to newly created %d \n",i,nb_edit_slot);
							rtcopy(renderer,project[nb_edit_slot].tx,project[i].tx,0,0,0,0,NULL);
						}
					}else{
						LOGD("cb>e, doing nothing \n");
					}
				}else{
					//TODO pasting before sel
					if(cb<=ce){
						//before sel, we move the sel,
						//so we need to handle copy cursor differently
					
						Uint16 nbPaste= (ce-cb)+1; //if begin = end we still have one to paste
						//WIP since current frame pasted we need to bengin from last frame of sel
						Uint16 frameToPaste = ce+1; //because before first paste we do a shift
						//we start pasting at nb_edit_slot and keep pasting there,
						//since selection further
						
						while(nbPaste>0){
							appendframe(nb_edit_slot);
							
							//we just expanded the space before the frame to paste
							LOGD("frame %d shifted by append\n",frameToPaste);
							// frameToPaste=frameToPaste+1;
							LOGD("copying %d to newly created %d \n",frameToPaste,nb_edit_slot);
							rtcopy(renderer,project[nb_edit_slot].tx,project[frameToPaste].tx,0,0,0,0,NULL);
							//frame consumed
							//we dunno need to change frameToPaste, as the addition of frames
							//pushes next of selection under the 'cursor'
							// frameToPaste=frameToPaste+1; //now we actually advanc in the range to paste
							nbPaste--;
							LOGD(" nb still to paste %d , next slot to paste %d \n",nbPaste,frameToPaste );
						}
						LOGD("end of paste \n");
						// int i;
						// for(int i=ce;i>=cb;i--){
							// appendframe(nb_edit_slot);
							// //TODO copy correct to buff ( descending)
							// //TODO paste in created
							// //TODO logs, to test
							// LOGD("copying %d to newly created %d \n",i,nb_edit_slot);
							// rtcopy(renderer,project[nb_edit_slot].tx,project[i].tx);
						
					}else{
						LOGD("cb>e, doing nothing \n");
					}
					
				}
				
			}else{
				LOGD("back to edit");
				//mode=edit;
				initedit();
			}
		}
	}

	// void init_play(){
		// // last=0;now=0;elapsed=0;
		// mode = play_anm;
		// frameTime=
		// PB_TIME
		// ;
		// disp_nb=0;
	// }

	
	
//#######	END SETTINGS SCREEN
	
	

	void readTranspColor(){
	char path[256];

	strcpy(path,projectPath);

		
		char transpColorFile[512];
		strcpy(transpColorFile,projectPath);
		strcat(transpColorFile,"transpColor.txt");
		LOGD("zzn looking for transp file: %s \n",transpColorFile);
		ifstream myFile (
				transpColorFile
				);
		char charTab[512]; 
		if (myFile.is_open()){
			LOGD("zzn transp file open  \n");
			myFile.getline(charTab,512);
			char sred[4];
			sred[0]=charTab[0];
			sred[1]=charTab[1];
			sred[2]=charTab[2];
			sred[3]='\0';
			//Uint16 ired;
			sscanf(sred,"%d",&clearR);
			
			LOGD("transp col r after load: %d \n",clearR);

			myFile.getline(charTab,512);
			char sgreen[4];
			sgreen[0]=charTab[0];
			sgreen[1]=charTab[1];
			sgreen[2]=charTab[2];
			sgreen[3]='\0';
			// Uint16 igreen;
			sscanf(sgreen,"%d",&clearG);
			
			LOGD("transp col g after load: %d \n",clearG);
			myFile.getline(charTab,512);
			char sblue[4];
			sblue[0]=charTab[0];
			sblue[1]=charTab[1];
			sblue[2]=charTab[2];
			sblue[3]='\0';
			// Uint16 iblue;
			sscanf(sblue,"%d",&clearB);
			
			LOGD("transp col b after load: %d \n",clearB);
			//for some reason on android copying red Uint8 in clearR,g ,b didn't work
			// direct sscsanf works though

			// clearR=ired;
			// clearG=igreen;
			// clearB=iblue;
			// LOGD(" transpColorFile  found,setting clear color %d %d %d \n",clearR,clearG,clearB );
			
			
		}else{
			LOGD(" transpColorFile not found,setting default clear color \n" );
			clearR=CL_R;
			clearG=CL_G;
			clearB=CL_B;
			
		}
		
	}

void saveTranspCol(){
	
	char path[256];
	strcpy(path,projectPath);
	// strcpy(path,"./");
	// #ifdef __ANDROID_API__
	// //overriding with android sensible default
	// strcpy(path, 
	// SDL_AndroidGetExternalStoragePath()
	// );
	// strcat(path,"/");
	// #endif
	strcat(path,"transpColor.txt");

	
	fstream fo(path,ios::out);
	char frm[4];
	sprintf(frm,"%03d",clearR);
	fo<<frm<<endl;
	sprintf(frm,"%03d",clearG);
	fo<<frm<<endl;
	sprintf(frm,"%03d",clearB);
	fo<<frm<<endl;
	
	fo.close();
	
	
}
	
	
	
	
	void readProjectPath(){
		//sensible default, will be read from file 
		strcpy(projectPath,"./");
		#ifdef __ANDROID_API__
		//overriding with android sensible default
		strcpy(projectPath, 
		SDL_AndroidGetExternalStoragePath()
		);
		// strcpy(pathAndName,"/storage/extSdCard");
		strcat(projectPath,"/");
		#endif
		LOGD("zzn default before reading redirection file %s\n",projectPath);

		
		char redirectFile[512];
		strcpy(redirectFile,projectPath);
		strcat(redirectFile,"redirect.txt");
		LOGD("zzn looking for redirect file: %s \n",redirectFile);
		ifstream myFile (
				redirectFile
				);
		char charTab[512]; 
		if (myFile.is_open()){
			LOGD("zzn redirect file open  \n");
			myFile.getline(charTab,512);
			strcpy(projectPath,charTab);	
			LOGD("project path after load: %s \n",projectPath);
		}
		
	}
	
	
	// not sure necessary
	
	//each time we commit behind paint we reinit
	void initBehind(){
		// //we use buffer surf and blit tmp on RT as usual
		// //let s try to reset buffer surf (from one call to the next there seems to be a 'memory')
		// int i,j;
		// //CVSWDTH,CVSHGTH
		// for(j=0;j<CVSHGTH;j++){
			// for(i=0;i<CVSWDTH;i++){				
					// //clear color found and alpha not 0
					// ((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+0]=0;
					// ((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+1]=0;
					// ((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+2]=0;
					// ((Uint8 *)bufferSurf->pixels)[ 4*(CVSWDTH*j+i)+3]=0;
			// }
		// }
		
		
		// //for some reason on direct 3D, on second call copy tex only gives non white areas from penultimate frame,
		// // we hijack save slot as it works fine (BROWN TAPE FIX)
		// copyTexToBufferSurf(nb_edit_slot);
		// //saveSlotToBufferSurf(nb_edit_slot);
		
		
		// //WINDOWS DEBUG
		// LOGD("ctex debug.bmp SAVE");
		// SDL_SaveBMP(
				// bufferSurf
				// ,"debug.bmp");
		
		//at this point all white is 255 on windows (patch to copytex buffer surf, and debug save is ok)
		
		// removeAllClearColorAlphaInBufferSurf();
		
		
		// loadsurftostreamingtex(
							// bufferSurf,
							// tmp,
							// true,
							// 255
			// );
			
		clearRenderTargetWithSquareEraser(pane);			
		// blittexoncleanrt(renderer,project[nb_edit_slot].tx,tmp);		
		
	}


	void allocateUndoBuf(){
		
		for(int i=0;i<undoDepth;i++){
			undoBuf[i]=createFrameTexture();
		}
		
	}
	

	void deallocateUndoBuf(){
		
		for(int i=0;i<undoDepth;i++){
			SDL_DestroyTexture(undoBuf[i]);
		}
		
	}
		
	
	//main test
	void mainloop(){
		readProjectPath();
		readTranspColor();
		
		//cjson test
		// char test[256]="{'a':1,'b':2}";
		// cJSON * root = cJSON_Parse(test);
		
		// cJSON_Delete(root);
		LOGD("zzn logcat test\n");

	col.r=DF_PT_R;
	col.g=DF_PT_G;
	col.b=DF_PT_B;


		

		
		// win=SDL_CreateWindow("hello",posx,posy,width,height,0;
		// renderer = SDL_CreateRenderer(win,-1,SDL_RENDER_ACCELERATED)
		// SDL_SetHint(SDL_HINT_RENDER_VSYNC,"1");

		//if android we get the real screen width height after
		Uint16 reqscrw=0;
		Uint16 reqscrh=0;
		//this is how we detect windows
		#ifndef __ANDROID_API__
		reqscrw=
		// SCRWDTH
		//852
		1300
		;
		reqscrh=
		700
		// SCRHGTH
		//480
		;

		#endif
		
		SDL_CreateWindowAndRenderer(
		// SCRWDTH,SCRHGTH,
		reqscrw,reqscrh,
		0, &window, &renderer) ;

		SDL_RendererInfo info;
		SDL_GetRendererInfo(renderer,&info);
		LOGD("zzn renderer : %s\n",info.name);

		SDL_GetWindowSize(window, &sw, &sh);
		LOGD("zzn real height and w %d %d \n",sh,sw);
		//canvas zoom
		zoom=((float) SCRHGTH) / ((float)CVSHGTH);
		//button zoom
		//720p should give 2
		buttonZoom=((float)sh)/((float)360);
		LOGD("zzn button zoom %f \n",buttonZoom);
	
		xorig=sw/2 - CVSWDTH*zoom /2;

	
		//TODO update origin to center display
	   cvsDispRect.w=CVSWDTH*zoom;
		cvsDispRect.h=CVSHGTH*zoom;
	   cvsDispRect.x= xorig;
	   // XORIG;
	   cvsDispRect.y=YORIG;
		
//########### BEGIN SOUND TEST
	//debug :)
	Mix_Chunk * tstsnd;
	// Mix_Chunk * soundtrack;

	
	#ifdef SOUND
	//testing sound 
	if( Mix_OpenAudio(
//			   22050
	44100
	   , MIX_DEFAULT_FORMAT, 2, 
	8192
	//2048
	//4096
	 ) == -1 ) {
		LOGD("zzn sdl mixer call failed");
	}
	tstsnd = Mix_LoadWAV( "slash.wav");
	
	// soundtrack=Mix_LoadWAV("soundtrack.wav");
	//play will be done if soundtrack is loaded successfuly 
	
	Mix_PlayChannel( -1, tstsnd, 0 );

	#endif
//##### END SOUND TEST 

//initing buffer surf with sensible default
		bufferSurf = SDL_LoadBMP(
					 "template.bmp"
		);
				
				
				
		//will be refac to use buff
		loadprojectsurfs();
		loadTimeCodes(projectPath,project);
		allocateUndoBuf();
		
		setEditSlot(nb_edit_slot);

		
		// LOGD("test %d \n",composeBrushWithAlpha(16, col, 255));
		brush=0; //for cleanup code in function below

		composeBrushInVideoMemory();
		
		
		
		composeEraser();

		activeBrush=brush;
		
		SDL_Surface * buttonsSurf = SDL_LoadBMP(
					"buttons.bmp"
		);
		buttons  = SDL_CreateTextureFromSurface(renderer, buttonsSurf);
		SDL_FreeSurface( buttonsSurf);
		


		//TO REFAC setup for paint behind mode
        pane=SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
												CVSWDTH,CVSHGTH);
		SDL_SetTextureBlendMode(pane,SDL_BLENDMODE_BLEND);
		initBehind();
		
		


		paletteSurface=SDL_LoadBMP("palette.bmp");		
		palette = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		CVSWDTH,CVSHGTH
		);
		loadsurftostreamingtex(paletteSurface,palette,false,255);


		
		//not pushing it in render gpu poc ( perf ? ) NOT WORKING RIGHT NOW
		//in case set render target clears ops?
		rendergpupoc(renderer,
		true,false);
		
		polled.quit=false;//toget in the while
		polled.pressed=false;//init 
		polled.sh=sh;
		polled.sw=sw;
		
		prevxc=-1;prevyc=-1;
		initedit();
		
		while(!
			polled.quit
		)
		{
			mode();
		}
		LOGD("zzn quitting\n");
		SDL_DestroyTexture(buttons);	
		//no need for him
		SDL_DestroyTexture(brush);
		SDL_DestroyTexture(eraser);
		SDL_DestroyTexture(roundEraser);

		//freeing real proj textures
			int i;
		// for(i=0;i<DFLT_FRAME_NMBER;i++){
			// SDL_DestroyTexture(project[i].tx);
		// }
		
		for( i= 0;i<MAX_FRAME_NMBER;i++){
			LOGD("zzn freeing tex %d  :  %d \n",i,project[i]);
			if(project[i].tx!=NULL){
				LOGD("zzn not null");
				SDL_DestroyTexture(project[i].tx);
				
			}else{
				break;
			}
			
			if(project[i].snd!=NULL){
				LOGD("freeing sound trigger for frame %d ",i);
				Mix_FreeChunk( project[i].snd );
			}
		}
		
		//the loading "buffer"
		SDL_DestroyTexture(tmp);

		SDL_DestroyTexture(palette);
		
		SDL_DestroyTexture(pane);
		
		deallocateUndoBuf();
		
		//load/ save buffer
		SDL_FreeSurface(bufferSurf);
		
		SDL_FreeSurface(paletteSurface);
		
		//for sound test

		#ifdef SOUND

		Mix_FreeChunk( tstsnd );

		//even if zeroed
		// Mix_FreeChunk( soundtrack );

		#endif
		
	}

}//ns end


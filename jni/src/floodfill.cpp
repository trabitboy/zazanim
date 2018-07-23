#include "SDL.h"
#include "stdio.h"
#include "floodfill.h"
#include "globstruct.h"
#include <queue>

#define FLOOD_DBG false
#define LFLOOD if(FLOOD_DBG)LOGD


//TODO xy struct


//declaring an arry for the pixels to color
bool floodMap[CVSWDTH*CVSHGTH];

//check floodability without recursion
bool floodability(Uint8* pixels,Uint16 x,Uint16 y, myRgba target ){
  //we check that we are still on canvas
	
  
  //if x y color != target color ret
  if(
  target.b!=(pixels)[4*(x+CVSWDTH*y)]
  ||target.g!=(pixels)[4*(x+CVSWDTH*y)+1]
  ||target.r!=(pixels)[4*(x+CVSWDTH*y)+2]
  //  &&target.a!=(pixels)[4*(x+CVSWDTH*y)+3]
     ){
    //	LOGD("zzn x y is not target color \n");
    return false;
  }

  //we need to color this
  return true;
	
}


/* change surf to pix for clarity */
void noRecFloodFill( 
Uint8 * pixels,
Uint16 x, Uint16 y,  myRgba replacecol ){
//what comes from copy tex from fb is always BGRA

	myRgba targetcol;
	//determining target
	targetcol.b=pixels[4*(x+CVSWDTH*y)];
	targetcol.g=pixels[4*(x+CVSWDTH*y)+1];
	targetcol.r=pixels[4*(x+CVSWDTH*y)+2];
	targetcol.a=pixels[4*(x+CVSWDTH*y)+3];

	LOGD("zzn about to fill color b %d g %d r %d a %d \n",targetcol.b,targetcol.g,targetcol.r,targetcol.a);
	LOGD("zzn with b %d g %d r %d a %d \n",replacecol.b,replacecol.g,replacecol.r,replacecol.a);
	LOGD("zzn at %d %d \n",x,y);
	//now calling recursion on current pixel
	//recurse((Uint8*)surf->pixels,x,y,targetcol,replacecol);

	std::queue<CanvasPoint> toTreat;

	Uint32 queueCount;
	queueCount=0;
	
	//to avoid recursion we just flag everything we need to paint in the buffer above
	Uint32 i;
	for(i=0;i<CVSHGTH*CVSWDTH;i++){
		floodMap[i]=false;
	}
	//LOGD(
	LFLOOD("FLOOD MAP FILLED \n");
	//WIP flood map doesn't solve recursion as we need a stack, we still need a stack for treated points,
	//test inclusion of sdl stack
	CanvasPoint origin;
	origin.x=x;
	origin.y=y;
	floodMap[origin.x+origin.y*CVSWDTH]=true;	
	toTreat.push(origin);
	//TODO implement queue or implement queue ( FIFO ) in c ( should be queue of coordinates)
	while(!toTreat.empty()){
	  //LOGD(
	  LFLOOD("queue count : %d \n",queueCount);
	  CanvasPoint point = toTreat.front();
	  toTreat.pop();
	  //LOGD(
	  LFLOOD("items in queue : %d \n ",toTreat.size());
	  //TODO we assume target is valid
//	  floodMap[point.x+point.y*CVSWDTH]=true;

	  //LOGD(
	  LFLOOD("about to colour %d %d \n",point.x,point.y);
  //x y color = replace
  //  LOGD("zzn replacing pixel \n");
  pixels[4*(point.x+CVSWDTH*point.y)]=replacecol.b;
  pixels[4*(point.x+CVSWDTH*point.y)+1]=replacecol.g;
  pixels[4*(point.x+CVSWDTH*point.y)+2]=replacecol.r;	
  pixels[4*(point.x+CVSWDTH*point.y)+3]=replacecol.a;
	  
	  
	  //TODO in map check
	  
	  //pb in floundability we add floodMap check
	  
	  //we check validity of cardinal points, if yes we add them to queue


	  if(point.y>0 && (!floodMap[point.x+(point.y-1)*CVSWDTH])&& floodability(pixels,point.x,point.y-1,targetcol)){
	    CanvasPoint eligible;
	    eligible.x=point.x;
	    eligible.y=point.y-1;
	    toTreat.push(eligible);
		floodMap[eligible.x+eligible.y*CVSWDTH]=true;
	  }
/*
	  */
	  if(point.y<CVSHGTH-1&& (!floodMap[(point.x)+(point.y+1)*CVSWDTH]) && floodability(pixels,point.x,(point.y+1),targetcol)){
	    CanvasPoint eligible;
	    eligible.x=point.x;
	    eligible.y=point.y+1;
	    toTreat.push(eligible);
		floodMap[eligible.x+eligible.y*CVSWDTH]=true;
	  }
	  if(point.x>0 && (!floodMap[(point.x-1)+(point.y)*CVSWDTH]) && floodability(pixels,point.x-1,point.y,targetcol)){
	    CanvasPoint eligible;
	    eligible.x=point.x-1;
	    eligible.y=point.y;
	    toTreat.push(eligible);
		floodMap[eligible.x+eligible.y*CVSWDTH]=true;
	  }
	  if(point.x<CVSWDTH-1 && (!floodMap[(point.x+1)+(point.y)*CVSWDTH]) &&  floodability(pixels,point.x+1,point.y,targetcol)){
	    CanvasPoint eligible;
	    eligible.x=point.x+1;
	    eligible.y=point.y;
	    toTreat.push(eligible);
		floodMap[eligible.x+eligible.y*CVSWDTH]=true;
	  }
	  /*
	  */
	  queueCount++;
	  
	}
	
}


//WIP NOT STABLE recursion seems to crash the app, working on alternative non recursive version
//alpha check commented, when flood filling we are not caring about light table stuff
// void recurse(Uint8 * pixels,Uint16 x,Uint16 y, myRgba target , myRgba replace){
	
  // //we check that we are still on canvas
	
  // //if x y color = replace color ret
  // if(
  // replace.b==pixels[4*(x+CVSWDTH*y)]
  // &&replace.g==(pixels)[4*(x+CVSWDTH*y)+1]
  // &&replace.r==(pixels)[4*(x+CVSWDTH*y)+2]
  // //&&replace.a==(pixels)[4*(x+CVSWDTH*y)+3]
     // ){
    // //	LOGD("zzn x y already has replace color \n");
    // return;
  // }
  
  // //if x y color != target color ret
  // if(
  // target.b!=(pixels)[4*(x+CVSWDTH*y)]
  // &&target.g!=(pixels)[4*(x+CVSWDTH*y)+1]
  // &&target.r!=(pixels)[4*(x+CVSWDTH*y)+2]
  // //  &&target.a!=(pixels)[4*(x+CVSWDTH*y)+3]
     // ){
    // //	LOGD("zzn x y is not target color \n");
    // return;
  // }

  
  // //x y color = replace
  // //  LOGD("zzn replacing pixel \n");
  // (pixels)[4*(x+CVSWDTH*y)]=replace.b;
  // (pixels)[4*(x+CVSWDTH*y)+1]=replace.g;
  // (pixels)[4*(x+CVSWDTH*y)+2]=replace.r;
  // (pixels)[4*(x+CVSWDTH*y)+3]=replace.a;


  // //recursive call n,s,e,w
// if(y>0){
  // recurse(pixels,x,y-1,target,replace);
// }
// if(y<CVSHGTH-1)
// recurse(pixels,x,y+1,target,replace);
// if(x>0){
	// recurse(pixels,x-1,y,target,replace);
// }
// if(x<CVSWDTH-1){
// recurse(pixels,x+1,y,target,replace);
// }

  
  // //return
// }


// void floodfill( SDL_Surface * surf , Uint16 x, Uint16 y,  myRgba replacecol ){
// //what comes from copy tex from fb is always BGRA

// myRgba targetcol;
// //determining target
// targetcol.b=((Uint8*)surf->pixels)[4*(x+CVSWDTH*y)];
// targetcol.g=((Uint8*)surf->pixels)[4*(x+CVSWDTH*y)+1];
// targetcol.r=((Uint8*)surf->pixels)[4*(x+CVSWDTH*y)+2];
// targetcol.a=((Uint8*)surf->pixels)[4*(x+CVSWDTH*y)+3];

// LOGD("zzn about to fill color b %d g %d r %d a %d \n",targetcol.b,targetcol.g,targetcol.r,targetcol.a);
// LOGD("zzn with b %d g %d r %d a %d \n",replacecol.b,replacecol.g,replacecol.r,replacecol.a);
// LOGD("zzn at %d %d \n",x,y);
// //now calling recursion on current pixel
// recurse((Uint8*)surf->pixels,x,y,targetcol,replacecol);

// }

#include "SDL.h"
#include "stdio.h"
#include "floodfill.h" //for types
#include "cleanartifacts.h"
#include "globstruct.h"

bool colorEq(Uint8* pixels,Uint16 x,Uint16 y, myRgba target ){
  if(
  target.b==(pixels)[4*(x+CVSWDTH*y)]
  &&target.g==(pixels)[4*(x+CVSWDTH*y)+1]
  &&target.r==(pixels)[4*(x+CVSWDTH*y)+2]
  //  &&target.a!=(pixels)[4*(x+CVSWDTH*y)+3]
     ){
    //	LOGD("zzn x y is not target color \n");
    return true;
  }

  //we need to color this
  return false;
	
}

//if all pixels around are targetcol, I am isolated and otherwritten
bool colorability(Uint8* pixels,Uint16 x,Uint16 y, myRgba target ){
  
  
  if ((x+1)<CVSWDTH){
	  if(!colorEq(pixels, x+1, y, target)){
		  //NOT surrounded by same color 
		  return false;
	  }
  } 
  
  if ((y+1)<CVSHGTH){
	  if(!colorEq(pixels, x, y+1, target)){
		  //NOT surrounded by same color 
		  return false;
	  }
  } 
  if ((x-1)>=0){
	  if(!colorEq(pixels, x-1, y, target)){
		  //NOT surrounded by same color 
		  return false;
	  }
  } 
  if ((y-1)>0){
	  if(!colorEq(pixels, x, y-1, target)){
		  //NOT surrounded by same color 
		  return false;
	  }
  } 
  

  //we need to color this,all pixels around are target col
  return true;
	
}



// void noRecCleanArtifacts( Uint8 * pixels ,  myRgba replacecol );

void noRecCleanArtifacts( 
Uint8 * pixels,
  myRgba replacecol ){

	LOGD("zzn about to clean artifacts for: b %d g %d r %d a %d \n",replacecol.b,replacecol.g,replacecol.r,replacecol.a);
	//now calling recursion on current pixel

	
  Uint16 i,j;
  for(j=0;j<CVSHGTH;j++){
  
	for(i=0;i<CVSWDTH;i++){
		if(colorability(pixels,i,j, replacecol )){
			pixels[4*(i+CVSWDTH*j)]=replacecol.b;
			pixels[4*(i+CVSWDTH*j)+1]=replacecol.g;
			pixels[4*(i+CVSWDTH*j)+2]=replacecol.r;	
			pixels[4*(i+CVSWDTH*j)+3]=replacecol.a;
		}
	}
  }
	
}





#include "SDL.h"
#include "Tex.h"
#include "globstruct.h"
#include "stdio.h"
#include <fstream>
//using std::ifstream;
//using std::fstream;
#include <iostream>
using namespace std;

//extern Tex gputransparentrtpoc::project[];





void loadTimeCodes(char * projectPath,Tex * project){

	char path[256];
	strcpy(path,projectPath);


	// char path[256];
	// strcpy(path,"./");
	// #ifdef __ANDROID_API__
	// //overriding with android sensible default
	// strcpy(path, 
	// SDL_AndroidGetExternalStoragePath()
	// );
	// strcat(path,"/");
	// #endif
	strcat(path,"timecodes.txt");


	
    char charTab[512];
	char fnb[4];
	char tc[4];
//	project[0].timecode=2;
    ifstream myFile (
    		//animFilePath
//			"timecodes.txt"
			path
    		);
	
    if (myFile.is_open()){
        while(myFile.getline(charTab,512)){
			LOGD("%s \n",charTab);
			//TODO check if file overflow
			fnb[0]=charTab[0];
			fnb[1]=charTab[1];
			fnb[2]=charTab[2];
			fnb[3]='\0';
			LOGD("%s \n",fnb);
			//TODO get 3 digits for frame number 
			//TODO do not touch delimiter
			//TODO get 3 digits for time code
			tc[0]=charTab[4];
			tc[1]=charTab[5];
			tc[2]=charTab[6];
			tc[3]='\0';
			LOGD("%s \n",tc);
			int frameNb;
			sscanf(fnb,"%d",&frameNb);
			LOGD("%d",frameNb);
			int timeCode;
			sscanf(tc,"%d",&timeCode);
			LOGD("%d",timeCode);
			//gputransparentrtpoc::
			project[frameNb].timecode=timeCode;
		}
	}else{
		LOGD("no preexisting tc file \n");
		
	}
	
}


void saveTimeCodes(char * projectPath,Tex * project , Uint16 nbFrames){
	
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
	strcat(path,"timecodes.txt");

	
	//maybe this was the cause of note 8 pb? ( the remove )
//	remove(path);
	fstream fo(path,ios::out);
	int i;
	for(i=0;i<nbFrames;i++){
		int itc = project[i].timecode;
		if(itc!=1){
			char frm[4];char tc[4];
			sprintf(frm,"%03d",i);
			sprintf(tc,"%03d",itc);
			fo<<frm<<";"<<tc<<endl;
		}
		
	}

	
	
	fo.close();
	
	
}

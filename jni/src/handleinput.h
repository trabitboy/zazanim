struct{
	
	int x;
	int y;
	bool pressed;
	bool newpress;
	bool endofpress;
	
	
	//multigesture
	
	//TODO pinch only available above threshold and if no big xy move
	bool pinch;
	float pamount;
	float pxcenter,pycenter; //0 1 range
	int xcenter,ycenter;
	bool multidrag;
	float lastpxcenter,lastpycenter;
	int lastxcenter,lastycenter;
	
	
	//keyboard ( disabled at the mo )
	bool quit;
	bool kleft;
	bool kright;
}typedef input;

void cleaninput(input *to_clean); //NOT WORKING on state change, to get rid of "ghost presses"
void handleinput(input *to_populate,bool blocking,int sw,int sh);

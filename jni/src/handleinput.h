struct{
	//hack to implement resizable screen on mobile
	//inited just one time with real screen width and height
	int sw;
	int sh; 
	
	int x;
	int y;
	bool pressed;
	bool newpress;
	bool endofpress;
	bool quit;
	bool kleft;
	bool kright;
}typedef input;

void cleaninput(input *to_clean); //NOT WORKING on state change, to get rid of "ghost presses"
void handleinput(input *to_populate,bool blocking);

struct CanvasPoint{
  Uint16 x;
  Uint16 y;

};


struct myRgba{

	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};


void noRecFloodFill( Uint8 * pixels , Uint16 x, Uint16 y, myRgba replacecol );

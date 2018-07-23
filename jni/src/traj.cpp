#include "SDL.h"
#include "stdlib.h"
#include "traj.h"
#include "globstruct.h"

//BUGGY
void calculateTraj(Blit * buf,Sint16 x1,Sint16 y1,Sint16 x2,Sint16 y2){

	if( (x1==-1 && y1==-1)
		||( INTERPOLATE == false )
	)  {
		//no interpolation needed
		//if x1 and y1 is -1, we just put last event
		buf[0].xbl=x2;
		buf[0].ybl=y2;

		// to see end of buffer
		buf[1].xbl=-1; 
		buf[1].ybl=-1; 
		return;
	}

	//otherwise, we have work todo
	if( (x1-x2)*(x1-x2) >= (y1-y2)*(y1-y2) ){
		//x projection is longer
		//we will draw a number of dot corresponding to x proj

		int dx = x2-x1; //can be negative

		int dy = y2-y1;

		int absdx = abs(dx);
		//goint through the points to generate
		int i;
		for(i=0;i<absdx;i++){
			// Point * p = new Point();
			buf[i].xbl = x1 + i*(dx)/absdx; //trick to keep sign
			buf[i].ybl = (float)y1 + ((float)i/(float)absdx)*(float)dy;
			// pointsToDraw.push_back(p);
		}
		//signalling last slot
		buf[absdx].xbl = -1;
		buf[absdx].ybl = -1;

	}else{
		//y projection is longer
		//we will draw a number of dots cor. to y proj
		int dx = x2-x1; //can be negative

		int dy = y2-y1;

		int absdy = abs(dy);
		//goint through the points to generate
		int i;
		for(i=0;i<absdy;i++){
			// Point * p = new Point();
			buf[i].ybl  = y1 + i*dy/absdy;
			buf[i].xbl  = (float)x1 + ((float)i/(float)absdy)*(float)dx;
			// pointsToDraw.push_back(p);
		}
		//signalling last slot
		buf[absdy].xbl = -1;
		buf[absdy].ybl = -1;

	}
	


}

	// Uint16 x1, y1, x2, y2;

	// x1 = p1->_x;
	// y1 = p1->_y;
	// x2 = p2->_x;
	// y2 = p2->_y;


	// vector<Point *> pointsToDraw;


	// //we determine which is eh bigest diff, x or y, it will determine the axis

	// if( (x1-x2)*(x1-x2) >= (y1-y2)*(y1-y2) ){
		// //x projection is longer
		// //we will draw a number of dot corresponding to x proj

		// int dx = x2-x1; //can be negative

		// int dy = y2-y1;

		// int absdx = abs(dx);
		// //goint through the points to generate
		// int i;
		// for(i=0;i<absdx;i++){
			// Point * p = new Point();
			// p->_x = x1 + i*(dx)/absdx; //trick to keep sign
			// p->_y = (float)y1 + ((float)i/(float)absdx)*(float)dy;
			// pointsToDraw.push_back(p);
		// }


	// }else{
		// //y projection is longer
		// //we will draw a number of dots cor. to y proj
		// int dx = x2-x1; //can be negative

		// int dy = y2-y1;

		// int absdy = abs(dy);
		// //goint through the points to generate
		// int i;
		// for(i=0;i<absdy;i++){
			// Point * p = new Point();
			// p->_y = y1 + i*dy/absdy;
			// p->_x = (float)x1 + ((float)i/(float)absdy)*(float)dx;
			// pointsToDraw.push_back(p);
		// }

	// }


	////calcul de la linge entre les 2 points consécutifs
	////x1,y1
	////
	////x2,y2
	////
	////y = a x + b
	////
	////y1 = a x1 + b
	////
	////y2 = a x2 + b
	////
	////y1 - y2  = a x1 - a x2
	////
	////a = (y1 - y2 ) / ( x1 - x2 )
	////
	////b= y1 - a x1
	////
	//// avec nos variables:
	////

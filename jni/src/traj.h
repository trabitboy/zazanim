

//we will preallocate a buffer of these
struct{
	Sint16 xbl;
	Sint16 ybl;
}typedef Blit;


//is it possible to use negative coords ? ( when stylus out of canvas )
void calculateTraj(Blit * buf,Sint16 x1,Sint16 y1,Sint16 x2,Sint16 y2);
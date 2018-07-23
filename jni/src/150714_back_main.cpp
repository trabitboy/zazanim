/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/
// #include "testrtex.h"
#include "testsimple.h"
#include "treadpix.h"
#include "testfbreadpix.h"
#include "testmodifytexture.h"
#include "testcvsalpha.h"
#include "testsw.h"
#include "gpupaintpoc.h"
#include "gpuopaquertpoc.h"
#include "gputransparentrtpoc.h"
#include "testsurfaccess.h"
#include "SDL.h"

//TODO
//do a menu for the tests,
//experiment with destroying the screen/ context and 
//recreating it


int main( int argc, char* args[] )
{
	//include test 
	// test();
	// testsimple();

	//BUTCHERED was super slow anyway
	//very slow painting exp
	// testmodifytexture();
	
	//works, however couldn't read from tex itself in gpuopaquertpoc > 
	//read pix doesn't seem to be able to target rt on dx
	// treadpix::treadpix();
	
	//fb readpixels had a pb in gles2 andro in gpuopaque rt poc : doesn't work
	// testfbreadpix::testfbreadpix();
	
	//what was this test ?
	// testcvsalpha();
	
	//soft render poc, slow ut works
	//slow painting experience
	// testswblit();
	
	//replaced by last main poc
	// gpupaintpoc();
	
	//to validate "weird" texture format
	// testsurfaccess::testsurfaccess();
	
	
	//done on an assumption that we could compose the 3 tex each time we scroll
	//downloading the work texture on each scroll is a killer ( 3s on note3 neo !!! )
	// opaqueRTPOC::gpuopaquertpoc();
	
	//TODO now that we know a RT can be transparent ( latest treadpix )
	//poc that allocates a tex for each frame as SDL_TEX_ACC_TARGET
	gputransparentrtpoc::gputransparentrtpoc();
	return 0;
}

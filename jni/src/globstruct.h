#ifdef __ANDROID_API__
#include <android/log.h>
#define  LOG_TAG    "zzn"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define XORIG 160
// #define XORIG 0
#define YORIG 0
// #define CVSWDTH 960
// #define CVSHGTH 720
#define CVSWDTH 640
#define CVSHGTH 480
// #define SCRWDTH 1280
//we redimension now
// #define SCRHGTH 720
#define SCRHGTH sh
#define SCRWDTH sw
//wip dev so disabled andro
#define INTERPOLATE true

#endif

//WINDOWS
#ifndef __ANDROID_API__
#define LOGD(...) printf(__VA_ARGS__)
#define XORIG 64
#define YORIG 0
#define CVSWDTH 640
#define CVSHGTH 480
// #define SCRWDTH 896
// #define SCRHGTH 480
#define SCRHGTH sh
#define SCRWDTH sw

#define INTERPOLATE true

#endif

//global sound switch for stability issues
//just sound output / lib , not eventual metadatas
#define SOUND true

#define ROUNDERASERHACK true

#define ALPHA_BORDER 1

//#define GLOBAL_ALPHA 128
 #define GLOBAL_ALPHA 255

// #define CL_R 0X00
// #define CL_G 0X00
// #define CL_B 0X00

// #define BEHIND false

//light table color
// #define CL_R 0XFF
// #define CL_G 0XFF
// #define CL_B 0XFF

#define CL_R 130
#define CL_G 130
#define CL_B 130


// #define DF_PT_R 255
// #define DF_PT_G 255
// #define DF_PT_B 255

#define DF_PT_R 0
#define DF_PT_G 0
#define DF_PT_B 0

#define MAX_BLITS 2000 // totally arbitrary, we should calculate

#define DFLT_FRAME_NMBER 1

#define MAX_FRAME_NMBER 500

#define PB_TIME 150 //andro test


//tex offset
#define TOFF_NXT_X 0
#define TOFF_NXT_Y 0

#define TOFF_PREV_X 0
#define TOFF_PREV_Y 64

#define TOFF_TCODE_X 64
#define TOFF_TCODE_Y 64

#define TOFF_TCODEELAPSED_X 128
#define TOFF_TCODEELAPSED_Y 64


#define TOFF_SAVE_X 0
#define TOFF_SAVE_Y 128

#define TOFF_ROUND_ERASER_X 64
#define TOFF_ROUND_ERASER_Y 128

#define TOFF_ERASER_X 0
#define TOFF_ERASER_Y 192

#define TOFF_BRUSH_X 64
#define TOFF_BRUSH_Y 192


#define TOFF_PLAY_X 0
#define TOFF_PLAY_Y 256

#define TOFF_ADD_X 0
#define TOFF_ADD_Y 320

#define TOFF_FLR_X 0
#define TOFF_FLR_Y 384
#define TOFF_FLR_W 64

#define TOFF_FLG_X 0
#define TOFF_FLG_Y 448
#define TOFF_FLG_W 64

#define TOFF_COPY_X 0
#define TOFF_COPY_Y 512
#define TOFF_COPY_W 64


#define TOFF_PASTE_X 0
#define TOFF_PASTE_Y 576
#define TOFF_PASTE_W 64

#define TOFF_SETTINGS_X 0
#define TOFF_SETTINGS_Y 640
#define TOFF_SETTINGS_W 64

#define TOFF_DELETE_X 0
#define TOFF_DELETE_Y 704
#define TOFF_DELETE_W 64

#define TOFF_FILL_X 64
#define TOFF_FILL_Y 0
#define TOFF_FILL_W 64

#define TOFF_DELETECOLOR_X 0
#define TOFF_DELETECOLOR_Y 704
#define TOFF_DELETECOLOR_W 64


#define TOFF_CB_X 0
#define TOFF_CB_Y 768
#define TOFF_CB_W 64

#define TOFF_CE_X 0
#define TOFF_CE_Y 832
#define TOFF_CE_W 64

#define TOFF_PR_X 0
#define TOFF_PR_Y 896
#define TOFF_PR_W 64

#define TOFF_PIP_X 0
#define TOFF_PIP_Y 960

#define TOFF_PP_X 0
#define TOFF_PP_Y 1024

#define TOFF_CANCEL_X 0
#define TOFF_CANCEL_Y 1088

#define TOFF_VALIDATE_X 0
#define TOFF_VALIDATE_Y 1152

#define TOFF_SCALE_X 64
#define TOFF_SCALE_Y 256

#define TOFF_SUBSELECT_X 64
#define TOFF_SUBSELECT_Y 320

#define TOFF_PALETTE_X 64
#define TOFF_PALETTE_Y 384

#define TOFF_DDP_X 64
#define TOFF_DDP_Y 448

#define TOFF_CR_X 64
#define TOFF_CR_Y 512

#define TOFF_MULTIPLE_X 64
#define TOFF_MULTIPLE_Y 576

#define TOFF_SND_X 64
#define TOFF_SND_Y 640

#define TOFF_MOVEWAV_X 64
#define TOFF_MOVEWAV_Y 704

#define TOFF_PASTEBIT_X 64
#define TOFF_PASTEBIT_Y 768

#define TOFF_CLEAR_ARTIFACTS_X 64
#define TOFF_CLEAR_ARTIFACTS_Y 832


//FOR TARGET
#define TOFF_TGTUL_X 64
#define TOFF_TGTUL_Y 1084

#define TOFF_TGTDL_X 64
#define TOFF_TGTDL_Y 1116

#define TOFF_TGTUR_X 96
#define TOFF_TGTUR_Y 1084

#define TOFF_TGTDR_X 96
#define TOFF_TGTDR_Y 1116

#define TOFF_UNDO_X 64
#define TOFF_UNDO_Y 1152


//screen pos main screen
#define BTN_BASE_W (Uint16)64*buttonZoom

#define BTN_NXT_UL_X (Uint16)(SCRWDTH - 64*buttonZoom )
#define BTN_NXT_UL_Y 0
// #define BTN_NXT_W 64	

#define BTN_PREV_UL_X 0
#define BTN_PREV_UL_Y 0
// // #define BTN_PREV_W 64	


#define BTN_FLR_UL_X (Uint16)(SCRWDTH -64*buttonZoom )
#define BTN_FLR_UL_Y (Uint16)64*buttonZoom
// #define BTN_FLR_W 64

#define BTN_SETTINGS_UL_X (Uint16)(SCRWDTH -64*buttonZoom )
#define BTN_SETTINGS_UL_Y (Uint16)128*buttonZoom
// #define BTN_SETTINGS_W 64

#define BTN_UNDO_UL_X (Uint16)(0 )
#define BTN_UNDO_UL_Y (Uint16)128*buttonZoom



#define BTN_FLG_UL_X 0
#define BTN_FLG_UL_Y (Uint16)64*buttonZoom
// #define BTN_FLG_W 64




#define BTN_PLAY_UL_X (SCRWDTH - (Uint16)64*buttonZoom )
#define BTN_PLAY_UL_Y (SCRHGTH-(Uint16)192*buttonZoom )
// // #define BTN_PLAY_W 64


#define BTN_PASTE_UL_X (SCRWDTH - (Uint16)64*buttonZoom )
#define BTN_PASTE_UL_Y (SCRHGTH - (Uint16)128*buttonZoom)
// #define BTN_PASTE_W 64
#define BTN_SAVE_UL_X (SCRWDTH - (Uint16)64*buttonZoom )
#define BTN_SAVE_UL_Y (SCRHGTH - (Uint16)64*buttonZoom)
// #define BTN_SAVE_W 64	

#define DEC_CR_UL_X (0 + (Uint16)64*buttonZoom )
#define DEC_CR_UL_Y (0 + (Uint16)64*buttonZoom)

#define DEC_SND_UL_X (0 + (Uint16)64*buttonZoom )
#define DEC_SND_UL_Y (0 + (Uint16)128*buttonZoom)


#define BTN_ERASER_UL_X 0
#define BTN_ERASER_UL_Y (SCRHGTH-(Uint16)192*buttonZoom)
// #define BTN_ERASER_W 64

#define BTN_COPY_UL_X 0
#define BTN_COPY_UL_Y (SCRHGTH - 128*buttonZoom)
// #define BTN_COPY_W 64*buttonZoom

#define BTN_ADD_UL_X 0
#define BTN_ADD_UL_Y (SCRHGTH - 64*buttonZoom)

// #define BTN_ADD_W 64

#define NB_FLICK 10

//SETTINGS SCREEN

#define SLDR_BRSH_HGHT SCRHGTH
#define SLDR_BRSH_WDTH 64*buttonZoom

#define DEL_ENABLED false

#define BTN_DELETE_UL_X (SCRWDTH - 64*buttonZoom )
#define BTN_DELETE_UL_Y (SCRHGTH - 144*buttonZoom)

#define BTN_MOVEWAV_UL_X (SCRWDTH - 64*buttonZoom )
#define BTN_MOVEWAV_UL_Y (SCRHGTH - 64*buttonZoom)


#define BTN_FILL_UL_X (192*buttonZoom )
#define BTN_FILL_UL_Y 0
// // #define BTN_DELETE_W 64

#define BTN_PIP_UL_X (128*buttonZoom )
#define BTN_PIP_UL_Y 0
// #define BTN_CB_W 64	

#define BTN_PALETTE_UL_X (64*buttonZoom )
#define BTN_PALETTE_UL_Y 0

#define BTN_DELETECOLOR_UL_X (64*buttonZoom )
#define BTN_DELETECOLOR_UL_Y (64*buttonZoom )


#define BTN_TCODE_UL_X (128*buttonZoom )
#define BTN_TCODE_UL_Y 64*buttonZoom

#define BTN_DDP_UL_X (Uint16)(128*buttonZoom )
#define BTN_DDP_UL_Y (Uint16)(SCRHGTH-64*buttonZoom)

  

#define BTN_CB_UL_X (SCRWDTH - 256*buttonZoom )
#define BTN_CB_UL_Y 0
// #define BTN_CB_W 64	

#define BTN_CE_UL_X (SCRWDTH - 192*buttonZoom )
#define BTN_CE_UL_Y 0
// #define BTN_CE_W 64	

#define BTN_PASTEBIT_UL_X (SCRWDTH - 192*buttonZoom )
#define BTN_PASTEBIT_UL_Y (SCRHGTH-64*buttonZoom)

#define BTN_CLEAR_ARTIFACTS_UL_X (SCRWDTH - 256*buttonZoom )
#define BTN_CLEAR_ARTIFACTS_UL_Y (SCRHGTH-64*buttonZoom)


#define BTN_PR_UL_X (SCRWDTH - 64*buttonZoom )
#define BTN_PR_UL_Y 0
// #define BTN_PR_W 64	

#define BTN_PP_UL_X (SCRWDTH - 64*buttonZoom )
#define BTN_PP_UL_Y buttonZoom*128

//PP STATE
#define PP_CANCEL_UL_X (SCRWDTH - 64*buttonZoom )
#define PP_CANCEL_UL_Y buttonZoom*64

#define PP_VALIDATE_UL_X (SCRWDTH - 64*buttonZoom )
#define PP_VALIDATE_UL_Y buttonZoom*128

#define PP_COPYCLIP_UL_X (SCRWDTH - 64*buttonZoom )
#define PP_COPYCLIP_UL_Y buttonZoom*192

#define PP_SCALE_UL_X (SCRWDTH - 64*buttonZoom )
#define PP_SCALE_UL_Y buttonZoom*256

//COPY CLIP STATE 
#define CC_EXIT_UL_X (SCRWDTH - 64*buttonZoom )
#define CC_EXIT_UL_Y buttonZoom*64



//time code mode
#define TC_CANCEL_UL_X (SCRWDTH - 64*buttonZoom )
#define TC_CANCEL_UL_Y buttonZoom*64

#define TC_DEFAULT_UL_X (SCRWDTH - 64*buttonZoom )
#define TC_DEFAULT_UL_Y buttonZoom*128

#define TC_MULTIPLE_UL_X (SCRWDTH - 64*buttonZoom )
#define TC_MULTIPLE_UL_Y buttonZoom*192


#define TC_CLICK_UL_X 0
#define TC_CLICK_UL_Y 0

#define TC_CLICK_W (SCRWDTH - 128*buttonZoom )


// #define CS_VALIDATE_UL_X (SCRWDTH - 64*buttonZoom )
// #define CS_VALIDATE_UL_Y buttonZoom*128


#include "SDL.h"






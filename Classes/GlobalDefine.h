#ifndef __GLOBALDEFINE_H__
#define __GLOBALDEFINE_H__

//resource paths
#define PATH_STAGE_ROOT "stage"
#define FILENAME_STAGEDEFINE "StageDef.json"
#define PATH_UI_ROOT "ui"
#define PATH_IMAGE_ROOT "image"
#define PATH_FONT_ROOT "font"


//special tags
#define TAG_PLAYERNODE 10200
#define TAG_CAMERAMOVINGACTION 90000
#define TAG_CAMERAACTOR 99900


//special z orders
#define ZORDER_ACTORLAYER 50
#define ZORDER_DEBUGLAYER 100
#define ZORDER_CAMERALAYER 999
#define ZORDER_CONTROLLERLAYER 200

//game configurations
#define GMCFG_SHOWDEBUGINFO 1
#define GMCFG_FRAMESIZE_WIDTH 1280
#define GMCFG_FRAMESIZE_HEIGHT 720
#define GMCFG_DESIGNRESOLUSION_WIDTH 2560
#define GMCFG_DESIGNRESOLUSION_HEIGHT 1440
#define GMCFG_GRAVITYCONST 0.1f
#define GMCFG_MAXBODYNUM 200
#define GMCFG_PTMRATIO 5.f


//////////////////////////////////////////////////////////////////////////
//Actor ids
#define ID_MASK 100

#define ID_CAMERA 999
#define ID_COMET 110
#define ID_METEOROLITE 120
#define ID_FIXEDSTAR 130
#define ID_PLANET 140
#define ID_BLACKHOLE 150
//////////////////////////////////////////////////////////////////////////

#endif
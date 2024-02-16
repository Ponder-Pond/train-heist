#include "ttr_01.h"

extern EvtScript N(EVS_Main);

extern char wMapHitName[0x18];
extern char wMapShapeName[0x18];
extern char wMapTexName[0x18];
extern char wMapBgName[0x18];

s32 N(map_init)(void) {
    sprintf(wMapHitName, "%s", "ttr_01_hit");
    sprintf(wMapShapeName, "%s", "ttr_01_shape");
    sprintf(wMapTexName, "%s", "ttr_tex");
    return FALSE;
}

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_THEATER)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    // Exec(N(EVS_StartTexPanners))
    Return
    End
};

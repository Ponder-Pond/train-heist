#include "ttr_01.h"

extern EvtScript N(EVS_Main);

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_THEATER)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Exec(N(EVS_StartTexPanners))
    Return
    End
};

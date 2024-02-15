#include "ttr_01.h"

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_THEATER)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Return
    End
};

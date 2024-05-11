#include "trn_01.h"

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, GEN_MAP_LOCATION)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, TRUE, Ref(N(DefaultNPCs)))
    Exec(N(EVS_StartTexPanners))
    Return
    End
};

#include "trn_01.h"
#include "common.h"
#include "world/common/atomic/TexturePan.inc.c"
#include "generated.h"

EvtScript N(EVS_StartTexPanners) = {
    Call(SetTexPanner, MODEL_Outside, TEX_PANNER_1)
    Call(EnableTexPanning, MODEL_Outside, TRUE)
    Thread
        GEN_TEX_PANNER_1
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

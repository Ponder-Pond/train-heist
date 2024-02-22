#include "battle/battle.h"
#include "mapfs/smb_bt01_shape.h"
#include "mapfs/smb_bt01_hit.h"

#define NAMESPACE A(smb_01)

#include "battle/common/stage/lib/TexturePanner.inc.c"

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    // Set(LVar0, 0x11)
    // Set(LVar1, TEX_PANNER_1)
    // Set(LVar2, -160)
    // Set(LVar3, 0)
    // Exec(N(EVS_TexturePanMain))
    // Set(LVar0, 0xF)
    // Set(LVar1, TEX_PANNER_2)
    // Set(LVar2, 0)
    // Set(LVar3, 140)
    // Exec(N(EVS_TexturePanMain))
    Return
    End
};

EvtScript N(EVS_PostBattle) = {
    Return
    End
};

s32 N(ForegroundModels)[] = {
    STAGE_MODEL_LIST_END
};

Stage NAMESPACE = {
    .texture = "smb_tex", //"aaa_tex"
    .shape = "smb_bt01_shape",
    .hit = "smb_bt01_hit",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
    .foregroundModelList = N(ForegroundModels),
};

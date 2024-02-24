#include "battle/battle.h"
#include "mapfs/smb_bt01_shape.h"
#include "mapfs/smb_bt01_hit.h"

#define NAMESPACE A(smb_00)

#include "battle/common/stage/lib/TexturePanner.inc.c"

// #include "world/common/atomic/TexturePan.inc.c"

// EvtScript N(EVS_StartTexPanners) = {
//     Call(SetTexPanner, MODEL_smb_bt01_LavaFlow, TEX_PANNER_1)
//     Call(EnableTexPanning, MODEL_smb_bt01_LavaFlow, TRUE)
//     Thread
//         TEX_PAN_PARAMS_ID(TEX_PANNER_1)
//         TEX_PAN_PARAMS_STEP(-160, 0, 0, 0)
//         TEX_PAN_PARAMS_FREQ(0, 0, 0, 0)
//         TEX_PAN_PARAMS_INIT(0, 0, 0, 0)
//         Exec(N(EVS_UpdateTexturePan))
//     EndThread
//     Call(SetTexPanner, MODEL_smb_bt01_Lava, TEX_PANNER_2)
//     Call(EnableTexPanning, MODEL_smb_bt01_Lava, TRUE)
//     Thread
//         TEX_PAN_PARAMS_ID(TEX_PANNER_2)
//         TEX_PAN_PARAMS_STEP(0, 140, 0, 0)
//         TEX_PAN_PARAMS_FREQ(0, 0, 0, 0)
//         TEX_PAN_PARAMS_INIT(0, 0, 0, 0)
//         Exec(N(EVS_UpdateTexturePan))
//     EndThread
//     Return
//     End
// };

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_smb_bt01_LavaFlow)
    Set(LVar1, TEX_PANNER_1)
    Set(LVar2, -160)
    Set(LVar3, 0)
    Exec(N(EVS_TexturePanMain))
    Set(LVar0, MODEL_smb_bt01_Lava)
    Set(LVar1, TEX_PANNER_2)
    Set(LVar2, 0)
    Set(LVar3, 140)
    Exec(N(EVS_TexturePanMain))
    // Exec(N(EVS_StartTexPanners))
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

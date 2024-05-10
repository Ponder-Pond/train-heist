#include "battle/battle.h"
#include "mapfs/trn_bt00_shape.h"
#include "mapfs/trn_bt00_hit.h"

#define NAMESPACE A(trn_00)

#include "battle/common/stage/lib/TexturePanner.inc.c"

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_Cactus)
    Set(LVar1, TEX_PANNER_0)
    Set(LVar2, 1164)
    Set(LVar3, 0)
    Exec(N(EVS_TexturePanMain))
    Set(LVar0, MODEL_MountainsShade)
    Set(LVar1, TEX_PANNER_0)
    Set(LVar2, 1164)
    Set(LVar3, 0)
    Exec(N(EVS_TexturePanMain))
    Set(LVar0, MODEL_GravelTop)
    Set(LVar1, TEX_PANNER_1)
    Set(LVar2, -8000)
    Set(LVar3, 0)
    Exec(N(EVS_TexturePanMain))
    Set(LVar0, MODEL_GravelMiddle)
    Set(LVar1, TEX_PANNER_1)
    Set(LVar2, -8000)
    Set(LVar3, 0)
    Exec(N(EVS_TexturePanMain))
    Set(LVar0, MODEL_GravelFront)
    Set(LVar1, TEX_PANNER_1)
    Set(LVar2, -8000)
    Set(LVar3, 0)
    Exec(N(EVS_TexturePanMain))
    Set(LVar0, MODEL_TrainTracksTop)
    Set(LVar1, TEX_PANNER_1)
    Set(LVar2, -8000)
    Set(LVar3, 0)
    Exec(N(EVS_TexturePanMain))
    Set(LVar0, MODEL_TrainTracksFront)
    Set(LVar1, TEX_PANNER_1)
    Set(LVar2, -8000)
    Set(LVar3, 0)
    Exec(N(EVS_TexturePanMain))
    Set(LVar0, MODEL_BrushBig)
    Set(LVar1, TEX_PANNER_1)
    Set(LVar2, -8000)
    Set(LVar3, 0)
    Exec(N(EVS_TexturePanMain))
    Set(LVar0, MODEL_Hill)
    Set(LVar1, TEX_PANNER_2)
    Set(LVar2, 2368)
    Set(LVar3, 0)
    Exec(N(EVS_TexturePanMain))
    Set(LVar0, MODEL_BrushSmall)
    Set(LVar1, TEX_PANNER_3)
    Set(LVar2, -8000)
    Set(LVar3, 0)
    Exec(N(EVS_TexturePanMain))
    Call(EnableModel, MODEL_Tunnel, FALSE)
    Call(EnableModel, MODEL_SnipingCrate, FALSE)
    Call(EnableModel, MODEL_BarrelBlack, FALSE)
    Call(EnableModel, MODEL_BombBox, FALSE)
    Call(EnableModel, MODEL_BombPile, FALSE)
    Call(EnableModel, MODEL_BarrelRed, FALSE)
    Label(0)
        Loop(0)
            Add(LVar0, 28)
            IfGt(LVar0, 359)
                Sub(LVar0, 360)
            EndIf
            Call(RotateModel, MODEL_Wheel1, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel2, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel3, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel4, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel5, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel6, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel7, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel8, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel9, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel10, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel11, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel12, LVar0, 0, 0, 1)
            Call(RotateModel, MODEL_Wheel13, LVar0, 0, 0, 1)
            Wait(1)
        EndLoop
    Goto(0)
    Label(1)
        Call(RandInt, 100, LVar9)
        Switch(LVar9)
            CaseLt(80)
                WaitSecs(1)
            CaseDefault
                Call(ShakeCam, CAM_BATTLE, 0, 1, Float(0.5))
                WaitSecs(2)
        EndSwitch
        Wait(1)
    Goto(1)
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
    .texture = "trn_tex",
    .shape = "trn_bt00_shape",
    .hit = "trn_bt00_hit",
    .bg = "trn_bg",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
    .foregroundModelList = N(ForegroundModels),
};

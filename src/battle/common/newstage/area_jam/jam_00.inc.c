#include "battle/battle.h"
#include "mapfs/jam_bt00_shape.h"
#include "mapfs/jam_bt00_hit.h"

#define NAMESPACE A(jam_00)

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_jam_bt00_Tunnel, FALSE)
    // Label(0)
    //     Loop(0)
    //         Add(LVar0, 1)
    //         IfGt(LVar0, 359)
    //             Sub(LVar0, 360)
    //         EndIf
    //         Call(RotateModel, MODEL_jam_bt00_Wheel1, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel2, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel3, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel4, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel5, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel6, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel7, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel8, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel9, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel10, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel11, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel12, LVar0, 0, 0, 1)
    //         Call(RotateModel, MODEL_jam_bt00_Wheel13, LVar0, 0, 0, 1)
    //         Wait(1)
    //     EndLoop
    // Goto(0)
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

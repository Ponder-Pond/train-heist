#include "trn_01.h"

API_CALLABLE(N(MapTransition)) {
    set_map_transition_effect(TRANSITION_BEGIN_OR_END_GAME);
    return ApiStatus_DONE2;
}

EvtScript N(EVS_EnterMap) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(trn_01_ENTRY_Scene)
            Call(N(MapTransition))
            Exec(N(EVS_Scene_BeginGame))
            Wait(5)
        CaseEq(trn_01_ENTRY_Center)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, GEN_MAP_LOCATION)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, TRUE, Ref(N(DefaultNPCs)))
    Exec(N(EVS_EnterMap))
    Exec(N(EVS_StartTexPanners))
    Exec(N(EVS_TrainBounce))
    Return
    End
};

EvtScript N(EVS_TrainBounce) = {
    Label(1)
        Call(RandInt, 100, LVar9)
        Switch(LVar9)
            CaseLt(40)
                Wait(10)
            CaseDefault
                Call(ShakeCam, CAM_DEFAULT, 0, 10, Float(0.1))
                Wait(12.5)
                Call(ShakeCam, CAM_DEFAULT, 0, 10, Float(0.1))
                Wait(12.5)
        EndSwitch
        Wait(1)
    Goto(1)
    Return
    End
};

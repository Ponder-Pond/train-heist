#include "../area.h"
#include "mapfs/trn_bt00_shape.h"
#include "sprite/npc/KoopaGang.h"
#include "sprite/npc/ShyGuyRider.h"
#include "boss.h"

#define NAMESPACE A(black_bandit_koopa)

// Black Bandit Params
enum N(ThisBanditsParams) {
    // THIS_ACTOR_ID               = ACTOR_ENEMY2,
    THIS_ACTOR_TYPE             = ACTOR_TYPE_BLACK_BANDIT,
    THIS_LEVEL                  = ACTOR_LEVEL_BLACK_BANDIT,
    THIS_SLEEP_CHANCE           = 0,
    THIS_DIZZY_CHANCE           = 0,
    THIS_PARALYZE_CHANCE        = 0,
    THIS_ANIM_IDLE              = ANIM_KoopaGang_Black_BlackIdle,
    THIS_ANIM_STILL             = ANIM_KoopaGang_Black_Still,
    THIS_ANIM_RUN               = ANIM_KoopaGang_Black_Run,
    THIS_ANIM_HURT              = ANIM_KoopaGang_Black_Hurt,
    THIS_ANIM_HURT_STILL        = ANIM_KoopaGang_Black_HurtStill,
    THIS_ANIM_TOP_ENTER_SHELL   = ANIM_KoopaGang_Black_TopEnterShell,
    THIS_ANIM_TOP_EXIT_SHELL    = ANIM_KoopaGang_Black_TopExitShell,
    THIS_ANIM_ENTER_SHELL       = ANIM_KoopaGang_Black_EnterShell,
    THIS_ANIM_EXIT_SHELL        = ANIM_KoopaGang_Black_ExitShell,
    THIS_ANIM_SHELL_SPIN        = ANIM_KoopaGang_Black_ShellSpin,
    THIS_ANIM_POINT             = ANIM_KoopaGang_Black_PointForward,
    DMG_PARABEETLE_SHOT             = 4,
};

extern s32 N(DefaultAnims)[];
extern s32 N(ParaBeetleAnims)[];
extern EvtScript N(EVS_Init);
extern EvtScript N(EVS_ManageThirdPhase);
extern EvtScript N(EVS_Idle);
extern EvtScript N(EVS_HandleEvent);
extern EvtScript N(EVS_HandlePhase);
extern EvtScript N(EVS_Defeat);
extern EvtScript N(EVS_FourthPhaseTransition);
extern EvtScript N(EVS_TakeTurn);
extern EvtScript N(EVS_Attack_SniperShot);

enum N(ActorPartIDs) {
    PRT_MAIN            = 1,
    PRT_PARABEETLE      = 2,
};

s32 N(DefaultDefense)[] = {
    ELEMENT_NORMAL,   1,
    ELEMENT_END,
};

s32 N(ToppledDefense)[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_END,
};

s32 N(StatusTable)[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,               THIS_SLEEP_CHANCE,
    STATUS_KEY_POISON,              0,
    STATUS_KEY_FROZEN,              0,
    STATUS_KEY_DIZZY,               THIS_DIZZY_CHANCE,
    STATUS_KEY_FEAR,                0,
    STATUS_KEY_STATIC,              0,
    STATUS_KEY_PARALYZE,            THIS_PARALYZE_CHANCE,
    STATUS_KEY_SHRINK,            100,
    STATUS_KEY_STOP,               75,
    STATUS_TURN_MOD_DEFAULT,        0,
    STATUS_TURN_MOD_SLEEP,         -1,
    STATUS_TURN_MOD_POISON,         0,
    STATUS_TURN_MOD_FROZEN,         0,
    STATUS_TURN_MOD_DIZZY,         -1,
    STATUS_TURN_MOD_FEAR,           0,
    STATUS_TURN_MOD_STATIC,         0,
    STATUS_TURN_MOD_PARALYZE,      -1,
    STATUS_TURN_MOD_SHRINK,        -1,
    STATUS_TURN_MOD_STOP,          -2,
    STATUS_END,
};

ActorPartBlueprint N(ActorParts)[] = {
    {
        .flags = ACTOR_PART_FLAG_PRIMARY_TARGET | ACTOR_PART_FLAG_NO_TARGET,
        .index = PRT_MAIN,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 36 },
        .opacity = 255,
        .idleAnimations = N(DefaultAnims),
        .defenseTable = N(DefaultDefense),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = PRT_PARABEETLE,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(DefaultAnims),
        .defenseTable = N(ToppledDefense),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
};

ActorBlueprint NAMESPACE = {
    .flags = 0, // ACTOR_FLAG_NO_HEALTH_BAR | ACTOR_FLAG_NO_ATTACK,
    .type = THIS_ACTOR_TYPE,
    .level = THIS_LEVEL,
    .maxHP = 1,
    .partCount = ARRAY_COUNT(N(ActorParts)),
    .partsData = N(ActorParts),
    .initScript = &N(EVS_Init),
    .statusTable = N(StatusTable),
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 70,
    .coinReward = 0,
    .size = { 38, 42 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

s32 N(DefaultAnims)[] = {
    STATUS_KEY_NORMAL,    THIS_ANIM_IDLE,
    STATUS_END,
};

s32 N(ParaBeetleAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_KoopaGang_Black_ParaBeetle,
    STATUS_END,
};

#include "common/StartRumbleWithParams.inc.c"

BSS PlayerStatus N(DummyPlayerStatus);

API_CALLABLE(N(SpawnSpinEffect)) {
    Bytecode* args = script->ptrReadPos;
    s32 posX = evt_get_variable(script, *args++);
    s32 posY = evt_get_variable(script, *args++);
    s32 posZ = evt_get_variable(script, *args++);
    s32 duration = evt_get_variable(script, *args++);

    N(DummyPlayerStatus).pos.x = posX;
    N(DummyPlayerStatus).pos.y = posY - 10.0f;
    N(DummyPlayerStatus).pos.z = posZ;

    fx_effect_46(6, &N(DummyPlayerStatus), 1.0f, duration);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(FadeScreenToBlack)) {
    if (isInitialCall) {
        script->functionTemp[1] = 0;
    }

    script->functionTemp[1] += 16;

    if (script->functionTemp[1] > 255) {
        script->functionTemp[1] = 255;
    }

    set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, script->functionTemp[1]);

    if (script->functionTemp[1] == 255) {
        return ApiStatus_DONE2;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(N(FadeScreenFromBlack)) {
    if (isInitialCall) {
        script->functionTemp[1] = 255;
    }

    script->functionTemp[1] -= 16;
    if (script->functionTemp[1] <= 0) {
        script->functionTemp[1] = 0;
        return ApiStatus_DONE2;
    }

    set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, script->functionTemp[1]);
    return ApiStatus_BLOCK;
}

EvtScript N(EVS_Init) = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(N(EVS_TakeTurn)))
    Call(BindIdle, ACTOR_SELF, Ref(N(EVS_Idle)))
    Call(BindHandleEvent, ACTOR_SELF, Ref(N(EVS_HandleEvent)))
    Call(BindHandlePhase, ACTOR_SELF, Ref(N(EVS_HandlePhase)))
    // Call(SetActorPos, ACTOR_SELF, NPC_DISPOSE_LOCATION)
    // Call(ForceHomePos, ACTOR_SELF, NPC_DISPOSE_LOCATION)
    // Call(HPBarToHome, ACTOR_SELF)
    // Call(SetPartFlagBits, ACTOR_SELF, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET, TRUE)
    // Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, TRUE)
    // Call(SetActorVar, ACTOR_SELF, AVAR_Koopa_State, AVAL_Koopa_State_Ready)
    // Call(SetActorVar, ACTOR_SELF, AVAR_Koopa_ToppleTurns, 0)
    Exec(N(EVS_ManageThirdPhase))
    Return
    End
};

EvtScript N(EVS_ManageThirdPhase) = {
    // Call(EnableModel, MODEL_SnipingCrate, TRUE)
    // Call(EnableModel, MODEL_BarrelBlack, TRUE)
    Call(N(FadeScreenFromBlack))
    Return
    End
};

EvtScript N(EVS_Idle) = {
    Return
    End
};

EvtScript N(EVS_HandlePhase) = {
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_HandleEvent) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(EVENT_HIT_COMBO)
        CaseOrEq(EVENT_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, THIS_ANIM_HURT)
            ExecWait(EVS_Enemy_Hit)
        EndCaseGroup
        CaseOrEq(EVENT_ZERO_DAMAGE)
        CaseOrEq(EVENT_IMMUNE)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, THIS_ANIM_TOP_ENTER_SHELL)
            ExecWait(EVS_Enemy_NoDamageHit)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfEq(LVar0, 0)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_TOP_EXIT_SHELL)
                Wait(10)
            EndIf
        EndCaseGroup
        CaseEq(EVENT_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, THIS_ANIM_HURT)
            ExecWait(EVS_Enemy_Hit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, THIS_ANIM_HURT)
            ExecWait(N(EVS_Defeat))
            Return
        CaseEq(EVENT_RECOVER_STATUS)
            // Call(GetActorVar, ACTOR_SELF, AVAR_Koopa_State, LVar0)
            // IfEq(LVar0, AVAL_Koopa_State_Ready)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, THIS_ANIM_IDLE)
                ExecWait(EVS_Enemy_Recover)
            // EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_Defeat) = {
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(SetActorFlagBits, ACTOR_BLACK_BANDIT, ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_HURT)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_EMOTE_IDEA)
    PlayEffect(EFFECT_EMOTE, EMOTE_EXCLAMATION, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0)
    Wait(10)
    Call(ActorExists, ACTOR_SHY_GUY_RIDER_1, LVar2)
    IfNe(LVar2, FALSE)
        Call(GetActorHP, ACTOR_SHY_GUY_RIDER_1, LVar2)
        IfNe(LVar2, 0)
            Thread
                Call(HideHealthBar, ACTOR_SHY_GUY_RIDER_1)
                Call(EnableIdleScript, ACTOR_SHY_GUY_RIDER_1, IDLE_SCRIPT_DISABLE)
                Call(UseIdleAnimation, ACTOR_SHY_GUY_RIDER_1, FALSE)
                // Call(SetAnimation, ACTOR_SHY_GUY_RIDER_1, PRT_MAIN, ANIM_ShyGuyRider_Hurt)
                Wait(10)
                // Set(LVar2, 0)
                // Loop(24)
                //     Call(SetActorYaw, ACTOR_SHY_GUY_RIDER_1, LVar2)
                //     Add(LVar2, 30)
                //     Wait(1)
                // EndLoop
                // Call(SetActorYaw, ACTOR_SHY_GUY_RIDER_1, 0)
                // Call(GetActorPos, ACTOR_SHY_GUY_RIDER_1, LVar0, LVar1, LVar2)
                // Add(LVar1, 10)
                // PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0)
                // Call(PlaySoundAtActor, ACTOR_SHY_GUY_RIDER_1, SOUND_ACTOR_DEATH)
                // Set(LVar3, 0)
                // Loop(12)
                //     Call(SetActorRotation, ACTOR_SHY_GUY_RIDER_1, LVar3, 0, 0)
                //     Add(LVar3, 8)
                //     Wait(1)
                // EndLoop
                Call(RemoveActor, ACTOR_SHY_GUY_RIDER_1)
            EndThread
        EndIf
    EndIf
    Call(ActorExists, ACTOR_SHY_GUY_RIDER_2, LVar2)
    IfNe(LVar2, FALSE)
        Call(GetActorHP, ACTOR_SHY_GUY_RIDER_2, LVar2)
        IfNe(LVar2, 0)
            Thread
                Call(HideHealthBar, ACTOR_SHY_GUY_RIDER_2)
                Call(EnableIdleScript, ACTOR_SHY_GUY_RIDER_2, IDLE_SCRIPT_DISABLE)
                Call(UseIdleAnimation, ACTOR_SHY_GUY_RIDER_2, FALSE)
                // Call(SetAnimation, ACTOR_SHY_GUY_RIDER_2, PRT_MAIN, ANIM_HammerBrosSMB3_Alt_Anim_0E)
                Wait(10)
                // Set(LVar2, 0)
                // Loop(24)
                //     Call(SetActorYaw, ACTOR_SHY_GUY_RIDER_2, LVar2)
                //     Add(LVar2, 30)
                //     Wait(1)
                // EndLoop
                // Call(SetActorYaw, ACTOR_SHY_GUY_RIDER_2, 0)
                // Call(GetActorPos, ACTOR_SHY_GUY_RIDER_2, LVar0, LVar1, LVar2)
                // Add(LVar1, 10)
                // PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0)
                // Call(PlaySoundAtActor, ACTOR_SHY_GUY_RIDER_2, SOUND_ACTOR_DEATH)
                // Set(LVar3, 0)
                // Loop(12)
                //     Call(SetActorRotation, ACTOR_SHY_GUY_RIDER_2, LVar3, 0, 0)
                //     Add(LVar3, 8)
                //     Wait(1)
                // EndLoop
                Call(RemoveActor, ACTOR_SHY_GUY_RIDER_2)
            EndThread
        EndIf
    EndIf
    SetConst(LVar0, PRT_MAIN)
    SetConst(LVar1, THIS_ANIM_HURT)
    ExecWait(EVS_Enemy_DeathWithoutRemove)
    Label(0)
        Call(ActorExists, ACTOR_SHY_GUY_RIDER_1, LVar0)
        IfNe(LVar0, FALSE)
            Wait(1)
            Goto(0)
        EndIf
        Call(ActorExists, ACTOR_SHY_GUY_RIDER_2, LVar0)
        IfNe(LVar0, FALSE)
            Wait(1)
            Goto(0)
        EndIf
    Call(RemoveActor, ACTOR_SELF)
    Call(SetBattleFlagBits, BS_FLAGS1_DISABLE_CELEBRATION | BS_FLAGS1_BATTLE_FLED, TRUE)
    Call(SetBattleFlagBits2, BS_FLAGS2_DONT_STOP_MUSIC, TRUE)
    Call(SetEndBattleFadeOutRate, 20)
    Call(N(FadeScreenToBlack))
    Return
    End
};

EvtScript N(EVS_FourthPhaseTransition) = {
    Call(CancelEnemyTurn, 1)
    Call(EnableModel, MODEL_Tunnel, TRUE)
    Set(LVar0, 0)
    Label(0)
        Set(LVar0, 0) // Reset LVar0 to 0
        Loop(0)
            Add(LVar0, 10) // Increment LVar0 by 10
            IfGt(LVar0, 1000)
                //* Models
                Call(EnableModel, MODEL_SnipingCrate, FALSE)
                Call(EnableModel, MODEL_BarrelBlack, FALSE)
                Call(EnableModel, MODEL_BombBox, TRUE)
                Call(EnableModel, MODEL_BombPile, TRUE)
                Call(EnableModel, MODEL_BarrelRed, TRUE)

                // BLACKANCHOR Actors
                Call(SetActorPos, ACTOR_BLACK_BANDIT, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_BLACK_BANDIT, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_BLACK_BANDIT, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
                Call(SetPartFlagBits, ACTOR_BLACK_BANDIT, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, TRUE)
                // Call(RemoveActor, ACTOR_BLACK_BANDIT)
                Call(SetActorPos, ACTOR_CRATE, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_CRATE, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_CRATE, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, TRUE)
                Call(SetPartFlagBits, ACTOR_CRATE, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, TRUE)
                // Call(RemoveActor, ACTOR_CRATE)
                Call(SetActorPos, ACTOR_DYANMITE_CRATE, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_DYANMITE_CRATE, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_DYANMITE_CRATE, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, TRUE)
                Call(SetPartFlagBits, ACTOR_DYANMITE_CRATE, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, TRUE)
                // Call(RemoveActor, ACTOR_DYANMITE_CRATE)
                Call(SetActorPos, ACTOR_SHY_GUY_RIDER_1, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_SHY_GUY_RIDER_1, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_SHY_GUY_RIDER_1, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, TRUE)
                Call(SetPartFlagBits, ACTOR_SHY_GUY_RIDER_1, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, TRUE)
                // Call(RemoveActor, ACTOR_SHY_GUY_RIDER_1)
                Call(SetActorPos, ACTOR_SHY_GUY_RIDER_2, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_SHY_GUY_RIDER_2, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_SHY_GUY_RIDER_2, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, TRUE)
                Call(SetPartFlagBits, ACTOR_SHY_GUY_RIDER_2, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, TRUE)

                // REDANCHOR Actors
                Call(SetActorPos, ACTOR_RED_BANDIT, 115, 25, 20)
                Call(ForceHomePos, ACTOR_RED_BANDIT, 115, 25, 20)
                Call(SetActorFlagBits, ACTOR_RED_BANDIT, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, FALSE)
                Call(SetPartFlagBits, ACTOR_RED_BANDIT, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, FALSE)
                Call(SetActorPos, ACTOR_PYRO_GUY, 145, 55, 25)
                Call(ForceHomePos, ACTOR_PYRO_GUY, 145, 55, 25)
                Call(SetActorYaw, ACTOR_PYRO_GUY, 180)
                Call(SetActorFlagBits, ACTOR_PYRO_GUY, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, FALSE)
                Call(SetPartFlagBits, ACTOR_PYRO_GUY, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, FALSE)
            EndIf
            IfGt(LVar0, 2250)
                Set(LVar0, 0) // Reset LVar0 back to 0 when it exceeds 2250
                Goto(1) // Go to Label 1 to perform additional actions
            EndIf
            Call(TranslateModel, MODEL_Tunnel, LVar0, 0, 0)
            Wait(1)
        EndLoop
    Goto(0)
    Label(1)
        Call(TranslateModel, MODEL_Tunnel, LVar0, 0, 0)
        // DebugPrintf("Transition Done!")
        Call(EnableModel, MODEL_Tunnel, FALSE)
    Return
    End
};

EvtScript N(EVS_TakeTurn) = {
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    ExecWait(N(EVS_Attack_SniperShot))
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_Attack_SniperShot) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, BTL_CAM_PRESET_15)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 25)
    Call(SetBattleCamZoom, 250)
    Thread
        Wait(20)
        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(MoveBattleCamOver, 20)
    EndThread
    // Wait(20)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KoopaGang_Black_BlackAim)
    Wait(20)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 35)
    Add(LVar1, 28)
    Add(LVar2, 5)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KoopaGang_Black_BlackFire)
    PlayEffect(EFFECT_BLAST, 0, LVar0, LVar1, LVar2, Float(0.75), 30, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, PRT_PARABEETLE, SOUND_BOMB_BLAST)
    // Wait(3)
    Call(SetPartPos, ACTOR_SELF, PRT_PARABEETLE, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, PRT_PARABEETLE, ANIM_KoopaGang_Black_ParaBeetle)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_PARABEETLE, ACTOR_PART_FLAG_INVISIBLE, FALSE)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 35)
    Add(LVar1, 28)
    Add(LVar2, 5)
    Call(SetPartPos, ACTOR_SELF, PRT_PARABEETLE, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_PARABEETLE, ACTOR_PART_FLAG_INVISIBLE, FALSE)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 4, BS_FLAGS1_TRIGGER_EVENTS)
    Switch(LVar0)
        CaseEq(HIT_RESULT_MISS)
            // Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KoopaGang_Black_BlackIdle)
            Call(PlaySoundAtPart, ACTOR_SELF, PRT_PARABEETLE, SOUND_TOSS)
            Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 120)
            Call(SetPartMoveSpeed, ACTOR_SELF, PRT_PARABEETLE, Float(12.0))
            Call(SetPartJumpGravity, ACTOR_SELF, PRT_PARABEETLE, Float(0.1))
            Call(JumpPartTo, ACTOR_SELF, PRT_PARABEETLE, LVar0, LVar1, LVar2, 0, TRUE)
            Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_MISS, 0, 0, 0)
            Call(SetPartFlagBits, ACTOR_SELF, PRT_PARABEETLE, ACTOR_PART_FLAG_INVISIBLE, TRUE)
            // Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_GeneralGuy_Anim02)
            Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
            Call(UseIdleAnimation, ACTOR_SELF, TRUE)
            Return
        CaseEq(HIT_RESULT_LUCKY)
            // Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KoopaGang_Black_BlackIdle)
            Call(PlaySoundAtPart, ACTOR_SELF, PRT_PARABEETLE, SOUND_TOSS)
            Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Set(LVar1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, PRT_PARABEETLE, Float(14.0))
            Call(SetPartJumpGravity, ACTOR_SELF, PRT_PARABEETLE, Float(0.1))
            Call(FlyPartTo, ACTOR_SELF, PRT_PARABEETLE, LVar0, LVar1, LVar2, 0, 0, EASING_COS_IN_OUT)
            Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
            Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
            Sub(LVar0, 65)
            Set(LVar1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, PRT_PARABEETLE, Float(6.0))
            Call(SetPartJumpGravity, ACTOR_SELF, PRT_PARABEETLE, Float(0.1))
            Call(FlyPartTo, ACTOR_SELF, PRT_PARABEETLE, LVar0, LVar1, LVar2, 0, 0, EASING_COS_IN_OUT)
            Call(SetPartFlagBits, ACTOR_SELF, PRT_PARABEETLE, ACTOR_PART_FLAG_INVISIBLE, TRUE)
            // Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_GeneralGuy_Anim02)
            Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
            Call(UseIdleAnimation, ACTOR_SELF, TRUE)
            Return
    EndSwitch
    // Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KoopaGang_Black_BlackIdle)
    Call(PlaySoundAtPart, ACTOR_SELF, PRT_PARABEETLE, SOUND_TOSS)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 15)
    Call(SetPartMoveSpeed, ACTOR_SELF, PRT_PARABEETLE, Float(20.0))
    Call(SetPartJumpGravity, ACTOR_SELF, PRT_PARABEETLE, Float(0.1))
    Call(FlyPartTo, ACTOR_SELF, PRT_PARABEETLE, LVar0, LVar1, LVar2, 0, 0, EASING_COS_IN_OUT)
    // Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    // Add(LVar1, 20)
    // PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0)
    // Call(PlaySoundAtPart, ACTOR_SELF, PRT_PARABEETLE, SOUND_BOMB_BLAST)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_PARABEETLE, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, DAMAGE_TYPE_NO_CONTACT, 0, 0, DMG_PARABEETLE_SHOT, BS_FLAGS1_TRIGGER_EVENTS)
    Switch(LVarF)
        CaseOrEq(HIT_RESULT_HIT)
        CaseOrEq(HIT_RESULT_NO_DAMAGE)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

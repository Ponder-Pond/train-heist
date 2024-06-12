#include "../area.h"
#include "mapfs/trn_bt00_shape.h"
#include "sprite/npc/KoopaGang.h"
#include "sprite/npc/ChainChomp.h"
#include "sprite/npc/HammerBrosSMB3.h"
#include "boss.h"

#define NAMESPACE A(yellow_bandit_koopa)

// Yellow Bandit Params
enum N(ThisBanditsParams) {
    // THIS_ACTOR_ID               = ACTOR_ENEMY0,
    THIS_ACTOR_TYPE             = ACTOR_TYPE_YELLOW_BANDIT,
    THIS_LEVEL                  = ACTOR_LEVEL_YELLOW_BANDIT,
    THIS_SLEEP_CHANCE           = 0,
    THIS_DIZZY_CHANCE           = 100,
    THIS_PARALYZE_CHANCE        = 0,
    THIS_ANIM_IDLE              = ANIM_KoopaGang_Yellow_Idle,
    THIS_ANIM_STILL             = ANIM_KoopaGang_Yellow_Still,
    THIS_ANIM_RUN               = ANIM_KoopaGang_Yellow_Run,
    THIS_ANIM_HURT              = ANIM_KoopaGang_Yellow_Hurt,
    THIS_ANIM_HURT_STILL        = ANIM_KoopaGang_Yellow_HurtStill,
    THIS_ANIM_TOP_ENTER_SHELL   = ANIM_KoopaGang_Yellow_TopEnterShell,
    THIS_ANIM_TOP_EXIT_SHELL    = ANIM_KoopaGang_Yellow_TopExitShell,
    THIS_ANIM_ENTER_SHELL       = ANIM_KoopaGang_Yellow_EnterShell,
    THIS_ANIM_EXIT_SHELL        = ANIM_KoopaGang_Yellow_ExitShell,
    THIS_ANIM_SHELL_SPIN        = ANIM_KoopaGang_Yellow_ShellSpin,
    THIS_ANIM_POINT             = ANIM_KoopaGang_Yellow_PointForward,
    ATTACK_BOOST_AMT            = 1,
    DMG_SHELL_TOSS              = 2,
};

extern s32 N(DefaultAnims)[];
extern EvtScript N(EVS_Init);
extern EvtScript N(EVS_Idle);
extern EvtScript N(EVS_HandleEvent);
extern EvtScript N(EVS_HandlePhase);
extern EvtScript N(EVS_TakeTurn);
extern EvtScript N(EVS_Defeat);
extern EvtScript N(EVS_ThirdPhaseTransition);
extern EvtScript N(EVS_Move_Cheer);
extern EvtScript N(EVS_Attack_ShellToss);

enum N(ActorPartIDs) {
    PRT_MAIN            = 1,
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
    STATUS_KEY_SHRINK,              0,
    STATUS_KEY_STOP,                0,
    STATUS_TURN_MOD_DEFAULT,        0,
    STATUS_TURN_MOD_SLEEP,          0,
    STATUS_TURN_MOD_POISON,         0,
    STATUS_TURN_MOD_FROZEN,         0,
    STATUS_TURN_MOD_DIZZY,          0,
    STATUS_TURN_MOD_FEAR,           0,
    STATUS_TURN_MOD_STATIC,         0,
    STATUS_TURN_MOD_PARALYZE,       0,
    STATUS_TURN_MOD_SHRINK,         0,
    STATUS_TURN_MOD_STOP,           0,
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
};

ActorBlueprint NAMESPACE = {
    .flags = 0, //ACTOR_FLAG_NO_HEALTH_BAR | ACTOR_FLAG_NO_ATTACK,
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
    STATUS_KEY_STONE,     THIS_ANIM_STILL,
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
    Call(N(FadeScreenFromBlack))
    Return
    End
};

EvtScript N(EVS_Idle) = {
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
    Call(SetActorFlagBits, ACTOR_YELLOW_BANDIT, ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_HURT)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_EMOTE_IDEA)
    PlayEffect(EFFECT_EMOTE, EMOTE_EXCLAMATION, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0)
    Wait(10)
    // ExecWait(N(EVS_ThirdPhaseTransition))
    Call(ActorExists, ACTOR_GIANT_CHOMP, LVar2)
    IfNe(LVar2, FALSE)
        Call(GetActorHP, ACTOR_GIANT_CHOMP, LVar2)
        IfNe(LVar2, 0)
            Thread
                Call(HideHealthBar, ACTOR_GIANT_CHOMP)
                Call(EnableIdleScript, ACTOR_GIANT_CHOMP, IDLE_SCRIPT_DISABLE)
                Call(UseIdleAnimation, ACTOR_GIANT_CHOMP, FALSE)
                Call(SetAnimation, ACTOR_GIANT_CHOMP, PRT_MAIN, ANIM_ChainChomp_Hurt)
                Wait(10)
                Set(LVar2, 0)
                Loop(24)
                    Call(SetActorYaw, ACTOR_GIANT_CHOMP, LVar2)
                    Add(LVar2, 30)
                    Wait(1)
                EndLoop
                Call(SetActorYaw, ACTOR_GIANT_CHOMP, 0)
                Call(GetActorPos, ACTOR_GIANT_CHOMP, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0)
                Call(PlaySoundAtActor, ACTOR_GIANT_CHOMP, SOUND_ACTOR_DEATH)
                Set(LVar3, 0)
                Loop(12)
                    Call(SetActorRotation, ACTOR_GIANT_CHOMP, LVar3, 0, 0)
                    Add(LVar3, 8)
                    Wait(1)
                EndLoop
                Call(RemoveActor, ACTOR_GIANT_CHOMP)
            EndThread
        EndIf
    EndIf
    Call(ActorExists, ACTOR_HAMMER_BRO_ALT, LVar2)
    IfNe(LVar2, FALSE)
        Call(GetActorHP, ACTOR_HAMMER_BRO_ALT, LVar2)
        IfNe(LVar2, 0)
            Thread
                Call(HideHealthBar, ACTOR_HAMMER_BRO_ALT)
                Call(EnableIdleScript, ACTOR_HAMMER_BRO_ALT, IDLE_SCRIPT_DISABLE)
                Call(UseIdleAnimation, ACTOR_HAMMER_BRO_ALT, FALSE)
                Call(SetAnimation, ACTOR_HAMMER_BRO_ALT, PRT_MAIN, ANIM_HammerBrosSMB3_Alt_Anim_0E)
                Wait(10)
                Set(LVar2, 0)
                Loop(24)
                    Call(SetActorYaw, ACTOR_HAMMER_BRO_ALT, LVar2)
                    Add(LVar2, 30)
                    Wait(1)
                EndLoop
                Call(SetActorYaw, ACTOR_HAMMER_BRO_ALT, 0)
                Call(GetActorPos, ACTOR_HAMMER_BRO_ALT, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0)
                Call(PlaySoundAtActor, ACTOR_HAMMER_BRO_ALT, SOUND_ACTOR_DEATH)
                Set(LVar3, 0)
                Loop(12)
                    Call(SetActorRotation, ACTOR_HAMMER_BRO_ALT, LVar3, 0, 0)
                    Add(LVar3, 8)
                    Wait(1)
                EndLoop
                Call(RemoveActor, ACTOR_HAMMER_BRO_ALT)
            EndThread
        EndIf
    EndIf
    SetConst(LVar0, PRT_MAIN)
    SetConst(LVar1, THIS_ANIM_HURT)
    ExecWait(EVS_Enemy_DeathWithoutRemove)
    Label(0)
        Call(ActorExists, ACTOR_GIANT_CHOMP, LVar0)
        IfNe(LVar0, FALSE)
            Wait(1)
            Goto(0)
        EndIf
        Call(ActorExists, ACTOR_HAMMER_BRO_ALT, LVar0)
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

EvtScript N(EVS_ThirdPhaseTransition) = {
    Call(CancelEnemyTurn, 1)
    Call(EnableModel, MODEL_Tunnel, TRUE)
    Set(LVar0, 0)
    Label(0)
        Set(LVar0, 0) // Reset LVar0 to 0
        Loop(0)
            Add(LVar0, 10) // Increment LVar0 by 10
            IfGt(LVar0, 1000)
                //* Models
                Call(EnableModel, MODEL_SnipingCrate, TRUE)
                Call(EnableModel, MODEL_BarrelBlack, TRUE)

                // YELLOWANCHOR Actors
                Call(SetActorPos, ACTOR_YELLOW_BANDIT, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_YELLOW_BANDIT, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_YELLOW_BANDIT, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
                Call(SetPartFlagBits, ACTOR_YELLOW_BANDIT, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
                Call(SetActorPos, ACTOR_GIANT_CHOMP, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_GIANT_CHOMP, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_GIANT_CHOMP, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
                Call(SetPartFlagBits, ACTOR_GIANT_CHOMP, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, TRUE)
                Call(SetPartFlagBits, ACTOR_GIANT_CHOMP, 2, ACTOR_PART_FLAG_NO_TARGET, TRUE)
                Call(SetActorPos, ACTOR_HAMMER_BRO_ALT, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_HAMMER_BRO_ALT, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_HAMMER_BRO_ALT, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
                Call(SetPartFlagBits, ACTOR_HAMMER_BRO_ALT, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)

                // BLACKANCHOR Actors
                Call(SetActorPos, ACTOR_BLACK_BANDIT, 115, 10, 20)
                Call(ForceHomePos, ACTOR_BLACK_BANDIT, 115, 10, 20)
                Call(SetActorFlagBits, ACTOR_BLACK_BANDIT, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, FALSE)
                Call(SetPartFlagBits, ACTOR_BLACK_BANDIT, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, FALSE)
                // Call(RemoveActor, ACTOR_BLACK_BANDIT)
                Call(SetActorPos, ACTOR_CRATE, 15, 0, 20)
                Call(ForceHomePos, ACTOR_CRATE, 15, 0, 20)
                Call(SetActorFlagBits, ACTOR_CRATE, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, FALSE)
                Call(SetPartFlagBits, ACTOR_CRATE, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, FALSE)
                // Call(RemoveActor, ACTOR_CRATE)
                Call(SetActorPos, ACTOR_DYANMITE_CRATE, 55, 0, 20)
                Call(ForceHomePos, ACTOR_DYANMITE_CRATE, 55, 0, 20)
                Call(SetActorFlagBits, ACTOR_DYANMITE_CRATE, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, FALSE)
                Call(SetPartFlagBits, ACTOR_DYANMITE_CRATE, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, FALSE)
                // Call(RemoveActor, ACTOR_DYANMITE_CRATE)
                Call(SetActorPos, ACTOR_SHY_GUY_RIDER_1, 45, -25, -50)
                Call(ForceHomePos, ACTOR_SHY_GUY_RIDER_1, 45, -25, -50)
                Call(SetActorFlagBits, ACTOR_SHY_GUY_RIDER_1, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, FALSE)
                Call(SetPartFlagBits, ACTOR_SHY_GUY_RIDER_1, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, FALSE)
                // Call(RemoveActor, ACTOR_SHY_GUY_RIDER_1)
                Call(SetActorPos, ACTOR_SHY_GUY_RIDER_2, -25, -25, -50)
                Call(ForceHomePos, ACTOR_SHY_GUY_RIDER_2, -25, -25, -50)
                Call(SetActorFlagBits, ACTOR_SHY_GUY_RIDER_2, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, FALSE)
                Call(SetPartFlagBits, ACTOR_SHY_GUY_RIDER_2, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, FALSE)
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
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(ActorExists, ACTOR_GIANT_CHOMP, LVar0)
    IfEq(LVar0, TRUE)
        Call(GetStatusFlags, ACTOR_GIANT_CHOMP, LVar0)
        IfNotFlag(LVar0, STATUS_FLAG_DIZZY)
            ExecWait(N(EVS_Move_Cheer))
        Else
            ExecWait(N(EVS_Attack_ShellToss))
        EndIf
    Else
        ExecWait(N(EVS_Attack_ShellToss))
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

EvtScript N(EVS_Move_Cheer) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(UseBattleCamPreset, BTL_CAM_PRESET_14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KoopaGang_Yellow_ThumbsUp)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 7)
    Add(LVar1, 28)
    Add(LVar2, 5)
    PlayEffect(EFFECT_LENS_FLARE, 0, LVar0, LVar1, LVar2, 30, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SMALL_LENS_FLARE)
    Wait(30)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, ACTOR_HAMMER_BRO_ALT, SOUND_MAGIKOOPA_POWER_UP)
    EndThread
    Thread
        Call(FreezeBattleState, TRUE)
        Call(BoostAttack, ACTOR_HAMMER_BRO_ALT, ATTACK_BOOST_AMT, FALSE)
        Call(FreezeBattleState, FALSE)
    EndThread
    Call(WaitForBuffDone)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_IDLE)
    Wait(5)
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(YieldTurn)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

EvtScript N(EVS_Attack_ShellToss) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SMALL_LENS_FLARE)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_POINT)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 22)
    Add(LVar1, 19)
    PlayEffect(EFFECT_LENS_FLARE, 0, LVar0, LVar1, LVar2, 30, 0)
    Wait(30)
    Call(GetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar2, 15)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_RUN)
    Call(RunToGoal, ACTOR_SELF, 10, FALSE)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_ENTER_SHELL)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_KOOPA_BROS_SPINUP)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_SHELL_SPIN)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(N(SpawnSpinEffect), LVar0, LVar1, LVar2, 30)
    Wait(30)
    Thread
        Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_IGNORE_DEFENSE, 0, 0, BS_FLAGS1_INCLUDE_POWER_UPS)
        Switch(LVar0)
            CaseEq(HIT_RESULT_LUCKY)
                Wait(20)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
                Return
            CaseEq(HIT_RESULT_MISS)
                Return
        EndSwitch
        Label(0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetActorPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
        IfGt(LVar0, LVar3)
            Wait(1)
            Goto(0)
        EndIf
        Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, SUPPRESS_EVENT_ALL, 0, DMG_SHELL_TOSS, BS_FLAGS1_TRIGGER_EVENTS)
    EndThread
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_KOOPA_LAUNCH_SHELL)
    Call(SetActorSounds, ACTOR_SELF, ACTOR_SOUND_WALK, SOUND_NONE, SOUND_NONE)
    Call(EnableActorBlur, ACTOR_SELF, ACTOR_BLUR_ENABLE)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, FALSE)
    Call(ResetActorSounds, ACTOR_SELF, ACTOR_SOUND_WALK)
    Call(EnableActorBlur, ACTOR_SELF, ACTOR_BLUR_DISABLE)
    Thread
        Call(SetPartRotationOffset, ACTOR_SELF, PRT_MAIN, 0, 15, 0)
        Set(LVar0, 0)
        Loop(40)
            Sub(LVar0, 45)
            Call(SetPartRotation, ACTOR_SELF, PRT_MAIN, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetPartRotationOffset, ACTOR_SELF, PRT_MAIN, 0, 0, 0)
        Call(SetPartRotation, ACTOR_SELF, PRT_MAIN, 0, 0, 0)
    EndThread
    Call(GetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar2, 15)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
    Call(JumpToGoal, ACTOR_SELF, 40, FALSE, TRUE, FALSE)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(N(SpawnSpinEffect), LVar0, LVar1, LVar2, 30)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_TOP_EXIT_SHELL)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, ANIM_KoopaGang_Yellow_ThumbsUp)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 7)
    Add(LVar1, 28)
    Add(LVar2, 5)
    PlayEffect(EFFECT_LENS_FLARE, 0, LVar0, LVar1, LVar2, 30, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SMALL_LENS_FLARE)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_RUN)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(RunToGoal, ACTOR_SELF, 10, FALSE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

EvtScript N(EVS_HandlePhase) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

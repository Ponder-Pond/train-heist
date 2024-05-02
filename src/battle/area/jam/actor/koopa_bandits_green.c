#include "../area.h"
#include "mapfs/jam_bt00_shape.h"
#include "sprite/npc/KoopaGang.h"
#include "boss.h"
#include "dx/debug_menu.h"

#define NAMESPACE A(green_bandit_koopa)

// Green Bandit Params
enum N(ThisBanditsParams) {
    // THIS_ACTOR_ID               = ACTOR_ENEMY0,
    THIS_ACTOR_TYPE             = ACTOR_TYPE_GREEN_BANDIT,
    THIS_LEVEL                  = ACTOR_LEVEL_GREEN_BANDIT,
    THIS_SLEEP_CHANCE           = 0,
    THIS_DIZZY_CHANCE           = 0,
    THIS_PARALYZE_CHANCE        = 0,
    THIS_ANIM_IDLE              = ANIM_KoopaGang_Green_CannonSit,
    THIS_ANIM_STILL             = ANIM_KoopaGang_Green_Still,
    THIS_ANIM_SLEEP             = ANIM_KoopaGang_Green_Sleep,
    THIS_ANIM_DIZZY             = ANIM_KoopaGang_Green_Dizzy,
    THIS_ANIM_RUN               = ANIM_KoopaGang_Green_Run,
    THIS_ANIM_HURT              = ANIM_KoopaGang_Green_Hurt,
    THIS_ANIM_HURT_STILL        = ANIM_KoopaGang_Green_HurtStill,
    THIS_ANIM_BURN              = ANIM_KoopaGang_Green_BurnHurt,
    THIS_ANIM_BURN_STILL        = ANIM_KoopaGang_Green_BurnStill,
    THIS_ANIM_TOWER_IDLE        = ANIM_KoopaGang_Green_IdleCrouch,
    THIS_ANIM_TOWER_STILL       = ANIM_KoopaGang_Green_StillCrouch,
    THIS_ANIM_TOPPLE_IDLE       = ANIM_KoopaGang_Green_IdleToppled,
    THIS_ANIM_TOPPLE_STILL      = ANIM_KoopaGang_Green_StillToppled,
    THIS_ANIM_TOPPLE_DIZZY      = ANIM_KoopaGang_Green_DizzyToppled,
    THIS_ANIM_TIPPING_IDLE      = ANIM_KoopaGang_Green_IdleTipping,
    THIS_ANIM_TOP_ENTER_SHELL   = ANIM_KoopaGang_Green_TopEnterShell,
    THIS_ANIM_TOP_EXIT_SHELL    = ANIM_KoopaGang_Green_TopExitShell,
    THIS_ANIM_ENTER_SHELL       = ANIM_KoopaGang_Green_EnterShell,
    THIS_ANIM_EXIT_SHELL        = ANIM_KoopaGang_Green_ExitShell,
    THIS_ANIM_SHELL_SPIN        = ANIM_KoopaGang_Green_ShellSpin,
    THIS_ANIM_POINT             = ANIM_KoopaGang_Green_PointForward,
};

extern s32 N(DefaultAnims)[];
extern s32 N(CannonAnims)[];
extern s32 N(CannonSlowAnims)[];
extern EvtScript N(EVS_Init);
extern EvtScript N(EVS_Idle);
extern EvtScript N(EVS_HandleEvent);
extern EvtScript N(EVS_HandlePhase);
extern EvtScript N(EVS_TakeTurn);
extern EvtScript N(EVS_ManageFirstPhase);
extern EvtScript N(EVS_Defeat);
extern EvtScript N(EVS_SecondPhaseTransition);

enum N(ActorPartIDs) {
    PRT_MAIN            = 1,
    PRT_CANNON          = 2,
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
        .flags = ACTOR_PART_FLAG_PRIMARY_TARGET,
        .index = PRT_MAIN,
        .posOffset = { -10, 40, 0 },
        .targetOffset = { -5, 36 },
        .opacity = 255,
        .idleAnimations = N(DefaultAnims),
        .defenseTable = N(DefaultDefense),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_NO_TARGET,
        .index = PRT_CANNON,
        .posOffset = { -15, 0, 1 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(CannonAnims),
        .defenseTable = N(DefaultDefense),
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
    STATUS_KEY_STONE,     THIS_ANIM_STILL,
    STATUS_KEY_SLEEP,     THIS_ANIM_SLEEP,
    STATUS_KEY_POISON,    THIS_ANIM_STILL,
    STATUS_KEY_STOP,      THIS_ANIM_STILL,
    STATUS_KEY_STATIC,    THIS_ANIM_STILL,
    STATUS_KEY_PARALYZE,  THIS_ANIM_STILL,
    STATUS_KEY_PARALYZE,  THIS_ANIM_STILL,
    STATUS_KEY_DIZZY,     THIS_ANIM_DIZZY,
    STATUS_KEY_DIZZY,     THIS_ANIM_DIZZY,
    STATUS_END,
};

s32 N(CannonAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_KoopaGang_Green_CannonIdle,
    STATUS_END,
};

s32 N(CannonSlowAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_KoopaGang_Green_CannonIdleSlow,
    STATUS_END,
};

// s32 N(TowerAnims)[] = {
//     STATUS_KEY_NORMAL,    THIS_ANIM_TOWER_IDLE,
//     STATUS_KEY_STONE,     THIS_ANIM_TOWER_STILL,
//     STATUS_KEY_POISON,    THIS_ANIM_TOWER_STILL,
//     STATUS_KEY_STOP,      THIS_ANIM_TOWER_STILL,
//     STATUS_KEY_STATIC,    THIS_ANIM_TOWER_STILL,
//     STATUS_KEY_PARALYZE,  THIS_ANIM_TOWER_STILL,
//     STATUS_KEY_PARALYZE,  THIS_ANIM_TOWER_STILL,
//     STATUS_END,
// };

// s32 N(TippingAnims)[] = {
//     STATUS_KEY_NORMAL,    THIS_ANIM_TIPPING_IDLE,
//     STATUS_KEY_STONE,     THIS_ANIM_TOWER_STILL,
//     STATUS_KEY_POISON,    THIS_ANIM_TOWER_STILL,
//     STATUS_KEY_STOP,      THIS_ANIM_TOWER_STILL,
//     STATUS_KEY_STATIC,    THIS_ANIM_TOWER_STILL,
//     STATUS_KEY_PARALYZE,  THIS_ANIM_TOWER_STILL,
//     STATUS_KEY_PARALYZE,  THIS_ANIM_TOWER_STILL,
//     STATUS_END,
// };

// s32 N(ToppledAnims)[] = {
//     STATUS_KEY_NORMAL,    THIS_ANIM_TOPPLE_IDLE,
//     STATUS_KEY_STONE,     THIS_ANIM_TOPPLE_STILL,
//     STATUS_KEY_SLEEP,     THIS_ANIM_TOPPLE_STILL,
//     STATUS_KEY_POISON,    THIS_ANIM_TOPPLE_STILL,
//     STATUS_KEY_STOP,      THIS_ANIM_TOPPLE_STILL,
//     STATUS_KEY_STATIC,    THIS_ANIM_TOPPLE_STILL,
//     STATUS_KEY_PARALYZE,  THIS_ANIM_TOPPLE_STILL,
//     STATUS_KEY_PARALYZE,  THIS_ANIM_TOPPLE_STILL,
//     STATUS_KEY_DIZZY,     THIS_ANIM_TOPPLE_DIZZY,
//     STATUS_KEY_DIZZY,     THIS_ANIM_TOPPLE_DIZZY,
//     STATUS_END,
// };

s32 N(BasicHurtAnims)[] = {
    STATUS_KEY_NORMAL,    THIS_ANIM_HURT_STILL,
    STATUS_END,
};

s32 N(BasicToppledAnims)[] = {
    STATUS_KEY_NORMAL,    THIS_ANIM_TOPPLE_IDLE,
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

EvtScript N(EVS_Init) = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(N(EVS_TakeTurn)))
    Call(BindIdle, ACTOR_SELF, Ref(N(EVS_Idle)))
    Call(BindHandleEvent, ACTOR_SELF, Ref(N(EVS_HandleEvent)))
    Call(BindHandlePhase, ACTOR_SELF, Ref(N(EVS_HandlePhase)))
    // Call(SetActorPos, ACTOR_SELF, NPC_DISPOSE_LOCATION)
    // Call(ForceHomePos, ACTOR_SELF, NPC_DISPOSE_LOCATION)
    // Call(HPBarToHome, ACTOR_SELF)
    // Call(SetPartFlagBits, ACTOR_SELF, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET, TRUE)
    Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, TRUE)
    // Call(SetActorVar, ACTOR_SELF, AVAR_Koopa_State, AVAL_Koopa_State_Ready)
    // Call(SetActorVar, ACTOR_SELF, AVAR_Koopa_ToppleTurns, 0)
    Exec(N(EVS_ManageFirstPhase))
    Return
    End
};

EvtScript N(EVS_ManageFirstPhase) = {
    Call(EnableModel, MODEL_jam_bt00_BombBox, TRUE)
    // Yellow Phase Actors
    Call(SetActorFlagBits, ACTOR_YELLOW_BANDIT, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
    Call(SetPartFlagBits, ACTOR_YELLOW_BANDIT, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(SetActorFlagBits, ACTOR_GIANT_CHOMP, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
    Call(SetPartFlagBits, ACTOR_GIANT_CHOMP, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(SetPartFlagBits, ACTOR_GIANT_CHOMP, 2, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(SetActorFlagBits, ACTOR_HAMMER_BRO, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
    Call(SetPartFlagBits, ACTOR_HAMMER_BRO, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
    // Black Phase Actors
    Call(SetActorFlagBits, ACTOR_BLACK_BANDIT, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
    Call(SetPartFlagBits, ACTOR_BLACK_BANDIT, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(SetActorFlagBits, ACTOR_CRATE, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, TRUE)
    Call(SetPartFlagBits, ACTOR_CRATE, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(SetActorFlagBits, ACTOR_DYANMITE_CRATE, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, TRUE)
    Call(SetPartFlagBits, ACTOR_DYANMITE_CRATE, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(SetActorFlagBits, ACTOR_SHY_GUY_RIDER_1, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, TRUE)
    Call(SetPartFlagBits, ACTOR_SHY_GUY_RIDER_1, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(SetActorFlagBits, ACTOR_SHY_GUY_RIDER_2, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, TRUE)
    Call(SetPartFlagBits, ACTOR_SHY_GUY_RIDER_2, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    // Red Phase Actors
    Call(SetActorFlagBits, ACTOR_RED_BANDIT, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
    Call(SetPartFlagBits, ACTOR_RED_BANDIT, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(SetActorFlagBits, ACTOR_PYRO_GUY, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
    Call(SetPartFlagBits, ACTOR_PYRO_GUY, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
    // Bowser Phase Actors

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
        CaseEq(EVENT_BURN_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, THIS_ANIM_BURN)
            SetConst(LVar2, THIS_ANIM_BURN_STILL)
            ExecWait(EVS_Enemy_BurnHit)
        CaseEq(EVENT_BURN_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, THIS_ANIM_BURN)
            SetConst(LVar2, THIS_ANIM_BURN_STILL)
            ExecWait(EVS_Enemy_BurnHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, THIS_ANIM_BURN_STILL)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_SPIN_SMASH_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, THIS_ANIM_HURT)
            ExecWait(EVS_Enemy_SpinSmashHit)
        CaseEq(EVENT_SPIN_SMASH_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, THIS_ANIM_HURT)
            ExecWait(EVS_Enemy_SpinSmashHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, THIS_ANIM_HURT)
            ExecWait(EVS_Enemy_Death)
            Return
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
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, THIS_ANIM_TOPPLE_IDLE)
            ExecWait(EVS_Enemy_NoDamageHit)
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
    Call(SetActorFlagBits, ACTOR_GREEN_BANDIT, ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_HURT)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    //Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_EMOTE_IDEA)
    PlayEffect(EFFECT_EMOTE, EMOTE_EXCLAMATION, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0)
    Wait(10)
    ExecWait(N(EVS_SecondPhaseTransition))
    Return
    End
};

EvtScript N(EVS_SecondPhaseTransition) = {
    Call(CancelEnemyTurn, 1)
    Call(EnableModel, MODEL_jam_bt00_Tunnel, TRUE)
    Set(LVar0, 0)
    Label(0)
        Set(LVar0, 0) // Reset LVar0 to 0
        Loop(0)
            Add(LVar0, 10) // Increment LVar0 by 10
            IfGt(LVar0, 1000)
                Call(EnableModel, MODEL_jam_bt00_BombBox, FALSE)
                Call(SetActorPos, ACTOR_GREEN_BANDIT, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_GREEN_BANDIT, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_GREEN_BANDIT, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
                Call(SetPartFlagBits, ACTOR_GREEN_BANDIT, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
                Call(SetActorPos, ACTOR_BUZZY_BEETLE, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_BUZZY_BEETLE, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_BUZZY_BEETLE, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
                Call(SetPartFlagBits, ACTOR_BUZZY_BEETLE, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
                Call(SetActorPos, ACTOR_HOWITZER_HAL, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_HOWITZER_HAL, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_HOWITZER_HAL, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
                Call(SetPartFlagBits, ACTOR_HOWITZER_HAL, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
                Call(SetActorPos, ACTOR_BRIGADER_BONES, NPC_DISPOSE_LOCATION)
                Call(ForceHomePos, ACTOR_BRIGADER_BONES, NPC_DISPOSE_LOCATION)
                Call(SetActorFlagBits, ACTOR_BRIGADER_BONES, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
                Call(SetPartFlagBits, ACTOR_BRIGADER_BONES, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
                Call(SetActorPos, ACTOR_YELLOW_BANDIT, 105, 0, 10)
                Call(ForceHomePos, ACTOR_YELLOW_BANDIT, 105, 0, 10)
                Call(SetActorFlagBits, ACTOR_YELLOW_BANDIT, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, FALSE)
                Call(SetPartFlagBits, ACTOR_YELLOW_BANDIT, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, FALSE)
                Call(SetActorPos, ACTOR_GIANT_CHOMP, 25, 0, 10)
                Call(ForceHomePos, ACTOR_GIANT_CHOMP, 25, 0, 10)
                Call(SetActorFlagBits, ACTOR_GIANT_CHOMP, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, FALSE)
                Call(SetPartFlagBits, ACTOR_GIANT_CHOMP, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE, FALSE)
                Call(SetPartFlagBits, ACTOR_GIANT_CHOMP, 2, ACTOR_PART_FLAG_NO_TARGET, FALSE)
                Call(SetActorPos, ACTOR_HAMMER_BRO, 145, 0, 10)
                Call(ForceHomePos, ACTOR_HAMMER_BRO, 145, 0, 10)
                Call(SetActorFlagBits, ACTOR_HAMMER_BRO, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, FALSE)
                Call(SetPartFlagBits, ACTOR_HAMMER_BRO, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, FALSE)
            EndIf
            IfGt(LVar0, 2250)
                Set(LVar0, 0) // Reset LVar0 back to 0 when it exceeds 2250
                Goto(1) // Go to Label 1 to perform additional actions
            EndIf
            Call(TranslateModel, MODEL_jam_bt00_Tunnel, LVar0, 0, 0)
            Wait(1)
        EndLoop
    Goto(0)
    Label(1)
        Call(TranslateModel, MODEL_jam_bt00_Tunnel, LVar0, 0, 0)
        DebugPrintf("Transition Done!")
        Call(EnableModel, MODEL_jam_bt00_Tunnel, FALSE)
    Return
    End
};

EvtScript N(EVS_TakeTurn) = {
    Return
    End
};

EvtScript N(EVS_HandlePhase) = {
    Return
    End
};

#include "../area.h"
#include "sprite/npc/KoopaGang.h"

#define NAMESPACE A(black_bandit_koopa)

// Black Bandit Params
enum N(ThisBanditsParams) {
    // THIS_ACTOR_ID               = ACTOR_ENEMY2,
    THIS_ACTOR_TYPE             = ACTOR_TYPE_BLACK_BANDIT,
    THIS_LEVEL                  = ACTOR_LEVEL_BLACK_BANDIT,
    THIS_SLEEP_CHANCE           = 0,
    THIS_DIZZY_CHANCE           = 0,
    THIS_PARALYZE_CHANCE        = 0,
    THIS_ANIM_IDLE              = ANIM_KoopaGang_Black_Idle,
    THIS_ANIM_STILL             = ANIM_KoopaGang_Black_Still,
    THIS_ANIM_SLEEP             = ANIM_KoopaGang_Black_Sleep,
    THIS_ANIM_DIZZY             = ANIM_KoopaGang_Black_Dizzy,
    THIS_ANIM_RUN               = ANIM_KoopaGang_Black_Run,
    THIS_ANIM_HURT              = ANIM_KoopaGang_Black_Hurt,
    THIS_ANIM_HURT_STILL        = ANIM_KoopaGang_Black_HurtStill,
    THIS_ANIM_BURN              = ANIM_KoopaGang_Black_BurnHurt,
    THIS_ANIM_BURN_STILL        = ANIM_KoopaGang_Black_BurnStill,
    THIS_ANIM_TOWER_IDLE        = ANIM_KoopaGang_Black_IdleCrouch,
    THIS_ANIM_TOWER_STILL       = ANIM_KoopaGang_Black_StillCrouch,
    THIS_ANIM_TOPPLE_IDLE       = ANIM_KoopaGang_Black_IdleToppled,
    THIS_ANIM_TOPPLE_STILL      = ANIM_KoopaGang_Black_StillToppled,
    THIS_ANIM_TOPPLE_DIZZY      = ANIM_KoopaGang_Black_DizzyToppled,
    THIS_ANIM_TIPPING_IDLE      = ANIM_KoopaGang_Black_IdleTipping,
    THIS_ANIM_TOP_ENTER_SHELL   = ANIM_KoopaGang_Black_TopEnterShell,
    THIS_ANIM_TOP_EXIT_SHELL    = ANIM_KoopaGang_Black_TopExitShell,
    THIS_ANIM_ENTER_SHELL       = ANIM_KoopaGang_Black_EnterShell,
    THIS_ANIM_EXIT_SHELL        = ANIM_KoopaGang_Black_ExitShell,
    THIS_ANIM_SHELL_SPIN        = ANIM_KoopaGang_Black_ShellSpin,
    THIS_ANIM_POINT             = ANIM_KoopaGang_Black_PointForward,
};

extern s32 N(DefaultAnims)[];
extern EvtScript N(EVS_Init);
extern EvtScript N(EVS_Idle);
extern EvtScript N(EVS_HandleEvent);
extern EvtScript N(EVS_HandlePhase);
extern EvtScript N(EVS_TakeTurn);

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
};

ActorBlueprint NAMESPACE = {
    .flags = 0, // ACTOR_FLAG_NO_HEALTH_BAR | ACTOR_FLAG_NO_ATTACK,
    .type = THIS_ACTOR_TYPE,
    .level = THIS_LEVEL,
    .maxHP = 15,
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

s32 N(TowerAnims)[] = {
    STATUS_KEY_NORMAL,    THIS_ANIM_TOWER_IDLE,
    STATUS_KEY_STONE,     THIS_ANIM_TOWER_STILL,
    STATUS_KEY_POISON,    THIS_ANIM_TOWER_STILL,
    STATUS_KEY_STOP,      THIS_ANIM_TOWER_STILL,
    STATUS_KEY_STATIC,    THIS_ANIM_TOWER_STILL,
    STATUS_KEY_PARALYZE,  THIS_ANIM_TOWER_STILL,
    STATUS_KEY_PARALYZE,  THIS_ANIM_TOWER_STILL,
    STATUS_END,
};

s32 N(TippingAnims)[] = {
    STATUS_KEY_NORMAL,    THIS_ANIM_TIPPING_IDLE,
    STATUS_KEY_STONE,     THIS_ANIM_TOWER_STILL,
    STATUS_KEY_POISON,    THIS_ANIM_TOWER_STILL,
    STATUS_KEY_STOP,      THIS_ANIM_TOWER_STILL,
    STATUS_KEY_STATIC,    THIS_ANIM_TOWER_STILL,
    STATUS_KEY_PARALYZE,  THIS_ANIM_TOWER_STILL,
    STATUS_KEY_PARALYZE,  THIS_ANIM_TOWER_STILL,
    STATUS_END,
};

s32 N(ToppledAnims)[] = {
    STATUS_KEY_NORMAL,    THIS_ANIM_TOPPLE_IDLE,
    STATUS_KEY_STONE,     THIS_ANIM_TOPPLE_STILL,
    STATUS_KEY_SLEEP,     THIS_ANIM_TOPPLE_STILL,
    STATUS_KEY_POISON,    THIS_ANIM_TOPPLE_STILL,
    STATUS_KEY_STOP,      THIS_ANIM_TOPPLE_STILL,
    STATUS_KEY_STATIC,    THIS_ANIM_TOPPLE_STILL,
    STATUS_KEY_PARALYZE,  THIS_ANIM_TOPPLE_STILL,
    STATUS_KEY_PARALYZE,  THIS_ANIM_TOPPLE_STILL,
    STATUS_KEY_DIZZY,     THIS_ANIM_TOPPLE_DIZZY,
    STATUS_KEY_DIZZY,     THIS_ANIM_TOPPLE_DIZZY,
    STATUS_END,
};

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
    // Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, TRUE)
    // Call(SetActorVar, ACTOR_SELF, AVAR_Koopa_State, AVAL_Koopa_State_Ready)
    // Call(SetActorVar, ACTOR_SELF, AVAR_Koopa_ToppleTurns, 0)
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
            ExecWait(EVS_Enemy_Death)
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

EvtScript N(EVS_TakeTurn) = {
    Return
    End
};

EvtScript N(EVS_HandlePhase) = {
    Return
    End
};

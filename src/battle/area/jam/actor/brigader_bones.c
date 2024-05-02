#include "../area.h"
#include "sprite/npc/BrigaderBones.h"
#include "boss.h"
#include "dx/debug_menu.h"

#define NAMESPACE A(brigader_bones)

extern EvtScript N(EVS_Init);
extern EvtScript N(EVS_Idle);
extern EvtScript N(EVS_TakeTurn);
extern EvtScript N(EVS_HandleEvent);
extern EvtScript N(EVS_HandlePhase);
extern EvtScript N(EVS_Move_Command);

enum N(ActorPartIDs) {
    PRT_MAIN        = 1,
};

enum N(ActorVars) {
    AVAR_CollapseTurns     = 0,
    AVAL_CollapseTurnZero  = 0,
    AVAL_CollapseTurnOne   = 1,
    AVAL_CollapseTurnTwo   = 2,
    AVAR_Collapsed         = 2,
};

#define BASE_COLLAPSE_DURATION  2

s32 N(DefaultAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_BrigaderBones_Idle,
    STATUS_KEY_STONE,     ANIM_BrigaderBones_Still,
    STATUS_KEY_POISON,    ANIM_BrigaderBones_Idle,
    STATUS_KEY_STOP,      ANIM_BrigaderBones_Still,
    STATUS_KEY_STATIC,    ANIM_BrigaderBones_Idle,
    STATUS_KEY_PARALYZE,  ANIM_BrigaderBones_Still,
    STATUS_END,
};

s32 N(CollapsedAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_BrigaderBones_StillDead,
    STATUS_END,
};

s32 N(DefenseTable)[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_END,
};

s32 N(CollapsedDefense)[] = {
    ELEMENT_NORMAL,  99,
    ELEMENT_END,
};

s32 N(StatusTable)[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,               0,
    STATUS_KEY_POISON,              0,
    STATUS_KEY_FROZEN,              0,
    STATUS_KEY_DIZZY,               0,
    STATUS_KEY_FEAR,                0,
    STATUS_KEY_STATIC,              0,
    STATUS_KEY_PARALYZE,            0,
    STATUS_KEY_SHRINK,            100,
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
    STATUS_TURN_MOD_STOP,          -1,
    STATUS_END,
};

s32 N(CollapsedStatusTable)[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,               0,
    STATUS_KEY_POISON,              0,
    STATUS_KEY_FROZEN,              0,
    STATUS_KEY_DIZZY,               0,
    STATUS_KEY_FEAR,                0,
    STATUS_KEY_STATIC,              0,
    STATUS_KEY_PARALYZE,            0,
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
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -8, 30 },
        .opacity = 255,
        .idleAnimations = N(DefaultAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { -1, -10 },
    },
};

ActorBlueprint NAMESPACE = {
    .flags = ACTOR_FLAG_NO_HEALTH_BAR,
    .type = ACTOR_TYPE_DRY_BONES,
    .level = 0,
    .maxHP = 1,
    .partCount = ARRAY_COUNT(N(ActorParts)),
    .partsData = N(ActorParts),
    .initScript = &N(EVS_Init),
    .statusTable = N(StatusTable),
    .escapeChance = 50,
    .airLiftChance = 75,
    .hurricaneChance = 70,
    .spookChance = 10,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 1,
    .size = { 28, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 15 },
    .statusTextOffset = { 3, 27 },
};

EvtScript N(EVS_Init) = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(N(EVS_TakeTurn)))
    Call(BindIdle, ACTOR_SELF, Ref(N(EVS_Idle)))
    Call(BindHandleEvent, ACTOR_SELF, Ref(N(EVS_HandleEvent)))
    Call(BindHandlePhase, ACTOR_SELF, Ref(N(EVS_HandlePhase)))
    Call(SetActorVar, ACTOR_SELF, AVAR_GreenPhase_BrigaderCommand, FALSE)
    Call(SetActorVar, ACTOR_SELF, AVAR_Collapsed, FALSE)
    Return
    End
};

EvtScript N(EVS_HandlePhase) = {
    Call(GetOriginalActorType, ACTOR_SELF, LVarA)
    Call(CreateHomeTargetList, TARGET_FLAG_2 | TARGET_FLAG_PRIMARY_ONLY)
    Call(InitTargetIterator)
    Label(0)
        Call(GetOwnerTarget, LVar0, LVar1)
        Call(GetOriginalActorType, LVar0, LVar2)
        IfNe(LVar2, LVarA)
            Call(GetActorHP, LVar0, LVar3)
            IfNe(LVar3, 0)
                Return
            EndIf
        EndIf
        Call(ChooseNextTarget, ITER_NEXT, LVar0)
        IfNe(LVar0, ITER_NO_MORE)
            Goto(0)
        EndIf
    Call(CreateHomeTargetList, TARGET_FLAG_2 | TARGET_FLAG_PRIMARY_ONLY)
    Call(InitTargetIterator)
    Label(1)
        Call(GetOwnerTarget, LVar0, LVar1)
        Call(GetActorVar, LVar0, AVAR_Collapsed, LVar3)
        IfNe(LVar3, TRUE)
            Return
        EndIf
        Call(ChooseNextTarget, ITER_NEXT, LVar0)
        IfNe(LVar0, ITER_NO_MORE)
            Goto(1)
        EndIf
    Call(CreateHomeTargetList, TARGET_FLAG_2 | TARGET_FLAG_PRIMARY_ONLY)
    Call(InitTargetIterator)
    Label(2)
        Call(GetOwnerTarget, LVar0, LVar1)
        Call(SetActorFlagBits, LVar0, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_NO_DMG_APPLY, TRUE)
        Call(ChooseNextTarget, ITER_NEXT, LVar0)
        IfNe(LVar0, ITER_NO_MORE)
            Goto(2)
        EndIf
    Return
    End
};

EvtScript N(EVS_Idle) = {
    Label(0)
        Call(GetActorVar, ACTOR_SELF, AVAR_Collapsed, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        Switch(LVar0)
            CaseEq(0)
                Switch(LVar1)
                    CaseFlag(STATUS_FLAG_SLEEP)
                        Call(SetTargetOffset, ACTOR_SELF, PRT_MAIN, -6, 24)
                        Call(SetProjectileTargetOffset, ACTOR_SELF, PRT_MAIN, 1, -5)
                    CaseDefault
                        Call(SetTargetOffset, ACTOR_SELF, PRT_MAIN, -8, 30)
                        Call(SetProjectileTargetOffset, ACTOR_SELF, PRT_MAIN, -1, -10)
                EndSwitch
            CaseEq(1)
                Switch(LVar1)
                    CaseFlag(STATUS_FLAG_SLEEP)
                        Call(SetTargetOffset, ACTOR_SELF, PRT_MAIN, -1, 10)
                        Call(SetProjectileTargetOffset, ACTOR_SELF, PRT_MAIN, 0, 0)
                    CaseDefault
                        Call(SetTargetOffset, ACTOR_SELF, PRT_MAIN, -1, 10)
                        Call(SetProjectileTargetOffset, ACTOR_SELF, PRT_MAIN, 0, 0)
                EndSwitch
        EndSwitch
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript N(EVS_Collapse) = {
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_DRY_BONES_COLLAPSE)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_Death)
    Wait(20)
    Call(SetActorVar, ACTOR_SELF, AVAR_Collapsed, TRUE)
    Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(N(CollapsedAnims)))
    Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(N(CollapsedDefense)))
    Call(SetStatusTable, ACTOR_SELF, Ref(N(CollapsedStatusTable)))
    Call(ClearStatusEffects, ACTOR_SELF)
    Call(SetTargetOffset, ACTOR_SELF, PRT_MAIN, -1, 10)
    Call(SetProjectileTargetOffset, ACTOR_SELF, PRT_MAIN, 0, 0)
    Set(LVar0, BASE_COLLAPSE_DURATION)
    Call(SetActorVar, ACTOR_SELF, AVAR_CollapseTurns, LVar0)
    Call(GetOriginalActorType, ACTOR_SELF, LVarA)
    Call(CreateHomeTargetList, TARGET_FLAG_2 | TARGET_FLAG_PRIMARY_ONLY)
    Call(InitTargetIterator)
    Label(0)
        Call(GetOwnerTarget, LVar0, LVar1)
        Call(GetOriginalActorType, LVar0, LVar2)
        IfNe(LVar2, LVarA)
            Return
        EndIf
        Call(ChooseNextTarget, ITER_NEXT, LVar0)
        IfNe(LVar0, ITER_NO_MORE)
            Goto(0)
        EndIf
    Call(CreateHomeTargetList, TARGET_FLAG_2 | TARGET_FLAG_PRIMARY_ONLY)
    Call(InitTargetIterator)
    Label(1)
        Call(GetOwnerTarget, LVar0, LVar1)
        Call(GetActorVar, LVar0, AVAR_Collapsed, LVar3)
        IfNe(LVar3, TRUE)
            Return
        EndIf
        Call(ChooseNextTarget, ITER_NEXT, LVar0)
        IfNe(LVar0, ITER_NO_MORE)
            Goto(1)
        EndIf
    Call(CreateHomeTargetList, TARGET_FLAG_2 | TARGET_FLAG_PRIMARY_ONLY)
    Call(InitTargetIterator)
    Label(2)
        Call(GetOwnerTarget, LVar0, LVar1)
        Call(SetActorFlagBits, LVar0, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_NO_DMG_APPLY, TRUE)
        Call(ChooseNextTarget, ITER_NEXT, LVar0)
        IfNe(LVar0, ITER_NO_MORE)
            Goto(2)
        EndIf
    Return
    End
};

EvtScript N(EVS_HandleEvent) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(EVENT_HIT_COMBO)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_BrigaderBones_Hurt)
            ExecWait(EVS_Enemy_Hit)
        CaseEq(EVENT_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_BrigaderBones_Hurt)
            ExecWait(EVS_Enemy_Hit)
        CaseEq(EVENT_SPIN_SMASH_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_BrigaderBones_Hurt)
            ExecWait(EVS_Enemy_SpinSmashHit)
        CaseEq(EVENT_SPIN_SMASH_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_BrigaderBones_Hurt)
            ExecWait(EVS_Enemy_SpinSmashHit)
            ExecWait(N(EVS_Collapse))
        CaseOrEq(EVENT_ZERO_DAMAGE)
        CaseOrEq(EVENT_IMMUNE)
            Call(GetActorVar, ACTOR_SELF, AVAR_Collapsed, LVar0)
            IfEq(LVar0, FALSE)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_BrigaderBones_Idle)
                ExecWait(EVS_Enemy_NoDamageHit)
            Else
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_BrigaderBones_StillDead)
                ExecWait(EVS_Enemy_NoDamageHit)
                Call(SetActorVar, ACTOR_SELF, AVAR_CollapseTurns, AVAL_CollapseTurnTwo)
            EndIf
        EndCaseGroup
        CaseEq(EVENT_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_BrigaderBones_Hurt)
            ExecWait(EVS_Enemy_Hit)
            Call(GetActorVar, ACTOR_SELF, AVAR_Collapsed, LVar0)
            IfEq(LVar0, FALSE)
                Wait(10)
                ExecWait(N(EVS_Collapse))
            EndIf
        CaseEq(EVENT_RECOVER_STATUS)
            Call(GetActorVar, ACTOR_SELF, AVAR_Collapsed, LVar0)
            IfEq(LVar0, FALSE)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_BrigaderBones_Idle)
                ExecWait(EVS_Enemy_Recover)
            EndIf
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_TakeTurn) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorVar, ACTOR_SELF, AVAR_Collapsed, LVar0)
    IfEq(LVar0, TRUE)
        Call(GetActorVar, ACTOR_SELF, AVAR_CollapseTurns, LVar0)
        Switch(LVar0)
            CaseEq(AVAL_CollapseTurnTwo)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_DRY_BONES_RATTLE)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_DeathRattle)
                Wait(10)
                Call(SetActorVar, ACTOR_SELF, AVAR_CollapseTurns, AVAL_CollapseTurnOne)
                DebugPrintf("2 Turns Remaining...")
            CaseEq(AVAL_CollapseTurnOne)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_DRY_BONES_RATTLE)
                Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(4.0))
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_DeathRattle)
                Wait(10)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_StillDead)
                Wait(10)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_DRY_BONES_RATTLE)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_DeathRattle)
                Wait(10)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_StillDead)
                Wait(10)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_DRY_BONES_RATTLE)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_DeathRattle)
                Call(SetActorVar, ACTOR_SELF, AVAR_CollapseTurns, AVAL_CollapseTurnZero)
                Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(1.0))
                DebugPrintf("1 Turn Remaining...")
            CaseEq(AVAL_CollapseTurnZero)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_DRY_BONES_RATTLE)
                Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(8.0))
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_DeathRattle)
                Wait(10)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_StillDead)
                Wait(10)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_DRY_BONES_RATTLE)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_DeathRattle)
                Wait(10)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_StillDead)
                Wait(10)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_DRY_BONES_RATTLE)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_DeathRattle)
                Wait(10)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_StillDead)
                Wait(10)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_DRY_BONES_RATTLE)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_DeathRattle)
                Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(1.0))
                Wait(10)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_DRY_BONES_ARISE)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_Revive)
                Wait(20)
                Call(SetActorVar, ACTOR_SELF, AVAR_Collapsed, FALSE)
                Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(N(DefaultAnims)))
                Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(N(DefenseTable)))
                Call(SetStatusTable, ACTOR_SELF, Ref(N(StatusTable)))
                Call(SetPartFlagBits, ACTOR_SELF, PRT_MAIN, ACTOR_PART_FLAG_DAMAGE_IMMUNE, FALSE)
                Call(SetTargetOffset, ACTOR_SELF, PRT_MAIN, -8, 30)
                Call(SetProjectileTargetOffset, ACTOR_SELF, PRT_MAIN, -1, -10)
                ExecWait(N(EVS_Move_Command))
        EndSwitch
    Else
        ExecWait(N(EVS_Move_Command))
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_Move_Command) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_CommandStart)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_BrigaderBones_CommandEnd)
    Wait(15)
    Call(SetActorVar, ACTOR_SELF, AVAR_GreenPhase_BrigaderCommand, TRUE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

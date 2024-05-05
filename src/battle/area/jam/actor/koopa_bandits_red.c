#include "../area.h"
#include "mapfs/jam_bt00_shape.h"
#include "sprite/npc/KoopaGang.h"
#include "boss.h"

#define NAMESPACE A(red_bandit_koopa)

// Red Bandit Params
enum N(ThisBanditsParams) {
    // THIS_ACTOR_ID               = ACTOR_ENEMY3,
    THIS_ACTOR_TYPE             = ACTOR_TYPE_RED_BANDIT,
    THIS_LEVEL                  = ACTOR_LEVEL_RED_BANDIT,
    THIS_SLEEP_CHANCE           = 0,
    THIS_DIZZY_CHANCE           = 0,
    THIS_PARALYZE_CHANCE        = 0,
    THIS_ANIM_IDLE              = ANIM_KoopaGang_Red_Digging,
    THIS_ANIM_STILL             = ANIM_KoopaGang_Red_Still,
    THIS_ANIM_RUN               = ANIM_KoopaGang_Red_Run,
    THIS_ANIM_HURT              = ANIM_KoopaGang_Red_Hurt,
    THIS_ANIM_HURT_STILL        = ANIM_KoopaGang_Red_HurtStill,
    THIS_ANIM_TOP_ENTER_SHELL   = ANIM_KoopaGang_Red_TopEnterShell,
    THIS_ANIM_TOP_EXIT_SHELL    = ANIM_KoopaGang_Red_TopExitShell,
    THIS_ANIM_ENTER_SHELL       = ANIM_KoopaGang_Red_EnterShell,
    THIS_ANIM_EXIT_SHELL        = ANIM_KoopaGang_Red_ExitShell,
    THIS_ANIM_SHELL_SPIN        = ANIM_KoopaGang_Red_ShellSpin,
    THIS_ANIM_POINT             = ANIM_KoopaGang_Red_PointForward,
};

extern ActorBlueprint A(bob_omb);
extern Formation N(ThrowBobomb);
extern s32 N(DefaultAnims)[];
extern EvtScript N(EVS_Init);
extern EvtScript N(EVS_Idle);
extern EvtScript N(EVS_HandleEvent);
extern EvtScript N(EVS_HandlePhase);
extern EvtScript N(EVS_TakeTurn);
extern EvtScript N(EVS_Defeat);
extern EvtScript N(EVS_FifthPhaseTransition);
extern EvtScript N(EVS_Attack_LitBomb);
extern EvtScript N(EVS_Attack_UnlitBomb);
extern EvtScript N(EVS_Summon_LitBobomb);
extern EvtScript N(EVS_Summon_UnlitBobomb);
extern EvtScript N(EVS_Attack_Pokey);

enum N(ActorPartIDs) {
    PRT_MAIN            = 1,
    PRT_BOMB            = 2,
    PRT_POKEY           = 3,
};

enum N(ActorParams) {
    DMG_LIT_BOMB        = 1,
    DMG_UNLIT_BOMB      = 2,
    DMG_POKEY           = 2,
};

s32 N(DefaultDefense)[] = {
    ELEMENT_NORMAL,   1,
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
    .maxHP = 20,
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

EvtScript N(EVS_Init) = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(N(EVS_TakeTurn)))
    Call(BindIdle, ACTOR_SELF, Ref(N(EVS_Idle)))
    Call(BindHandleEvent, ACTOR_SELF, Ref(N(EVS_HandleEvent)))
    Call(BindHandlePhase, ACTOR_SELF, Ref(N(EVS_HandlePhase)))
    Call(SetActorVar, ACTOR_SELF, AVAR_RedPhase_PyroDefeated, FALSE)
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

EvtScript N(EVS_HandlePhase) = {
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
    Call(SetActorFlagBits, ACTOR_RED_BANDIT, ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, THIS_ANIM_HURT)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    //Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_EMOTE_IDEA)
    PlayEffect(EFFECT_EMOTE, EMOTE_EXCLAMATION, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0)
    Wait(10)
    ExecWait(N(EVS_FifthPhaseTransition))
    Return
    End
};

EvtScript N(EVS_FifthPhaseTransition) = {
    Call(CancelEnemyTurn, 1)
    Call(EnableModel, MODEL_jam_bt00_Tunnel, TRUE)
    Set(LVar0, 0)
    Label(0)
        Set(LVar0, 0) // Reset LVar0 to 0
        Loop(0)
            Add(LVar0, 10) // Increment LVar0 by 10
            IfGt(LVar0, 1000)
                // Models
                Call(EnableModel, MODEL_jam_bt00_BombBox, FALSE)
                Call(EnableModel, MODEL_jam_bt00_BombPile, FALSE)
                Call(EnableModel, MODEL_jam_bt00_BarrelRed, FALSE)
                // Red Phase Actors AKA Fourth Phase Actors
                Call(SetActorFlagBits, ACTOR_RED_BANDIT, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
                Call(SetPartFlagBits, ACTOR_RED_BANDIT, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
                Call(SetActorFlagBits, ACTOR_PYRO_GUY, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, TRUE)
                Call(SetPartFlagBits, ACTOR_PYRO_GUY, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, TRUE)
                // Bowser Phase Actors AKA Fifth Phase Actors
                Call(SetActorPos, ACTOR_KOOPA_THE_KID, 130, 35, 20)
                Call(ForceHomePos, ACTOR_KOOPA_THE_KID, 130, 35, 20)
                Call(SetActorFlagBits, ACTOR_KOOPA_THE_KID, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN | ACTOR_FLAG_NO_HEALTH_BAR, FALSE)
                Call(SetPartFlagBits, ACTOR_KOOPA_THE_KID, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, FALSE)
                Call(SetActorPos, ACTOR_KOOPA_GANG, 60, 0, 20)
                Call(ForceHomePos, ACTOR_KOOPA_GANG, 60, 0, 20)
                Call(SetActorFlagBits, ACTOR_KOOPA_GANG, ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_SKIP_TURN, FALSE)
                Call(SetPartFlagBits, ACTOR_KOOPA_GANG, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE, FALSE)
                Call(SetActorPos, ACTOR_HAMMER_BRO, 15, 0, 20)
                Call(ForceHomePos, ACTOR_HAMMER_BRO, 15, 0, 20)
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
        // DebugPrintf("Transition Done!")
        Call(EnableModel, MODEL_jam_bt00_Tunnel, FALSE)
    Return
    End
};

Vec3i N(SummonPos) = { NPC_DISPOSE_LOCATION };

Formation N(ThrowBobOmb) = {
    ACTOR_BY_POS(A(bob_omb), N(SummonPos), 100),
};

#define LBL_ENDTURN 0
EvtScript N(EVS_TakeTurn) = {
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(GetActorVar, ACTOR_SELF, AVAR_RedPhase_PyroDefeated, LVar3)
    Switch(LVar3)
        CaseEq(FALSE)
            Call(RandInt, 100, LVar1)
            Switch(LVar1)
                CaseLt(60)
                    Set(LVar0, AVAL_RedPhase_LitBombAttack)
                CaseLt(30)
                    Set(LVar0, AVAL_RedPhase_LitBobombSummon)
                CaseDefault
                    Set(LVar0, AVAL_RedPhase_PokeyAttack)
            EndSwitch
            Call(GetActorVar, ACTOR_SELF, AVAR_RedPhase_RandomAttack, LVar0)
            Set(LVar0, AVAL_RedPhase_LitBombAttack) // Set Attack
            Switch(LVar0)
                CaseEq(AVAL_RedPhase_LitBombAttack)
                    ExecWait(N(EVS_Attack_LitBomb))
                    Goto(LBL_ENDTURN)
                CaseEq(AVAL_RedPhase_LitBobombSummon)
                    ExecWait(N(EVS_Summon_LitBobomb))
                    Goto(LBL_ENDTURN)
                CaseEq(AVAL_RedPhase_PokeyAttack)
                    ExecWait(N(EVS_Attack_Pokey))
                    Goto(LBL_ENDTURN)
            EndSwitch
        CaseEq(TRUE)
            Call(RandInt, 100, LVar1)
            Switch(LVar1)
                CaseLt(60)
                    Set(LVar0, AVAL_RedPhase_UnlitBombAttack)
                CaseLt(30)
                    Set(LVar0, AVAL_RedPhase_UnlitBobombSummon)
                CaseDefault
                    Set(LVar0, AVAL_RedPhase_PokeyAttack)
            EndSwitch
            Call(GetActorVar, ACTOR_SELF, AVAR_RedPhase_RandomAttack, LVar0)
            Set(LVar0, AVAL_RedPhase_UnlitBombAttack) // Set Attack
            Switch(LVar0)
                CaseEq(AVAL_RedPhase_UnlitBombAttack)
                    ExecWait(N(EVS_Attack_LitBomb))
                    Goto(LBL_ENDTURN)
                CaseEq(AVAL_RedPhase_UnlitBobombSummon)
                    ExecWait(N(EVS_Summon_LitBobomb))
                    Goto(LBL_ENDTURN)
                CaseEq(AVAL_RedPhase_PokeyAttack)
                    ExecWait(N(EVS_Attack_Pokey))
                    Goto(LBL_ENDTURN)
            EndSwitch
    EndSwitch
    Label(LBL_ENDTURN)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_Attack_BulletBiff_Slow) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, BTL_CAM_PRESET_15)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Thread
        Wait(35)
        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(MoveBattleCamOver, 30)
    EndThread
    Wait(5)
    // Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_GeneralGuy_Anim0B)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 8)
    Add(LVar1, 27)
    Sub(LVar2, 4)
    Call(SetPartPos, ACTOR_SELF, PRT_BOMB, LVar0, LVar1, LVar2)
    // Call(SetAnimation, ACTOR_SELF, PRT_BOMB, ANIM_GeneralGuyBomb_Anim00)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_BOMB, ACTOR_PART_FLAG_INVISIBLE, FALSE)
    Wait(15)
    // Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_GeneralGuy_Anim0A)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_BOMB, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Wait(6)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 8)
    Add(LVar1, 20)
    Call(SetPartPos, ACTOR_SELF, PRT_BOMB, LVar0, LVar1, LVar2)
    // Call(SetAnimation, ACTOR_SELF, PRT_BOMB, ANIM_GeneralGuyBomb_Anim01)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_BOMB, ACTOR_PART_FLAG_INVISIBLE, FALSE)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 4, BS_FLAGS1_TRIGGER_EVENTS)
    Switch(LVar0)
        CaseEq(HIT_RESULT_MISS)
            Call(PlaySoundAtPart, ACTOR_SELF, PRT_BOMB, SOUND_TOSS)
            Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 120)
            Call(SetPartMoveSpeed, ACTOR_SELF, PRT_BOMB, Float(12.0))
            Call(SetPartJumpGravity, ACTOR_SELF, PRT_BOMB, Float(0.1))
            Call(JumpPartTo, ACTOR_SELF, PRT_BOMB, LVar0, LVar1, LVar2, 0, TRUE)
            Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_MISS, 0, 0, 0)
            Call(SetPartFlagBits, ACTOR_SELF, PRT_BOMB, ACTOR_PART_FLAG_INVISIBLE, TRUE)
            // Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_GeneralGuy_Anim02)
            Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
            Call(UseIdleAnimation, ACTOR_SELF, TRUE)
            Return
        CaseEq(HIT_RESULT_LUCKY)
            Call(PlaySoundAtPart, ACTOR_SELF, PRT_BOMB, SOUND_TOSS)
            Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Set(LVar1, -5)
            Call(SetPartMoveSpeed, ACTOR_SELF, PRT_BOMB, Float(14.0))
            Call(SetPartJumpGravity, ACTOR_SELF, PRT_BOMB, Float(0.1))
            Call(FlyPartTo, ACTOR_SELF, PRT_BOMB, LVar0, LVar1, LVar2, 0, 30, EASING_LINEAR)
            Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
            Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
            Sub(LVar0, 65)
            Set(LVar1, -5)
            Call(SetPartMoveSpeed, ACTOR_SELF, PRT_BOMB, Float(6.0))
            Call(SetPartJumpGravity, ACTOR_SELF, PRT_BOMB, Float(0.1))
            Call(FlyPartTo, ACTOR_SELF, PRT_BOMB, LVar0, LVar1, LVar2, 0, 15, EASING_LINEAR)
            Call(SetPartFlagBits, ACTOR_SELF, PRT_BOMB, ACTOR_PART_FLAG_INVISIBLE, TRUE)
            // Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_GeneralGuy_Anim02)
            Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
            Call(UseIdleAnimation, ACTOR_SELF, TRUE)
            Return
    EndSwitch
    Call(PlaySoundAtPart, ACTOR_SELF, PRT_BOMB, SOUND_TOSS)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartMoveSpeed, ACTOR_SELF, PRT_BOMB, Float(14.0))
    Call(SetPartJumpGravity, ACTOR_SELF, PRT_BOMB, Float(0.1))
    Call(FlyPartTo, ACTOR_SELF, PRT_BOMB, LVar0, LVar1, LVar2, 0, 15, EASING_LINEAR)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, PRT_BOMB, SOUND_BOMB_BLAST)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_BOMB, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, DAMAGE_TYPE_BLAST | DAMAGE_TYPE_NO_CONTACT, 0, 0, DMG_LIT_BOMB, BS_FLAGS1_TRIGGER_EVENTS)
    Switch(LVarF)
        CaseOrEq(HIT_RESULT_HIT)
        CaseOrEq(HIT_RESULT_NO_DAMAGE)
        CaseOrEq(HIT_RESULT_10)
            // Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_GeneralGuy_Anim02)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

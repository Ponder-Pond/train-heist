#include "trn_01.h"
#include "generated.h"
#include "world/common/npc/Bubba.inc.c"
#include "world/common/npc/Toad_Stationary.inc.c"
#include "world/common/npc/Luigi.inc.c"
#include "world/common/enemy/Kammy.inc.c"
#include "world/common/npc/Peach.inc.c"

EvtScript N(EVS_NpcInteract_Toadsworth) = {
    Call(SpeakToPlayer, NPC_Toadsworth, ANIM_Toadsworth_Talk, ANIM_Toadsworth_Idle, 0, MSG_Misc_ToadsworthInteract)
    Return
    End
};

EvtScript N(EVS_NpcInit_Toadsworth) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Toadsworth)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_ToadMinister) = {
    Call(SpeakToPlayer, NPC_ToadMinister, ANIM_ToadMinister_Talk, ANIM_ToadMinister_Idle, 0, MSG_Misc_ToadMinisterInteract)
    Return
    End
};

EvtScript N(EVS_NpcInit_ToadMinister) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_ToadMinister)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Bubba) = {
    Call(SpeakToPlayer, NPC_Bubba, ANIM_BigBubba_Talk, ANIM_BigBubba_Idle, 0, MSG_Misc_BubbaInteract)
    Return
    End
};

EvtScript N(EVS_NpcInit_Bubba) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Bubba)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Luigi) = {
    Call(DisablePlayerInput, TRUE)
    Call(ShowMessageAtScreenPos, MSG_Misc_LuigiInteract, 160, 40)
    // Call(SpeakToPlayer, NPC_Luigi, ANIM_LuigiSleeping_LuigiSleep, ANIM_LuigiSleeping_LuigiSleep, 0, MSG_Misc_LuigiInteract)
    Call(DisablePlayerInput, FALSE)
    Return
    End
};

EvtScript N(EVS_NpcInit_Luigi) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Luigi)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Kammy) = {
    Call(SpeakToPlayer, NPC_CalamityKammy, ANIM_CalamityKammy_Talk, ANIM_CalamityKammy_Idle, 0, MSG_Misc_KammyInteract)
    Return
    End
};

EvtScript N(EVS_NpcInit_Kammy) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Kammy)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Peach) = {
    Call(SpeakToPlayer, NPC_Peach, ANIM_ParadePeach_Talk, ANIM_ParadePeach_IdleRaisedArms, 0, MSG_Misc_PeachInteract)
    Return
    End
};

EvtScript N(EVS_NpcInit_Peach) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Peach)))
    Return
    End
};

NpcData N(NpcData_Characters)[] = {
    {
        .id = NPC_Toadsworth,
        .pos = { GEN_TOADSWORTH_VEC },
        .yaw = GEN_TOADSWORTH_DIR,
        .init = &N(EVS_NpcInit_Toadsworth),
        .settings = &N(NpcSettings_Toad_Stationary),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOADSWORTH_ANIMS, // Change to Toadsworth Animations
        .tattle = MSG_Misc_ToadsworthTattle,
    },
    {
        .id = NPC_TayceT,
        .pos = { GEN_TAYCE_T_VEC },
        .yaw = GEN_TAYCE_T_DIR,
        .init = &N(EVS_NpcInit_TayceT),
        .settings = &N(NpcSettings_Toad_Stationary),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TAYCE_T_ANIMS,
        .tattle = MSG_Misc_TayceTTattle,
    },
    {
        .id = NPC_ToadMinister,
        .pos = { GEN_TOAD_MINISTER_VEC },
        .yaw = GEN_TOAD_MINISTER_DIR,
        .init = &N(EVS_NpcInit_ToadMinister),
        .settings = &N(NpcSettings_Toad_Stationary),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_MINISTER_ANIMS,
        .tattle = MSG_Misc_ToadMinisterTattle,
    },
    {
        .id = NPC_Bubba,
        .pos = { GEN_BUBBA_VEC },
        .yaw = GEN_BUBBA_DIR,
        .init = &N(EVS_NpcInit_Bubba),
        .settings = &N(NpcSettings_Bubba),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = BUBBA_ANIMS,
        .tattle = MSG_Misc_BigBubbaTattle,
    },
    {
        .id = NPC_Toad,
        .pos = { GEN_TOAD_VEC },
        .yaw = GEN_TOAD_DIR,
        .init = &N(EVS_NpcInit_Toad),
        .settings = &N(NpcSettings_Toad_Stationary),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_Misc_ToadTattle,
    },
    {
        .id = NPC_Luigi,
        .pos = { GEN_LUIGI_VEC },
        .yaw = GEN_LUIGI_DIR,
        .init = &N(EVS_NpcInit_Luigi),
        .settings = &N(NpcSettings_Luigi),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = LUIGI_SLEEPING_ANIMS,
        .tattle = MSG_Misc_LuigiTattle,
    },
    {
        .id = NPC_CalamityKammy,
        .pos = { GEN_CALAMITY_KAMMY_VEC },
        .yaw = GEN_CALAMITY_KAMMY_DIR,
        .init = &N(EVS_NpcInit_Kammy),
        .settings = &N(NpcSettings_Kammy),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = CALAMITY_KAMMY_ANIMS,
        .tattle = MSG_Misc_CalamityKammyTattle,
    },
    {
        .id = NPC_Peach,
        .pos = { GEN_PEACH_VEC },
        .yaw = GEN_PEACH_DIR,
        .init = &N(EVS_NpcInit_Peach),
        .settings = &N(NpcSettings_Peach),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = PEACH_NPC_ANIMS,
        .tattle = MSG_Misc_PeachTattle,
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Characters)),
    {}
};

EvtScript N(EVS_Scene_BeginGame) = {
    Call(DisablePlayerInput, TRUE)
    Thread
        Wait(5)
        Call(SetMusicTrack, 0, SONG_WHALE_THEME, 0, 8)
        Wait(5)
    EndThread
    Call(DisablePlayerInput, FALSE)
    Return
    End
};

#include "trn_01.h"
#include "generated.h"
#include "world/common/npc/Toad_Stationary.inc.c"
#include "world/common/npc/Luigi.inc.c"
#include "world/common/enemy/Kammy.inc.c"
#include "world/common/npc/Peach.inc.c"

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
        .settings = &N(NpcSettings_Toad_Stationary),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS, // Change to Toadsworth Animations
    },
    {
        .id = NPC_TayceT,
        .pos = { GEN_TAYCE_T_VEC },
        .yaw = GEN_TAYCE_T_DIR,
        .settings = &N(NpcSettings_Toad_Stationary),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TAYCE_T_ANIMS,
    },
    {
        .id = NPC_ToadMinister,
        .pos = { GEN_TOAD_MINISTER_VEC },
        .yaw = GEN_TOAD_MINISTER_DIR,
        .settings = &N(NpcSettings_Toad_Stationary),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_MINISTER_ANIMS,
    },
    {
        .id = NPC_Bubba,
        .pos = { GEN_BUBBA_VEC },
        .yaw = GEN_BUBBA_DIR,
        .settings = &N(NpcSettings_Toad_Stationary),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
    },
    {
        .id = NPC_Toad,
        .pos = { GEN_TOAD_VEC },
        .yaw = GEN_TOAD_DIR,
        .settings = &N(NpcSettings_Toad_Stationary),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
    },
    {
        .id = NPC_Luigi,
        .pos = { GEN_LUIGI_VEC },
        .yaw = GEN_LUIGI_DIR,
        .settings = &N(NpcSettings_Luigi),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = LUIGI_ANIMS,
    },
    {
        .id = NPC_CalamityKammy,
        .pos = { GEN_CALAMITY_KAMMY_VEC },
        .yaw = GEN_CALAMITY_KAMMY_DIR,
        .settings = &N(NpcSettings_Kammy),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = KAMMY_ANIMS,
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
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Characters)),
    {}
};

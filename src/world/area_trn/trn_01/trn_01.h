/// @file trn_01.h
/// @brief  - Lobby

#include "common.h"
#include "generated.h"
#include "message_ids.h"
#include "map.h"

#include "../trn.h"
#include "mapfs/trn_01_shape.h"
#include "mapfs/trn_01_hit.h"

#include "sprite/npc/Toadsworth.h"
#include "sprite/npc/ToadMinister.h"
#include "sprite/npc/TayceT.h"
#include "sprite/npc/BigBubba.h"
#include "sprite/npc/Toad.h"
#include "sprite/npc/LuigiSleeping.h"
#include "sprite/npc/CalamityKammy.h"
#include "sprite/npc/ParadePeach.h"

#define TOAD_BADGE_COUNT 14 // Badge Shop

#define TAYCE_T_ITEM_COUNT 6 // Item Shop

enum {
    MF_PurchasedBadge   = MapFlag(0),
    MF_PurchasedItem    = MapFlag(1),
};

enum {
    NPC_Toadsworth      = 0,
    NPC_TayceT          = 1,
    NPC_ToadMinister    = 2,
    NPC_Bubba           = 3,
    NPC_Toad            = 4,
    NPC_Luigi           = 5,
    NPC_CalamityKammy   = 6,
    NPC_Peach           = 7,
};

#define NAMESPACE trn_01

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_StartTexPanners);
extern EvtScript N(EVS_TrainBounce);
extern NpcGroupList N(DefaultNPCs);
extern EvtScript N(EVS_NpcInit_Toad);
extern EvtScript N(EVS_NpcInteract_Toad);
extern EvtScript N(EVS_NpcInit_TayceT);
extern EvtScript N(EVS_NpcInteract_TayceT);

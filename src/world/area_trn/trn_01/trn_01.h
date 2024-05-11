/// @file trn_01.h
/// @brief  - Lobby

#include "common.h"
#include "generated.h"
#include "message_ids.h"
#include "map.h"

#include "../trn.h"
#include "mapfs/trn_01_shape.h"
#include "mapfs/trn_01_hit.h"

#include "sprite/npc/ToadMinister.h"
#include "sprite/npc/TayceT.h"
#include "sprite/npc/Toad.h"
#include "sprite/npc/Luigi.h"
#include "sprite/npc/WorldKammy.h"
#include "sprite/npc/ParadePeach.h"

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
extern NpcGroupList N(DefaultNPCs);

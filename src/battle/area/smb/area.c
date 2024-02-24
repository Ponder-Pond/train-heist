#include "area.h"

#include "battle/common/newstage/area_smb/smb_00.inc.c"
#include "battle/common/newstage/area_smb/smb_01.inc.c"
#include "battle/common/newstage/area_smb/smb_02.inc.c"

extern ActorBlueprint A(goomba);
extern ActorBlueprint A(koopa_troopa);
extern ActorBlueprint A(piranha_plant);
extern ActorBlueprint A(false_bowser);

extern Stage A(smb_00);
extern Stage A(smb_01);
extern Stage A(smb_02);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(goomba), BTL_POS_GROUND_C, 10),
};

Formation A(Formation_01) = {
    ACTOR_BY_IDX(A(koopa_troopa), BTL_POS_GROUND_C, 10),
};

Formation A(Formation_02) = {
    ACTOR_BY_IDX(A(piranha_plant), BTL_POS_GROUND_C, 10),
};

Formation A(Formation_03) = {
    ACTOR_BY_IDX(A(false_bowser), BTL_POS_GROUND_C, 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(smb_01), "Goomba"),
    BATTLE(A(Formation_01), A(smb_01), "Koopa Troopa"),
    BATTLE(A(Formation_02), A(smb_01), "Piranha Plant"),
    BATTLE(A(Formation_03), A(smb_01), "False Bowser"),
    {},
};

StageList A(Stages) = {
    STAGE("smb_00", A(smb_00)),
    STAGE("smb_01", A(smb_01)),
    STAGE("smb_02", A(smb_02)),
    {},
};

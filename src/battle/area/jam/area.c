#include "area.h"

#include "battle/common/newstage/area_jam/jam_00.inc.c"

extern ActorBlueprint A(goomba);
extern ActorBlueprint A(koopa_troopa);
extern ActorBlueprint A(piranha_plant);
extern ActorBlueprint A(false_bowser);

extern Stage A(jam_00);

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
    BATTLE(A(Formation_00), A(jam_00), "Goomba"),
    BATTLE(A(Formation_01), A(jam_00), "Koopa Troopa"),
    BATTLE(A(Formation_02), A(jam_00), "Piranha Plant"),
    BATTLE(A(Formation_03), A(jam_00), "False Bowser"),
    {},
};

StageList A(Stages) = {
    STAGE("jam_00", A(jam_00)),
    {},
};

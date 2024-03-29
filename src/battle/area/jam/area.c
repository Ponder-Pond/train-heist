#include "area.h"

#include "battle/common/newstage/area_jam/jam_00.inc.c"

extern ActorBlueprint A(koopa_bandit_green);
extern ActorBlueprint A(buzzy_beetle);
extern ActorBlueprint A(koopa_bandit_yellow);
extern ActorBlueprint A(giant_chain_chomp);
extern ActorBlueprint A(hammer_bro);
extern ActorBlueprint A(koopa_bandit_black);
extern ActorBlueprint A(koopa_bandit_red);

extern Stage A(jam_00);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(koopa_bandit_green), BTL_POS_GROUND_A, 9),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_C, 10),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_D, 10),
    ACTOR_BY_IDX(A(koopa_bandit_yellow), BTL_POS_GROUND_C, 9),
    ACTOR_BY_IDX(A(giant_chain_chomp), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(hammer_bro), BTL_POS_GROUND_D, 8),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(jam_00), "The Train Heist"),
    {},
};

StageList A(Stages) = {
    STAGE("jam_00", A(jam_00)),
    {},
};

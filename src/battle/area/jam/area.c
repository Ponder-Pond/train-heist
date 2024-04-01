#include "area.h"

#include "battle/common/newstage/area_jam/jam_00.inc.c"

extern ActorBlueprint A(green_bandit_koopa);
extern ActorBlueprint A(buzzy_beetle);
extern ActorBlueprint A(yellow_bandit_koopa);
extern ActorBlueprint A(giant_chain_chomp);
extern ActorBlueprint A(hammer_bro);
extern ActorBlueprint A(black_bandit_koopa);
extern ActorBlueprint A(red_bandit_koopa);

extern Stage A(jam_00);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(green_bandit_koopa), BTL_POS_GROUND_A, 9),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_C, 10),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_D, 10),
    ACTOR_BY_IDX(A(yellow_bandit_koopa), BTL_POS_GROUND_C, 9),
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

#include "area.h"

#include "battle/common/newstage/area_jam/jam_00.inc.c"

extern ActorBlueprint A(green_bandit_koopa);
extern ActorBlueprint A(buzzy_beetle);
extern ActorBlueprint A(yellow_bandit_koopa);
extern ActorBlueprint A(giant_chain_chomp);
extern ActorBlueprint A(hammer_bro);
extern ActorBlueprint A(black_bandit_koopa);
extern ActorBlueprint A(crate);
extern ActorBlueprint A(dyanmite_crate);
extern ActorBlueprint A(shy_guy_rider);
extern ActorBlueprint A(red_bandit_koopa);
extern ActorBlueprint A(pyro_guy);

extern Stage A(jam_00);

Vec3i A(BlackPos) = { 140, 10, 20 };
Vec3i A(CratePos) = { 15, 0, 20 };
Vec3i A(DyanmitePos) = { 55, 0, 20 };
Vec3i A(Rider1Pos) = { 45, -25, -65 };
Vec3i A(Rider2Pos) = { -25, -25, -65 };

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(green_bandit_koopa), BTL_POS_GROUND_A, 9),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_C, 10),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_D, 10),
    ACTOR_BY_IDX(A(yellow_bandit_koopa), BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(giant_chain_chomp), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(hammer_bro), BTL_POS_GROUND_D, 9),
    ACTOR_BY_POS(A(black_bandit_koopa), A(BlackPos), 8),
    ACTOR_BY_POS(A(crate), A(CratePos), 10),
    ACTOR_BY_POS(A(dyanmite_crate), A(DyanmitePos), 10),
    ACTOR_BY_POS(A(shy_guy_rider), A(Rider1Pos), 10),
    ACTOR_BY_POS(A(shy_guy_rider), A(Rider2Pos), 9),
    ACTOR_BY_IDX(A(red_bandit_koopa), BTL_POS_GROUND_C, 10),
    ACTOR_BY_IDX(A(pyro_guy), BTL_POS_GROUND_D, 9),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(jam_00), "The Train Heist"),
    {},
};

StageList A(Stages) = {
    STAGE("jam_00", A(jam_00)),
    {},
};

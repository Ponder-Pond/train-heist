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

Vec3i A(YellowPos) = { 105, 0, 10 };
Vec3i A(GiantChompPos) = { 25, 0, 10 };
Vec3i A(HammerBroPos) = { 145, 0, 10 };
Vec3i A(BlackPos) = { 140, 10, 20 };
Vec3i A(CratePos) = { 15, 0, 20 };
Vec3i A(DyanmitePos) = { 55, 0, 20 };
Vec3i A(Rider1Pos) = { 45, -25, -50 };
Vec3i A(Rider2Pos) = { -25, -25, -50 };

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(green_bandit_koopa), BTL_POS_GROUND_A, 9),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_C, 10),
    ACTOR_BY_IDX(A(buzzy_beetle), BTL_POS_GROUND_D, 10),
    ACTOR_BY_POS(A(yellow_bandit_koopa), A(YellowPos), 8),
    ACTOR_BY_POS(A(giant_chain_chomp), A(GiantChompPos), 10),
    ACTOR_BY_POS(A(hammer_bro), A(HammerBroPos), 9),
    ACTOR_BY_POS(A(black_bandit_koopa), A(BlackPos), 8),
    ACTOR_BY_POS(A(crate), A(CratePos), 10),
    ACTOR_BY_POS(A(dyanmite_crate), A(DyanmitePos), 10),
    ACTOR_BY_POS(A(shy_guy_rider), A(Rider1Pos), 9),
    ACTOR_BY_POS(A(shy_guy_rider), A(Rider2Pos), 10),
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

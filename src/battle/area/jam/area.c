#include "area.h"

#include "battle/common/newstage/area_jam/jam_00.inc.c"

extern ActorBlueprint A(green_bandit_koopa);
extern ActorBlueprint A(buzzy_beetle);
extern ActorBlueprint A(brigader_bones);
extern ActorBlueprint A(yellow_bandit_koopa);
extern ActorBlueprint A(giant_chain_chomp);
extern ActorBlueprint A(hammer_bro_alt);
extern ActorBlueprint A(black_bandit_koopa);
extern ActorBlueprint A(crate);
extern ActorBlueprint A(dyanmite_crate);
extern ActorBlueprint A(shy_guy_rider);
extern ActorBlueprint A(red_bandit_koopa);
extern ActorBlueprint A(pyro_guy);
extern ActorBlueprint A(bob_omb);
extern ActorBlueprint A(koopa_the_kid);
extern ActorBlueprint A(koopa_gang);
extern ActorBlueprint A(hammer_bro);

extern Stage A(jam_00);

Vec3i A(GreenPos) = { 70, 25, 20 };
Vec3i A(BuzzyBeetlePos) = { 100, 25, 20 };
Vec3i A(BrigaderBonesPos) = { 23, 0, 30 };
Vec3i A(YellowPos) = { NPC_DISPOSE_LOCATION };
Vec3i A(GiantChompPos) = { NPC_DISPOSE_LOCATION };
Vec3i A(HammerBroAltPos) = { NPC_DISPOSE_LOCATION };
Vec3i A(BlackPos) = { NPC_DISPOSE_LOCATION };
Vec3i A(CratePos) = { NPC_DISPOSE_LOCATION };
Vec3i A(DyanmitePos) = { NPC_DISPOSE_LOCATION };
Vec3i A(Rider1Pos) = { NPC_DISPOSE_LOCATION };
Vec3i A(Rider2Pos) = { NPC_DISPOSE_LOCATION };
Vec3i A(RedPos) = { NPC_DISPOSE_LOCATION };
Vec3i A(PyroGuyPos) = { NPC_DISPOSE_LOCATION };
Vec3i A(KoopaTheKidPos) = { NPC_DISPOSE_LOCATION };
Vec3i A(KoopaGangPos) = { NPC_DISPOSE_LOCATION };
Vec3i A(HammerBroPos) = { NPC_DISPOSE_LOCATION };
Vec3i A(KoopaTheKidTestingPos) = { 130, 35, 20 };
Vec3i A(KoopaGangTestingPos) = { 60, 0, 20 };
Vec3i A(HammerBroTestingPos) = { 15, 0, 20 };
// Vec3i A(HowitzerHalPos) = { -5, 0, 25 };
// Vec3i A(YellowPos) = { 105, 0, 10 };
// Vec3i A(GiantChompPos) = { 25, 0, 10 };
// Vec3i A(HammerBroPos) = { 145, 0, 10 };
// Vec3i A(BlackPos) = { 140, 10, 20 };
// Vec3i A(CratePos) = { 15, 0, 20 };
// Vec3i A(DyanmitePos) = { 55, 0, 20 };
// Vec3i A(Rider1Pos) = { 45, -25, -50 };
// Vec3i A(Rider2Pos) = { -25, -25, -50 };

    // [BTL_POS_GROUND_A] { 5, 0, -20 },
    // [BTL_POS_GROUND_B] { 45, 0, -5 },
    // [BTL_POS_GROUND_C] { 85, 0, 10 },
    // [BTL_POS_GROUND_D] { 125, 0, 25 },

Formation A(Formation_00) = {
    ACTOR_BY_POS(A(green_bandit_koopa), A(GreenPos), 8),
    ACTOR_BY_POS(A(buzzy_beetle), A(BuzzyBeetlePos), 9),
    ACTOR_BY_POS(A(brigader_bones), A(BrigaderBonesPos), 10),
    ACTOR_BY_POS(A(yellow_bandit_koopa), A(YellowPos), 8),
    ACTOR_BY_POS(A(giant_chain_chomp), A(GiantChompPos), 10),
    ACTOR_BY_POS(A(hammer_bro_alt), A(HammerBroAltPos), 9),
    ACTOR_BY_POS(A(black_bandit_koopa), A(BlackPos), 8),
    ACTOR_BY_POS(A(crate), A(CratePos), 10),
    ACTOR_BY_POS(A(dyanmite_crate), A(DyanmitePos), 10),
    ACTOR_BY_POS(A(shy_guy_rider), A(Rider1Pos), 9),
    ACTOR_BY_POS(A(shy_guy_rider), A(Rider2Pos), 10),
    ACTOR_BY_POS(A(red_bandit_koopa), A(RedPos), 10),
    ACTOR_BY_POS(A(pyro_guy), A(PyroGuyPos), 9),
    ACTOR_BY_POS(A(koopa_the_kid), A(KoopaTheKidPos), 8),
    ACTOR_BY_POS(A(koopa_gang), A(KoopaGangPos), 9),
    ACTOR_BY_POS(A(hammer_bro), A(HammerBroPos), 10),
};

Formation A(Formation_01) = {
    // ACTOR_BY_POS(A(green_bandit_koopa), A(GreenPos), 8),
    // ACTOR_BY_POS(A(buzzy_beetle), A(BuzzyBeetlePos), 9),
    // ACTOR_BY_POS(A(brigader_bones), A(BrigaderBonesPos), 10),
    // ACTOR_BY_POS(A(yellow_bandit_koopa), A(YellowPos), 8),
    // ACTOR_BY_POS(A(giant_chain_chomp), A(GiantChompPos), 10),
    // ACTOR_BY_POS(A(hammer_bro_alt), A(HammerBroAltPos), 9),
    // ACTOR_BY_POS(A(black_bandit_koopa), A(BlackPos), 8),
    // ACTOR_BY_POS(A(crate), A(CratePos), 10),
    // ACTOR_BY_POS(A(dyanmite_crate), A(DyanmitePos), 10),
    // ACTOR_BY_POS(A(shy_guy_rider), A(Rider1Pos), 9),
    // ACTOR_BY_POS(A(shy_guy_rider), A(Rider2Pos), 10),
    // ACTOR_BY_POS(A(red_bandit_koopa), A(RedPos), 10),
    // ACTOR_BY_POS(A(pyro_guy), A(PyroGuyPos), 9),
    ACTOR_BY_POS(A(koopa_the_kid), A(KoopaTheKidTestingPos), 8),
    ACTOR_BY_POS(A(koopa_gang), A(KoopaGangTestingPos), 9),
    ACTOR_BY_POS(A(hammer_bro), A(HammerBroTestingPos), 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(jam_00), "The Train Heist"),
    BATTLE(A(Formation_01), A(jam_00), "Testing"),
    {},
};

StageList A(Stages) = {
    STAGE("jam_00", A(jam_00)),
    {},
};

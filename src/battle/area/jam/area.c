#include "area.h"

#include "battle/common/newstage/area_jam/jam_00.inc.c"

extern ActorBlueprint A(goomba);
extern ActorBlueprint A(koopa_troopa);
extern ActorBlueprint A(piranha_plant);
extern ActorBlueprint A(false_bowser);
extern ActorBlueprint A(koopa_bandits_yellow);
extern ActorBlueprint A(giant_chain_chomp);
extern ActorBlueprint A(hammer_bro);

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

Formation A(Formation_04) = {
    ACTOR_BY_IDX(A(koopa_bandits_yellow), BTL_POS_GROUND_C, 10),
    ACTOR_BY_IDX(A(hammer_bro), BTL_POS_GROUND_D, 9),
    ACTOR_BY_IDX(A(giant_chain_chomp), BTL_POS_GROUND_A, 8),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(jam_00), "Goomba"),
    BATTLE(A(Formation_01), A(jam_00), "Koopa Troopa"),
    BATTLE(A(Formation_02), A(jam_00), "Piranha Plant"),
    BATTLE(A(Formation_03), A(jam_00), "False Bowser"),
    BATTLE(A(Formation_04), A(jam_00), "Yellow Bandit Koopa, Hammer Bro, Giant Chain Chomp"),
    {},
};

StageList A(Stages) = {
    STAGE("jam_00", A(jam_00)),
    {},
};

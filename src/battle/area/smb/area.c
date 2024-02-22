#include "area.h"

#include "battle/common/stage/area_smb/smb_01.inc.c"

extern ActorBlueprint A(goomba);
extern ActorBlueprint A(koopa_troopa);
extern ActorBlueprint A(piranha_plant);
extern ActorBlueprint A(fake_bowser);
extern ActorBlueprint A(king_boo);

extern Stage A(smb_01);

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
    ACTOR_BY_IDX(A(fake_bowser), BTL_POS_GROUND_C, 10),
};

Vec3i A(KingBooPos) = { 70, 50, 5 };

Formation A(Formation_04) = {
    ACTOR_BY_POS(A(king_boo), A(KingBooPos), 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(smb_01), "Goomba"),
    BATTLE(A(Formation_01), A(smb_01), "Koopa Troopa"),
    BATTLE(A(Formation_02), A(smb_01), "Piranha Plant"),
    BATTLE(A(Formation_03), A(smb_01), "Fake Bowser"),
    BATTLE(A(Formation_04), A(smb_01), "King Boo"),
    {},
};

StageList A(Stages) = {
    STAGE("smb_01", A(smb_01)),
    {},
};

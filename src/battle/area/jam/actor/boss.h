#ifndef _BOSS_COMMON_H_
#define _BOSS_COMMON_H_

enum N(BattleCommon) {
    ACTOR_GREEN_BANDIT                  = ACTOR_ENEMY0,
    ACTOR_BUZZY_BEETLE                  = ACTOR_ENEMY1,
    ACTOR_HOWITZER_HAL                  = ACTOR_ENEMY2,
    ACTOR_BRIGADER_BONES                = ACTOR_ENEMY3,
    ACTOR_YELLOW_BANDIT                 = ACTOR_ENEMY4,
    ACTOR_GIANT_CHOMP                   = ACTOR_ENEMY5,
    ACTOR_HAMMER_BRO                    = ACTOR_ENEMY6,
    ACTOR_BLACK_BANDIT                  = ACTOR_ENEMY7,
    ACTOR_CRATE                         = ACTOR_ENEMY8,
    ACTOR_DYANMITE_CRATE                = ACTOR_ENEMY9,
    ACTOR_SHY_GUY_RIDER_1               = ACTOR_ENEMY10,
    ACTOR_SHY_GUY_RIDER_2               = ACTOR_ENEMY11,
    ACTOR_RED_BANDIT                    = ACTOR_ENEMY12,
    ACTOR_PYRO_GUY                      = ACTOR_ENEMY13,
    ACTOR_BOB_OMB                       = ACTOR_ENEMY14,
    ACTOR_BOWSER                        = ACTOR_ENEMY15,
    ACTOR_KOOPA_GANG                    = ACTOR_ENEMY16,
    ACTOR_BIFF_BLASTER_1                = ACTOR_ENEMY17,
    ACTOR_BIFF_BLASTER_2                = ACTOR_ENEMY18,
    // Phase Actor Vars
    AVAR_Phase                          = 0,
    AVAL_IntroPhase                     = 0,
    AVAL_GreenPhase                     = 1,
    AVAL_YellowPhase                    = 2,
    AVAL_BlackPhase                     = 3,
    AVAL_RedPhase                       = 4,
    AVAL_BowserPhase                    = 5,
    // Green Phase Actor Vars
    AVAR_GreenPhase_BrigaderCommand     = 1,
    // Yellow Phase Actor Vars
    // Black Phase Actor Vars
    AVAR_BlackPhase_RidersDefeated      = 1,
    // Red Phase Actor Vars
    AVAR_RedPhase_PyroDefeated          = 1,
};

#endif // _BOSS_COMMON_H_
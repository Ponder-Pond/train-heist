#include "tst_13.h"
//#include "world/common/enemy/ShyGuy_Wander.inc.c"
#include "world/common/npc/Bowser.inc.c"

// void mdl_project_tex_coords(s32 modelID, Gfx* destGfx, Matrix4f destMtx, void* destVertices);

extern EvtScript N(EVS_Main);
// extern EvtScript N(D_80240510_B1DC70);
extern NpcGroupList N(DefaultNPCs);

EntryList N(Entrances) = {
    [tst_13_ENTRY_0]    {    0.0,    0.0,  100.0,   90.0 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .background = &gBackgroundImage,
};

#include "world/common/atomic/BetaFloorPanels.inc.c"

EvtScript N(EVS_NpcInteract_Bowser) = {
    Call(SpeakToPlayer, NPC_Bowser, ANIM_WorldBowser_Talk, ANIM_WorldBowser_Idle, 0, MSG_Misc_BowserInteract)
    Return
    End
};

EvtScript N(EVS_NpcInit_Bowser) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Bowser)))
    Return
    End
};

AnimID N(ExtraAnims_Bowser)[] = {
    ANIM_WorldBowser_Still,
    ANIM_WorldBowser_Idle,
    ANIM_WorldBowser_BrandishIdle,
    ANIM_WorldBowser_Walk,
    ANIM_WorldBowser_Run,
    ANIM_WorldBowser_Talk,
    ANIM_WorldBowser_TalkEyesClosed,
    ANIM_WorldBowser_BrandishTalk,
    ANIM_WorldBowser_RearUpTalk,
    ANIM_WorldBowser_RearUpLaugh,
    ANIM_WorldBowser_Brandish,
    ANIM_WorldBowser_RearUpMock,
    ANIM_WorldBowser_PostJump,
    ANIM_WorldBowser_ClownCarStill,
    ANIM_WorldBowser_ClownCarIdle,
    ANIM_WorldBowser_ClownCarPropeller,
    ANIM_LIST_END
};

NpcData N(NpcData_Testing)[] = {
    {
        .id = NPC_Bowser,
        .settings = &N(NpcSettings_Bowser),
        .pos = { 0.0f, 0.0f, 0.0f },
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .init = &N(EVS_NpcInit_Bowser),
        .yaw = 270,
        .drops = NO_DROPS,
        .animations = BOWSER_ANIMS,
        .extraAnimations = N(ExtraAnims_Bowser),
    },
};

// EvtScript N(EVS_NpcInit_ShyGuy) = {
//     Call(SetNpcPos, NPC_SELF, 0, 0, 0)
//     Return
//     End
// };

// NpcData N(NpcData_ShyGuy) = {
//     .id = NPC_ShyGuy,
//     .pos = { NPC_DISPOSE_LOCATION },
//     .yaw = 270,
//     .territory = {
//         .wander = {
//             .isFlying = FALSE,
//             .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
//             .wanderShape = SHAPE_CYLINDER,
//             .centerPos  = { 0, 0, 0 },
//             .wanderSize = { 30 },
//             .detectShape = SHAPE_CYLINDER,
//             .detectPos  = { 0, 0, 0 },
//             .detectSize = { 200 },
//         }
//     },
//     .init = &N(EVS_NpcInit_ShyGuy),
//     .settings = &N(NpcSettings_ShyGuy_Wander),
//     .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
//     .drops = SHY_GUY_DROPS,
//     .animations = PINK_SHY_GUY_ANIMS,
//     .aiDetectFlags = AI_DETECT_SIGHT,
// };

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Testing)),
    // NPC_GROUP(N(NpcData_ShyGuy), BTL_MOD_FORMATION_01, BTL_MOD_STAGE_00),
    {}
};

// #include "world/area_tst/tst_13/shockwave.vtx.inc.c"
// #include "world/area_tst/tst_13/shockwave.gfx.inc.c"

// Gfx N(dummy_gfx)[] = {
//     gsSPEndDisplayList()
// };

// s32 N(BuildGfxCallCount) = 0;

// void N(build_gfx_floor)(void) {
//     Matrix4f sp10;
//     Matrix4f sp50;
//     f32 x, y, z;

//     N(BuildGfxCallCount)++;
//     guTranslateF(sp10, gPlayerStatus.pos.x, 0.0f, gPlayerStatus.pos.z);

//     x = (sin_rad(N(BuildGfxCallCount) / 50.0f) * 0.5) + 0.5;
//     y = SQ(cos_rad(N(BuildGfxCallCount) / 50.0f)) + 0.1;
//     z = (sin_rad(N(BuildGfxCallCount) / 50.0f) * 0.5) + 0.5;

//     guScaleF(sp50, x, y, z);
//     guMtxCatF(sp50, sp10, sp10);
//     guMtxF2L(sp10, &gDisplayContext->matrixStack[gMatrixListPos]);
//     mdl_project_tex_coords(MODEL_o152, N(shockwave_gfx), sp10, NULL);

//     gDPPipeSync(gMainGfxPos++);
//     gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
//     gDPSetRenderMode(gMainGfxPos++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
//     mdl_draw_hidden_panel_surface(&gMainGfxPos, 1);
//     gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
//     gSPDisplayList(gMainGfxPos++, N(shockwave_gfx));
//     gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
// }


s32 N(BetaPanelData)[] = {
    MODEL_point, COLLIDER_point, -35, 0, -45, ITEM_HEART
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TESTING)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, FALSE, Ref(N(DefaultNPCs)))
    Set(LVar0, Ref(N(BetaPanelData)))
    Exec(N(EVS_BetaPanel_Setup))
    // Call(SetModelCustomGfx, MODEL_o152, CUSTOM_GFX_0, -1)
    // Call(SetCustomGfxBuilders, CUSTOM_GFX_0, 0, Ref(N(build_gfx_floor)))
    Return
    End
};

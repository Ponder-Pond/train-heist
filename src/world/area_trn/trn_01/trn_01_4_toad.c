#include "trn_01.h"
#include "hud_element.h"


extern IconHudScriptPair gItemHudScripts[];

// #define NAME_SUFFIX _Toad
// #include "world/common/complete/LetterDelivery.inc.c"

// s32 N(LetterList)[] = {
//     ITEM_LETTER_TO_MERLOW,
//     ITEM_NONE
// };

// EvtScript N(EVS_LetterPrompt) = {
//     Call(N(LetterDelivery_Init),
//         NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle,
//         ITEM_LETTER_TO_MERLOW, ITEM_NONE,
//         MSG_HOS_0058, MSG_HOS_0059, MSG_HOS_005A, MSG_HOS_005B,
//         Ref(N(LetterList)))
//     ExecWait(N(EVS_DoLetterDelivery))
//     Return
//     End
// };

// EvtScript N(EVS_LetterReward) = {
//     IfEq(LVarC, DELIVERY_ACCEPTED)
//         EVT_GIVE_STAR_PIECE()
//     EndIf
//     Return
//     End
// };
// #define NAME_SUFFIX

// EvtScript N(EVS_NpcInteract_Merluvlee_Passthrough) = {
//     ExecWait(N(EVS_NpcInteract_Merluvlee))
//     Return
//     End
// };

ShopItemData N(ToadBadgeInventory)[TOAD_BADGE_COUNT] = {
    { .itemID = ITEM_FIRE_SHIELD,    .price =  3, .descMsg = MSG_ItemShopDesc_AttackFXA },
    { .itemID = ITEM_HAPPY_HEART_A,  .price =  15, .descMsg = MSG_ItemShopDesc_HappyHeart },
    { .itemID = ITEM_HAPPY_FLOWER_A, .price =  15, .descMsg = MSG_ItemShopDesc_HappyFlower },

    { .itemID = ITEM_POWER_JUMP,     .price =  10, .descMsg = MSG_ItemShopDesc_PayOff },
    { .itemID = ITEM_SHRINK_STOMP,   .price =  7, .descMsg = MSG_ItemShopDesc_ChillOut },
    { .itemID = ITEM_POWER_SMASH,    .price =  10, .descMsg = MSG_ItemShopDesc_PrettyLucky },

    { .itemID = ITEM_JUMP_CHARGE,    .price = 3, .descMsg = MSG_ItemShopDesc_FeelingFine },
    { .itemID = ITEM_POWER_RUSH,     .price = 7, .descMsg = MSG_ItemShopDesc_Peekaboo },

    { .itemID = ITEM_CLOSE_CALL,     .price = 5, .descMsg = MSG_ItemShopDesc_ZapTap },
    { .itemID = ITEM_LAST_STAND,     .price = 5, .descMsg = MSG_ItemShopDesc_HeartFinder },
    { .itemID = ITEM_PRETTY_LUCKY,   .price = 10, .descMsg = MSG_ItemShopDesc_FlowerFinder },

    { .itemID = ITEM_DOUBLE_DIP,       .price = 3, .descMsg = MSG_ItemShopDesc_HPDrain },
    { .itemID = ITEM_QUICK_CHANGE,     .price = 20, .descMsg = MSG_ItemShopDesc_MoneyMoney },
    { .itemID = ITEM_ALLOR_NOTHING,    .price = 10, .descMsg = MSG_ItemShopDesc_FlowerSaver },
};

API_CALLABLE(N(Toad_GetPlayerStarPieces)) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, gPlayerData.starPieces);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(Toad_SetBadgePurchased)) {
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    evt_set_variable(NULL, GF_TRN01_ToadBadge_00 + index, TRUE);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(Toad_ShopBadgesPopup)) {
    PlayerData* playerData = &gPlayerData;
    PopupMenu* menu;
    s32 selected, menuPos, i;

    if (isInitialCall) {
        script->functionTempPtr[2] = heap_malloc(sizeof(*menu));
        menu = script->functionTempPtr[2];
        menuPos = 0;
        for (i = 0; i < TOAD_BADGE_COUNT; i++) {
            if (!evt_get_variable(NULL, GF_TRN01_ToadBadge_00 + i)) {
                ItemData* item = &gItemTable[N(ToadBadgeInventory)[i].itemID];
                IconHudScriptPair* itemHudScripts = &gItemHudScripts[item->hudElemID];
                menu->userIndex[menuPos] = i;
                menu->nameMsg[menuPos] = item->nameMsg;
                menu->ptrIcon[menuPos] = itemHudScripts->enabled;
                menu->enabled[menuPos] = playerData->starPieces >= N(ToadBadgeInventory)[i].price;
                if (playerData->starPieces < N(ToadBadgeInventory)[i].price) {
                    menu->ptrIcon[menuPos] = itemHudScripts->disabled;
                    menu->enabled[menuPos] = FALSE;
                }
                menu->descMsg[menuPos] = N(ToadBadgeInventory)[i].descMsg;
                menu->value[menuPos] = N(ToadBadgeInventory)[i].price;
                menuPos++;
            }
        }
        menu->popupType = POPUP_MENU_TRADE_FOR_BADGE;
        menu->numEntries = menuPos;
        menu->initialPos = 0;
        create_standard_popup_menu(menu);
        script->functionTemp[0] = 0;
    }

    menu = script->functionTempPtr[2];
    if (script->functionTemp[0] == 0) {
        script->functionTemp[1] = menu->result;
        if (script->functionTemp[1] != POPUP_RESULT_CHOOSING) {
            hide_popup_menu();
        } else {
            return ApiStatus_BLOCK;
        }
    }
    script->functionTemp[0]++;
    if (script->functionTemp[0] < 20) {
        return ApiStatus_BLOCK;
    }

    destroy_popup_menu();
    selected = script->functionTemp[1];
    if (selected != POPUP_RESULT_CANCEL) {
        ShopItemData* selectedItem;
        i = menu->userIndex[selected - 1];
        selectedItem = &N(ToadBadgeInventory)[i];
        script->varTable[0] = selectedItem->itemID;
        script->varTable[1] = selectedItem->price;
        script->varTable[2] = i;
        script->varTable[4] = gItemTable[selectedItem->itemID].nameMsg;
        script->varTable[5] = gMoveTable[gItemTable[selectedItem->itemID].moveID].costBP;
    } else {
        script->varTable[0] = -1;
    }

    heap_free(script->functionTempPtr[2]);
    return ApiStatus_DONE2;
}

EvtScript N(EVS_NpcInteract_Toad) = {
    IfGe(GB_TRN01_Toad_PurchaseCount, TOAD_BADGE_COUNT)
        Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad6)
        Return
    EndIf
    IfEq(MF_PurchasedBadge, TRUE)
        Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad3)
    Else
        Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad1)
    EndIf
    Call(ShowChoice, MSG_Choice_0014)
    IfEq(LVar0, 1)
        Call(ContinueSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad4)
        Return
    EndIf
    Call(N(Toad_GetPlayerStarPieces), LVar0)
    IfEq(LVar0, 0)
        Call(ContinueSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad5)
        Return
    EndIf
    Call(ContinueSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad7)
    Label(0)
    Call(N(Toad_ShopBadgesPopup))
    Wait(10)
    IfEq(LVar0, -1)
        Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad8)
        Return
    EndIf
    Call(N(Toad_GetPlayerStarPieces), LVar3)
    IfLt(LVar3, LVar1)
        Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad8)
        Goto(0)
    EndIf
    Call(SetMessageText, LVar4, 0)
    Call(SetMessageValue, LVar1, 1)
    Call(SetMessageValue, LVar5, 2)
    IfEq(LVar1, 1)
        Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad2)
    Else
        Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad9)
    EndIf
    Set(LVar3, LVar0)
    Call(ShowChoice, MSG_Choice_000D)
    IfEq(LVar0, 1)
        Call(ContinueSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad10)
        Goto(0)
    EndIf
    Call(CloseMessage)
    Mul(LVar1, -1)
    Call(AddStarPieces, LVar1)
    Add(GB_TRN01_Toad_PurchaseCount, 1)
    Set(MF_PurchasedBadge, TRUE)
    Call(N(Toad_SetBadgePurchased), LVar2)
    // awkward
    // #define NAME_SUFFIX _Toad
    Set(LVar0, LVar3)
    Call(ShowGotItem, LVar0, TRUE, 0)
    Call(AddItem, LVar0, LVar1)
    // EVT_GIVE_REWARD(LVar3)
    // #define NAME_SUFFIX
    IfGe(GB_TRN01_Toad_PurchaseCount, TOAD_BADGE_COUNT)
        Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad11)
        Return
    EndIf
    Call(N(Toad_GetPlayerStarPieces), LVar0)
    IfLe(LVar0, 0)
        Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad11)
        Return
    EndIf
    Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad12)
    Call(ShowChoice, MSG_Choice_000D)
    IfEq(LVar0, 1)
        Call(ContinueSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Misc_BuyToad13)
        Return
    EndIf
    Call(CloseMessage)
    Goto(0)
    Return
    End
};

EvtScript N(EVS_NpcInit_Toad) = {
    Set(MF_PurchasedBadge, FALSE)
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Toad)))
    Return
    End
};

#include "trn_01.h"
#include "hud_element.h"

extern IconHudScriptPair gItemHudScripts[];

// #define NAME_SUFFIX _Tayce_T
// #include "world/common/complete/LetterDelivery.inc.c"

// s32 N(LetterList)[] = {
//     ITEM_LETTER_TO_MERLOW,
//     ITEM_NONE
// };

// EvtScript N(EVS_LetterPrompt) = {
//     Call(N(LetterDelivery_Init),
//         NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking,
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

ShopItemData N(TayceTItemInventory)[TAYCE_T_ITEM_COUNT] = {
    { .itemID = ITEM_POTATO_SALAD,    .price =  5, .descMsg = MSG_ItemShopDesc_AttackFXA },
    { .itemID = ITEM_NUTTY_CAKE,  .price =  5, .descMsg = MSG_ItemShopDesc_HappyHeart },
    { .itemID = ITEM_APPLE_PIE, .price =  10, .descMsg = MSG_ItemShopDesc_HappyFlower },

    { .itemID = ITEM_YUMMY_MEAL,     .price =  20, .descMsg = MSG_ItemShopDesc_PayOff },
    { .itemID = ITEM_LIFE_SHROOM,   .price =  40, .descMsg = MSG_ItemShopDesc_ChillOut },
    { .itemID = ITEM_REPEL_GEL,    .price =  15, .descMsg = MSG_ItemShopDesc_PrettyLucky },
};

API_CALLABLE(N(TayceT_GetPlayerCoins)) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, gPlayerData.coins);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(TayceT_SetItemPurchased)) {
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    evt_set_variable(NULL, GF_TRN01_TayceTItem_00 + index, TRUE);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(TayceT_ShopItemsPopup)) {
    PlayerData* playerData = &gPlayerData;
    PopupMenu* menu;
    s32 selected, menuPos, i;

    if (isInitialCall) {
        script->functionTempPtr[2] = heap_malloc(sizeof(*menu));
        menu = script->functionTempPtr[2];
        menuPos = 0;
        for (i = 0; i < TAYCE_T_ITEM_COUNT; i++) {
            if (!evt_get_variable(NULL, GF_TRN01_TayceTItem_00 + i)) {
                ItemData* item = &gItemTable[N(TayceTItemInventory)[i].itemID];
                IconHudScriptPair* itemHudScripts = &gItemHudScripts[item->hudElemID];
                menu->userIndex[menuPos] = i;
                menu->nameMsg[menuPos] = item->nameMsg;
                menu->ptrIcon[menuPos] = itemHudScripts->enabled;
                menu->enabled[menuPos] = playerData->coins >= N(TayceTItemInventory)[i].price;
                if (playerData->coins < N(TayceTItemInventory)[i].price) {
                    menu->ptrIcon[menuPos] = itemHudScripts->disabled;
                    menu->enabled[menuPos] = FALSE;
                }
                menu->descMsg[menuPos] = N(TayceTItemInventory)[i].descMsg;
                menu->value[menuPos] = N(TayceTItemInventory)[i].price;
                menuPos++;
            }
        }
        menu->popupType = POPUP_MENU_BUY_ITEM;
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
        selectedItem = &N(TayceTItemInventory)[i];
        script->varTable[0] = selectedItem->itemID;
        script->varTable[1] = selectedItem->price;
        script->varTable[2] = i;
        script->varTable[4] = gItemTable[selectedItem->itemID].nameMsg;
    } else {
        script->varTable[0] = -1;
    }

    heap_free(script->functionTempPtr[2]);
    return ApiStatus_DONE2;
}

EvtScript N(EVS_NpcInteract_TayceT) = {
    IfGe(GB_TRN01_TayceT_PurchaseCount, TAYCE_T_ITEM_COUNT)
        Call(SpeakToPlayer, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT6)
        Return
    EndIf
    IfEq(MF_PurchasedItem, TRUE)
        Call(SpeakToPlayer, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT3)
    Else
        Call(SpeakToPlayer, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT1)
    EndIf
    Call(ShowChoice, MSG_Choice_0014)
    IfEq(LVar0, 1)
        Call(ContinueSpeech, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT4)
        Return
    EndIf
    Call(N(TayceT_GetPlayerCoins), LVar0)
    IfEq(LVar0, 0)
        Call(ContinueSpeech, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT5)
        Return
    EndIf
    Call(ContinueSpeech, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT7)
    Label(0)
    Call(N(TayceT_ShopItemsPopup))
    Wait(10)
    IfEq(LVar0, -1)
        Call(SpeakToPlayer, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT8)
        Return
    EndIf
    Call(N(TayceT_GetPlayerCoins), LVar3)
    IfLt(LVar3, LVar1)
        Call(SpeakToPlayer, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT8)
        Goto(0)
    EndIf
    Call(SetMessageText, LVar4, 0)
    Call(SetMessageValue, LVar1, 1)
    Call(SetMessageValue, LVar5, 2)
    IfEq(LVar1, 1)
        Call(SpeakToPlayer, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT2)
    Else
        Call(SpeakToPlayer, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT9)
    EndIf
    Set(LVar3, LVar0)
    Call(ShowChoice, MSG_Choice_000D)
    IfEq(LVar0, 1)
        Call(ContinueSpeech, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT10)
        Goto(0)
    EndIf
    Call(CloseMessage)
    Mul(LVar1, -1)
    Call(AddCoin, LVar1)
    Add(GB_TRN01_TayceT_PurchaseCount, 1)
    Set(MF_PurchasedItem, TRUE)
    Call(N(TayceT_SetItemPurchased), LVar2)
    // awkward
    // #define NAME_SUFFIX _Tayce_T
    Set(LVar0, LVar3)
    Call(ShowGotItem, LVar0, TRUE, 0)
    Call(AddItem, LVar0, LVar1)
    // EVT_GIVE_REWARD(LVar3)
    // #define NAME_SUFFIX
    IfGe(GB_TRN01_TayceT_PurchaseCount, TAYCE_T_ITEM_COUNT)
        Call(SpeakToPlayer, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT11)
        Return
    EndIf
    Call(N(TayceT_GetPlayerCoins), LVar0)
    IfLe(LVar0, 0)
        Call(SpeakToPlayer, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT11)
        Return
    EndIf
    Call(SpeakToPlayer, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT12)
    Call(ShowChoice, MSG_Choice_000D)
    IfEq(LVar0, 1)
        Call(ContinueSpeech, NPC_TayceT, ANIM_TayceT_Cooking, ANIM_TayceT_Cooking, 0, MSG_Misc_BuyTayceT13)
        Return
    EndIf
    Call(CloseMessage)
    Goto(0)
    Return
    End
};

EvtScript N(EVS_NpcInit_TayceT) = {
    Set(MF_PurchasedItem, FALSE)
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_TayceT)))
    Return
    End
};

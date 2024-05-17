#include "trn_01.h"

EntryList N(Entrances) = {
    [trn_01_ENTRY_Scene]    { GEN_ENTRY_SCENE_VEC, GEN_ENTRY_SCENE_DIR },
    [trn_01_ENTRY_Center]    { GEN_ENTRY_CENTER_VEC, GEN_ENTRY_CENTER_DIR },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .tattle = { MSG_Misc_TrainHeistMapTattle },
};

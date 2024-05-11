#include "trn_01.h"

EntryList N(Entrances) = {
    [trn_01_ENTRY_Center]    { 0.0, 0.0, 0.0, 0.0 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .tattle = { MSG_NONE },
};

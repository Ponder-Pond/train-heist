#include "ttr_01.h"

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_StartTexPanners);

EntryList N(Entrances) = {
    [ttr_01_ENTRY_Testing]    { -111, 0, 0, 0.000000 },
    [ttr_01_ENTRY_Lounge]    { -724, 0, -180, 0.000000 },
    [ttr_01_ENTRY_Gift_Shop]    { 511, 0, -180, 0.000000 },
    [ttr_01_ENTRY_Auditorium]    { -195, 0, -599, 0.000000 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .background = &gBackgroundImage,
    .tattle = { MSG_NONE },
};

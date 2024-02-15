#include "ttr_01.h"

EntryList N(Entrances) = {
    [ttr_01_ENTRY_Lounge]        {    -724.0,    0.0,    -180.0,   0.0 },
    [ttr_01_ENTRY_Gift_Shop]     {    511.0,    0.0,    -180.0,   0.0 },
    [ttr_01_ENTRY_Auditorium]    {    -195.0,    0.0,    -599.0,   0.0 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
};

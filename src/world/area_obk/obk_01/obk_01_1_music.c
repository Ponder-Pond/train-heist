#include "obk_01.h"

EvtScript N(EVS_SetupMusic) = {
    EVT_IF_LT(GB_StoryProgress, STORY_CH3_DEFEATED_TUBBA_BLUBBA)
        EVT_CALL(SetMusicTrack, 0, SONG_BOOS_MANSION, 0, 8)
    EVT_ELSE
        EVT_CALL(SetMusicTrack, 0, SONG_CHEERFUL_BOOS_MANSION, 0, 8)
    EVT_END_IF
    EVT_CALL(ClearAmbientSounds, 250)
    EVT_RETURN
    EVT_END
};
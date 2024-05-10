// #include "trn_01.h"
// #include "common.h"
// #include "world/common/atomic/TexturePan.inc.c"

// EvtScript N(EVS_StartTexPanners) = {
//     Call(SetTexPanner, MODEL_trn_01_StaircaseSidesA, TEX_PANNER_1)
//     Call(EnableTexPanning, MODEL_trn_01_StaircaseSidesA, TRUE)

//     Call(SetTexPanner, MODEL_trn_01_StarTrim, TEX_PANNER_1)
//     Call(EnableTexPanning, MODEL_trn_01_StarTrim, TRUE)
//     Thread
//         TEX_PAN_PARAMS_ID(TEX_PANNER_1)
//         TEX_PAN_PARAMS_STEP(573, 0, 0, 0)
//         TEX_PAN_PARAMS_FREQ(0, 0, 0, 0)
//         TEX_PAN_PARAMS_INIT(0, 0, 0, 0)
//         Exec(N(EVS_UpdateTexturePan))
//     EndThread
//     Thread
//         TEX_PAN_PARAMS_ID(TEX_PANNER_2)
//         TEX_PAN_PARAMS_STEP(-573, 0, 0, 0)
//         TEX_PAN_PARAMS_FREQ(0, 0, 0, 0)
//         TEX_PAN_PARAMS_INIT(0, 0, 0, 0)
//         Exec(N(EVS_UpdateTexturePan))
//     EndThread
//     Return
//     End
// };

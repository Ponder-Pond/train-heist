#ifndef _WORLD_AREA_TTR_TTR_H_
#define _WORLD_AREA_TTR_TTR_H_

enum {
    AB_TTR_Unused_0       = AreaByte(0),
    AB_TTR_Unused_1       = AreaByte(1),
    AB_TTR_Unused_2       = AreaByte(2),
    AB_TTR_Unused_3       = AreaByte(3),
    AB_TTR_Unused_4       = AreaByte(4),
    AB_TTR_Unused_5       = AreaByte(5),
    AB_TTR_Unused_6       = AreaByte(6),
    AB_TTR_Unused_7       = AreaByte(7),
    AB_TTR_Unused_8       = AreaByte(8),
    AB_TTR_Unused_9       = AreaByte(9),
    AB_TTR_Unused_A       = AreaByte(10),
    AB_TTR_Unused_B       = AreaByte(11),
    AB_TTR_Unused_C       = AreaByte(12),
    AB_TTR_Unused_D       = AreaByte(13),
    AB_TTR_Unused_E       = AreaByte(14),
    AB_TTR_Unused_F       = AreaByte(15),
};

#define AF_TTR(index) AreaFlag(index)

extern MapSettings ttr_01_settings;

#endif

.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel func_80035B6C
/* 10F6C 80035B6C 27BDFFE8 */  addiu     $sp, $sp, -0x18
/* 10F70 80035B70 AFB00010 */  sw        $s0, 0x10($sp)
/* 10F74 80035B74 3C10800A */  lui       $s0, %hi(D_8009E754)
/* 10F78 80035B78 2610E754 */  addiu     $s0, $s0, %lo(D_8009E754)
/* 10F7C 80035B7C AFBF0014 */  sw        $ra, 0x14($sp)
/* 10F80 80035B80 86030000 */  lh        $v1, ($s0)
/* 10F84 80035B84 24020001 */  addiu     $v0, $zero, 1
/* 10F88 80035B88 1062003D */  beq       $v1, $v0, .L80035C80
/* 10F8C 80035B8C 28620002 */   slti     $v0, $v1, 2
/* 10F90 80035B90 50400005 */  beql      $v0, $zero, .L80035BA8
/* 10F94 80035B94 24020002 */   addiu    $v0, $zero, 2
/* 10F98 80035B98 10600007 */  beqz      $v1, .L80035BB8
/* 10F9C 80035B9C 00000000 */   nop
/* 10FA0 80035BA0 0800D75B */  j         .L80035D6C
/* 10FA4 80035BA4 00000000 */   nop
.L80035BA8:
/* 10FA8 80035BA8 10620055 */  beq       $v1, $v0, .L80035D00
/* 10FAC 80035BAC 00000000 */   nop
/* 10FB0 80035BB0 0800D75B */  j         .L80035D6C
/* 10FB4 80035BB4 00000000 */   nop
.L80035BB8:
/* 10FB8 80035BB8 3C04800A */  lui       $a0, %hi(D_8009E756)
/* 10FBC 80035BBC 2484E756 */  addiu     $a0, $a0, %lo(D_8009E756)
/* 10FC0 80035BC0 84820000 */  lh        $v0, ($a0)
/* 10FC4 80035BC4 94830000 */  lhu       $v1, ($a0)
/* 10FC8 80035BC8 1440003B */  bnez      $v0, .L80035CB8
/* 10FCC 80035BCC 2462FFFF */   addiu    $v0, $v1, -1
/* 10FD0 80035BD0 3C038007 */  lui       $v1, %hi(D_8007417C)
/* 10FD4 80035BD4 2463417C */  addiu     $v1, $v1, %lo(D_8007417C)
/* 10FD8 80035BD8 8C620000 */  lw        $v0, ($v1)
/* 10FDC 80035BDC A0400070 */  sb        $zero, 0x70($v0)
/* 10FE0 80035BE0 8C620000 */  lw        $v0, ($v1)
/* 10FE4 80035BE4 A0400078 */  sb        $zero, 0x78($v0)
/* 10FE8 80035BE8 3C02800A */  lui       $v0, %hi(D_8009E758)
/* 10FEC 80035BEC 8442E758 */  lh        $v0, %lo(D_8009E758)($v0)
/* 10FF0 80035BF0 14400006 */  bnez      $v0, .L80035C0C
/* 10FF4 80035BF4 24060001 */   addiu    $a2, $zero, 1
/* 10FF8 80035BF8 8C620000 */  lw        $v0, ($v1)
/* 10FFC 80035BFC 84440086 */  lh        $a0, 0x86($v0)
/* 11000 80035C00 8445008C */  lh        $a1, 0x8c($v0)
/* 11004 80035C04 0800D706 */  j         .L80035C18
/* 11008 80035C08 0000302D */   daddu    $a2, $zero, $zero
.L80035C0C:
/* 1100C 80035C0C 8C620000 */  lw        $v0, ($v1)
/* 11010 80035C10 84440086 */  lh        $a0, 0x86($v0)
/* 11014 80035C14 8445008C */  lh        $a1, 0x8c($v0)
.L80035C18:
/* 11018 80035C18 0C0168E9 */  jal       func_8005A3A4
/* 1101C 80035C1C 00000000 */   nop
/* 11020 80035C20 3C108007 */  lui       $s0, %hi(D_8007417C)
/* 11024 80035C24 2610417C */  addiu     $s0, $s0, %lo(D_8007417C)
/* 11028 80035C28 8E020000 */  lw        $v0, ($s0)
/* 1102C 80035C2C 94430086 */  lhu       $v1, 0x86($v0)
/* 11030 80035C30 0000202D */  daddu     $a0, $zero, $zero
/* 11034 80035C34 0C009C15 */  jal       func_80027054
/* 11038 80035C38 A4430088 */   sh       $v1, 0x88($v0)
/* 1103C 80035C3C 8E020000 */  lw        $v0, ($s0)
/* 11040 80035C40 80420071 */  lb        $v0, 0x71($v0)
/* 11044 80035C44 14400003 */  bnez      $v0, .L80035C54
/* 11048 80035C48 00000000 */   nop
/* 1104C 80035C4C 0C038056 */  jal       func_800E0158
/* 11050 80035C50 00000000 */   nop
.L80035C54:
/* 11054 80035C54 0C00B424 */  jal       func_8002D090
/* 11058 80035C58 00000000 */   nop
/* 1105C 80035C5C 3C02800A */  lui       $v0, %hi(D_8009E754)
/* 11060 80035C60 2442E754 */  addiu     $v0, $v0, %lo(D_8009E754)
/* 11064 80035C64 94430000 */  lhu       $v1, ($v0)
/* 11068 80035C68 24040002 */  addiu     $a0, $zero, 2
/* 1106C 80035C6C 3C01800A */  lui       $at, %hi(D_8009E756)
/* 11070 80035C70 A424E756 */  sh        $a0, %lo(D_8009E756)($at)
/* 11074 80035C74 24630001 */  addiu     $v1, $v1, 1
/* 11078 80035C78 0800D75B */  j         .L80035D6C
/* 1107C 80035C7C A4430000 */   sh       $v1, ($v0)
.L80035C80:
/* 11080 80035C80 0C00F879 */  jal       func_8003E1E4
/* 11084 80035C84 00000000 */   nop
/* 11088 80035C88 0C00E57C */  jal       func_800395F0
/* 1108C 80035C8C 00000000 */   nop
/* 11090 80035C90 0C037DC8 */  jal       func_800DF720
/* 11094 80035C94 00000000 */   nop
/* 11098 80035C98 0C00B424 */  jal       func_8002D090
/* 1109C 80035C9C 00000000 */   nop
/* 110A0 80035CA0 3C04800A */  lui       $a0, %hi(D_8009E756)
/* 110A4 80035CA4 2484E756 */  addiu     $a0, $a0, %lo(D_8009E756)
/* 110A8 80035CA8 84820000 */  lh        $v0, ($a0)
/* 110AC 80035CAC 94830000 */  lhu       $v1, ($a0)
/* 110B0 80035CB0 10400003 */  beqz      $v0, .L80035CC0
/* 110B4 80035CB4 2462FFFF */   addiu    $v0, $v1, -1
.L80035CB8:
/* 110B8 80035CB8 0800D75B */  j         .L80035D6C
/* 110BC 80035CBC A4820000 */   sh       $v0, ($a0)
.L80035CC0:
/* 110C0 80035CC0 3C028007 */  lui       $v0, %hi(D_8007417C)
/* 110C4 80035CC4 8C42417C */  lw        $v0, %lo(D_8007417C)($v0)
/* 110C8 80035CC8 0C0B1059 */  jal       func_802C4164
/* 110CC 80035CCC 8C44006C */   lw       $a0, 0x6c($v0)
/* 110D0 80035CD0 14400026 */  bnez      $v0, .L80035D6C
/* 110D4 80035CD4 00000000 */   nop
/* 110D8 80035CD8 3C05800A */  lui       $a1, %hi(D_8009A630)
/* 110DC 80035CDC 24A5A630 */  addiu     $a1, $a1, %lo(D_8009A630)
/* 110E0 80035CE0 2404FFF7 */  addiu     $a0, $zero, -9
/* 110E4 80035CE4 8CA20000 */  lw        $v0, ($a1)
/* 110E8 80035CE8 96030000 */  lhu       $v1, ($s0)
/* 110EC 80035CEC 00441024 */  and       $v0, $v0, $a0
/* 110F0 80035CF0 24630001 */  addiu     $v1, $v1, 1
/* 110F4 80035CF4 ACA20000 */  sw        $v0, ($a1)
/* 110F8 80035CF8 0800D75B */  j         .L80035D6C
/* 110FC 80035CFC A6030000 */   sh       $v1, ($s0)
.L80035D00:
/* 11100 80035D00 0C00E57C */  jal       func_800395F0
/* 11104 80035D04 00000000 */   nop
/* 11108 80035D08 0C037DC8 */  jal       func_800DF720
/* 1110C 80035D0C 00000000 */   nop
/* 11110 80035D10 0C016680 */  jal       func_80059A00
/* 11114 80035D14 00000000 */   nop
/* 11118 80035D18 0C00B424 */  jal       func_8002D090
/* 1111C 80035D1C 00000000 */   nop
/* 11120 80035D20 3C04800A */  lui       $a0, %hi(D_8009E750)
/* 11124 80035D24 2484E750 */  addiu     $a0, $a0, %lo(D_8009E750)
/* 11128 80035D28 0C04F5A1 */  jal       func_8013D684
/* 1112C 80035D2C 00000000 */   nop
/* 11130 80035D30 00021400 */  sll       $v0, $v0, 0x10
/* 11134 80035D34 1040000D */  beqz      $v0, .L80035D6C
/* 11138 80035D38 00000000 */   nop
/* 1113C 80035D3C 3C028007 */  lui       $v0, %hi(D_8007417C)
/* 11140 80035D40 8C42417C */  lw        $v0, %lo(D_8007417C)($v0)
/* 11144 80035D44 80420071 */  lb        $v0, 0x71($v0)
/* 11148 80035D48 14400003 */  bnez      $v0, .L80035D58
/* 1114C 80035D4C 00000000 */   nop
/* 11150 80035D50 0C038061 */  jal       func_800E0184
/* 11154 80035D54 00000000 */   nop
.L80035D58:
/* 11158 80035D58 3C05BF80 */  lui       $a1, 0xbf80
/* 1115C 80035D5C 0C04F38E */  jal       func_8013CE38
/* 11160 80035D60 240400FF */   addiu    $a0, $zero, 0xff
/* 11164 80035D64 0C00CC60 */  jal       func_80033180
/* 11168 80035D68 24040004 */   addiu    $a0, $zero, 4
.L80035D6C:
/* 1116C 80035D6C 8FBF0014 */  lw        $ra, 0x14($sp)
/* 11170 80035D70 8FB00010 */  lw        $s0, 0x10($sp)
/* 11174 80035D74 03E00008 */  jr        $ra
/* 11178 80035D78 27BD0018 */   addiu    $sp, $sp, 0x18
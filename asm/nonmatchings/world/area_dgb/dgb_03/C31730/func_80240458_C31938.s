.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel func_80240458_C31938
/* C31938 80240458 27BDFFD0 */  addiu     $sp, $sp, -0x30
/* C3193C 8024045C AFBF0024 */  sw        $ra, 0x24($sp)
/* C31940 80240460 AFB40020 */  sw        $s4, 0x20($sp)
/* C31944 80240464 AFB3001C */  sw        $s3, 0x1c($sp)
/* C31948 80240468 AFB20018 */  sw        $s2, 0x18($sp)
/* C3194C 8024046C AFB10014 */  sw        $s1, 0x14($sp)
/* C31950 80240470 AFB00010 */  sw        $s0, 0x10($sp)
/* C31954 80240474 F7B40028 */  sdc1      $f20, 0x28($sp)
/* C31958 80240478 8C900148 */  lw        $s0, 0x148($a0)
/* C3195C 8024047C 86040008 */  lh        $a0, 8($s0)
/* C31960 80240480 0C00EABB */  jal       get_npc_unsafe
/* C31964 80240484 24110001 */   addiu    $s1, $zero, 1
/* C31968 80240488 86040008 */  lh        $a0, 8($s0)
/* C3196C 8024048C 0040802D */  daddu     $s0, $v0, $zero
/* C31970 80240490 3C05800B */  lui       $a1, %hi(gCameras)
/* C31974 80240494 24A51D80 */  addiu     $a1, $a1, %lo(gCameras)
/* C31978 80240498 3C03800A */  lui       $v1, 0x800a
/* C3197C 8024049C 8463A634 */  lh        $v1, -0x59cc($v1)
/* C31980 802404A0 00912021 */  addu      $a0, $a0, $s1
/* C31984 802404A4 00031080 */  sll       $v0, $v1, 2
/* C31988 802404A8 00431021 */  addu      $v0, $v0, $v1
/* C3198C 802404AC 00021080 */  sll       $v0, $v0, 2
/* C31990 802404B0 00431023 */  subu      $v0, $v0, $v1
/* C31994 802404B4 000218C0 */  sll       $v1, $v0, 3
/* C31998 802404B8 00431021 */  addu      $v0, $v0, $v1
/* C3199C 802404BC 000210C0 */  sll       $v0, $v0, 3
/* C319A0 802404C0 0C00FB3A */  jal       get_enemy
/* C319A4 802404C4 00459021 */   addu     $s2, $v0, $a1
/* C319A8 802404C8 3C14800F */  lui       $s4, %hi(gPlayerStatusPtr)
/* C319AC 802404CC 26947B30 */  addiu     $s4, $s4, %lo(gPlayerStatusPtr)
/* C319B0 802404D0 C60C0038 */  lwc1      $f12, 0x38($s0)
/* C319B4 802404D4 8E830000 */  lw        $v1, ($s4)
/* C319B8 802404D8 C60E0040 */  lwc1      $f14, 0x40($s0)
/* C319BC 802404DC 8C660028 */  lw        $a2, 0x28($v1)
/* C319C0 802404E0 8C670030 */  lw        $a3, 0x30($v1)
/* C319C4 802404E4 0C00A7B5 */  jal       dist2D
/* C319C8 802404E8 0040982D */   daddu    $s3, $v0, $zero
/* C319CC 802404EC C6620074 */  lwc1      $f2, 0x74($s3)
/* C319D0 802404F0 468010A0 */  cvt.s.w   $f2, $f2
/* C319D4 802404F4 4600103C */  c.lt.s    $f2, $f0
/* C319D8 802404F8 00000000 */  nop       
/* C319DC 802404FC 45030001 */  bc1tl     .L80240504
/* C319E0 80240500 0000882D */   daddu    $s1, $zero, $zero
.L80240504:
/* C319E4 80240504 C64C006C */  lwc1      $f12, 0x6c($s2)
/* C319E8 80240508 C60E000C */  lwc1      $f14, 0xc($s0)
/* C319EC 8024050C 3C014387 */  lui       $at, 0x4387
/* C319F0 80240510 4481A000 */  mtc1      $at, $f20
/* C319F4 80240514 0C00A70A */  jal       get_clamped_angle_diff
/* C319F8 80240518 00000000 */   nop      
/* C319FC 8024051C 0C00A6C9 */  jal       clamp_angle
/* C31A00 80240520 46000306 */   mov.s    $f12, $f0
/* C31A04 80240524 3C018024 */  lui       $at, 0x8024
/* C31A08 80240528 D42249F0 */  ldc1      $f2, 0x49f0($at)
/* C31A0C 8024052C 46000021 */  cvt.d.s   $f0, $f0
/* C31A10 80240530 4622003C */  c.lt.d    $f0, $f2
/* C31A14 80240534 00000000 */  nop       
/* C31A18 80240538 45000003 */  bc1f      .L80240548
/* C31A1C 8024053C 00000000 */   nop      
/* C31A20 80240540 3C0142B4 */  lui       $at, 0x42b4
/* C31A24 80240544 4481A000 */  mtc1      $at, $f20
.L80240548:
/* C31A28 80240548 C60C0038 */  lwc1      $f12, 0x38($s0)
/* C31A2C 8024054C 8E820000 */  lw        $v0, ($s4)
/* C31A30 80240550 C60E0040 */  lwc1      $f14, 0x40($s0)
/* C31A34 80240554 8C460028 */  lw        $a2, 0x28($v0)
/* C31A38 80240558 0C00A720 */  jal       atan2
/* C31A3C 8024055C 8C470030 */   lw       $a3, 0x30($v0)
/* C31A40 80240560 4600A306 */  mov.s     $f12, $f20
/* C31A44 80240564 0C00A70A */  jal       get_clamped_angle_diff
/* C31A48 80240568 46000386 */   mov.s    $f14, $f0
/* C31A4C 8024056C C6620078 */  lwc1      $f2, 0x78($s3)
/* C31A50 80240570 468010A0 */  cvt.s.w   $f2, $f2
/* C31A54 80240574 46000005 */  abs.s     $f0, $f0
/* C31A58 80240578 4600103C */  c.lt.s    $f2, $f0
/* C31A5C 8024057C 00000000 */  nop       
/* C31A60 80240580 45030001 */  bc1tl     .L80240588
/* C31A64 80240584 0000882D */   daddu    $s1, $zero, $zero
.L80240588:
/* C31A68 80240588 8E820000 */  lw        $v0, ($s4)
/* C31A6C 8024058C C600003C */  lwc1      $f0, 0x3c($s0)
/* C31A70 80240590 C442002C */  lwc1      $f2, 0x2c($v0)
/* C31A74 80240594 860200A8 */  lh        $v0, 0xa8($s0)
/* C31A78 80240598 46020001 */  sub.s     $f0, $f0, $f2
/* C31A7C 8024059C 44821000 */  mtc1      $v0, $f2
/* C31A80 802405A0 00000000 */  nop       
/* C31A84 802405A4 468010A1 */  cvt.d.w   $f2, $f2
/* C31A88 802405A8 46221080 */  add.d     $f2, $f2, $f2
/* C31A8C 802405AC 46000005 */  abs.s     $f0, $f0
/* C31A90 802405B0 46000021 */  cvt.d.s   $f0, $f0
/* C31A94 802405B4 4620103E */  c.le.d    $f2, $f0
/* C31A98 802405B8 00000000 */  nop       
/* C31A9C 802405BC 45030001 */  bc1tl     .L802405C4
/* C31AA0 802405C0 0000882D */   daddu    $s1, $zero, $zero
.L802405C4:
/* C31AA4 802405C4 3C038011 */  lui       $v1, 0x8011
/* C31AA8 802405C8 8063EBB3 */  lb        $v1, -0x144d($v1)
/* C31AAC 802405CC 24020009 */  addiu     $v0, $zero, 9
/* C31AB0 802405D0 50620001 */  beql      $v1, $v0, .L802405D8
/* C31AB4 802405D4 0000882D */   daddu    $s1, $zero, $zero
.L802405D8:
/* C31AB8 802405D8 24020007 */  addiu     $v0, $zero, 7
/* C31ABC 802405DC 50620001 */  beql      $v1, $v0, .L802405E4
/* C31AC0 802405E0 0000882D */   daddu    $s1, $zero, $zero
.L802405E4:
/* C31AC4 802405E4 0220102D */  daddu     $v0, $s1, $zero
/* C31AC8 802405E8 8FBF0024 */  lw        $ra, 0x24($sp)
/* C31ACC 802405EC 8FB40020 */  lw        $s4, 0x20($sp)
/* C31AD0 802405F0 8FB3001C */  lw        $s3, 0x1c($sp)
/* C31AD4 802405F4 8FB20018 */  lw        $s2, 0x18($sp)
/* C31AD8 802405F8 8FB10014 */  lw        $s1, 0x14($sp)
/* C31ADC 802405FC 8FB00010 */  lw        $s0, 0x10($sp)
/* C31AE0 80240600 D7B40028 */  ldc1      $f20, 0x28($sp)
/* C31AE4 80240604 03E00008 */  jr        $ra
/* C31AE8 80240608 27BD0030 */   addiu    $sp, $sp, 0x30
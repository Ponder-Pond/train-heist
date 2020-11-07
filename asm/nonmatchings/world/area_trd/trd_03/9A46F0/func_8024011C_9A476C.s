.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel func_8024011C_9A476C
/* 9A476C 8024011C 27BDFFD8 */  addiu     $sp, $sp, -0x28
/* 9A4770 80240120 AFB3001C */  sw        $s3, 0x1c($sp)
/* 9A4774 80240124 0080982D */  daddu     $s3, $a0, $zero
/* 9A4778 80240128 AFBF0020 */  sw        $ra, 0x20($sp)
/* 9A477C 8024012C AFB20018 */  sw        $s2, 0x18($sp)
/* 9A4780 80240130 AFB10014 */  sw        $s1, 0x14($sp)
/* 9A4784 80240134 AFB00010 */  sw        $s0, 0x10($sp)
/* 9A4788 80240138 8E710148 */  lw        $s1, 0x148($s3)
/* 9A478C 8024013C 86240008 */  lh        $a0, 8($s1)
/* 9A4790 80240140 0C00EABB */  jal       get_npc_unsafe
/* 9A4794 80240144 00A0902D */   daddu    $s2, $a1, $zero
/* 9A4798 80240148 0040802D */  daddu     $s0, $v0, $zero
/* 9A479C 8024014C 8602008E */  lh        $v0, 0x8e($s0)
/* 9A47A0 80240150 9603008E */  lhu       $v1, 0x8e($s0)
/* 9A47A4 80240154 18400005 */  blez      $v0, .L8024016C
/* 9A47A8 80240158 2462FFFF */   addiu    $v0, $v1, -1
/* 9A47AC 8024015C A602008E */  sh        $v0, 0x8e($s0)
/* 9A47B0 80240160 00021400 */  sll       $v0, $v0, 0x10
/* 9A47B4 80240164 1C400033 */  bgtz      $v0, .L80240234
/* 9A47B8 80240168 00000000 */   nop      
.L8024016C:
/* 9A47BC 8024016C 8602008C */  lh        $v0, 0x8c($s0)
/* 9A47C0 80240170 14400030 */  bnez      $v0, .L80240234
/* 9A47C4 80240174 00000000 */   nop      
/* 9A47C8 80240178 8E2200CC */  lw        $v0, 0xcc($s1)
/* 9A47CC 8024017C 8C420024 */  lw        $v0, 0x24($v0)
/* 9A47D0 80240180 AE020028 */  sw        $v0, 0x28($s0)
/* 9A47D4 80240184 C6400018 */  lwc1      $f0, 0x18($s2)
/* 9A47D8 80240188 E6000018 */  swc1      $f0, 0x18($s0)
/* 9A47DC 8024018C 8E230088 */  lw        $v1, 0x88($s1)
/* 9A47E0 80240190 24020005 */  addiu     $v0, $zero, 5
/* 9A47E4 80240194 10620005 */  beq       $v1, $v0, .L802401AC
/* 9A47E8 80240198 00000000 */   nop      
/* 9A47EC 8024019C 10600003 */  beqz      $v1, .L802401AC
/* 9A47F0 802401A0 24020001 */   addiu    $v0, $zero, 1
/* 9A47F4 802401A4 14620006 */  bne       $v1, $v0, .L802401C0
/* 9A47F8 802401A8 00000000 */   nop      
.L802401AC:
/* 9A47FC 802401AC 8E220084 */  lw        $v0, 0x84($s1)
/* 9A4800 802401B0 00021FC2 */  srl       $v1, $v0, 0x1f
/* 9A4804 802401B4 00431021 */  addu      $v0, $v0, $v1
/* 9A4808 802401B8 00021043 */  sra       $v0, $v0, 1
/* 9A480C 802401BC A60200A8 */  sh        $v0, 0xa8($s0)
.L802401C0:
/* 9A4810 802401C0 3C02800F */  lui       $v0, %hi(gPlayerStatusPtr)
/* 9A4814 802401C4 8C427B30 */  lw        $v0, %lo(gPlayerStatusPtr)($v0)
/* 9A4818 802401C8 C60C0038 */  lwc1      $f12, 0x38($s0)
/* 9A481C 802401CC C60E0040 */  lwc1      $f14, 0x40($s0)
/* 9A4820 802401D0 8C460028 */  lw        $a2, 0x28($v0)
/* 9A4824 802401D4 0C00A7B5 */  jal       dist2D
/* 9A4828 802401D8 8C470030 */   lw       $a3, 0x30($v0)
/* 9A482C 802401DC C6020018 */  lwc1      $f2, 0x18($s0)
/* 9A4830 802401E0 46020003 */  div.s     $f0, $f0, $f2
/* 9A4834 802401E4 3C018024 */  lui       $at, 0x8024
/* 9A4838 802401E8 D4223D40 */  ldc1      $f2, 0x3d40($at)
/* 9A483C 802401EC 46000021 */  cvt.d.s   $f0, $f0
/* 9A4840 802401F0 46220000 */  add.d     $f0, $f0, $f2
/* 9A4844 802401F4 4620010D */  trunc.w.d $f4, $f0
/* 9A4848 802401F8 44022000 */  mfc1      $v0, $f4
/* 9A484C 802401FC 00000000 */  nop       
/* 9A4850 80240200 A602008E */  sh        $v0, 0x8e($s0)
/* 9A4854 80240204 00021400 */  sll       $v0, $v0, 0x10
/* 9A4858 80240208 8E230078 */  lw        $v1, 0x78($s1)
/* 9A485C 8024020C 00021403 */  sra       $v0, $v0, 0x10
/* 9A4860 80240210 0043102A */  slt       $v0, $v0, $v1
/* 9A4864 80240214 10400003 */  beqz      $v0, .L80240224
/* 9A4868 80240218 00000000 */   nop      
/* 9A486C 8024021C 9622007A */  lhu       $v0, 0x7a($s1)
/* 9A4870 80240220 A602008E */  sh        $v0, 0x8e($s0)
.L80240224:
/* 9A4874 80240224 8602008E */  lh        $v0, 0x8e($s0)
/* 9A4878 80240228 AE22007C */  sw        $v0, 0x7c($s1)
/* 9A487C 8024022C 2402000E */  addiu     $v0, $zero, 0xe
/* 9A4880 80240230 AE620070 */  sw        $v0, 0x70($s3)
.L80240234:
/* 9A4884 80240234 8FBF0020 */  lw        $ra, 0x20($sp)
/* 9A4888 80240238 8FB3001C */  lw        $s3, 0x1c($sp)
/* 9A488C 8024023C 8FB20018 */  lw        $s2, 0x18($sp)
/* 9A4890 80240240 8FB10014 */  lw        $s1, 0x14($sp)
/* 9A4894 80240244 8FB00010 */  lw        $s0, 0x10($sp)
/* 9A4898 80240248 03E00008 */  jr        $ra
/* 9A489C 8024024C 27BD0028 */   addiu    $sp, $sp, 0x28
.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global avoidChk__Q29PSAutoBgm19MeloArr_RandomAvoidFRQ29PSAutoBgm10MeloArrArg
avoidChk__Q29PSAutoBgm19MeloArr_RandomAvoidFRQ29PSAutoBgm10MeloArrArg:
/* 8033EE9C 0033BDDC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8033EEA0 0033BDE0  7C 08 02 A6 */	mflr r0
/* 8033EEA4 0033BDE4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8033EEA8 0033BDE8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8033EEAC 0033BDEC  7C 7F 1B 78 */	mr r31, r3
/* 8033EEB0 0033BDF0  4B D7 B6 45 */	bl getRandom_0_1__7JALCalcFv
/* 8033EEB4 0033BDF4  C0 1F 00 1C */	lfs f0, 0x1c(r31)
/* 8033EEB8 0033BDF8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8033EEBC 0033BDFC  7C 00 00 26 */	mfcr r0
/* 8033EEC0 0033BE00  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8033EEC4 0033BE04  54 03 0F FE */	srwi r3, r0, 0x1f
/* 8033EEC8 0033BE08  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8033EECC 0033BE0C  7C 08 03 A6 */	mtlr r0
/* 8033EED0 0033BE10  38 21 00 10 */	addi r1, r1, 0x10
/* 8033EED4 0033BE14  4E 80 00 20 */	blr 

.global isToAvoid__Q29PSAutoBgm10MeloArrMgrFRQ29PSAutoBgm10MeloArrArg
isToAvoid__Q29PSAutoBgm10MeloArrMgrFRQ29PSAutoBgm10MeloArrArg:
/* 8033EED8 0033BE18  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8033EEDC 0033BE1C  7C 08 02 A6 */	mflr r0
/* 8033EEE0 0033BE20  90 01 00 24 */	stw r0, 0x24(r1)
/* 8033EEE4 0033BE24  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8033EEE8 0033BE28  7C 9F 23 78 */	mr r31, r4
/* 8033EEEC 0033BE2C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8033EEF0 0033BE30  7C 7E 1B 78 */	mr r30, r3
/* 8033EEF4 0033BE34  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8033EEF8 0033BE38  88 04 00 00 */	lbz r0, 0(r4)
/* 8033EEFC 0033BE3C  28 00 00 10 */	cmplwi r0, 0x10
/* 8033EF00 0033BE40  41 80 00 20 */	blt lbl_8033EF20
/* 8033EF04 0033BE44  3C 60 80 49 */	lis r3, lbl_80490010@ha
/* 8033EF08 0033BE48  3C A0 80 49 */	lis r5, lbl_8049002C@ha
/* 8033EF0C 0033BE4C  38 63 00 10 */	addi r3, r3, lbl_80490010@l
/* 8033EF10 0033BE50  38 80 00 59 */	li r4, 0x59
/* 8033EF14 0033BE54  38 A5 00 2C */	addi r5, r5, lbl_8049002C@l
/* 8033EF18 0033BE58  4C C6 31 82 */	crclr 6
/* 8033EF1C 0033BE5C  4B CE B7 25 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_8033EF20:
/* 8033EF20 0033BE60  88 1F 00 01 */	lbz r0, 1(r31)
/* 8033EF24 0033BE64  28 00 00 FF */	cmplwi r0, 0xff
/* 8033EF28 0033BE68  40 82 00 20 */	bne lbl_8033EF48
/* 8033EF2C 0033BE6C  3C 60 80 49 */	lis r3, lbl_80490010@ha
/* 8033EF30 0033BE70  3C A0 80 49 */	lis r5, lbl_8049002C@ha
/* 8033EF34 0033BE74  38 63 00 10 */	addi r3, r3, lbl_80490010@l
/* 8033EF38 0033BE78  38 80 00 5A */	li r4, 0x5a
/* 8033EF3C 0033BE7C  38 A5 00 2C */	addi r5, r5, lbl_8049002C@l
/* 8033EF40 0033BE80  4C C6 31 82 */	crclr 6
/* 8033EF44 0033BE84  4B CE B6 FD */	bl panic_f__12JUTExceptionFPCciPCce
lbl_8033EF48:
/* 8033EF48 0033BE88  88 1E 00 12 */	lbz r0, 0x12(r30)
/* 8033EF4C 0033BE8C  28 00 00 00 */	cmplwi r0, 0
/* 8033EF50 0033BE90  40 82 00 0C */	bne lbl_8033EF5C
/* 8033EF54 0033BE94  38 60 00 00 */	li r3, 0
/* 8033EF58 0033BE98  48 00 00 9C */	b lbl_8033EFF4
lbl_8033EF5C:
/* 8033EF5C 0033BE9C  A0 7E 00 10 */	lhz r3, 0x10(r30)
/* 8033EF60 0033BEA0  3B A0 00 00 */	li r29, 0
/* 8033EF64 0033BEA4  88 1F 00 00 */	lbz r0, 0(r31)
/* 8033EF68 0033BEA8  7C 60 06 30 */	sraw r0, r3, r0
/* 8033EF6C 0033BEAC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8033EF70 0033BEB0  41 82 00 80 */	beq lbl_8033EFF0
/* 8033EF74 0033BEB4  83 DE 00 04 */	lwz r30, 4(r30)
/* 8033EF78 0033BEB8  48 00 00 70 */	b lbl_8033EFE8
lbl_8033EF7C:
/* 8033EF7C 0033BEBC  80 7E 00 00 */	lwz r3, 0(r30)
/* 8033EF80 0033BEC0  7F E4 FB 78 */	mr r4, r31
/* 8033EF84 0033BEC4  81 83 00 14 */	lwz r12, 0x14(r3)
/* 8033EF88 0033BEC8  81 8C 00 1C */	lwz r12, 0x1c(r12)
/* 8033EF8C 0033BECC  7D 89 03 A6 */	mtctr r12
/* 8033EF90 0033BED0  4E 80 04 21 */	bctrl 
/* 8033EF94 0033BED4  57 A0 06 3F */	clrlwi. r0, r29, 0x18
/* 8033EF98 0033BED8  40 82 00 34 */	bne lbl_8033EFCC
/* 8033EF9C 0033BEDC  80 7E 00 00 */	lwz r3, 0(r30)
/* 8033EFA0 0033BEE0  88 03 00 19 */	lbz r0, 0x19(r3)
/* 8033EFA4 0033BEE4  28 00 00 01 */	cmplwi r0, 1
/* 8033EFA8 0033BEE8  40 82 00 1C */	bne lbl_8033EFC4
/* 8033EFAC 0033BEEC  81 83 00 14 */	lwz r12, 0x14(r3)
/* 8033EFB0 0033BEF0  7F E4 FB 78 */	mr r4, r31
/* 8033EFB4 0033BEF4  81 8C 00 24 */	lwz r12, 0x24(r12)
/* 8033EFB8 0033BEF8  7D 89 03 A6 */	mtctr r12
/* 8033EFBC 0033BEFC  4E 80 04 21 */	bctrl 
/* 8033EFC0 0033BF00  48 00 00 08 */	b lbl_8033EFC8
lbl_8033EFC4:
/* 8033EFC4 0033BF04  38 60 00 00 */	li r3, 0
lbl_8033EFC8:
/* 8033EFC8 0033BF08  7C 7D 1B 78 */	mr r29, r3
lbl_8033EFCC:
/* 8033EFCC 0033BF0C  80 7E 00 00 */	lwz r3, 0(r30)
/* 8033EFD0 0033BF10  7F E4 FB 78 */	mr r4, r31
/* 8033EFD4 0033BF14  81 83 00 14 */	lwz r12, 0x14(r3)
/* 8033EFD8 0033BF18  81 8C 00 20 */	lwz r12, 0x20(r12)
/* 8033EFDC 0033BF1C  7D 89 03 A6 */	mtctr r12
/* 8033EFE0 0033BF20  4E 80 04 21 */	bctrl 
/* 8033EFE4 0033BF24  83 DE 00 0C */	lwz r30, 0xc(r30)
lbl_8033EFE8:
/* 8033EFE8 0033BF28  28 1E 00 00 */	cmplwi r30, 0
/* 8033EFEC 0033BF2C  40 82 FF 90 */	bne lbl_8033EF7C
lbl_8033EFF0:
/* 8033EFF0 0033BF30  7F A3 EB 78 */	mr r3, r29
lbl_8033EFF4:
/* 8033EFF4 0033BF34  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8033EFF8 0033BF38  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8033EFFC 0033BF3C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8033F000 0033BF40  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8033F004 0033BF44  7C 08 03 A6 */	mtlr r0
/* 8033F008 0033BF48  38 21 00 20 */	addi r1, r1, 0x20
/* 8033F00C 0033BF4C  4E 80 00 20 */	blr 

.global post__Q29PSAutoBgm11MeloArrBaseFRQ29PSAutoBgm10MeloArrArg
post__Q29PSAutoBgm11MeloArrBaseFRQ29PSAutoBgm10MeloArrArg:
/* 8033F010 0033BF50  4E 80 00 20 */	blr 

.global pre__Q29PSAutoBgm11MeloArrBaseFRQ29PSAutoBgm10MeloArrArg
pre__Q29PSAutoBgm11MeloArrBaseFRQ29PSAutoBgm10MeloArrArg:
/* 8033F014 0033BF54  4E 80 00 20 */	blr 

.global directOn__Q29PSAutoBgm11MeloArrBaseFPQ29PSAutoBgm5Track
directOn__Q29PSAutoBgm11MeloArrBaseFPQ29PSAutoBgm5Track:
/* 8033F018 0033BF58  38 00 00 01 */	li r0, 1
/* 8033F01C 0033BF5C  98 03 00 19 */	stb r0, 0x19(r3)
/* 8033F020 0033BF60  4E 80 00 20 */	blr 

.global directOff__Q29PSAutoBgm11MeloArrBaseFPQ29PSAutoBgm5Track
directOff__Q29PSAutoBgm11MeloArrBaseFPQ29PSAutoBgm5Track:
/* 8033F024 0033BF64  38 00 00 00 */	li r0, 0
/* 8033F028 0033BF68  98 03 00 19 */	stb r0, 0x19(r3)
/* 8033F02C 0033BF6C  4E 80 00 20 */	blr 

.global __dt__Q29PSAutoBgm11MeloArrBaseFv
__dt__Q29PSAutoBgm11MeloArrBaseFv:
/* 8033F030 0033BF70  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8033F034 0033BF74  7C 08 02 A6 */	mflr r0
/* 8033F038 0033BF78  90 01 00 14 */	stw r0, 0x14(r1)
/* 8033F03C 0033BF7C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8033F040 0033BF80  7C 9F 23 78 */	mr r31, r4
/* 8033F044 0033BF84  93 C1 00 08 */	stw r30, 8(r1)
/* 8033F048 0033BF88  7C 7E 1B 79 */	or. r30, r3, r3
/* 8033F04C 0033BF8C  41 82 00 48 */	beq lbl_8033F094
/* 8033F050 0033BF90  3C 80 80 4E */	lis r4, __vt__Q29PSAutoBgm11MeloArrBase@ha
/* 8033F054 0033BF94  38 7E 00 10 */	addi r3, r30, 0x10
/* 8033F058 0033BF98  38 A4 AD E8 */	addi r5, r4, __vt__Q29PSAutoBgm11MeloArrBase@l
/* 8033F05C 0033BF9C  38 80 00 00 */	li r4, 0
/* 8033F060 0033BFA0  90 BE 00 14 */	stw r5, 0x14(r30)
/* 8033F064 0033BFA4  38 05 00 08 */	addi r0, r5, 8
/* 8033F068 0033BFA8  90 1E 00 10 */	stw r0, 0x10(r30)
/* 8033F06C 0033BFAC  4B D7 B1 91 */	bl __dt__10JADHioNodeFv
/* 8033F070 0033BFB0  28 1E 00 00 */	cmplwi r30, 0
/* 8033F074 0033BFB4  41 82 00 10 */	beq lbl_8033F084
/* 8033F078 0033BFB8  7F C3 F3 78 */	mr r3, r30
/* 8033F07C 0033BFBC  38 80 00 00 */	li r4, 0
/* 8033F080 0033BFC0  4B CE 77 51 */	bl __dt__10JSUPtrLinkFv
lbl_8033F084:
/* 8033F084 0033BFC4  7F E0 07 35 */	extsh. r0, r31
/* 8033F088 0033BFC8  40 81 00 0C */	ble lbl_8033F094
/* 8033F08C 0033BFCC  7F C3 F3 78 */	mr r3, r30
/* 8033F090 0033BFD0  4B CE 50 25 */	bl __dl__FPv
lbl_8033F094:
/* 8033F094 0033BFD4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8033F098 0033BFD8  7F C3 F3 78 */	mr r3, r30
/* 8033F09C 0033BFDC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8033F0A0 0033BFE0  83 C1 00 08 */	lwz r30, 8(r1)
/* 8033F0A4 0033BFE4  7C 08 03 A6 */	mtlr r0
/* 8033F0A8 0033BFE8  38 21 00 10 */	addi r1, r1, 0x10
/* 8033F0AC 0033BFEC  4E 80 00 20 */	blr 

.global __dt__Q29PSAutoBgm19MeloArr_RandomAvoidFv
__dt__Q29PSAutoBgm19MeloArr_RandomAvoidFv:
/* 8033F0B0 0033BFF0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8033F0B4 0033BFF4  7C 08 02 A6 */	mflr r0
/* 8033F0B8 0033BFF8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8033F0BC 0033BFFC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8033F0C0 0033C000  7C 9F 23 78 */	mr r31, r4
/* 8033F0C4 0033C004  93 C1 00 08 */	stw r30, 8(r1)
/* 8033F0C8 0033C008  7C 7E 1B 79 */	or. r30, r3, r3
/* 8033F0CC 0033C00C  41 82 00 60 */	beq lbl_8033F12C
/* 8033F0D0 0033C010  3C 60 80 4E */	lis r3, __vt__Q29PSAutoBgm19MeloArr_RandomAvoid@ha
/* 8033F0D4 0033C014  38 63 AE 14 */	addi r3, r3, __vt__Q29PSAutoBgm19MeloArr_RandomAvoid@l
/* 8033F0D8 0033C018  90 7E 00 14 */	stw r3, 0x14(r30)
/* 8033F0DC 0033C01C  38 03 00 08 */	addi r0, r3, 8
/* 8033F0E0 0033C020  90 1E 00 10 */	stw r0, 0x10(r30)
/* 8033F0E4 0033C024  41 82 00 38 */	beq lbl_8033F11C
/* 8033F0E8 0033C028  3C 80 80 4E */	lis r4, __vt__Q29PSAutoBgm11MeloArrBase@ha
/* 8033F0EC 0033C02C  38 7E 00 10 */	addi r3, r30, 0x10
/* 8033F0F0 0033C030  38 A4 AD E8 */	addi r5, r4, __vt__Q29PSAutoBgm11MeloArrBase@l
/* 8033F0F4 0033C034  38 80 00 00 */	li r4, 0
/* 8033F0F8 0033C038  90 BE 00 14 */	stw r5, 0x14(r30)
/* 8033F0FC 0033C03C  38 05 00 08 */	addi r0, r5, 8
/* 8033F100 0033C040  90 1E 00 10 */	stw r0, 0x10(r30)
/* 8033F104 0033C044  4B D7 B0 F9 */	bl __dt__10JADHioNodeFv
/* 8033F108 0033C048  28 1E 00 00 */	cmplwi r30, 0
/* 8033F10C 0033C04C  41 82 00 10 */	beq lbl_8033F11C
/* 8033F110 0033C050  7F C3 F3 78 */	mr r3, r30
/* 8033F114 0033C054  38 80 00 00 */	li r4, 0
/* 8033F118 0033C058  4B CE 76 B9 */	bl __dt__10JSUPtrLinkFv
lbl_8033F11C:
/* 8033F11C 0033C05C  7F E0 07 35 */	extsh. r0, r31
/* 8033F120 0033C060  40 81 00 0C */	ble lbl_8033F12C
/* 8033F124 0033C064  7F C3 F3 78 */	mr r3, r30
/* 8033F128 0033C068  4B CE 4F 8D */	bl __dl__FPv
lbl_8033F12C:
/* 8033F12C 0033C06C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8033F130 0033C070  7F C3 F3 78 */	mr r3, r30
/* 8033F134 0033C074  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8033F138 0033C078  83 C1 00 08 */	lwz r30, 8(r1)
/* 8033F13C 0033C07C  7C 08 03 A6 */	mtlr r0
/* 8033F140 0033C080  38 21 00 10 */	addi r1, r1, 0x10
/* 8033F144 0033C084  4E 80 00 20 */	blr 

.global "@16@__dt__Q29PSAutoBgm19MeloArr_RandomAvoidFv"
"@16@__dt__Q29PSAutoBgm19MeloArr_RandomAvoidFv":
/* 8033F148 0033C088  38 63 FF F0 */	addi r3, r3, -16
/* 8033F14C 0033C08C  4B FF FF 64 */	b __dt__Q29PSAutoBgm19MeloArr_RandomAvoidFv

.global "@16@__dt__Q29PSAutoBgm11MeloArrBaseFv"
"@16@__dt__Q29PSAutoBgm11MeloArrBaseFv":
/* 8033F150 0033C090  38 63 FF F0 */	addi r3, r3, -16
/* 8033F154 0033C094  4B FF FE DC */	b __dt__Q29PSAutoBgm11MeloArrBaseFv

.include "macros.inc"
.section .rodata  # 0x804732E0 - 0x8049E220
.balign 0x4
.global lbl_8049E1C8
lbl_8049E1C8:
	.4byte 0x50534D61
	.4byte 0x696E5369
	.4byte 0x64655F4F
	.4byte 0x626A4361
	.4byte 0x6C632E63
	.4byte 0x70700000
.global lbl_8049E1E0
lbl_8049E1E0:
	.4byte 0x50324173
	.4byte 0x73657274
	.4byte 0x00000000
	.4byte 0x82A082E8
	.4byte 0x82A682C8
	.4byte 0x82A28350
	.4byte 0x815B8358
	.4byte 0x31000000
	.4byte 0x82A082E8
	.4byte 0x82A682C8
	.4byte 0x82A28350
	.4byte 0x815B8358
	.4byte 0x32000000
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x00000000

.section .data, "wa"  # 0x8049E220 - 0x804EFC20
.balign 0x8
.global __vt__Q23PSM14ObjCalc_2PGame
__vt__Q23PSM14ObjCalc_2PGame:
  .4byte 0
  .4byte 0
  .4byte __dt__Q23PSM14ObjCalc_2PGameFv
  .4byte getPlayerNo__Q23PSM14ObjCalc_2PGameFPQ23PSM8Creature
  .4byte getPlayerNo__Q23PSM14ObjCalc_2PGameFR3Vec
  .4byte setMode__Q23PSM11ObjCalcBaseFQ33PSM11ObjCalcBase4Mode
  .4byte is1PGame__Q23PSM14ObjCalc_2PGameFv
.global __vt__Q23PSM18ObjCalc_SingleGame
__vt__Q23PSM18ObjCalc_SingleGame:
  .4byte 0
  .4byte 0
  .4byte __dt__Q23PSM18ObjCalc_SingleGameFv
  .4byte getPlayerNo__Q23PSM18ObjCalc_SingleGameFPQ23PSM8Creature
  .4byte getPlayerNo__Q23PSM18ObjCalc_SingleGameFR3Vec
  .4byte setMode__Q23PSM11ObjCalcBaseFQ33PSM11ObjCalcBase4Mode
  .4byte is1PGame__Q23PSM11ObjCalcBaseFv
  .4byte 0
  .4byte 0
  .4byte 0
  .4byte 0
  .4byte 0
  .4byte 0

.section .sdata2, "a"     # 0x80516360 - 0x80520E40
.balign 0x8
.global lbl_80520E28
lbl_80520E28:
	.float 100000.0
.global lbl_80520E2C
lbl_80520E2C:
	.float 1000000.0
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x00000000

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global newInstance_SingleGame__Q23PSM18ObjCalc_SingleGameFv
newInstance_SingleGame__Q23PSM18ObjCalc_SingleGameFv:
/* 804728A4 0046F7E4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 804728A8 0046F7E8  7C 08 02 A6 */	mflr r0
/* 804728AC 0046F7EC  38 60 00 0C */	li r3, 0xc
/* 804728B0 0046F7F0  90 01 00 14 */	stw r0, 0x14(r1)
/* 804728B4 0046F7F4  4B BB 15 F1 */	bl __nw__FUl
/* 804728B8 0046F7F8  28 03 00 00 */	cmplwi r3, 0
/* 804728BC 0046F7FC  41 82 00 38 */	beq lbl_804728F4
/* 804728C0 0046F800  3C 80 80 4F */	lis r4, "__vt__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@ha
/* 804728C4 0046F804  3C A0 80 4F */	lis r5, __vt__Q23PSM11ObjCalcBase@ha
/* 804728C8 0046F808  38 04 F5 5C */	addi r0, r4, "__vt__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@l
/* 804728CC 0046F80C  3C 80 80 4F */	lis r4, __vt__Q23PSM18ObjCalc_SingleGame@ha
/* 804728D0 0046F810  90 03 00 00 */	stw r0, 0(r3)
/* 804728D4 0046F814  38 C5 F5 68 */	addi r6, r5, __vt__Q23PSM11ObjCalcBase@l
/* 804728D8 0046F818  38 A0 00 00 */	li r5, 0
/* 804728DC 0046F81C  38 04 FB EC */	addi r0, r4, __vt__Q23PSM18ObjCalc_SingleGame@l
/* 804728E0 0046F820  90 6D 91 B4 */	stw r3, "sInstance__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@sda21(r13)
/* 804728E4 0046F824  90 C3 00 00 */	stw r6, 0(r3)
/* 804728E8 0046F828  90 A3 00 04 */	stw r5, 4(r3)
/* 804728EC 0046F82C  90 03 00 00 */	stw r0, 0(r3)
/* 804728F0 0046F830  98 A3 00 08 */	stb r5, 8(r3)
lbl_804728F4:
/* 804728F4 0046F834  80 01 00 14 */	lwz r0, 0x14(r1)
/* 804728F8 0046F838  7C 08 03 A6 */	mtlr r0
/* 804728FC 0046F83C  38 21 00 10 */	addi r1, r1, 0x10
/* 80472900 0046F840  4E 80 00 20 */	blr 

.global getPlayerNo__Q23PSM18ObjCalc_SingleGameFPQ23PSM8Creature
getPlayerNo__Q23PSM18ObjCalc_SingleGameFPQ23PSM8Creature:
/* 80472904 0046F844  88 63 00 08 */	lbz r3, 8(r3)
/* 80472908 0046F848  4E 80 00 20 */	blr 

.global getPlayerNo__Q23PSM18ObjCalc_SingleGameFR3Vec
getPlayerNo__Q23PSM18ObjCalc_SingleGameFR3Vec:
/* 8047290C 0046F84C  88 63 00 08 */	lbz r3, 8(r3)
/* 80472910 0046F850  4E 80 00 20 */	blr 

.global newInstance_2PGame__Q23PSM14ObjCalc_2PGameFv
newInstance_2PGame__Q23PSM14ObjCalc_2PGameFv:
/* 80472914 0046F854  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80472918 0046F858  7C 08 02 A6 */	mflr r0
/* 8047291C 0046F85C  38 60 00 08 */	li r3, 8
/* 80472920 0046F860  90 01 00 14 */	stw r0, 0x14(r1)
/* 80472924 0046F864  4B BB 15 81 */	bl __nw__FUl
/* 80472928 0046F868  28 03 00 00 */	cmplwi r3, 0
/* 8047292C 0046F86C  41 82 00 34 */	beq lbl_80472960
/* 80472930 0046F870  3C 80 80 4F */	lis r4, "__vt__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@ha
/* 80472934 0046F874  3C A0 80 4F */	lis r5, __vt__Q23PSM11ObjCalcBase@ha
/* 80472938 0046F878  38 04 F5 5C */	addi r0, r4, "__vt__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@l
/* 8047293C 0046F87C  3C 80 80 4F */	lis r4, __vt__Q23PSM14ObjCalc_2PGame@ha
/* 80472940 0046F880  90 03 00 00 */	stw r0, 0(r3)
/* 80472944 0046F884  38 C5 F5 68 */	addi r6, r5, __vt__Q23PSM11ObjCalcBase@l
/* 80472948 0046F888  38 A0 00 00 */	li r5, 0
/* 8047294C 0046F88C  38 04 FB D0 */	addi r0, r4, __vt__Q23PSM14ObjCalc_2PGame@l
/* 80472950 0046F890  90 6D 91 B4 */	stw r3, "sInstance__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@sda21(r13)
/* 80472954 0046F894  90 C3 00 00 */	stw r6, 0(r3)
/* 80472958 0046F898  90 A3 00 04 */	stw r5, 4(r3)
/* 8047295C 0046F89C  90 03 00 00 */	stw r0, 0(r3)
lbl_80472960:
/* 80472960 0046F8A0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80472964 0046F8A4  7C 08 03 A6 */	mtlr r0
/* 80472968 0046F8A8  38 21 00 10 */	addi r1, r1, 0x10
/* 8047296C 0046F8AC  4E 80 00 20 */	blr 

.global getPlayerNo__Q23PSM14ObjCalc_2PGameFR3Vec
getPlayerNo__Q23PSM14ObjCalc_2PGameFR3Vec:
/* 80472970 0046F8B0  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 80472974 0046F8B4  7C 08 02 A6 */	mflr r0
/* 80472978 0046F8B8  90 01 00 94 */	stw r0, 0x94(r1)
/* 8047297C 0046F8BC  93 E1 00 8C */	stw r31, 0x8c(r1)
/* 80472980 0046F8C0  93 C1 00 88 */	stw r30, 0x88(r1)
/* 80472984 0046F8C4  93 A1 00 84 */	stw r29, 0x84(r1)
/* 80472988 0046F8C8  7C 9D 23 78 */	mr r29, r4
/* 8047298C 0046F8CC  80 03 00 04 */	lwz r0, 4(r3)
/* 80472990 0046F8D0  2C 00 00 01 */	cmpwi r0, 1
/* 80472994 0046F8D4  41 82 00 14 */	beq lbl_804729A8
/* 80472998 0046F8D8  40 80 03 58 */	bge lbl_80472CF0
/* 8047299C 0046F8DC  2C 00 00 00 */	cmpwi r0, 0
/* 804729A0 0046F8E0  40 80 00 10 */	bge lbl_804729B0
/* 804729A4 0046F8E4  48 00 03 4C */	b lbl_80472CF0
lbl_804729A8:
/* 804729A8 0046F8E8  38 60 00 00 */	li r3, 0
/* 804729AC 0046F8EC  48 00 03 64 */	b lbl_80472D10
lbl_804729B0:
/* 804729B0 0046F8F0  38 00 00 00 */	li r0, 0
/* 804729B4 0046F8F4  80 C2 2A C8 */	lwz r6, lbl_80520E28@sda21(r2)
/* 804729B8 0046F8F8  80 A2 2A CC */	lwz r5, lbl_80520E2C@sda21(r2)
/* 804729BC 0046F8FC  3C 80 80 4B */	lis r4, "__vt__22Iterator<Q24Game4Navi>"@ha
/* 804729C0 0046F900  80 6D 92 E0 */	lwz r3, naviMgr__4Game@sda21(r13)
/* 804729C4 0046F904  38 84 BC B4 */	addi r4, r4, "__vt__22Iterator<Q24Game4Navi>"@l
/* 804729C8 0046F908  28 00 00 00 */	cmplwi r0, 0
/* 804729CC 0046F90C  90 C1 00 08 */	stw r6, 8(r1)
/* 804729D0 0046F910  3B C0 00 00 */	li r30, 0
/* 804729D4 0046F914  90 A1 00 0C */	stw r5, 0xc(r1)
/* 804729D8 0046F918  90 81 00 64 */	stw r4, 0x64(r1)
/* 804729DC 0046F91C  90 01 00 70 */	stw r0, 0x70(r1)
/* 804729E0 0046F920  90 01 00 68 */	stw r0, 0x68(r1)
/* 804729E4 0046F924  90 61 00 6C */	stw r3, 0x6c(r1)
/* 804729E8 0046F928  40 82 00 1C */	bne lbl_80472A04
/* 804729EC 0046F92C  81 83 00 00 */	lwz r12, 0(r3)
/* 804729F0 0046F930  81 8C 00 18 */	lwz r12, 0x18(r12)
/* 804729F4 0046F934  7D 89 03 A6 */	mtctr r12
/* 804729F8 0046F938  4E 80 04 21 */	bctrl 
/* 804729FC 0046F93C  90 61 00 68 */	stw r3, 0x68(r1)
/* 80472A00 0046F940  48 00 00 8C */	b lbl_80472A8C
lbl_80472A04:
/* 80472A04 0046F944  81 83 00 00 */	lwz r12, 0(r3)
/* 80472A08 0046F948  81 8C 00 18 */	lwz r12, 0x18(r12)
/* 80472A0C 0046F94C  7D 89 03 A6 */	mtctr r12
/* 80472A10 0046F950  4E 80 04 21 */	bctrl 
/* 80472A14 0046F954  90 61 00 68 */	stw r3, 0x68(r1)
/* 80472A18 0046F958  48 00 00 58 */	b lbl_80472A70
lbl_80472A1C:
/* 80472A1C 0046F95C  80 61 00 6C */	lwz r3, 0x6c(r1)
/* 80472A20 0046F960  80 81 00 68 */	lwz r4, 0x68(r1)
/* 80472A24 0046F964  81 83 00 00 */	lwz r12, 0(r3)
/* 80472A28 0046F968  81 8C 00 20 */	lwz r12, 0x20(r12)
/* 80472A2C 0046F96C  7D 89 03 A6 */	mtctr r12
/* 80472A30 0046F970  4E 80 04 21 */	bctrl 
/* 80472A34 0046F974  7C 64 1B 78 */	mr r4, r3
/* 80472A38 0046F978  80 61 00 70 */	lwz r3, 0x70(r1)
/* 80472A3C 0046F97C  81 83 00 00 */	lwz r12, 0(r3)
/* 80472A40 0046F980  81 8C 00 08 */	lwz r12, 8(r12)
/* 80472A44 0046F984  7D 89 03 A6 */	mtctr r12
/* 80472A48 0046F988  4E 80 04 21 */	bctrl 
/* 80472A4C 0046F98C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80472A50 0046F990  40 82 00 3C */	bne lbl_80472A8C
/* 80472A54 0046F994  80 61 00 6C */	lwz r3, 0x6c(r1)
/* 80472A58 0046F998  80 81 00 68 */	lwz r4, 0x68(r1)
/* 80472A5C 0046F99C  81 83 00 00 */	lwz r12, 0(r3)
/* 80472A60 0046F9A0  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 80472A64 0046F9A4  7D 89 03 A6 */	mtctr r12
/* 80472A68 0046F9A8  4E 80 04 21 */	bctrl 
/* 80472A6C 0046F9AC  90 61 00 68 */	stw r3, 0x68(r1)
lbl_80472A70:
/* 80472A70 0046F9B0  81 81 00 64 */	lwz r12, 0x64(r1)
/* 80472A74 0046F9B4  38 61 00 64 */	addi r3, r1, 0x64
/* 80472A78 0046F9B8  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 80472A7C 0046F9BC  7D 89 03 A6 */	mtctr r12
/* 80472A80 0046F9C0  4E 80 04 21 */	bctrl 
/* 80472A84 0046F9C4  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80472A88 0046F9C8  41 82 FF 94 */	beq lbl_80472A1C
lbl_80472A8C:
/* 80472A8C 0046F9CC  3B E1 00 08 */	addi r31, r1, 8
/* 80472A90 0046F9D0  48 00 02 20 */	b lbl_80472CB0
lbl_80472A94:
/* 80472A94 0046F9D4  80 61 00 6C */	lwz r3, 0x6c(r1)
/* 80472A98 0046F9D8  81 83 00 00 */	lwz r12, 0(r3)
/* 80472A9C 0046F9DC  81 8C 00 20 */	lwz r12, 0x20(r12)
/* 80472AA0 0046F9E0  7D 89 03 A6 */	mtctr r12
/* 80472AA4 0046F9E4  4E 80 04 21 */	bctrl 
/* 80472AA8 0046F9E8  7C 64 1B 78 */	mr r4, r3
/* 80472AAC 0046F9EC  38 61 00 4C */	addi r3, r1, 0x4c
/* 80472AB0 0046F9F0  81 84 00 00 */	lwz r12, 0(r4)
/* 80472AB4 0046F9F4  81 8C 00 08 */	lwz r12, 8(r12)
/* 80472AB8 0046F9F8  7D 89 03 A6 */	mtctr r12
/* 80472ABC 0046F9FC  4E 80 04 21 */	bctrl 
/* 80472AC0 0046FA00  C0 41 00 4C */	lfs f2, 0x4c(r1)
/* 80472AC4 0046FA04  34 01 00 58 */	addic. r0, r1, 0x58
/* 80472AC8 0046FA08  C0 21 00 50 */	lfs f1, 0x50(r1)
/* 80472ACC 0046FA0C  C0 01 00 54 */	lfs f0, 0x54(r1)
/* 80472AD0 0046FA10  D0 41 00 58 */	stfs f2, 0x58(r1)
/* 80472AD4 0046FA14  D0 21 00 5C */	stfs f1, 0x5c(r1)
/* 80472AD8 0046FA18  D0 01 00 60 */	stfs f0, 0x60(r1)
/* 80472ADC 0046FA1C  40 82 00 20 */	bne lbl_80472AFC
/* 80472AE0 0046FA20  3C 60 80 4A */	lis r3, lbl_8049E1C8@ha
/* 80472AE4 0046FA24  3C A0 80 4A */	lis r5, lbl_8049E1E0@ha
/* 80472AE8 0046FA28  38 63 E1 C8 */	addi r3, r3, lbl_8049E1C8@l
/* 80472AEC 0046FA2C  38 80 00 41 */	li r4, 0x41
/* 80472AF0 0046FA30  38 A5 E1 E0 */	addi r5, r5, lbl_8049E1E0@l
/* 80472AF4 0046FA34  4C C6 31 82 */	crclr 6
/* 80472AF8 0046FA38  4B BB 7B 49 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_80472AFC:
/* 80472AFC 0046FA3C  2C 1E 00 02 */	cmpwi r30, 2
/* 80472B00 0046FA40  41 80 00 20 */	blt lbl_80472B20
/* 80472B04 0046FA44  3C 60 80 4A */	lis r3, lbl_8049E1C8@ha
/* 80472B08 0046FA48  3C A0 80 4A */	lis r5, lbl_8049E1E0@ha
/* 80472B0C 0046FA4C  38 63 E1 C8 */	addi r3, r3, lbl_8049E1C8@l
/* 80472B10 0046FA50  38 80 00 42 */	li r4, 0x42
/* 80472B14 0046FA54  38 A5 E1 E0 */	addi r5, r5, lbl_8049E1E0@l
/* 80472B18 0046FA58  4C C6 31 82 */	crclr 6
/* 80472B1C 0046FA5C  4B BB 7B 25 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_80472B20:
/* 80472B20 0046FA60  C0 01 00 58 */	lfs f0, 0x58(r1)
/* 80472B24 0046FA64  3B DE 00 01 */	addi r30, r30, 1
/* 80472B28 0046FA68  C0 21 00 5C */	lfs f1, 0x5c(r1)
/* 80472B2C 0046FA6C  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 80472B30 0046FA70  C0 01 00 60 */	lfs f0, 0x60(r1)
/* 80472B34 0046FA74  D0 21 00 38 */	stfs f1, 0x38(r1)
/* 80472B38 0046FA78  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80472B3C 0046FA7C  80 61 00 38 */	lwz r3, 0x38(r1)
/* 80472B40 0046FA80  90 01 00 40 */	stw r0, 0x40(r1)
/* 80472B44 0046FA84  C0 3D 00 00 */	lfs f1, 0(r29)
/* 80472B48 0046FA88  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 80472B4C 0046FA8C  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 80472B50 0046FA90  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80472B54 0046FA94  EC 61 00 28 */	fsubs f3, f1, f0
/* 80472B58 0046FA98  90 61 00 44 */	stw r3, 0x44(r1)
/* 80472B5C 0046FA9C  C0 5D 00 04 */	lfs f2, 4(r29)
/* 80472B60 0046FAA0  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 80472B64 0046FAA4  90 01 00 48 */	stw r0, 0x48(r1)
/* 80472B68 0046FAA8  EC 42 00 28 */	fsubs f2, f2, f0
/* 80472B6C 0046FAAC  C0 3D 00 08 */	lfs f1, 8(r29)
/* 80472B70 0046FAB0  C0 01 00 48 */	lfs f0, 0x48(r1)
/* 80472B74 0046FAB4  D0 61 00 28 */	stfs f3, 0x28(r1)
/* 80472B78 0046FAB8  EC 01 00 28 */	fsubs f0, f1, f0
/* 80472B7C 0046FABC  80 01 00 70 */	lwz r0, 0x70(r1)
/* 80472B80 0046FAC0  D0 41 00 2C */	stfs f2, 0x2c(r1)
/* 80472B84 0046FAC4  80 81 00 28 */	lwz r4, 0x28(r1)
/* 80472B88 0046FAC8  28 00 00 00 */	cmplwi r0, 0
/* 80472B8C 0046FACC  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 80472B90 0046FAD0  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 80472B94 0046FAD4  90 81 00 10 */	stw r4, 0x10(r1)
/* 80472B98 0046FAD8  80 01 00 30 */	lwz r0, 0x30(r1)
/* 80472B9C 0046FADC  90 61 00 14 */	stw r3, 0x14(r1)
/* 80472BA0 0046FAE0  C0 21 00 10 */	lfs f1, 0x10(r1)
/* 80472BA4 0046FAE4  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 80472BA8 0046FAE8  EC 41 00 72 */	fmuls f2, f1, f1
/* 80472BAC 0046FAEC  90 01 00 18 */	stw r0, 0x18(r1)
/* 80472BB0 0046FAF0  EC 20 00 32 */	fmuls f1, f0, f0
/* 80472BB4 0046FAF4  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 80472BB8 0046FAF8  D0 41 00 10 */	stfs f2, 0x10(r1)
/* 80472BBC 0046FAFC  EC 00 00 32 */	fmuls f0, f0, f0
/* 80472BC0 0046FB00  D0 21 00 14 */	stfs f1, 0x14(r1)
/* 80472BC4 0046FB04  80 01 00 10 */	lwz r0, 0x10(r1)
/* 80472BC8 0046FB08  80 61 00 14 */	lwz r3, 0x14(r1)
/* 80472BCC 0046FB0C  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80472BD0 0046FB10  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80472BD4 0046FB14  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 80472BD8 0046FB18  90 61 00 20 */	stw r3, 0x20(r1)
/* 80472BDC 0046FB1C  80 01 00 18 */	lwz r0, 0x18(r1)
/* 80472BE0 0046FB20  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 80472BE4 0046FB24  90 01 00 24 */	stw r0, 0x24(r1)
/* 80472BE8 0046FB28  EC 01 00 2A */	fadds f0, f1, f0
/* 80472BEC 0046FB2C  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80472BF0 0046FB30  EC 01 00 2A */	fadds f0, f1, f0
/* 80472BF4 0046FB34  D0 1F 00 00 */	stfs f0, 0(r31)
/* 80472BF8 0046FB38  3B FF 00 04 */	addi r31, r31, 4
/* 80472BFC 0046FB3C  40 82 00 24 */	bne lbl_80472C20
/* 80472C00 0046FB40  80 61 00 6C */	lwz r3, 0x6c(r1)
/* 80472C04 0046FB44  80 81 00 68 */	lwz r4, 0x68(r1)
/* 80472C08 0046FB48  81 83 00 00 */	lwz r12, 0(r3)
/* 80472C0C 0046FB4C  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 80472C10 0046FB50  7D 89 03 A6 */	mtctr r12
/* 80472C14 0046FB54  4E 80 04 21 */	bctrl 
/* 80472C18 0046FB58  90 61 00 68 */	stw r3, 0x68(r1)
/* 80472C1C 0046FB5C  48 00 00 94 */	b lbl_80472CB0
lbl_80472C20:
/* 80472C20 0046FB60  80 61 00 6C */	lwz r3, 0x6c(r1)
/* 80472C24 0046FB64  80 81 00 68 */	lwz r4, 0x68(r1)
/* 80472C28 0046FB68  81 83 00 00 */	lwz r12, 0(r3)
/* 80472C2C 0046FB6C  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 80472C30 0046FB70  7D 89 03 A6 */	mtctr r12
/* 80472C34 0046FB74  4E 80 04 21 */	bctrl 
/* 80472C38 0046FB78  90 61 00 68 */	stw r3, 0x68(r1)
/* 80472C3C 0046FB7C  48 00 00 58 */	b lbl_80472C94
lbl_80472C40:
/* 80472C40 0046FB80  80 61 00 6C */	lwz r3, 0x6c(r1)
/* 80472C44 0046FB84  80 81 00 68 */	lwz r4, 0x68(r1)
/* 80472C48 0046FB88  81 83 00 00 */	lwz r12, 0(r3)
/* 80472C4C 0046FB8C  81 8C 00 20 */	lwz r12, 0x20(r12)
/* 80472C50 0046FB90  7D 89 03 A6 */	mtctr r12
/* 80472C54 0046FB94  4E 80 04 21 */	bctrl 
/* 80472C58 0046FB98  7C 64 1B 78 */	mr r4, r3
/* 80472C5C 0046FB9C  80 61 00 70 */	lwz r3, 0x70(r1)
/* 80472C60 0046FBA0  81 83 00 00 */	lwz r12, 0(r3)
/* 80472C64 0046FBA4  81 8C 00 08 */	lwz r12, 8(r12)
/* 80472C68 0046FBA8  7D 89 03 A6 */	mtctr r12
/* 80472C6C 0046FBAC  4E 80 04 21 */	bctrl 
/* 80472C70 0046FBB0  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80472C74 0046FBB4  40 82 00 3C */	bne lbl_80472CB0
/* 80472C78 0046FBB8  80 61 00 6C */	lwz r3, 0x6c(r1)
/* 80472C7C 0046FBBC  80 81 00 68 */	lwz r4, 0x68(r1)
/* 80472C80 0046FBC0  81 83 00 00 */	lwz r12, 0(r3)
/* 80472C84 0046FBC4  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 80472C88 0046FBC8  7D 89 03 A6 */	mtctr r12
/* 80472C8C 0046FBCC  4E 80 04 21 */	bctrl 
/* 80472C90 0046FBD0  90 61 00 68 */	stw r3, 0x68(r1)
lbl_80472C94:
/* 80472C94 0046FBD4  81 81 00 64 */	lwz r12, 0x64(r1)
/* 80472C98 0046FBD8  38 61 00 64 */	addi r3, r1, 0x64
/* 80472C9C 0046FBDC  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 80472CA0 0046FBE0  7D 89 03 A6 */	mtctr r12
/* 80472CA4 0046FBE4  4E 80 04 21 */	bctrl 
/* 80472CA8 0046FBE8  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80472CAC 0046FBEC  41 82 FF 94 */	beq lbl_80472C40
lbl_80472CB0:
/* 80472CB0 0046FBF0  80 61 00 6C */	lwz r3, 0x6c(r1)
/* 80472CB4 0046FBF4  81 83 00 00 */	lwz r12, 0(r3)
/* 80472CB8 0046FBF8  81 8C 00 1C */	lwz r12, 0x1c(r12)
/* 80472CBC 0046FBFC  7D 89 03 A6 */	mtctr r12
/* 80472CC0 0046FC00  4E 80 04 21 */	bctrl 
/* 80472CC4 0046FC04  80 81 00 68 */	lwz r4, 0x68(r1)
/* 80472CC8 0046FC08  7C 04 18 40 */	cmplw r4, r3
/* 80472CCC 0046FC0C  40 82 FD C8 */	bne lbl_80472A94
/* 80472CD0 0046FC10  C0 21 00 08 */	lfs f1, 8(r1)
/* 80472CD4 0046FC14  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 80472CD8 0046FC18  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80472CDC 0046FC1C  7C 00 00 26 */	mfcr r0
/* 80472CE0 0046FC20  54 00 0F FE */	srwi r0, r0, 0x1f
/* 80472CE4 0046FC24  7C 00 00 34 */	cntlzw r0, r0
/* 80472CE8 0046FC28  54 03 D9 7E */	srwi r3, r0, 5
/* 80472CEC 0046FC2C  48 00 00 24 */	b lbl_80472D10
lbl_80472CF0:
/* 80472CF0 0046FC30  3C 60 80 4A */	lis r3, lbl_8049E1C8@ha
/* 80472CF4 0046FC34  3C A0 80 4A */	lis r5, lbl_8049E1E0@ha
/* 80472CF8 0046FC38  38 63 E1 C8 */	addi r3, r3, lbl_8049E1C8@l
/* 80472CFC 0046FC3C  38 80 00 4D */	li r4, 0x4d
/* 80472D00 0046FC40  38 A5 E1 E0 */	addi r5, r5, lbl_8049E1E0@l
/* 80472D04 0046FC44  4C C6 31 82 */	crclr 6
/* 80472D08 0046FC48  4B BB 79 39 */	bl panic_f__12JUTExceptionFPCciPCce
/* 80472D0C 0046FC4C  38 60 00 00 */	li r3, 0
lbl_80472D10:
/* 80472D10 0046FC50  80 01 00 94 */	lwz r0, 0x94(r1)
/* 80472D14 0046FC54  83 E1 00 8C */	lwz r31, 0x8c(r1)
/* 80472D18 0046FC58  83 C1 00 88 */	lwz r30, 0x88(r1)
/* 80472D1C 0046FC5C  83 A1 00 84 */	lwz r29, 0x84(r1)
/* 80472D20 0046FC60  7C 08 03 A6 */	mtlr r0
/* 80472D24 0046FC64  38 21 00 90 */	addi r1, r1, 0x90
/* 80472D28 0046FC68  4E 80 00 20 */	blr 

.global getPlayerNo__Q23PSM14ObjCalc_2PGameFPQ23PSM8Creature
getPlayerNo__Q23PSM14ObjCalc_2PGameFPQ23PSM8Creature:
/* 80472D2C 0046FC6C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80472D30 0046FC70  7C 08 02 A6 */	mflr r0
/* 80472D34 0046FC74  90 01 00 24 */	stw r0, 0x24(r1)
/* 80472D38 0046FC78  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80472D3C 0046FC7C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80472D40 0046FC80  7C 9E 23 79 */	or. r30, r4, r4
/* 80472D44 0046FC84  3C 80 80 4A */	lis r4, lbl_8049E1C8@ha
/* 80472D48 0046FC88  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80472D4C 0046FC8C  7C 7D 1B 78 */	mr r29, r3
/* 80472D50 0046FC90  3B E4 E1 C8 */	addi r31, r4, lbl_8049E1C8@l
/* 80472D54 0046FC94  40 82 00 18 */	bne lbl_80472D6C
/* 80472D58 0046FC98  38 7F 00 00 */	addi r3, r31, 0
/* 80472D5C 0046FC9C  38 BF 00 18 */	addi r5, r31, 0x18
/* 80472D60 0046FCA0  38 80 00 57 */	li r4, 0x57
/* 80472D64 0046FCA4  4C C6 31 82 */	crclr 6
/* 80472D68 0046FCA8  4B BB 78 D9 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_80472D6C:
/* 80472D6C 0046FCAC  80 1D 00 04 */	lwz r0, 4(r29)
/* 80472D70 0046FCB0  2C 00 00 01 */	cmpwi r0, 1
/* 80472D74 0046FCB4  41 82 00 14 */	beq lbl_80472D88
/* 80472D78 0046FCB8  40 80 00 34 */	bge lbl_80472DAC
/* 80472D7C 0046FCBC  2C 00 00 00 */	cmpwi r0, 0
/* 80472D80 0046FCC0  40 80 00 10 */	bge lbl_80472D90
/* 80472D84 0046FCC4  48 00 00 28 */	b lbl_80472DAC
lbl_80472D88:
/* 80472D88 0046FCC8  38 60 00 00 */	li r3, 0
/* 80472D8C 0046FCCC  48 00 00 4C */	b lbl_80472DD8
lbl_80472D90:
/* 80472D90 0046FCD0  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 80472D94 0046FCD4  81 83 00 00 */	lwz r12, 0(r3)
/* 80472D98 0046FCD8  81 8C 00 FC */	lwz r12, 0xfc(r12)
/* 80472D9C 0046FCDC  7D 89 03 A6 */	mtctr r12
/* 80472DA0 0046FCE0  4E 80 04 21 */	bctrl 
/* 80472DA4 0046FCE4  88 63 00 01 */	lbz r3, 1(r3)
/* 80472DA8 0046FCE8  48 00 00 30 */	b lbl_80472DD8
lbl_80472DAC:
/* 80472DAC 0046FCEC  38 7F 00 00 */	addi r3, r31, 0
/* 80472DB0 0046FCF0  38 BF 00 24 */	addi r5, r31, 0x24
/* 80472DB4 0046FCF4  38 80 00 7D */	li r4, 0x7d
/* 80472DB8 0046FCF8  4C C6 31 82 */	crclr 6
/* 80472DBC 0046FCFC  4B BB 78 85 */	bl panic_f__12JUTExceptionFPCciPCce
/* 80472DC0 0046FD00  38 7F 00 00 */	addi r3, r31, 0
/* 80472DC4 0046FD04  38 BF 00 38 */	addi r5, r31, 0x38
/* 80472DC8 0046FD08  38 80 00 80 */	li r4, 0x80
/* 80472DCC 0046FD0C  4C C6 31 82 */	crclr 6
/* 80472DD0 0046FD10  4B BB 78 71 */	bl panic_f__12JUTExceptionFPCciPCce
/* 80472DD4 0046FD14  38 60 00 00 */	li r3, 0
lbl_80472DD8:
/* 80472DD8 0046FD18  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80472DDC 0046FD1C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80472DE0 0046FD20  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80472DE4 0046FD24  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80472DE8 0046FD28  7C 08 03 A6 */	mtlr r0
/* 80472DEC 0046FD2C  38 21 00 20 */	addi r1, r1, 0x20
/* 80472DF0 0046FD30  4E 80 00 20 */	blr 

.global __dt__Q23PSM18ObjCalc_SingleGameFv
__dt__Q23PSM18ObjCalc_SingleGameFv:
/* 80472DF4 0046FD34  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80472DF8 0046FD38  7C 08 02 A6 */	mflr r0
/* 80472DFC 0046FD3C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80472E00 0046FD40  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80472E04 0046FD44  7C 7F 1B 79 */	or. r31, r3, r3
/* 80472E08 0046FD48  41 82 00 48 */	beq lbl_80472E50
/* 80472E0C 0046FD4C  3C 60 80 4F */	lis r3, __vt__Q23PSM18ObjCalc_SingleGame@ha
/* 80472E10 0046FD50  38 03 FB EC */	addi r0, r3, __vt__Q23PSM18ObjCalc_SingleGame@l
/* 80472E14 0046FD54  90 1F 00 00 */	stw r0, 0(r31)
/* 80472E18 0046FD58  41 82 00 28 */	beq lbl_80472E40
/* 80472E1C 0046FD5C  3C 60 80 4F */	lis r3, __vt__Q23PSM11ObjCalcBase@ha
/* 80472E20 0046FD60  38 03 F5 68 */	addi r0, r3, __vt__Q23PSM11ObjCalcBase@l
/* 80472E24 0046FD64  90 1F 00 00 */	stw r0, 0(r31)
/* 80472E28 0046FD68  41 82 00 18 */	beq lbl_80472E40
/* 80472E2C 0046FD6C  3C 60 80 4F */	lis r3, "__vt__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@ha
/* 80472E30 0046FD70  38 00 00 00 */	li r0, 0
/* 80472E34 0046FD74  38 63 F5 5C */	addi r3, r3, "__vt__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@l
/* 80472E38 0046FD78  90 7F 00 00 */	stw r3, 0(r31)
/* 80472E3C 0046FD7C  90 0D 91 B4 */	stw r0, "sInstance__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@sda21(r13)
lbl_80472E40:
/* 80472E40 0046FD80  7C 80 07 35 */	extsh. r0, r4
/* 80472E44 0046FD84  40 81 00 0C */	ble lbl_80472E50
/* 80472E48 0046FD88  7F E3 FB 78 */	mr r3, r31
/* 80472E4C 0046FD8C  4B BB 12 69 */	bl __dl__FPv
lbl_80472E50:
/* 80472E50 0046FD90  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80472E54 0046FD94  7F E3 FB 78 */	mr r3, r31
/* 80472E58 0046FD98  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80472E5C 0046FD9C  7C 08 03 A6 */	mtlr r0
/* 80472E60 0046FDA0  38 21 00 10 */	addi r1, r1, 0x10
/* 80472E64 0046FDA4  4E 80 00 20 */	blr 

.global __dt__Q23PSM14ObjCalc_2PGameFv
__dt__Q23PSM14ObjCalc_2PGameFv:
/* 80472E68 0046FDA8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80472E6C 0046FDAC  7C 08 02 A6 */	mflr r0
/* 80472E70 0046FDB0  90 01 00 14 */	stw r0, 0x14(r1)
/* 80472E74 0046FDB4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80472E78 0046FDB8  7C 7F 1B 79 */	or. r31, r3, r3
/* 80472E7C 0046FDBC  41 82 00 48 */	beq lbl_80472EC4
/* 80472E80 0046FDC0  3C 60 80 4F */	lis r3, __vt__Q23PSM14ObjCalc_2PGame@ha
/* 80472E84 0046FDC4  38 03 FB D0 */	addi r0, r3, __vt__Q23PSM14ObjCalc_2PGame@l
/* 80472E88 0046FDC8  90 1F 00 00 */	stw r0, 0(r31)
/* 80472E8C 0046FDCC  41 82 00 28 */	beq lbl_80472EB4
/* 80472E90 0046FDD0  3C 60 80 4F */	lis r3, __vt__Q23PSM11ObjCalcBase@ha
/* 80472E94 0046FDD4  38 03 F5 68 */	addi r0, r3, __vt__Q23PSM11ObjCalcBase@l
/* 80472E98 0046FDD8  90 1F 00 00 */	stw r0, 0(r31)
/* 80472E9C 0046FDDC  41 82 00 18 */	beq lbl_80472EB4
/* 80472EA0 0046FDE0  3C 60 80 4F */	lis r3, "__vt__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@ha
/* 80472EA4 0046FDE4  38 00 00 00 */	li r0, 0
/* 80472EA8 0046FDE8  38 63 F5 5C */	addi r3, r3, "__vt__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@l
/* 80472EAC 0046FDEC  90 7F 00 00 */	stw r3, 0(r31)
/* 80472EB0 0046FDF0  90 0D 91 B4 */	stw r0, "sInstance__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@sda21(r13)
lbl_80472EB4:
/* 80472EB4 0046FDF4  7C 80 07 35 */	extsh. r0, r4
/* 80472EB8 0046FDF8  40 81 00 0C */	ble lbl_80472EC4
/* 80472EBC 0046FDFC  7F E3 FB 78 */	mr r3, r31
/* 80472EC0 0046FE00  4B BB 11 F5 */	bl __dl__FPv
lbl_80472EC4:
/* 80472EC4 0046FE04  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80472EC8 0046FE08  7F E3 FB 78 */	mr r3, r31
/* 80472ECC 0046FE0C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80472ED0 0046FE10  7C 08 03 A6 */	mtlr r0
/* 80472ED4 0046FE14  38 21 00 10 */	addi r1, r1, 0x10
/* 80472ED8 0046FE18  4E 80 00 20 */	blr 

.global is1PGame__Q23PSM14ObjCalc_2PGameFv
is1PGame__Q23PSM14ObjCalc_2PGameFv:
/* 80472EDC 0046FE1C  38 60 00 00 */	li r3, 0
/* 80472EE0 0046FE20  4E 80 00 20 */	blr 
/* 80472EE4 0046FE24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80472EE8 0046FE28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80472EEC 0046FE2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80472EF0 0046FE30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80472EF4 0046FE34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80472EF8 0046FE38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80472EFC 0046FE3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */

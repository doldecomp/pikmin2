.include "macros.inc"
.section .sbss # 0x80514D80 - 0x80516360
.balign 0x8
.global __GDCurrentDL
__GDCurrentDL:
	.skip 0x4
.global overflowcb
overflowcb:
	.skip 0x4

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global GDInitGDLObj
GDInitGDLObj:
/* 800E1B04 000DEA44  90 83 00 00 */	stw r4, 0(r3)
/* 800E1B08 000DEA48  7C 04 2A 14 */	add r0, r4, r5
/* 800E1B0C 000DEA4C  90 83 00 08 */	stw r4, 8(r3)
/* 800E1B10 000DEA50  90 03 00 0C */	stw r0, 0xc(r3)
/* 800E1B14 000DEA54  90 A3 00 04 */	stw r5, 4(r3)
/* 800E1B18 000DEA58  4E 80 00 20 */	blr 

.global GDFlushCurrToMem
GDFlushCurrToMem:
/* 800E1B1C 000DEA5C  7C 08 02 A6 */	mflr r0
/* 800E1B20 000DEA60  90 01 00 04 */	stw r0, 4(r1)
/* 800E1B24 000DEA64  94 21 FF F8 */	stwu r1, -8(r1)
/* 800E1B28 000DEA68  80 8D 8E A8 */	lwz r4, __GDCurrentDL@sda21(r13)
/* 800E1B2C 000DEA6C  80 64 00 00 */	lwz r3, 0(r4)
/* 800E1B30 000DEA70  80 84 00 04 */	lwz r4, 4(r4)
/* 800E1B34 000DEA74  48 00 AB E5 */	bl DCFlushRange
/* 800E1B38 000DEA78  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800E1B3C 000DEA7C  38 21 00 08 */	addi r1, r1, 8
/* 800E1B40 000DEA80  7C 08 03 A6 */	mtlr r0
/* 800E1B44 000DEA84  4E 80 00 20 */	blr 

.global GDPadCurr32
GDPadCurr32:
/* 800E1B48 000DEA88  80 6D 8E A8 */	lwz r3, __GDCurrentDL@sda21(r13)
/* 800E1B4C 000DEA8C  80 03 00 08 */	lwz r0, 8(r3)
/* 800E1B50 000DEA90  54 00 06 FF */	clrlwi. r0, r0, 0x1b
/* 800E1B54 000DEA94  4D 82 00 20 */	beqlr 
/* 800E1B58 000DEA98  28 00 00 20 */	cmplwi r0, 0x20
/* 800E1B5C 000DEA9C  20 60 00 20 */	subfic r3, r0, 0x20
/* 800E1B60 000DEAA0  38 C0 00 00 */	li r6, 0
/* 800E1B64 000DEAA4  4C 80 00 20 */	bgelr 
/* 800E1B68 000DEAA8  54 60 E8 FF */	rlwinm. r0, r3, 0x1d, 3, 0x1f
/* 800E1B6C 000DEAAC  7C 09 03 A6 */	mtctr r0
/* 800E1B70 000DEAB0  41 82 00 B0 */	beq lbl_800E1C20
lbl_800E1B74:
/* 800E1B74 000DEAB4  80 AD 8E A8 */	lwz r5, __GDCurrentDL@sda21(r13)
/* 800E1B78 000DEAB8  80 85 00 08 */	lwz r4, 8(r5)
/* 800E1B7C 000DEABC  38 04 00 01 */	addi r0, r4, 1
/* 800E1B80 000DEAC0  90 05 00 08 */	stw r0, 8(r5)
/* 800E1B84 000DEAC4  98 C4 00 00 */	stb r6, 0(r4)
/* 800E1B88 000DEAC8  80 AD 8E A8 */	lwz r5, __GDCurrentDL@sda21(r13)
/* 800E1B8C 000DEACC  80 85 00 08 */	lwz r4, 8(r5)
/* 800E1B90 000DEAD0  38 04 00 01 */	addi r0, r4, 1
/* 800E1B94 000DEAD4  90 05 00 08 */	stw r0, 8(r5)
/* 800E1B98 000DEAD8  98 C4 00 00 */	stb r6, 0(r4)
/* 800E1B9C 000DEADC  80 AD 8E A8 */	lwz r5, __GDCurrentDL@sda21(r13)
/* 800E1BA0 000DEAE0  80 85 00 08 */	lwz r4, 8(r5)
/* 800E1BA4 000DEAE4  38 04 00 01 */	addi r0, r4, 1
/* 800E1BA8 000DEAE8  90 05 00 08 */	stw r0, 8(r5)
/* 800E1BAC 000DEAEC  98 C4 00 00 */	stb r6, 0(r4)
/* 800E1BB0 000DEAF0  80 AD 8E A8 */	lwz r5, __GDCurrentDL@sda21(r13)
/* 800E1BB4 000DEAF4  80 85 00 08 */	lwz r4, 8(r5)
/* 800E1BB8 000DEAF8  38 04 00 01 */	addi r0, r4, 1
/* 800E1BBC 000DEAFC  90 05 00 08 */	stw r0, 8(r5)
/* 800E1BC0 000DEB00  98 C4 00 00 */	stb r6, 0(r4)
/* 800E1BC4 000DEB04  80 AD 8E A8 */	lwz r5, __GDCurrentDL@sda21(r13)
/* 800E1BC8 000DEB08  80 85 00 08 */	lwz r4, 8(r5)
/* 800E1BCC 000DEB0C  38 04 00 01 */	addi r0, r4, 1
/* 800E1BD0 000DEB10  90 05 00 08 */	stw r0, 8(r5)
/* 800E1BD4 000DEB14  98 C4 00 00 */	stb r6, 0(r4)
/* 800E1BD8 000DEB18  80 AD 8E A8 */	lwz r5, __GDCurrentDL@sda21(r13)
/* 800E1BDC 000DEB1C  80 85 00 08 */	lwz r4, 8(r5)
/* 800E1BE0 000DEB20  38 04 00 01 */	addi r0, r4, 1
/* 800E1BE4 000DEB24  90 05 00 08 */	stw r0, 8(r5)
/* 800E1BE8 000DEB28  98 C4 00 00 */	stb r6, 0(r4)
/* 800E1BEC 000DEB2C  80 AD 8E A8 */	lwz r5, __GDCurrentDL@sda21(r13)
/* 800E1BF0 000DEB30  80 85 00 08 */	lwz r4, 8(r5)
/* 800E1BF4 000DEB34  38 04 00 01 */	addi r0, r4, 1
/* 800E1BF8 000DEB38  90 05 00 08 */	stw r0, 8(r5)
/* 800E1BFC 000DEB3C  98 C4 00 00 */	stb r6, 0(r4)
/* 800E1C00 000DEB40  80 AD 8E A8 */	lwz r5, __GDCurrentDL@sda21(r13)
/* 800E1C04 000DEB44  80 85 00 08 */	lwz r4, 8(r5)
/* 800E1C08 000DEB48  38 04 00 01 */	addi r0, r4, 1
/* 800E1C0C 000DEB4C  90 05 00 08 */	stw r0, 8(r5)
/* 800E1C10 000DEB50  98 C4 00 00 */	stb r6, 0(r4)
/* 800E1C14 000DEB54  42 00 FF 60 */	bdnz lbl_800E1B74
/* 800E1C18 000DEB58  70 63 00 07 */	andi. r3, r3, 7
/* 800E1C1C 000DEB5C  4D 82 00 20 */	beqlr 
lbl_800E1C20:
/* 800E1C20 000DEB60  7C 69 03 A6 */	mtctr r3
lbl_800E1C24:
/* 800E1C24 000DEB64  80 AD 8E A8 */	lwz r5, __GDCurrentDL@sda21(r13)
/* 800E1C28 000DEB68  80 85 00 08 */	lwz r4, 8(r5)
/* 800E1C2C 000DEB6C  38 04 00 01 */	addi r0, r4, 1
/* 800E1C30 000DEB70  90 05 00 08 */	stw r0, 8(r5)
/* 800E1C34 000DEB74  98 C4 00 00 */	stb r6, 0(r4)
/* 800E1C38 000DEB78  42 00 FF EC */	bdnz lbl_800E1C24
/* 800E1C3C 000DEB7C  4E 80 00 20 */	blr 

.global GDOverflowed
GDOverflowed:
/* 800E1C40 000DEB80  7C 08 02 A6 */	mflr r0
/* 800E1C44 000DEB84  90 01 00 04 */	stw r0, 4(r1)
/* 800E1C48 000DEB88  94 21 FF F8 */	stwu r1, -8(r1)
/* 800E1C4C 000DEB8C  81 8D 8E AC */	lwz r12, overflowcb@sda21(r13)
/* 800E1C50 000DEB90  28 0C 00 00 */	cmplwi r12, 0
/* 800E1C54 000DEB94  41 82 00 0C */	beq lbl_800E1C60
/* 800E1C58 000DEB98  7D 88 03 A6 */	mtlr r12
/* 800E1C5C 000DEB9C  4E 80 00 21 */	blrl 
lbl_800E1C60:
/* 800E1C60 000DEBA0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800E1C64 000DEBA4  38 21 00 08 */	addi r1, r1, 8
/* 800E1C68 000DEBA8  7C 08 03 A6 */	mtlr r0
/* 800E1C6C 000DEBAC  4E 80 00 20 */	blr 

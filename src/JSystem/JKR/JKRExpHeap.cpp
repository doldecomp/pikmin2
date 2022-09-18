#include "types.h"
#include "JSystem/JKR/JKRHeap.h"

/*
    Generated from dpostproc

    .section .rodata  # 0x804732E0 - 0x8049E220
    .global lbl_804736E8
    lbl_804736E8:
        .asciz ":::cannot alloc memory (0x%x byte).\n"
        .skip 3
    .global lbl_80473710
    lbl_80473710:
        .asciz "JKRExpHeap.cpp"
        .skip 1
    .global lbl_80473720
    lbl_80473720:
        .asciz ":::ERROR! appendUsedList\n"
        .skip 2
        .asciz ":::Heap may be broken. (block = %x)"
        .asciz ":::: Bad Block\n"
        .asciz ":::addr %08x: bad heap signature. (%c%c)\n"
        .skip 2
        .asciz ":::addr %08x: bad next pointer (%08x)\nabort\n"
        .skip 3
        .asciz ":::addr %08x: bad previous pointer (%08x)\n"
        .skip 1
        .asciz ":::addr %08x: bad used list(REV) (%08x)\n"
        .skip 3
        .asciz ":::addr %08x: bad block size (%08x)\n"
        .skip 3
        .asciz ":::bad total memory block size (%08X, %08X)\n"
        .skip 3
        .asciz ":::there is some error in this heap!\n"
        .skip 2
        .asciz " attr  address:   size    gid aln   prev_ptr next_ptr\n"
        .skip 1
        .asciz "(Used Blocks)\n"
        .skip 1
        .asciz "xxxxx %08x: --------  --- ---  (-------- --------)\nabort\n"
        .skip 2
        .asciz "%s %08x: %08x  %3d %3d  (%08x %08x)\n"
        .skip 3
        .asciz "(Free Blocks)\n"
        .skip 1
        .asciz "%d / %d bytes (%6.2f%%) used (U:%d F:%d)\n"
        .skip 2
        .asciz "+---------------JKRExpHeap\n"
        .asciz "|         Align Group  size    ( prev , next )\n"
        .asciz "| ---- FreeFirst\n"
        .skip 2
        .asciz "| %08x  "
        .skip 3
        .asciz "%2x  %3d  %6x  (%08x %08x)\n"
        .asciz "| ---- FreeLast\n"
        .skip 3
        .asciz "| ---- UsedFirst\n"
        .skip 2
        .asciz "| ---- UsedLast\n"
        .skip 3
        .asciz "+---------------End\n"
        .skip 3

    .section .data, "wa"  # 0x8049E220 - 0x804EFC20
    .global __vt__10JKRExpHeap
    __vt__10JKRExpHeap:
        .4byte 0
        .4byte 0
        .4byte __dt__10JKRExpHeapFv
        .4byte callAllDisposer__7JKRHeapFv
        .4byte getHeapType__10JKRExpHeapFv
        .4byte check__10JKRExpHeapFv
        .4byte dump_sort__10JKRExpHeapFv
        .4byte dump__10JKRExpHeapFv
        .4byte do_destroy__10JKRExpHeapFv
        .4byte do_alloc__10JKRExpHeapFUli
        .4byte do_free__10JKRExpHeapFPv
        .4byte do_freeAll__10JKRExpHeapFv
        .4byte do_freeTail__10JKRExpHeapFv
        .4byte do_fillFreeArea__10JKRExpHeapFv
        .4byte do_resize__10JKRExpHeapFPvUl
        .4byte do_getSize__10JKRExpHeapFPv
        .4byte do_getFreeSize__10JKRExpHeapFv
        .4byte do_getMaxFreeBlock__10JKRExpHeapFv
        .4byte do_getTotalFreeSize__10JKRExpHeapFv
        .4byte do_changeGroupID__10JKRExpHeapFUc
        .4byte do_getCurrentGroupId__10JKRExpHeapFv
        .4byte state_register__10JKRExpHeapCFPQ27JKRHeap6TStateUl
        .4byte
   state_compare__10JKRExpHeapCFRCQ27JKRHeap6TStateRCQ27JKRHeap6TState .4byte
   state_dump__7JKRHeapCFRCQ27JKRHeap6TState

    .section .sbss # 0x80514D80 - 0x80516360
    .global DBfoundSize
    DBfoundSize:
        .skip 0x4
    .global DBfoundOffset
    DBfoundOffset:
        .skip 0x4
    .global DBfoundBlock
    DBfoundBlock:
        .skip 0x4
    .global DBnewFreeBlock
    DBnewFreeBlock:
        .skip 0x4
    .global DBnewUsedBlock
    DBnewUsedBlock:
        .skip 0x8

    .section .sdata2, "a"     # 0x80516360 - 0x80520E40
    .global lbl_805164F0
    lbl_805164F0:
        .asciz " NONE\n"
        .skip 1
    .global lbl_805164F8
    lbl_805164F8:
        .asciz " temp"
        .skip 2
    .global lbl_80516500
    lbl_80516500:
        .asciz "alloc"
        .skip 2
    .global lbl_80516508
    lbl_80516508:
        .asciz " free"
        .skip 2
    .global lbl_80516510
    lbl_80516510:
        .float 100.0
        .skip 4
    .global lbl_80516518
    lbl_80516518:
        .4byte 0x43300000
        .4byte 0x00000000
*/

/*
 * --INFO--
 * Address:	8001FE48
 * Size:	000080
 */
JKRExpHeap* JKRExpHeap::createRoot(int, bool)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	mr       r31, r4
	li       r4, 0
	lwz      r0, sRootHeap__7JKRHeap@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_8001FEA8
	mr       r5, r3
	addi     r3, r1, 0xc
	addi     r4, r1, 8
	bl       initArena__7JKRHeapFPPcPUli
	lwz      r3, 0xc(r1)
	lwz      r5, 8(r1)
	cmplwi   r3, 0
	addi     r4, r3, 0x90
	addi     r5, r5, -144
	beq      lbl_8001FEA0
	mr       r7, r31
	li       r6, 0
	bl       __ct__10JKRExpHeapFPvUlP7JKRHeapb

lbl_8001FEA0:
	mr       r4, r3
	stw      r3, sRootHeap__7JKRHeap@sda21(r13)

lbl_8001FEA8:
	li       r0, 1
	mr       r3, r4
	stb      r0, 0x6e(r4)
	lwz      r31, 0x1c(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8001FEC8
 * Size:	0000E4
 */
JKRExpHeap* JKRExpHeap::create(unsigned long, JKRHeap*, bool)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	mr       r29, r5
	stw      r28, 0x10(r1)
	or.      r28, r4, r4
	bne      lbl_8001FEF4
	lwz      r28, sRootHeap__7JKRHeap@sda21(r13)

lbl_8001FEF4:
	addis    r0, r3, 1
	cmplwi   r0, 0xffff
	bne      lbl_8001FF0C
	mr       r3, r28
	li       r4, 0x10
	bl       getMaxAllocatableSize__7JKRHeapFi

lbl_8001FF0C:
	rlwinm   r31, r3, 0, 0, 0x1b
	cmplwi   r31, 0xa0
	bge      lbl_8001FF20
	li       r3, 0
	b        lbl_8001FF8C

lbl_8001FF20:
	mr       r3, r31
	mr       r5, r28
	li       r4, 0x10
	bl       alloc__7JKRHeapFUliP7JKRHeap
	mr       r0, r3
	or.      r30, r0, r0
	addi     r4, r30, 0x90
	bne      lbl_8001FF48
	li       r3, 0
	b        lbl_8001FF8C

lbl_8001FF48:
	mr       r5, r30
	beq      lbl_8001FF64
	mr       r6, r28
	mr       r7, r29
	addi     r5, r31, -144
	bl       __ct__10JKRExpHeapFPvUlP7JKRHeapb
	mr       r5, r3

lbl_8001FF64:
	cmplwi   r5, 0
	bne      lbl_8001FF80
	mr       r3, r30
	li       r4, 0
	bl       free__7JKRHeapFPvP7JKRHeap
	li       r3, 0
	b        lbl_8001FF8C

lbl_8001FF80:
	li       r0, 0
	mr       r3, r5
	stb      r0, 0x6e(r5)

lbl_8001FF8C:
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r28, 0x10(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8001FFAC
 * Size:	000084
 */
void JKRExpHeap::do_destroy()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	mr       r30, r3
	lbz      r0, 0x6e(r3)
	cmplwi   r0, 0
	bne      lbl_80020004
	lwz      r4, 0x50(r30)
	lwz      r31, 0xc(r4)
	cmplwi   r31, 0
	beq      lbl_80020018
	lwz      r12, 0(r3)
	li       r4, -1
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	mr       r3, r30
	mr       r4, r31
	bl       free__7JKRHeapFPvP7JKRHeap
	b        lbl_80020018

lbl_80020004:
	lwz      r12, 0(r3)
	li       r4, -1
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl

lbl_80020018:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020030
 * Size:	000098
 */
JKRExpHeap::JKRExpHeap(void*, unsigned long, JKRHeap*, bool)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	mr       r31, r5
	stw      r30, 0x18(r1)
	mr       r30, r4
	stw      r29, 0x14(r1)
	mr       r29, r3
	bl       __ct__7JKRHeapFPvUlP7JKRHeapb
	lis      r4, __vt__10JKRExpHeap@ha
	li       r3, 0
	addi     r4, r4, __vt__10JKRExpHeap@l
	li       r0, 0xff
	stw      r4, 0(r29)
	addi     r6, r31, -16
	li       r4, 0
	li       r5, 0
	stb      r3, 0x6c(r29)
	li       r7, 0
	li       r8, 0
	stb      r0, 0x6d(r29)
	stw      r30, 0x78(r29)
	lwz      r0, 0x78(r29)
	stw      r0, 0x7c(r29)
	lwz      r3, 0x78(r29)
	bl
	initiate__Q210JKRExpHeap9CMemBlockFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockUlUcUc
	li       r0, 0
	mr       r3, r29
	stw      r0, 0x80(r29)
	stw      r0, 0x84(r29)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	800200C8
 * Size:	000068
 */
JKRExpHeap::~JKRExpHeap()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_80020114
	lis      r4, __vt__10JKRExpHeap@ha
	addi     r0, r4, __vt__10JKRExpHeap@l
	stw      r0, 0(r30)
	bl       dispose__7JKRHeapFv
	mr       r3, r30
	li       r4, 0
	bl       __dt__7JKRHeapFv
	extsh.   r0, r31
	ble      lbl_80020114
	mr       r3, r30
	bl       __dl__FPv

lbl_80020114:
	lwz      r0, 0x14(r1)
	mr       r3, r30
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020130
 * Size:	00011C
 */
void* JKRExpHeap::do_alloc(unsigned long, int)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r30, r5
	stw      r29, 0x14(r1)
	mr       r29, r4
	stw      r28, 0x10(r1)
	mr       r28, r3
	addi     r3, r28, 0x18
	bl       OSLockMutex
	cmplwi   r29, 4
	bge      lbl_8002016C
	li       r29, 4

lbl_8002016C:
	cmpwi    r30, 0
	blt      lbl_800201A8
	cmpwi    r30, 4
	bgt      lbl_80020190
	mr       r3, r28
	mr       r4, r29
	bl       allocFromHead__10JKRExpHeapFUl
	mr       r31, r3
	b        lbl_800201D8

lbl_80020190:
	mr       r3, r28
	mr       r4, r29
	mr       r5, r30
	bl       allocFromHead__10JKRExpHeapFUli
	mr       r31, r3
	b        lbl_800201D8

lbl_800201A8:
	neg      r5, r30
	cmpwi    r5, 4
	bgt      lbl_800201C8
	mr       r3, r28
	mr       r4, r29
	bl       allocFromTail__10JKRExpHeapFUl
	mr       r31, r3
	b        lbl_800201D8

lbl_800201C8:
	mr       r3, r28
	mr       r4, r29
	bl       allocFromTail__10JKRExpHeapFUli
	mr       r31, r3

lbl_800201D8:
	cmplwi   r31, 0
	bne      lbl_80020220
	lis      r3, lbl_804736E8@ha
	mr       r4, r29
	addi     r3, r3, lbl_804736E8@l
	crclr    6
	bl       JUTWarningConsole_f
	lbz      r0, 0x68(r28)
	cmplwi   r0, 1
	bne      lbl_80020220
	lwz      r12, mErrorHandler__7JKRHeap@sda21(r13)
	cmplwi   r12, 0
	beq      lbl_80020220
	mr       r3, r28
	mr       r4, r29
	mr       r5, r30
	mtctr    r12
	bctrl

lbl_80020220:
	addi     r3, r28, 0x18
	bl       OSUnlockMutex
	lwz      r0, 0x24(r1)
	mr       r3, r31
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r28, 0x10(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8002024C
 * Size:	000254
 */
u32 JKRExpHeap::allocFromHead(unsigned long, int)
{
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	li       r7, -1
	stw      r0, 0x34(r1)
	addi     r0, r4, 3
	stmw     r25, 0x14(r1)
	mr       r29, r3
	addi     r3, r5, -1
	rlwinm   r30, r0, 0, 0, 0x1d
	nor      r4, r3, r3
	li       r28, 0
	li       r31, 0
	lwz      r8, 0x78(r29)
	b        lbl_800202D0

lbl_80020284:
	addi     r5, r8, 0x10
	lwz      r6, 4(r8)
	add      r0, r3, r5
	and      r0, r4, r0
	subf     r5, r5, r0
	add      r0, r30, r5
	cmplw    r6, r0
	blt      lbl_800202CC
	cmplw    r7, r6
	ble      lbl_800202CC
	lbz      r0, 0x6c(r29)
	mr       r7, r6
	mr       r31, r8
	mr       r28, r5
	cmplwi   r0, 0
	bne      lbl_800202D8
	cmplw    r6, r30
	beq      lbl_800202D8

lbl_800202CC:
	lwz      r8, 0xc(r8)

lbl_800202D0:
	cmplwi   r8, 0
	bne      lbl_80020284

lbl_800202D8:
	cmplwi   r31, 0
	stw      r7, DBfoundSize@sda21(r13)
	stw      r28, DBfoundOffset@sda21(r13)
	stw      r31, DBfoundBlock@sda21(r13)
	beq      lbl_80020488
	cmplwi   r28, 0x10
	blt      lbl_800203B0
	lwz      r26, 8(r31)
	mr       r3, r31
	lwz      r25, 0xc(r31)
	addi     r4, r28, -16
	li       r5, 0
	li       r6, 0
	li       r7, 0
	li       r8, 0
	bl       allocFore__Q210JKRExpHeap9CMemBlockFUlUcUcUcUc
	or.      r27, r3, r3
	beq      lbl_80020340
	lbz      r5, 0x6d(r29)
	mr       r4, r30
	li       r6, 0
	li       r7, 0
	li       r8, 0
	bl       allocFore__Q210JKRExpHeap9CMemBlockFUlUcUcUcUc
	mr       r6, r3
	b        lbl_80020344

lbl_80020340:
	li       r6, 0

lbl_80020344:
	cmplwi   r6, 0
	mr       r28, r6
	beq      lbl_80020364
	mr       r3, r29
	mr       r4, r31
	mr       r5, r26
	bl
setFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlock
	b        lbl_80020378

lbl_80020364:
	mr       r3, r29
	mr       r4, r31
	mr       r5, r26
	mr       r6, r25
	bl
setFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlock

lbl_80020378:
	cmplwi   r28, 0
	beq      lbl_80020394
	mr       r3, r29
	mr       r4, r28
	mr       r5, r31
	mr       r6, r25
	bl
setFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlock

lbl_80020394:
	mr       r3, r29
	mr       r4, r27
	bl       appendUsedList__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	stw      r28, DBnewFreeBlock@sda21(r13)
	addi     r3, r27, 0x10
	stw      r27, DBnewUsedBlock@sda21(r13)
	b        lbl_8002048C

lbl_800203B0:
	cmplwi   r28, 0
	beq      lbl_80020424
	lwz      r25, 8(r31)
	mr       r3, r29
	lwz      r26, 0xc(r31)
	mr       r4, r31
	bl       removeFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	lwz      r0, 4(r31)
	add      r31, r31, r28
	mr       r3, r31
	mr       r4, r30
	subf     r0, r28, r0
	clrlwi   r6, r28, 0x18
	stw      r0, 4(r31)
	li       r7, 0
	li       r8, 0
	lbz      r5, 0x6d(r29)
	bl       allocFore__Q210JKRExpHeap9CMemBlockFUlUcUcUcUc
	or.      r4, r3, r3
	beq      lbl_80020410
	mr       r3, r29
	mr       r5, r25
	mr       r6, r26
	bl
setFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlock

lbl_80020410:
	mr       r3, r29
	mr       r4, r31
	bl       appendUsedList__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	addi     r3, r31, 0x10
	b        lbl_8002048C

lbl_80020424:
	lwz      r25, 8(r31)
	mr       r3, r31
	lwz      r26, 0xc(r31)
	mr       r4, r30
	lbz      r5, 0x6d(r29)
	li       r6, 0
	li       r7, 0
	li       r8, 0
	bl       allocFore__Q210JKRExpHeap9CMemBlockFUlUcUcUcUc
	mr       r30, r3
	mr       r3, r29
	mr       r4, r31
	bl       removeFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	cmplwi   r30, 0
	beq      lbl_80020474
	mr       r3, r29
	mr       r4, r30
	mr       r5, r25
	mr       r6, r26
	bl
setFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlock

lbl_80020474:
	mr       r3, r29
	mr       r4, r31
	bl       appendUsedList__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	addi     r3, r31, 0x10
	b        lbl_8002048C

lbl_80020488:
	li       r3, 0

lbl_8002048C:
	lmw      r25, 0x14(r1)
	lwz      r0, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	800204A0
 * Size:	0000E4
 */
u32 JKRExpHeap::allocFromHead(unsigned long)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	li       r5, -1
	stw      r0, 0x14(r1)
	addi     r0, r4, 3
	rlwinm   r4, r0, 0, 0, 0x1d
	stw      r31, 0xc(r1)
	li       r31, 0
	stw      r30, 8(r1)
	mr       r30, r3
	lwz      r6, 0x78(r3)
	b        lbl_80020504

lbl_800204D0:
	lwz      r3, 4(r6)
	cmplw    r3, r4
	blt      lbl_80020500
	cmplw    r5, r3
	ble      lbl_80020500
	lbz      r0, 0x6c(r30)
	mr       r5, r3
	mr       r31, r6
	cmplwi   r0, 0
	bne      lbl_8002050C
	cmplw    r3, r4
	beq      lbl_8002050C

lbl_80020500:
	lwz      r6, 0xc(r6)

lbl_80020504:
	cmplwi   r6, 0
	bne      lbl_800204D0

lbl_8002050C:
	cmplwi   r31, 0
	beq      lbl_80020568
	lbz      r5, 0x6d(r30)
	mr       r3, r31
	li       r6, 0
	li       r7, 0
	li       r8, 0
	bl       allocFore__Q210JKRExpHeap9CMemBlockFUlUcUcUcUc
	or.      r4, r3, r3
	beq      lbl_80020548
	lwz      r5, 8(r31)
	mr       r3, r30
	lwz      r6, 0xc(r31)
	bl
setFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlock
	b        lbl_80020554

lbl_80020548:
	mr       r3, r30
	mr       r4, r31
	bl       removeFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock

lbl_80020554:
	mr       r3, r30
	mr       r4, r31
	bl       appendUsedList__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	addi     r3, r31, 0x10
	b        lbl_8002056C

lbl_80020568:
	li       r3, 0

lbl_8002056C:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020584
 * Size:	000158
 */
u32 JKRExpHeap::allocFromTail(unsigned long, int)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	addi     r0, r5, -1
	stmw     r27, 0xc(r1)
	mr       r27, r3
	li       r31, 0
	li       r30, 0
	li       r29, 0
	lwz      r8, 0x7c(r3)
	nor      r3, r0, r0
	b        lbl_800205E8

lbl_800205B4:
	lwz      r6, 4(r8)
	add      r5, r8, r6
	addi     r5, r5, 0x10
	subf     r0, r4, r5
	and      r7, r3, r0
	subf     r28, r7, r5
	cmplw    r6, r28
	blt      lbl_800205E4
	mr       r30, r8
	subf     r31, r28, r6
	addi     r29, r7, -16
	b        lbl_800205F0

lbl_800205E4:
	lwz      r8, 8(r8)

lbl_800205E8:
	cmplwi   r8, 0
	bne      lbl_800205B4

lbl_800205F0:
	cmplwi   r30, 0
	beq      lbl_800206C4
	cmplwi   r31, 0x10
	blt      lbl_80020640
	lbz      r7, 0x6d(r27)
	mr       r3, r29
	mr       r6, r28
	li       r4, 0
	li       r5, 0
	li       r8, 0x80
	bl
initiate__Q210JKRExpHeap9CMemBlockFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockUlUcUc
	lwz      r0, 4(r30)
	mr       r3, r27
	mr       r4, r29
	subf     r5, r28, r0
	addi     r0, r5, -16
	stw      r0, 4(r30)
	bl       appendUsedList__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	addi     r3, r29, 0x10
	b        lbl_800206C8

lbl_80020640:
	cmplwi   r31, 0
	beq      lbl_80020688
	mr       r3, r27
	mr       r4, r30
	bl       removeFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	ori      r0, r31, 0x80
	lbz      r7, 0x6d(r27)
	mr       r3, r29
	mr       r6, r28
	clrlwi   r8, r0, 0x18
	li       r4, 0
	li       r5, 0
	bl
initiate__Q210JKRExpHeap9CMemBlockFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockUlUcUc
	mr       r3, r27
	mr       r4, r29
	bl       appendUsedList__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	addi     r3, r29, 0x10
	b        lbl_800206C8

lbl_80020688:
	mr       r3, r27
	mr       r4, r30
	bl       removeFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	lbz      r7, 0x6d(r27)
	mr       r3, r29
	mr       r6, r28
	li       r4, 0
	li       r5, 0
	li       r8, 0x80
	bl
initiate__Q210JKRExpHeap9CMemBlockFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockUlUcUc
	mr       r3, r27
	mr       r4, r29
	bl       appendUsedList__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	addi     r3, r29, 0x10
	b        lbl_800206C8

lbl_800206C4:
	li       r3, 0

lbl_800206C8:
	lmw      r27, 0xc(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	800206DC
 * Size:	0000E0
 */
u32 JKRExpHeap::allocFromTail(unsigned long)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	addi     r0, r4, 3
	rlwinm   r4, r0, 0, 0, 0x1d
	stw      r31, 0x1c(r1)
	li       r31, 0
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	mr       r29, r3
	lwz      r3, 0x7c(r3)
	b        lbl_80020724

lbl_8002070C:
	lwz      r0, 4(r3)
	cmplw    r0, r4
	blt      lbl_80020720
	mr       r31, r3
	b        lbl_8002072C

lbl_80020720:
	lwz      r3, 8(r3)

lbl_80020724:
	cmplwi   r3, 0
	bne      lbl_8002070C

lbl_8002072C:
	cmplwi   r31, 0
	beq      lbl_8002079C
	lbz      r7, 0x6d(r29)
	mr       r3, r31
	li       r5, 0
	li       r6, 0
	li       r8, 0
	bl       allocBack__Q210JKRExpHeap9CMemBlockFUlUcUcUcUc
	or.      r30, r3, r3
	beq      lbl_8002075C
	mr       r4, r31
	b        lbl_80020770

lbl_8002075C:
	mr       r3, r29
	mr       r4, r31
	bl       removeFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	mr       r30, r31
	li       r4, 0

lbl_80020770:
	cmplwi   r4, 0
	beq      lbl_80020788
	lwz      r5, 8(r31)
	mr       r3, r29
	lwz      r6, 0xc(r31)
	bl
setFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlock

lbl_80020788:
	mr       r3, r29
	mr       r4, r30
	bl       appendUsedList__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	addi     r3, r30, 0x10
	b        lbl_800207A0

lbl_8002079C:
	li       r3, 0

lbl_800207A0:
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	800207BC
 * Size:	000074
 */
void JKRExpHeap::do_free(void*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	mr       r30, r3
	addi     r3, r30, 0x18
	bl       OSLockMutex
	lwz      r0, 0x30(r30)
	cmplw    r0, r31
	bgt      lbl_80020810
	lwz      r0, 0x34(r30)
	cmplw    r31, r0
	bgt      lbl_80020810
	mr       r3, r31
	bl       getHeapBlock__Q210JKRExpHeap9CMemBlockFPv
	cmplwi   r3, 0
	beq      lbl_80020810
	mr       r4, r30
	bl       free__Q210JKRExpHeap9CMemBlockFP10JKRExpHeap

lbl_80020810:
	addi     r3, r30, 0x18
	bl       OSUnlockMutex
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020830
 * Size:	000094
 */
int JKRExpHeap::freeGroup(unsigned char)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stmw     r27, 0xc(r1)
	mr       r27, r3
	mr       r28, r4
	addi     r3, r27, 0x18
	bl       OSLockMutex
	lwz      r30, 0x80(r27)
	clrlwi   r31, r28, 0x18
	li       r29, 0
	b        lbl_8002089C

lbl_80020860:
	lbz      r0, 3(r30)
	cmplw    r0, r31
	bne      lbl_80020898
	lwz      r5, 4(r30)
	mr       r3, r27
	addi     r4, r30, 0x10
	bl       dispose__7JKRHeapFPvUl
	lwz      r28, 0xc(r30)
	mr       r3, r30
	mr       r4, r27
	bl       free__Q210JKRExpHeap9CMemBlockFP10JKRExpHeap
	mr       r30, r28
	addi     r29, r29, 1
	b        lbl_8002089C

lbl_80020898:
	lwz      r30, 0xc(r30)

lbl_8002089C:
	cmplwi   r30, 0
	bne      lbl_80020860
	addi     r3, r27, 0x18
	bl       OSUnlockMutex
	mr       r3, r29
	lmw      r27, 0xc(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	800208C4
 * Size:	00007C
 */
void JKRExpHeap::do_freeAll()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	addi     r3, r31, 0x18
	bl       OSLockMutex
	mr       r3, r31
	bl       callAllDisposer__7JKRHeapFv
	lwz      r0, 0x30(r31)
	li       r4, 0
	li       r5, 0
	li       r7, 0
	stw      r0, 0x78(r31)
	li       r8, 0
	lwz      r0, 0x78(r31)
	stw      r0, 0x7c(r31)
	lwz      r6, 0x38(r31)
	lwz      r3, 0x78(r31)
	addi     r6, r6, -16
	bl
	initiate__Q210JKRExpHeap9CMemBlockFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockUlUcUc
	li       r0, 0
	addi     r3, r31, 0x18
	stw      r0, 0x80(r31)
	stw      r0, 0x84(r31)
	bl       OSUnlockMutex
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020940
 * Size:	000090
 */
void JKRExpHeap::do_freeTail()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	mr       r29, r3
	addi     r3, r29, 0x18
	bl       OSLockMutex
	lwz      r31, 0x80(r29)
	b        lbl_800209A4

lbl_8002096C:
	lbz      r0, 2(r31)
	rlwinm.  r0, r0, 0, 0x18, 0x18
	beq      lbl_800209A0
	lwz      r5, 4(r31)
	mr       r3, r29
	addi     r4, r31, 0x10
	bl       dispose__7JKRHeapFPvUl
	lwz      r30, 0xc(r31)
	mr       r3, r31
	mr       r4, r29
	bl       free__Q210JKRExpHeap9CMemBlockFP10JKRExpHeap
	mr       r31, r30
	b        lbl_800209A4

lbl_800209A0:
	lwz      r31, 0xc(r31)

lbl_800209A4:
	cmplwi   r31, 0
	bne      lbl_8002096C
	addi     r3, r29, 0x18
	bl       OSUnlockMutex
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	800209D0
 * Size:	000004
 */
void JKRExpHeap::do_fillFreeArea() { }

/*
 * --INFO--
 * Address:	800209D4
 * Size:	000058
 */
u8 JKRExpHeap::do_changeGroupID(unsigned char)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r30, r4
	stw      r29, 0x14(r1)
	mr       r29, r3
	addi     r3, r29, 0x18
	bl       OSLockMutex
	lbz      r31, 0x6d(r29)
	addi     r3, r29, 0x18
	stb      r30, 0x6d(r29)
	bl       OSUnlockMutex
	lwz      r0, 0x24(r1)
	mr       r3, r31
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020A2C
 * Size:	0001BC
 */
int JKRExpHeap::do_resize(void*, unsigned long)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r30, r5
	stw      r29, 0x14(r1)
	mr       r29, r3
	addi     r3, r29, 0x18
	stw      r28, 0x10(r1)
	mr       r28, r4
	bl       OSLockMutex
	mr       r3, r28
	bl       getHeapBlock__Q210JKRExpHeap9CMemBlockFPv
	or.      r31, r3, r3
	beq      lbl_80020A84
	lwz      r0, 0x30(r29)
	cmplw    r28, r0
	blt      lbl_80020A84
	lwz      r0, 0x34(r29)
	cmplw    r0, r28
	bge      lbl_80020A94

lbl_80020A84:
	addi     r3, r29, 0x18
	bl       OSUnlockMutex
	li       r3, -1
	b        lbl_80020BC8

lbl_80020A94:
	addi     r0, r30, 3
	lwz      r4, 4(r31)
	rlwinm   r30, r0, 0, 0, 0x1d
	cmplw    r30, r4
	bne      lbl_80020AB8
	addi     r3, r29, 0x18
	bl       OSUnlockMutex
	mr       r3, r30
	b        lbl_80020BC8

lbl_80020AB8:
	ble      lbl_80020B88
	addi     r0, r31, 0x10
	lwz      r3, 0x78(r29)
	add      r0, r0, r4
	li       r28, 0
	b        lbl_80020AE4

lbl_80020AD0:
	cmplw    r3, r0
	bne      lbl_80020AE0
	mr       r28, r3
	b        lbl_80020AEC

lbl_80020AE0:
	lwz      r3, 0xc(r3)

lbl_80020AE4:
	cmplwi   r3, 0
	bne      lbl_80020AD0

lbl_80020AEC:
	cmplwi   r28, 0
	bne      lbl_80020B04
	addi     r3, r29, 0x18
	bl       OSUnlockMutex
	li       r3, -1
	b        lbl_80020BC8

lbl_80020B04:
	lwz      r0, 4(r28)
	add      r3, r4, r0
	addi     r0, r3, 0x10
	cmplw    r30, r0
	ble      lbl_80020B28
	addi     r3, r29, 0x18
	bl       OSUnlockMutex
	li       r3, -1
	b        lbl_80020BC8

lbl_80020B28:
	mr       r3, r29
	mr       r4, r28
	bl       removeFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	lwz      r3, 4(r31)
	lwz      r0, 4(r28)
	add      r3, r0, r3
	addi     r0, r3, 0x10
	stw      r0, 4(r31)
	lwz      r0, 4(r31)
	subf     r0, r30, r0
	cmplwi   r0, 0x10
	ble      lbl_80020BBC
	lbz      r5, 3(r31)
	mr       r3, r31
	lbz      r6, 2(r31)
	mr       r4, r30
	li       r7, 0
	li       r8, 0
	bl       allocFore__Q210JKRExpHeap9CMemBlockFUlUcUcUcUc
	or.      r4, r3, r3
	beq      lbl_80020BBC
	mr       r3, r29
	bl       recycleFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	b        lbl_80020BBC

lbl_80020B88:
	subf     r0, r30, r4
	cmplwi   r0, 0x10
	ble      lbl_80020BBC
	lbz      r5, 3(r31)
	mr       r4, r30
	lbz      r6, 2(r31)
	li       r7, 0
	li       r8, 0
	bl       allocFore__Q210JKRExpHeap9CMemBlockFUlUcUcUcUc
	or.      r4, r3, r3
	beq      lbl_80020BBC
	mr       r3, r29
	bl       recycleFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock

lbl_80020BBC:
	addi     r3, r29, 0x18
	bl       OSUnlockMutex
	lwz      r3, 4(r31)

lbl_80020BC8:
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r28, 0x10(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020BE8
 * Size:	000088
 */
int JKRExpHeap::do_getSize(void*)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r30, r4
	stw      r29, 0x14(r1)
	mr       r29, r3
	addi     r3, r29, 0x18
	bl       OSLockMutex
	mr       r3, r30
	bl       getHeapBlock__Q210JKRExpHeap9CMemBlockFPv
	or.      r31, r3, r3
	beq      lbl_80020C38
	lwz      r0, 0x30(r29)
	cmplw    r30, r0
	blt      lbl_80020C38
	lwz      r0, 0x34(r29)
	cmplw    r0, r30
	bge      lbl_80020C48

lbl_80020C38:
	addi     r3, r29, 0x18
	bl       OSUnlockMutex
	li       r3, -1
	b        lbl_80020C54

lbl_80020C48:
	addi     r3, r29, 0x18
	bl       OSUnlockMutex
	lwz      r3, 4(r31)

lbl_80020C54:
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020C70
 * Size:	00006C
 */
u32 JKRExpHeap::do_getFreeSize()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	mr       r30, r3
	addi     r3, r30, 0x18
	bl       OSLockMutex
	lwz      r3, 0x78(r30)
	li       r31, 0
	b        lbl_80020CB0

lbl_80020C9C:
	lwz      r0, 4(r3)
	cmpw     r31, r0
	bge      lbl_80020CAC
	mr       r31, r0

lbl_80020CAC:
	lwz      r3, 0xc(r3)

lbl_80020CB0:
	cmplwi   r3, 0
	bne      lbl_80020C9C
	addi     r3, r30, 0x18
	bl       OSUnlockMutex
	lwz      r0, 0x14(r1)
	mr       r3, r31
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020CDC
 * Size:	000074
 */
void* JKRExpHeap::do_getMaxFreeBlock()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	mr       r30, r3
	addi     r3, r30, 0x18
	bl       OSLockMutex
	lwz      r4, 0x78(r30)
	li       r3, 0
	li       r31, 0
	b        lbl_80020D24

lbl_80020D0C:
	lwz      r0, 4(r4)
	cmpw     r3, r0
	bge      lbl_80020D20
	mr       r3, r0
	mr       r31, r4

lbl_80020D20:
	lwz      r4, 0xc(r4)

lbl_80020D24:
	cmplwi   r4, 0
	bne      lbl_80020D0C
	addi     r3, r30, 0x18
	bl       OSUnlockMutex
	lwz      r0, 0x14(r1)
	mr       r3, r31
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020D50
 * Size:	000064
 */
u32 JKRExpHeap::do_getTotalFreeSize()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	li       r31, 0
	stw      r30, 8(r1)
	mr       r30, r3
	addi     r3, r30, 0x18
	bl       OSLockMutex
	lwz      r3, 0x78(r30)
	b        lbl_80020D88

lbl_80020D7C:
	lwz      r0, 4(r3)
	lwz      r3, 0xc(r3)
	add      r31, r31, r0

lbl_80020D88:
	cmplwi   r3, 0
	bne      lbl_80020D7C
	addi     r3, r30, 0x18
	bl       OSUnlockMutex
	lwz      r0, 0x14(r1)
	mr       r3, r31
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020DB4
 * Size:	000098
 */
u32 JKRExpHeap::appendUsedList(JKRExpHeap::CMemBlock*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	or.      r31, r4, r4
	stw      r30, 8(r1)
	mr       r30, r3
	bne      lbl_80020DF0
	lis      r3, lbl_80473710@ha
	lis      r5, lbl_80473720@ha
	addi     r3, r3, lbl_80473710@l
	li       r4, 0x61f
	addi     r5, r5, lbl_80473720@l
	crclr    6
	bl       OSPanic

lbl_80020DF0:
	lwz      r3, 0x84(r30)
	li       r0, 0x484d
	cmplwi   r3, 0
	sth      r0, 0(r31)
	beq      lbl_80020E10
	stw      r31, 0xc(r3)
	stw      r3, 8(r31)
	b        lbl_80020E18

lbl_80020E10:
	li       r0, 0
	stw      r0, 8(r31)

lbl_80020E18:
	stw      r31, 0x84(r30)
	lwz      r0, 0x80(r30)
	cmplwi   r0, 0
	bne      lbl_80020E2C
	stw      r31, 0x80(r30)

lbl_80020E2C:
	li       r0, 0
	stw      r0, 0xc(r31)
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020E4C
 * Size:	00004C
 */
void JKRExpHeap::setFreeBlock(JKRExpHeap::CMemBlock*, JKRExpHeap::CMemBlock*, JKRExpHeap::CMemBlock*)
{
	/*
	.loc_0x0:
	  cmplwi    r5, 0
	  bne-      .loc_0x18
	  stw       r4, 0x78(r3)
	  li        r0, 0
	  stw       r0, 0x8(r4)
	  b         .loc_0x20

	.loc_0x18:
	  stw       r4, 0xC(r5)
	  stw       r5, 0x8(r4)

	.loc_0x20:
	  cmplwi    r6, 0
	  bne-      .loc_0x38
	  stw       r4, 0x7C(r3)
	  li        r0, 0
	  stw       r0, 0xC(r4)
	  b         .loc_0x40

	.loc_0x38:
	  stw       r4, 0x8(r6)
	  stw       r6, 0xC(r4)

	.loc_0x40:
	  li        r0, 0
	  sth       r0, 0x0(r4)
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80020E98
 * Size:	000034
 */
void JKRExpHeap::removeFreeBlock(JKRExpHeap::CMemBlock*)
{
	/*
	lwz      r5, 8(r4)
	lwz      r4, 0xc(r4)
	cmplwi   r5, 0
	bne      lbl_80020EB0
	stw      r4, 0x78(r3)
	b        lbl_80020EB4

lbl_80020EB0:
	stw      r4, 0xc(r5)

lbl_80020EB4:
	cmplwi   r4, 0
	bne      lbl_80020EC4
	stw      r5, 0x7c(r3)
	blr

lbl_80020EC4:
	stw      r5, 8(r4)
	blr
	*/
}

/*
 * --INFO--
 * Address:	80020ECC
 * Size:	0001E4
 */
void JKRExpHeap::recycleFreeBlock(JKRExpHeap::CMemBlock*)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	li       r5, 0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	mr       r31, r3
	stw      r30, 0x18(r1)
	mr       r30, r4
	stw      r29, 0x14(r1)
	lwz      r6, 4(r4)
	sth      r5, 0(r4)
	add      r7, r4, r6
	lbz      r0, 2(r4)
	clrlwi.  r0, r0, 0x19
	beq      lbl_80020F20
	subf     r30, r0, r4
	add      r6, r6, r0
	stb      r5, 3(r30)
	add      r7, r30, r6
	stb      r5, 2(r30)
	stw      r6, 4(r30)

lbl_80020F20:
	lwz      r3, 0x78(r31)
	cmplwi   r3, 0
	bne      lbl_80020F68
	mr       r3, r30
	li       r4, 0
	li       r5, 0
	li       r7, 0
	li       r8, 0
	bl
initiate__Q210JKRExpHeap9CMemBlockFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockUlUcUc
	stw      r30, 0x78(r31)
	li       r0, 0
	stw      r30, 0x7c(r31)
	stw      r30, 0x78(r31)
	stw      r0, 8(r30)
	stw      r30, 0x7c(r31)
	stw      r0, 0xc(r30)
	sth      r0, 0(r30)
	b        lbl_80021094

lbl_80020F68:
	cmplw    r3, r7
	blt      lbl_80020FCC
	mr       r3, r30
	li       r4, 0
	li       r5, 0
	li       r7, 0
	li       r8, 0
	bl
initiate__Q210JKRExpHeap9CMemBlockFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockUlUcUc
	lwz      r3, 0x78(r31)
	li       r0, 0
	stw      r30, 0x78(r31)
	cmplwi   r3, 0
	stw      r0, 8(r30)
	bne      lbl_80020FAC
	stw      r30, 0x7c(r31)
	stw      r0, 0xc(r30)
	b        lbl_80020FB4

lbl_80020FAC:
	stw      r30, 8(r3)
	stw      r3, 0xc(r30)

lbl_80020FB4:
	li       r0, 0
	mr       r3, r31
	sth      r0, 0(r30)
	mr       r4, r30
	bl       joinTwoBlocks__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	b        lbl_80021094

lbl_80020FCC:
	lwz      r0, 0x7c(r31)
	cmplw    r0, r30
	bgt      lbl_80021034
	mr       r3, r30
	li       r4, 0
	li       r5, 0
	li       r7, 0
	li       r8, 0
	bl
initiate__Q210JKRExpHeap9CMemBlockFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockUlUcUc
	lwz      r3, 0x7c(r31)
	cmplwi   r3, 0
	bne      lbl_8002100C
	stw      r30, 0x78(r31)
	li       r0, 0
	stw      r0, 8(r30)
	b        lbl_80021014

lbl_8002100C:
	stw      r30, 0xc(r3)
	stw      r3, 8(r30)

lbl_80021014:
	stw      r30, 0x7c(r31)
	li       r0, 0
	mr       r3, r31
	stw      r0, 0xc(r30)
	sth      r0, 0(r30)
	lwz      r4, 8(r30)
	bl       joinTwoBlocks__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	b        lbl_80021094

lbl_80021034:
	mr       r29, r3
	b        lbl_8002108C

lbl_8002103C:
	cmplw    r29, r30
	bge      lbl_80021088
	lwz      r0, 0xc(r29)
	cmplw    r30, r0
	bge      lbl_80021088
	stw      r0, 0xc(r30)
	li       r0, 0
	mr       r3, r31
	mr       r4, r30
	stw      r29, 8(r30)
	stw      r30, 0xc(r29)
	lwz      r5, 0xc(r30)
	stw      r30, 8(r5)
	stb      r0, 3(r30)
	bl       joinTwoBlocks__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	mr       r3, r31
	mr       r4, r29
	bl       joinTwoBlocks__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	b        lbl_80021094

lbl_80021088:
	lwz      r29, 0xc(r29)

lbl_8002108C:
	cmplwi   r29, 0
	bne      lbl_8002103C

lbl_80021094:
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	800210B0
 * Size:	000104
 */
void JKRExpHeap::joinTwoBlocks(JKRExpHeap::CMemBlock*)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r5, lbl_804736E8@ha
	stw      r0, 0x24(r1)
	stmw     r26, 8(r1)
	mr       r30, r3
	mr       r31, r4
	addi     r29, r5, lbl_804736E8@l
	lwz      r27, 0xc(r4)
	lwz      r3, 4(r4)
	lbz      r0, 2(r27)
	add      r28, r31, r3
	clrlwi   r0, r0, 0x19
	subf     r26, r0, r27
	addi     r28, r28, 0x10
	cmplw    r28, r26
	ble      lbl_80021128
	addi     r3, r29, 0x54
	crclr    6
	bl       JUTWarningConsole_f
	lwz      r3, sCurrentHeap__7JKRHeap@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	addi     r3, r29, 0x28
	addi     r5, r29, 0x78
	li       r4, 0x71b
	crclr    6
	bl       OSPanic

lbl_80021128:
	cmplw    r28, r26
	bne      lbl_800211A0
	lbz      r0, 2(r27)
	lwz      r3, 4(r27)
	clrlwi   r0, r0, 0x19
	lwz      r4, 4(r31)
	add      r0, r3, r0
	add      r3, r0, r4
	addi     r0, r3, 0x10
	stw      r0, 4(r31)
	lwz      r3, 8(r31)
	lwz      r4, 0xc(r27)
	cmplwi   r3, 0
	bne      lbl_80021170
	stw      r31, 0x78(r30)
	li       r0, 0
	stw      r0, 8(r31)
	b        lbl_80021178

lbl_80021170:
	stw      r31, 0xc(r3)
	stw      r3, 8(r31)

lbl_80021178:
	cmplwi   r4, 0
	bne      lbl_80021190
	stw      r31, 0x7c(r30)
	li       r0, 0
	stw      r0, 0xc(r31)
	b        lbl_80021198

lbl_80021190:
	stw      r31, 8(r4)
	stw      r4, 0xc(r31)

lbl_80021198:
	li       r0, 0
	sth      r0, 0(r31)

lbl_800211A0:
	lmw      r26, 8(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	800211B4
 * Size:	0001E0
 */
bool JKRExpHeap::check()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stmw     r27, 0xc(r1)
	mr       r28, r3
	lis      r3, lbl_804736E8@ha
	addi     r31, r3, lbl_804736E8@l
	addi     r3, r28, 0x18
	bl       OSLockMutex
	lwz      r27, 0x80(r28)
	li       r30, 0
	li       r29, 1
	b        lbl_800212A4

lbl_800211E8:
	lhz      r0, 0(r27)
	cmplwi   r0, 0x484d
	beq      lbl_80021210
	clrlwi   r6, r0, 0x18
	rlwinm   r5, r0, 0x18, 0x18, 0x1f
	mr       r4, r27
	addi     r3, r31, 0x88
	li       r29, 0
	crclr    6
	bl       JUTWarningConsole_f

lbl_80021210:
	lwz      r5, 0xc(r27)
	cmplwi   r5, 0
	beq      lbl_80021268
	lhz      r0, 0(r5)
	cmplwi   r0, 0x484d
	beq      lbl_80021240
	mr       r4, r27
	addi     r3, r31, 0xb4
	li       r29, 0
	crclr    6
	bl       JUTWarningConsole_f
	b        lbl_800212AC

lbl_80021240:
	lwz      r0, 8(r5)
	cmplw    r0, r27
	beq      lbl_80021288
	mr       r4, r5
	mr       r5, r0
	addi     r3, r31, 0xe4
	li       r29, 0
	crclr    6
	bl       JUTWarningConsole_f
	b        lbl_80021288

lbl_80021268:
	lwz      r5, 0x84(r28)
	cmplw    r5, r27
	beq      lbl_80021288
	mr       r4, r27
	addi     r3, r31, 0x110
	li       r29, 0
	crclr    6
	bl       JUTWarningConsole_f

lbl_80021288:
	lbz      r0, 2(r27)
	lwz      r3, 4(r27)
	clrlwi   r0, r0, 0x19
	lwz      r27, 0xc(r27)
	add      r0, r3, r0
	add      r30, r0, r30
	addi     r30, r30, 0x10

lbl_800212A4:
	cmplwi   r27, 0
	bne      lbl_800211E8

lbl_800212AC:
	lwz      r27, 0x78(r28)
	b        lbl_8002133C

lbl_800212B4:
	lwz      r4, 0xc(r27)
	lwz      r0, 4(r27)
	cmplwi   r4, 0
	add      r30, r0, r30
	addi     r30, r30, 0x10
	beq      lbl_80021318
	lwz      r5, 8(r4)
	cmplw    r5, r27
	beq      lbl_800212E8
	addi     r3, r31, 0xe4
	li       r29, 0
	crclr    6
	bl       JUTWarningConsole_f

lbl_800212E8:
	lwz      r5, 4(r27)
	lwz      r0, 0xc(r27)
	addi     r3, r5, 0x10
	add      r3, r27, r3
	cmplw    r3, r0
	ble      lbl_80021338
	mr       r4, r27
	addi     r3, r31, 0x13c
	li       r29, 0
	crclr    6
	bl       JUTWarningConsole_f
	b        lbl_80021338

lbl_80021318:
	lwz      r5, 0x7c(r28)
	cmplw    r5, r27
	beq      lbl_80021338
	mr       r4, r27
	addi     r3, r31, 0x110
	li       r29, 0
	crclr    6
	bl       JUTWarningConsole_f

lbl_80021338:
	lwz      r27, 0xc(r27)

lbl_8002133C:
	cmplwi   r27, 0
	bne      lbl_800212B4
	lwz      r4, 0x38(r28)
	cmplw    r30, r4
	beq      lbl_80021364
	mr       r5, r30
	addi     r3, r31, 0x164
	li       r29, 0
	crclr    6
	bl       JUTWarningConsole_f

lbl_80021364:
	clrlwi.  r0, r29, 0x18
	bne      lbl_80021374
	addi     r3, r31, 0x194
	bl       JUTWarningConsole

lbl_80021374:
	addi     r3, r28, 0x18
	bl       OSUnlockMutex
	mr       r3, r29
	lmw      r27, 0xc(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80021394
 * Size:	0001C8
 */
bool JKRExpHeap::dump()
{
	/*
	stwu     r1, -0x40(r1)
	mflr     r0
	stw      r0, 0x44(r1)
	stmw     r25, 0x24(r1)
	mr       r26, r3
	lis      r3, lbl_804736E8@ha
	addi     r31, r3, lbl_804736E8@l
	addi     r3, r26, 0x18
	bl       OSLockMutex
	mr       r3, r26
	lwz      r12, 0(r26)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	mr       r0, r3
	addi     r3, r31, 0x1bc
	mr       r30, r0
	li       r29, 0
	li       r28, 0
	li       r27, 0
	bl       JUTReportConsole
	addi     r3, r31, 0x1f4
	bl       JUTReportConsole
	lwz      r0, 0x80(r26)
	cmplwi   r0, 0
	bne      lbl_80021404
	addi     r3, r2, lbl_805164F0@sda21
	bl       JUTReportConsole

lbl_80021404:
	lwz      r25, 0x80(r26)
	b        lbl_80021484

lbl_8002140C:
	lhz      r0, 0(r25)
	cmplwi   r0, 0x484d
	beq      lbl_8002142C
	mr       r4, r25
	addi     r3, r31, 0x204
	crclr    6
	bl       JUTReportConsole_f
	b        lbl_8002148C

lbl_8002142C:
	lbz      r6, 2(r25)
	addi     r5, r25, 0x10
	addi     r3, r31, 0x240
	addi     r4, r2, lbl_80516500@sda21
	rlwinm.  r0, r6, 0, 0x18, 0x18
	clrlwi   r8, r6, 0x19
	beq      lbl_8002144C
	addi     r4, r2, lbl_805164F8@sda21

lbl_8002144C:
	lwz      r6, 4(r25)
	lbz      r7, 3(r25)
	lwz      r9, 8(r25)
	lwz      r10, 0xc(r25)
	crclr    6
	bl       JUTReportConsole_f
	lbz      r0, 2(r25)
	addi     r28, r28, 1
	lwz      r3, 4(r25)
	clrlwi   r0, r0, 0x19
	lwz      r25, 0xc(r25)
	add      r0, r3, r0
	add      r29, r0, r29
	addi     r29, r29, 0x10

lbl_80021484:
	cmplwi   r25, 0
	bne      lbl_8002140C

lbl_8002148C:
	addi     r3, r31, 0x268
	bl       JUTReportConsole
	lwz      r0, 0x78(r26)
	cmplwi   r0, 0
	bne      lbl_800214A8
	addi     r3, r2, lbl_805164F0@sda21
	bl       JUTReportConsole

lbl_800214A8:
	lwz      r25, 0x78(r26)
	b        lbl_800214E4

lbl_800214B0:
	lbz      r0, 2(r25)
	addi     r3, r31, 0x240
	lwz      r6, 4(r25)
	addi     r5, r25, 0x10
	lbz      r7, 3(r25)
	clrlwi   r8, r0, 0x19
	lwz      r9, 8(r25)
	addi     r4, r2, lbl_80516508@sda21
	lwz      r10, 0xc(r25)
	crclr    6
	bl       JUTReportConsole_f
	lwz      r25, 0xc(r25)
	addi     r27, r27, 1

lbl_800214E4:
	cmplwi   r25, 0
	bne      lbl_800214B0
	lis      r0, 0x4330
	lwz      r5, 0x38(r26)
	stw      r29, 0xc(r1)
	mr       r4, r29
	lfd      f2, lbl_80516518@sda21(r2)
	mr       r6, r28
	stw      r0, 8(r1)
	mr       r7, r27
	lfs      f3, lbl_80516510@sda21(r2)
	addi     r3, r31, 0x278
	lfd      f0, 8(r1)
	stw      r5, 0x14(r1)
	fsubs    f1, f0, f2
	stw      r0, 0x10(r1)
	lfd      f0, 0x10(r1)
	fsubs    f0, f0, f2
	fdivs    f0, f1, f0
	fmuls    f1, f3, f0
	crset    6
	bl       JUTReportConsole_f
	addi     r3, r26, 0x18
	bl       OSUnlockMutex
	mr       r3, r30
	lmw      r25, 0x24(r1)
	lwz      r0, 0x44(r1)
	mtlr     r0
	addi     r1, r1, 0x40
	blr
	*/
}

/*
 * --INFO--
 * Address:	8002155C
 * Size:	0001F8
 */
bool JKRExpHeap::dump_sort()
{
	/*
	stwu     r1, -0x40(r1)
	mflr     r0
	stw      r0, 0x44(r1)
	stmw     r25, 0x24(r1)
	mr       r26, r3
	lis      r3, lbl_804736E8@ha
	addi     r31, r3, lbl_804736E8@l
	addi     r3, r26, 0x18
	bl       OSLockMutex
	mr       r3, r26
	lwz      r12, 0(r26)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	mr       r0, r3
	addi     r3, r31, 0x1bc
	mr       r30, r0
	li       r29, 0
	li       r28, 0
	li       r27, 0
	bl       JUTReportConsole
	addi     r3, r31, 0x1f4
	bl       JUTReportConsole
	lwz      r0, 0x80(r26)
	cmplwi   r0, 0
	bne      lbl_800215D0
	addi     r3, r2, lbl_805164F0@sda21
	bl       JUTReportConsole
	b        lbl_80021684

lbl_800215D0:
	li       r4, 0

lbl_800215D4:
	lwz      r3, 0x80(r26)
	li       r25, -1
	b        lbl_800215F8

lbl_800215E0:
	cmplw    r4, r3
	bge      lbl_800215F4
	cmplw    r3, r25
	bge      lbl_800215F4
	mr       r25, r3

lbl_800215F4:
	lwz      r3, 0xc(r3)

lbl_800215F8:
	cmplwi   r3, 0
	bne      lbl_800215E0
	addis    r0, r25, 1
	cmplwi   r0, 0xffff
	beq      lbl_80021684
	lhz      r0, 0(r25)
	cmplwi   r0, 0x484d
	beq      lbl_80021628
	addi     r3, r31, 0x204
	crclr    6
	bl       JUTReportConsole_f
	b        lbl_80021684

lbl_80021628:
	lbz      r6, 2(r25)
	addi     r5, r25, 0x10
	addi     r3, r31, 0x240
	addi     r4, r2, lbl_80516500@sda21
	rlwinm.  r0, r6, 0, 0x18, 0x18
	clrlwi   r8, r6, 0x19
	beq      lbl_80021648
	addi     r4, r2, lbl_805164F8@sda21

lbl_80021648:
	lwz      r6, 4(r25)
	lbz      r7, 3(r25)
	lwz      r9, 8(r25)
	lwz      r10, 0xc(r25)
	crclr    6
	bl       JUTReportConsole_f
	lbz      r0, 2(r25)
	mr       r4, r25
	lwz      r3, 4(r25)
	addi     r28, r28, 1
	clrlwi   r0, r0, 0x19
	add      r0, r3, r0
	add      r29, r0, r29
	addi     r29, r29, 0x10
	b        lbl_800215D4

lbl_80021684:
	addi     r3, r31, 0x268
	bl       JUTReportConsole
	lwz      r0, 0x78(r26)
	cmplwi   r0, 0
	bne      lbl_800216A0
	addi     r3, r2, lbl_805164F0@sda21
	bl       JUTReportConsole

lbl_800216A0:
	lwz      r25, 0x78(r26)
	b        lbl_800216DC

lbl_800216A8:
	lbz      r0, 2(r25)
	addi     r3, r31, 0x240
	lwz      r6, 4(r25)
	addi     r5, r25, 0x10
	lbz      r7, 3(r25)
	clrlwi   r8, r0, 0x19
	lwz      r9, 8(r25)
	addi     r4, r2, lbl_80516508@sda21
	lwz      r10, 0xc(r25)
	crclr    6
	bl       JUTReportConsole_f
	lwz      r25, 0xc(r25)
	addi     r27, r27, 1

lbl_800216DC:
	cmplwi   r25, 0
	bne      lbl_800216A8
	lis      r0, 0x4330
	lwz      r5, 0x38(r26)
	stw      r29, 0xc(r1)
	mr       r4, r29
	lfd      f2, lbl_80516518@sda21(r2)
	mr       r6, r28
	stw      r0, 8(r1)
	mr       r7, r27
	lfs      f3, lbl_80516510@sda21(r2)
	addi     r3, r31, 0x278
	lfd      f0, 8(r1)
	stw      r5, 0x14(r1)
	fsubs    f1, f0, f2
	stw      r0, 0x10(r1)
	lfd      f0, 0x10(r1)
	fsubs    f0, f0, f2
	fdivs    f0, f1, f0
	fmuls    f1, f3, f0
	crset    6
	bl       JUTReportConsole_f
	addi     r3, r26, 0x18
	bl       OSUnlockMutex
	mr       r3, r30
	lmw      r25, 0x24(r1)
	lwz      r0, 0x44(r1)
	mtlr     r0
	addi     r1, r1, 0x40
	blr
	*/
}

/*
 * --INFO--
 * Address:	80021754
 * Size:	000020
 */
void JKRExpHeap::CMemBlock::initiate(JKRExpHeap::CMemBlock*, JKRExpHeap::CMemBlock*, unsigned long, unsigned char, unsigned char)
{
	/*
	.loc_0x0:
	  li        r0, 0x484D
	  sth       r0, 0x0(r3)
	  stb       r8, 0x2(r3)
	  stb       r7, 0x3(r3)
	  stw       r6, 0x4(r3)
	  stw       r4, 0x8(r3)
	  stw       r5, 0xC(r3)
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80021774
 * Size:	000044
 */
u32 JKRExpHeap::CMemBlock::allocFore(unsigned long, unsigned char, unsigned char, unsigned char, unsigned char)
{
	/*
	.loc_0x0:
	  stb       r5, 0x3(r3)
	  addi      r5, r4, 0x10
	  li        r9, 0
	  stb       r6, 0x2(r3)
	  lwz       r0, 0x4(r3)
	  cmplw     r0, r5
	  blt-      .loc_0x3C
	  add       r9, r4, r3
	  stb       r7, 0x13(r9)
	  stb       r8, 0x12(r9)
	  lwz       r0, 0x4(r3)
	  sub       r0, r0, r5
	  stw       r0, 0x14(r9)
	  addi      r9, r9, 0x10
	  stw       r4, 0x4(r3)

	.loc_0x3C:
	  mr        r3, r9
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800217B8
 * Size:	000058
 */
u32 JKRExpHeap::CMemBlock::allocBack(unsigned long, unsigned char, unsigned char, unsigned char, unsigned char)
{
	/*
	.loc_0x0:
	  lwz       r0, 0x4(r3)
	  addi      r10, r4, 0x10
	  li        r9, 0
	  cmplw     r0, r10
	  blt-      .loc_0x44
	  add       r9, r3, r0
	  ori       r0, r8, 0x80
	  sub       r9, r9, r4
	  stb       r7, 0x3(r9)
	  stb       r0, 0x2(r9)
	  stw       r4, 0x4(r9)
	  stb       r5, 0x3(r3)
	  stb       r6, 0x2(r3)
	  lwz       r0, 0x4(r3)
	  sub       r0, r0, r10
	  stw       r0, 0x4(r3)
	  b         .loc_0x50

	.loc_0x44:
	  stb       r7, 0x3(r3)
	  li        r0, 0x80
	  stb       r0, 0x2(r3)

	.loc_0x50:
	  mr        r3, r9
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80021810
 * Size:	000060
 */
void JKRExpHeap::CMemBlock::free(JKRExpHeap*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	mr       r6, r3
	stw      r0, 0x14(r1)
	lwz      r5, 8(r3)
	lwz      r3, 0xc(r3)
	cmplwi   r5, 0
	bne      lbl_80021838
	stw      r3, 0x80(r4)
	b        lbl_8002183C

lbl_80021838:
	stw      r3, 0xc(r5)

lbl_8002183C:
	cmplwi   r3, 0
	bne      lbl_8002184C
	stw      r5, 0x84(r4)
	b        lbl_80021850

lbl_8002184C:
	stw      r5, 8(r3)

lbl_80021850:
	mr       r3, r4
	mr       r4, r6
	bl       recycleFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock
	lwz      r0, 0x14(r1)
	li       r3, 0
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80021870
 * Size:	00001C
 */
u32 JKRExpHeap::CMemBlock::getHeapBlock(void*)
{
	/*
	cmplwi   r3, 0
	beq      lbl_80021884
	lhzu     r0, -0x10(r3)
	cmplwi   r0, 0x484d
	beqlr

lbl_80021884:
	li       r3, 0
	blr
	*/
}

/*
 * --INFO--
 * Address:	8002188C
 * Size:	0000F4
 */
void JKRExpHeap::state_register(JKRHeap::TState*, unsigned long) const
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r30, r5
	cmplwi   r30, 0xff
	stw      r29, 0x14(r1)
	mr       r29, r4
	stw      r28, 0x10(r1)
	mr       r28, r3
	stw      r30, 0x14(r4)
	bgt      lbl_8002190C
	addi     r3, r28, 0x18
	bl       OSLockMutex
	lwz      r4, 0x80(r28)
	clrlwi   r3, r30, 0x18
	li       r31, 0
	b        lbl_800218F4

lbl_800218D8:
	lbz      r0, 3(r4)
	cmplw    r0, r3
	bne      lbl_800218F0
	lwz      r0, 4(r4)
	add      r31, r0, r31
	addi     r31, r31, 0x10

lbl_800218F0:
	lwz      r4, 0xc(r4)

lbl_800218F4:
	cmplwi   r4, 0
	bne      lbl_800218D8
	addi     r3, r28, 0x18
	bl       OSUnlockMutex
	stw      r31, 0(r29)
	b        lbl_8002191C

lbl_8002190C:
	bl       getTotalFreeSize__7JKRHeapFv
	lwz      r0, 0x38(r28)
	subf     r0, r3, r0
	stw      r0, 0(r29)

lbl_8002191C:
	lwz      r4, 0x80(r28)
	li       r3, 0
	b        lbl_80021954

lbl_80021928:
	cmplwi   r30, 0xff
	bgt      lbl_80021948
	lbz      r0, 3(r4)
	cmplw    r0, r30
	bne      lbl_80021950
	mulli    r0, r4, 3
	add      r3, r3, r0
	b        lbl_80021950

lbl_80021948:
	mulli    r0, r4, 3
	add      r3, r3, r0

lbl_80021950:
	lwz      r4, 0xc(r4)

lbl_80021954:
	cmplwi   r4, 0
	bne      lbl_80021928
	stw      r3, 4(r29)
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r28, 0x10(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80021980
 * Size:	000030
 */
void JKRExpHeap::state_compare(const JKRHeap::TState&, const JKRHeap::TState&) const
{
	/*
	.loc_0x0:
	  lwz       r6, 0x4(r4)
	  li        r3, 0x1
	  lwz       r0, 0x4(r5)
	  cmplw     r6, r0
	  beq-      .loc_0x18
	  li        r3, 0

	.loc_0x18:
	  lwz       r4, 0x0(r4)
	  lwz       r0, 0x0(r5)
	  cmplw     r4, r0
	  beqlr-
	  li        r3, 0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800219B0
 * Size:	00000C
 */
u32 JKRExpHeap::getHeapType()
{
	/*
	lis      r3, 0x45585048@ha
	addi     r3, r3, 0x45585048@l
	blr
	*/
}

/*
 * --INFO--
 * Address:	800219BC
 * Size:	000008
 */
u8 JKRExpHeap::do_getCurrentGroupId()
{
	return m_currentGroupID;
	/*
	lbz      r3, 0x6d(r3)
	blr
	*/
}

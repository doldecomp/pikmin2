.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global E2DScreen_searchAssert__3ebiFP9J2DScreenUx
E2DScreen_searchAssert__3ebiFP9J2DScreenUx:
/* 803CA358 003C7298  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 803CA35C 003C729C  7C 08 02 A6 */	mflr r0
/* 803CA360 003C72A0  90 01 00 34 */	stw r0, 0x34(r1)
/* 803CA364 003C72A4  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 803CA368 003C72A8  93 C1 00 28 */	stw r30, 0x28(r1)
/* 803CA36C 003C72AC  7C BE 2B 78 */	mr r30, r5
/* 803CA370 003C72B0  93 A1 00 24 */	stw r29, 0x24(r1)
/* 803CA374 003C72B4  7C DD 33 78 */	mr r29, r6
/* 803CA378 003C72B8  81 83 00 00 */	lwz r12, 0(r3)
/* 803CA37C 003C72BC  81 8C 00 3C */	lwz r12, 0x3c(r12)
/* 803CA380 003C72C0  7D 89 03 A6 */	mtctr r12
/* 803CA384 003C72C4  4E 80 04 21 */	bctrl 
/* 803CA388 003C72C8  7C 7F 1B 79 */	or. r31, r3, r3
/* 803CA38C 003C72CC  40 82 00 38 */	bne lbl_803CA3C4
/* 803CA390 003C72D0  7F A4 EB 78 */	mr r4, r29
/* 803CA394 003C72D4  7F C3 F3 78 */	mr r3, r30
/* 803CA398 003C72D8  38 A1 00 08 */	addi r5, r1, 8
/* 803CA39C 003C72DC  4B FF 7B 19 */	bl EUTDebug_Tag64ToName__3ebiFUxPc
/* 803CA3A0 003C72E0  28 1F 00 00 */	cmplwi r31, 0
/* 803CA3A4 003C72E4  40 82 00 20 */	bne lbl_803CA3C4
/* 803CA3A8 003C72E8  3C 60 80 49 */	lis r3, lbl_80496428@ha
/* 803CA3AC 003C72EC  3C A0 80 49 */	lis r5, lbl_80496438@ha
/* 803CA3B0 003C72F0  38 63 64 28 */	addi r3, r3, lbl_80496428@l
/* 803CA3B4 003C72F4  38 80 00 14 */	li r4, 0x14
/* 803CA3B8 003C72F8  38 A5 64 38 */	addi r5, r5, lbl_80496438@l
/* 803CA3BC 003C72FC  4C C6 31 82 */	crclr 6
/* 803CA3C0 003C7300  4B C6 02 81 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_803CA3C4:
/* 803CA3C4 003C7304  80 01 00 34 */	lwz r0, 0x34(r1)
/* 803CA3C8 003C7308  7F E3 FB 78 */	mr r3, r31
/* 803CA3CC 003C730C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 803CA3D0 003C7310  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 803CA3D4 003C7314  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 803CA3D8 003C7318  7C 08 03 A6 */	mtlr r0
/* 803CA3DC 003C731C  38 21 00 30 */	addi r1, r1, 0x30
/* 803CA3E0 003C7320  4E 80 00 20 */	blr 

.global E2DPane_setTreeInfluencedAlpha__3ebiFP7J2DPaneb
E2DPane_setTreeInfluencedAlpha__3ebiFP7J2DPaneb:
/* 803CA3E4 003C7324  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 803CA3E8 003C7328  7C 08 02 A6 */	mflr r0
/* 803CA3EC 003C732C  38 A0 00 00 */	li r5, 0
/* 803CA3F0 003C7330  90 01 00 34 */	stw r0, 0x34(r1)
/* 803CA3F4 003C7334  BF 01 00 10 */	stmw r24, 0x10(r1)
/* 803CA3F8 003C7338  7C 78 1B 78 */	mr r24, r3
/* 803CA3FC 003C733C  7C 9F 23 78 */	mr r31, r4
/* 803CA400 003C7340  4B C6 E9 AD */	bl setInfluencedAlpha__7J2DPaneFbb
/* 803CA404 003C7344  83 D8 00 DC */	lwz r30, 0xdc(r24)
/* 803CA408 003C7348  28 1E 00 00 */	cmplwi r30, 0
/* 803CA40C 003C734C  41 82 01 94 */	beq lbl_803CA5A0
/* 803CA410 003C7350  3B DE FF F4 */	addi r30, r30, -12
/* 803CA414 003C7354  48 00 01 8C */	b lbl_803CA5A0
lbl_803CA418:
/* 803CA418 003C7358  83 7E 00 0C */	lwz r27, 0xc(r30)
/* 803CA41C 003C735C  7F E4 FB 78 */	mr r4, r31
/* 803CA420 003C7360  38 A0 00 00 */	li r5, 0
/* 803CA424 003C7364  7F 63 DB 78 */	mr r3, r27
/* 803CA428 003C7368  4B C6 E9 85 */	bl setInfluencedAlpha__7J2DPaneFbb
/* 803CA42C 003C736C  83 BB 00 DC */	lwz r29, 0xdc(r27)
/* 803CA430 003C7370  28 1D 00 00 */	cmplwi r29, 0
/* 803CA434 003C7374  41 82 01 54 */	beq lbl_803CA588
/* 803CA438 003C7378  3B BD FF F4 */	addi r29, r29, -12
/* 803CA43C 003C737C  48 00 01 4C */	b lbl_803CA588
lbl_803CA440:
/* 803CA440 003C7380  83 7D 00 0C */	lwz r27, 0xc(r29)
/* 803CA444 003C7384  7F E4 FB 78 */	mr r4, r31
/* 803CA448 003C7388  38 A0 00 00 */	li r5, 0
/* 803CA44C 003C738C  7F 63 DB 78 */	mr r3, r27
/* 803CA450 003C7390  4B C6 E9 5D */	bl setInfluencedAlpha__7J2DPaneFbb
/* 803CA454 003C7394  83 9B 00 DC */	lwz r28, 0xdc(r27)
/* 803CA458 003C7398  28 1C 00 00 */	cmplwi r28, 0
/* 803CA45C 003C739C  41 82 01 14 */	beq lbl_803CA570
/* 803CA460 003C73A0  3B 9C FF F4 */	addi r28, r28, -12
/* 803CA464 003C73A4  48 00 01 0C */	b lbl_803CA570
lbl_803CA468:
/* 803CA468 003C73A8  83 7C 00 0C */	lwz r27, 0xc(r28)
/* 803CA46C 003C73AC  7F E4 FB 78 */	mr r4, r31
/* 803CA470 003C73B0  38 A0 00 00 */	li r5, 0
/* 803CA474 003C73B4  7F 63 DB 78 */	mr r3, r27
/* 803CA478 003C73B8  4B C6 E9 35 */	bl setInfluencedAlpha__7J2DPaneFbb
/* 803CA47C 003C73BC  38 7B 00 DC */	addi r3, r27, 0xdc
/* 803CA480 003C73C0  4B C5 97 A1 */	bl getFirstLink__10JSUPtrListCFv
/* 803CA484 003C73C4  28 03 00 00 */	cmplwi r3, 0
/* 803CA488 003C73C8  41 82 00 08 */	beq lbl_803CA490
/* 803CA48C 003C73CC  38 63 FF F4 */	addi r3, r3, -12
lbl_803CA490:
/* 803CA490 003C73D0  7C 79 1B 78 */	mr r25, r3
/* 803CA494 003C73D4  48 00 00 C4 */	b lbl_803CA558
lbl_803CA498:
/* 803CA498 003C73D8  83 79 00 0C */	lwz r27, 0xc(r25)
/* 803CA49C 003C73DC  7F E4 FB 78 */	mr r4, r31
/* 803CA4A0 003C73E0  38 A0 00 00 */	li r5, 0
/* 803CA4A4 003C73E4  7F 63 DB 78 */	mr r3, r27
/* 803CA4A8 003C73E8  4B C6 E9 05 */	bl setInfluencedAlpha__7J2DPaneFbb
/* 803CA4AC 003C73EC  3B 5B 00 DC */	addi r26, r27, 0xdc
/* 803CA4B0 003C73F0  7F 43 D3 78 */	mr r3, r26
/* 803CA4B4 003C73F4  4B C6 E4 75 */	bl getFirstChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA4B8 003C73F8  7C 78 1B 78 */	mr r24, r3
/* 803CA4BC 003C73FC  48 00 00 7C */	b lbl_803CA538
lbl_803CA4C0:
/* 803CA4C0 003C7400  7F 03 C3 78 */	mr r3, r24
/* 803CA4C4 003C7404  4B C6 E4 79 */	bl getObject__17JSUTree$$07J2DPane$$1CFv
/* 803CA4C8 003C7408  7F E4 FB 78 */	mr r4, r31
/* 803CA4CC 003C740C  7C 7B 1B 78 */	mr r27, r3
/* 803CA4D0 003C7410  38 A0 00 00 */	li r5, 0
/* 803CA4D4 003C7414  4B C6 E8 D9 */	bl setInfluencedAlpha__7J2DPaneFbb
/* 803CA4D8 003C7418  7F 63 DB 78 */	mr r3, r27
/* 803CA4DC 003C741C  4B F3 90 19 */	bl getPaneTree__7J2DPaneFv
/* 803CA4E0 003C7420  7C 7B 1B 78 */	mr r27, r3
/* 803CA4E4 003C7424  4B C6 E4 45 */	bl getFirstChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA4E8 003C7428  7C 64 1B 78 */	mr r4, r3
/* 803CA4EC 003C742C  38 61 00 08 */	addi r3, r1, 8
/* 803CA4F0 003C7430  4B C6 E4 25 */	bl __ct__25JSUTreeIterator$$07J2DPane$$1FP17JSUTree$$07J2DPane$$1
/* 803CA4F4 003C7434  48 00 00 1C */	b lbl_803CA510
lbl_803CA4F8:
/* 803CA4F8 003C7438  38 61 00 08 */	addi r3, r1, 8
/* 803CA4FC 003C743C  4B F3 8F ED */	bl getObject__25JSUTreeIterator$$07J2DPane$$1CFv
/* 803CA500 003C7440  7F E4 FB 78 */	mr r4, r31
/* 803CA504 003C7444  4B FF FE E1 */	bl E2DPane_setTreeInfluencedAlpha__3ebiFP7J2DPaneb
/* 803CA508 003C7448  38 61 00 08 */	addi r3, r1, 8
/* 803CA50C 003C744C  4B C6 E3 ED */	bl __pp__25JSUTreeIterator$$07J2DPane$$1Fv
lbl_803CA510:
/* 803CA510 003C7450  7F 63 DB 78 */	mr r3, r27
/* 803CA514 003C7454  4B C6 E3 DD */	bl getEndChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA518 003C7458  7C 64 1B 78 */	mr r4, r3
/* 803CA51C 003C745C  38 61 00 08 */	addi r3, r1, 8
/* 803CA520 003C7460  4B C6 E3 B9 */	bl __ne__25JSUTreeIterator$$07J2DPane$$1CFPC17JSUTree$$07J2DPane$$1
/* 803CA524 003C7464  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 803CA528 003C7468  40 82 FF D0 */	bne lbl_803CA4F8
/* 803CA52C 003C746C  7F 03 C3 78 */	mr r3, r24
/* 803CA530 003C7470  4B C6 E3 95 */	bl getNextChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA534 003C7474  7C 78 1B 78 */	mr r24, r3
lbl_803CA538:
/* 803CA538 003C7478  7F 43 D3 78 */	mr r3, r26
/* 803CA53C 003C747C  4B C6 E3 B5 */	bl getEndChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA540 003C7480  7C 18 18 40 */	cmplw r24, r3
/* 803CA544 003C7484  40 82 FF 7C */	bne lbl_803CA4C0
/* 803CA548 003C7488  83 39 00 18 */	lwz r25, 0x18(r25)
/* 803CA54C 003C748C  28 19 00 00 */	cmplwi r25, 0
/* 803CA550 003C7490  41 82 00 08 */	beq lbl_803CA558
/* 803CA554 003C7494  3B 39 FF F4 */	addi r25, r25, -12
lbl_803CA558:
/* 803CA558 003C7498  28 19 00 00 */	cmplwi r25, 0
/* 803CA55C 003C749C  40 82 FF 3C */	bne lbl_803CA498
/* 803CA560 003C74A0  83 9C 00 18 */	lwz r28, 0x18(r28)
/* 803CA564 003C74A4  28 1C 00 00 */	cmplwi r28, 0
/* 803CA568 003C74A8  41 82 00 08 */	beq lbl_803CA570
/* 803CA56C 003C74AC  3B 9C FF F4 */	addi r28, r28, -12
lbl_803CA570:
/* 803CA570 003C74B0  28 1C 00 00 */	cmplwi r28, 0
/* 803CA574 003C74B4  40 82 FE F4 */	bne lbl_803CA468
/* 803CA578 003C74B8  83 BD 00 18 */	lwz r29, 0x18(r29)
/* 803CA57C 003C74BC  28 1D 00 00 */	cmplwi r29, 0
/* 803CA580 003C74C0  41 82 00 08 */	beq lbl_803CA588
/* 803CA584 003C74C4  3B BD FF F4 */	addi r29, r29, -12
lbl_803CA588:
/* 803CA588 003C74C8  28 1D 00 00 */	cmplwi r29, 0
/* 803CA58C 003C74CC  40 82 FE B4 */	bne lbl_803CA440
/* 803CA590 003C74D0  83 DE 00 18 */	lwz r30, 0x18(r30)
/* 803CA594 003C74D4  28 1E 00 00 */	cmplwi r30, 0
/* 803CA598 003C74D8  41 82 00 08 */	beq lbl_803CA5A0
/* 803CA59C 003C74DC  3B DE FF F4 */	addi r30, r30, -12
lbl_803CA5A0:
/* 803CA5A0 003C74E0  28 1E 00 00 */	cmplwi r30, 0
/* 803CA5A4 003C74E4  40 82 FE 74 */	bne lbl_803CA418
/* 803CA5A8 003C74E8  BB 01 00 10 */	lmw r24, 0x10(r1)
/* 803CA5AC 003C74EC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 803CA5B0 003C74F0  7C 08 03 A6 */	mtlr r0
/* 803CA5B4 003C74F4  38 21 00 30 */	addi r1, r1, 0x30
/* 803CA5B8 003C74F8  4E 80 00 20 */	blr 

.global E2DPane_setTreeShow__3ebiFP7J2DPane
E2DPane_setTreeShow__3ebiFP7J2DPane:
/* 803CA5BC 003C74FC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 803CA5C0 003C7500  7C 08 02 A6 */	mflr r0
/* 803CA5C4 003C7504  90 01 00 34 */	stw r0, 0x34(r1)
/* 803CA5C8 003C7508  38 00 00 01 */	li r0, 1
/* 803CA5CC 003C750C  BF 21 00 14 */	stmw r25, 0x14(r1)
/* 803CA5D0 003C7510  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA5D4 003C7514  83 E3 00 DC */	lwz r31, 0xdc(r3)
/* 803CA5D8 003C7518  28 1F 00 00 */	cmplwi r31, 0
/* 803CA5DC 003C751C  41 82 01 68 */	beq lbl_803CA744
/* 803CA5E0 003C7520  3B FF FF F4 */	addi r31, r31, -12
/* 803CA5E4 003C7524  48 00 01 60 */	b lbl_803CA744
lbl_803CA5E8:
/* 803CA5E8 003C7528  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 803CA5EC 003C752C  38 00 00 01 */	li r0, 1
/* 803CA5F0 003C7530  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA5F4 003C7534  83 C3 00 DC */	lwz r30, 0xdc(r3)
/* 803CA5F8 003C7538  28 1E 00 00 */	cmplwi r30, 0
/* 803CA5FC 003C753C  41 82 01 30 */	beq lbl_803CA72C
/* 803CA600 003C7540  3B DE FF F4 */	addi r30, r30, -12
/* 803CA604 003C7544  48 00 01 28 */	b lbl_803CA72C
lbl_803CA608:
/* 803CA608 003C7548  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 803CA60C 003C754C  38 00 00 01 */	li r0, 1
/* 803CA610 003C7550  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA614 003C7554  83 A3 00 DC */	lwz r29, 0xdc(r3)
/* 803CA618 003C7558  28 1D 00 00 */	cmplwi r29, 0
/* 803CA61C 003C755C  41 82 00 F8 */	beq lbl_803CA714
/* 803CA620 003C7560  3B BD FF F4 */	addi r29, r29, -12
/* 803CA624 003C7564  48 00 00 F0 */	b lbl_803CA714
lbl_803CA628:
/* 803CA628 003C7568  80 7D 00 0C */	lwz r3, 0xc(r29)
/* 803CA62C 003C756C  38 00 00 01 */	li r0, 1
/* 803CA630 003C7570  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA634 003C7574  38 63 00 DC */	addi r3, r3, 0xdc
/* 803CA638 003C7578  4B C5 95 E9 */	bl getFirstLink__10JSUPtrListCFv
/* 803CA63C 003C757C  28 03 00 00 */	cmplwi r3, 0
/* 803CA640 003C7580  41 82 00 08 */	beq lbl_803CA648
/* 803CA644 003C7584  38 63 FF F4 */	addi r3, r3, -12
lbl_803CA648:
/* 803CA648 003C7588  7C 7A 1B 78 */	mr r26, r3
/* 803CA64C 003C758C  48 00 00 B0 */	b lbl_803CA6FC
lbl_803CA650:
/* 803CA650 003C7590  80 7A 00 0C */	lwz r3, 0xc(r26)
/* 803CA654 003C7594  38 00 00 01 */	li r0, 1
/* 803CA658 003C7598  3B 63 00 DC */	addi r27, r3, 0xdc
/* 803CA65C 003C759C  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA660 003C75A0  7F 63 DB 78 */	mr r3, r27
/* 803CA664 003C75A4  4B C6 E2 C5 */	bl getFirstChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA668 003C75A8  7C 79 1B 78 */	mr r25, r3
/* 803CA66C 003C75AC  48 00 00 70 */	b lbl_803CA6DC
lbl_803CA670:
/* 803CA670 003C75B0  7F 23 CB 78 */	mr r3, r25
/* 803CA674 003C75B4  4B C6 E2 C9 */	bl getObject__17JSUTree$$07J2DPane$$1CFv
/* 803CA678 003C75B8  7C 7C 1B 78 */	mr r28, r3
/* 803CA67C 003C75BC  48 00 00 E5 */	bl show__7J2DPaneFv
/* 803CA680 003C75C0  7F 83 E3 78 */	mr r3, r28
/* 803CA684 003C75C4  4B F3 8E 71 */	bl getPaneTree__7J2DPaneFv
/* 803CA688 003C75C8  7C 7C 1B 78 */	mr r28, r3
/* 803CA68C 003C75CC  4B C6 E2 9D */	bl getFirstChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA690 003C75D0  7C 64 1B 78 */	mr r4, r3
/* 803CA694 003C75D4  38 61 00 08 */	addi r3, r1, 8
/* 803CA698 003C75D8  4B C6 E2 7D */	bl __ct__25JSUTreeIterator$$07J2DPane$$1FP17JSUTree$$07J2DPane$$1
/* 803CA69C 003C75DC  48 00 00 18 */	b lbl_803CA6B4
lbl_803CA6A0:
/* 803CA6A0 003C75E0  38 61 00 08 */	addi r3, r1, 8
/* 803CA6A4 003C75E4  4B F3 8E 45 */	bl getObject__25JSUTreeIterator$$07J2DPane$$1CFv
/* 803CA6A8 003C75E8  4B FF FF 15 */	bl E2DPane_setTreeShow__3ebiFP7J2DPane
/* 803CA6AC 003C75EC  38 61 00 08 */	addi r3, r1, 8
/* 803CA6B0 003C75F0  4B C6 E2 49 */	bl __pp__25JSUTreeIterator$$07J2DPane$$1Fv
lbl_803CA6B4:
/* 803CA6B4 003C75F4  7F 83 E3 78 */	mr r3, r28
/* 803CA6B8 003C75F8  4B C6 E2 39 */	bl getEndChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA6BC 003C75FC  7C 64 1B 78 */	mr r4, r3
/* 803CA6C0 003C7600  38 61 00 08 */	addi r3, r1, 8
/* 803CA6C4 003C7604  4B C6 E2 15 */	bl __ne__25JSUTreeIterator$$07J2DPane$$1CFPC17JSUTree$$07J2DPane$$1
/* 803CA6C8 003C7608  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 803CA6CC 003C760C  40 82 FF D4 */	bne lbl_803CA6A0
/* 803CA6D0 003C7610  7F 23 CB 78 */	mr r3, r25
/* 803CA6D4 003C7614  4B C6 E1 F1 */	bl getNextChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA6D8 003C7618  7C 79 1B 78 */	mr r25, r3
lbl_803CA6DC:
/* 803CA6DC 003C761C  7F 63 DB 78 */	mr r3, r27
/* 803CA6E0 003C7620  4B C6 E2 11 */	bl getEndChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA6E4 003C7624  7C 19 18 40 */	cmplw r25, r3
/* 803CA6E8 003C7628  40 82 FF 88 */	bne lbl_803CA670
/* 803CA6EC 003C762C  83 5A 00 18 */	lwz r26, 0x18(r26)
/* 803CA6F0 003C7630  28 1A 00 00 */	cmplwi r26, 0
/* 803CA6F4 003C7634  41 82 00 08 */	beq lbl_803CA6FC
/* 803CA6F8 003C7638  3B 5A FF F4 */	addi r26, r26, -12
lbl_803CA6FC:
/* 803CA6FC 003C763C  28 1A 00 00 */	cmplwi r26, 0
/* 803CA700 003C7640  40 82 FF 50 */	bne lbl_803CA650
/* 803CA704 003C7644  83 BD 00 18 */	lwz r29, 0x18(r29)
/* 803CA708 003C7648  28 1D 00 00 */	cmplwi r29, 0
/* 803CA70C 003C764C  41 82 00 08 */	beq lbl_803CA714
/* 803CA710 003C7650  3B BD FF F4 */	addi r29, r29, -12
lbl_803CA714:
/* 803CA714 003C7654  28 1D 00 00 */	cmplwi r29, 0
/* 803CA718 003C7658  40 82 FF 10 */	bne lbl_803CA628
/* 803CA71C 003C765C  83 DE 00 18 */	lwz r30, 0x18(r30)
/* 803CA720 003C7660  28 1E 00 00 */	cmplwi r30, 0
/* 803CA724 003C7664  41 82 00 08 */	beq lbl_803CA72C
/* 803CA728 003C7668  3B DE FF F4 */	addi r30, r30, -12
lbl_803CA72C:
/* 803CA72C 003C766C  28 1E 00 00 */	cmplwi r30, 0
/* 803CA730 003C7670  40 82 FE D8 */	bne lbl_803CA608
/* 803CA734 003C7674  83 FF 00 18 */	lwz r31, 0x18(r31)
/* 803CA738 003C7678  28 1F 00 00 */	cmplwi r31, 0
/* 803CA73C 003C767C  41 82 00 08 */	beq lbl_803CA744
/* 803CA740 003C7680  3B FF FF F4 */	addi r31, r31, -12
lbl_803CA744:
/* 803CA744 003C7684  28 1F 00 00 */	cmplwi r31, 0
/* 803CA748 003C7688  40 82 FE A0 */	bne lbl_803CA5E8
/* 803CA74C 003C768C  BB 21 00 14 */	lmw r25, 0x14(r1)
/* 803CA750 003C7690  80 01 00 34 */	lwz r0, 0x34(r1)
/* 803CA754 003C7694  7C 08 03 A6 */	mtlr r0
/* 803CA758 003C7698  38 21 00 30 */	addi r1, r1, 0x30
/* 803CA75C 003C769C  4E 80 00 20 */	blr 

.global show__7J2DPaneFv
show__7J2DPaneFv:
/* 803CA760 003C76A0  38 00 00 01 */	li r0, 1
/* 803CA764 003C76A4  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA768 003C76A8  4E 80 00 20 */	blr 

.global E2DPane_setTreeHide__3ebiFP7J2DPane
E2DPane_setTreeHide__3ebiFP7J2DPane:
/* 803CA76C 003C76AC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 803CA770 003C76B0  7C 08 02 A6 */	mflr r0
/* 803CA774 003C76B4  90 01 00 34 */	stw r0, 0x34(r1)
/* 803CA778 003C76B8  38 00 00 00 */	li r0, 0
/* 803CA77C 003C76BC  BF 21 00 14 */	stmw r25, 0x14(r1)
/* 803CA780 003C76C0  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA784 003C76C4  83 E3 00 DC */	lwz r31, 0xdc(r3)
/* 803CA788 003C76C8  28 1F 00 00 */	cmplwi r31, 0
/* 803CA78C 003C76CC  41 82 01 68 */	beq lbl_803CA8F4
/* 803CA790 003C76D0  3B FF FF F4 */	addi r31, r31, -12
/* 803CA794 003C76D4  48 00 01 60 */	b lbl_803CA8F4
lbl_803CA798:
/* 803CA798 003C76D8  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 803CA79C 003C76DC  38 00 00 00 */	li r0, 0
/* 803CA7A0 003C76E0  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA7A4 003C76E4  83 C3 00 DC */	lwz r30, 0xdc(r3)
/* 803CA7A8 003C76E8  28 1E 00 00 */	cmplwi r30, 0
/* 803CA7AC 003C76EC  41 82 01 30 */	beq lbl_803CA8DC
/* 803CA7B0 003C76F0  3B DE FF F4 */	addi r30, r30, -12
/* 803CA7B4 003C76F4  48 00 01 28 */	b lbl_803CA8DC
lbl_803CA7B8:
/* 803CA7B8 003C76F8  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 803CA7BC 003C76FC  38 00 00 00 */	li r0, 0
/* 803CA7C0 003C7700  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA7C4 003C7704  83 A3 00 DC */	lwz r29, 0xdc(r3)
/* 803CA7C8 003C7708  28 1D 00 00 */	cmplwi r29, 0
/* 803CA7CC 003C770C  41 82 00 F8 */	beq lbl_803CA8C4
/* 803CA7D0 003C7710  3B BD FF F4 */	addi r29, r29, -12
/* 803CA7D4 003C7714  48 00 00 F0 */	b lbl_803CA8C4
lbl_803CA7D8:
/* 803CA7D8 003C7718  80 7D 00 0C */	lwz r3, 0xc(r29)
/* 803CA7DC 003C771C  38 00 00 00 */	li r0, 0
/* 803CA7E0 003C7720  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA7E4 003C7724  38 63 00 DC */	addi r3, r3, 0xdc
/* 803CA7E8 003C7728  4B C5 94 39 */	bl getFirstLink__10JSUPtrListCFv
/* 803CA7EC 003C772C  28 03 00 00 */	cmplwi r3, 0
/* 803CA7F0 003C7730  41 82 00 08 */	beq lbl_803CA7F8
/* 803CA7F4 003C7734  38 63 FF F4 */	addi r3, r3, -12
lbl_803CA7F8:
/* 803CA7F8 003C7738  7C 7A 1B 78 */	mr r26, r3
/* 803CA7FC 003C773C  48 00 00 B0 */	b lbl_803CA8AC
lbl_803CA800:
/* 803CA800 003C7740  80 7A 00 0C */	lwz r3, 0xc(r26)
/* 803CA804 003C7744  38 00 00 00 */	li r0, 0
/* 803CA808 003C7748  3B 63 00 DC */	addi r27, r3, 0xdc
/* 803CA80C 003C774C  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA810 003C7750  7F 63 DB 78 */	mr r3, r27
/* 803CA814 003C7754  4B C6 E1 15 */	bl getFirstChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA818 003C7758  7C 79 1B 78 */	mr r25, r3
/* 803CA81C 003C775C  48 00 00 70 */	b lbl_803CA88C
lbl_803CA820:
/* 803CA820 003C7760  7F 23 CB 78 */	mr r3, r25
/* 803CA824 003C7764  4B C6 E1 19 */	bl getObject__17JSUTree$$07J2DPane$$1CFv
/* 803CA828 003C7768  7C 7C 1B 78 */	mr r28, r3
/* 803CA82C 003C776C  48 00 00 E5 */	bl hide__7J2DPaneFv
/* 803CA830 003C7770  7F 83 E3 78 */	mr r3, r28
/* 803CA834 003C7774  4B F3 8C C1 */	bl getPaneTree__7J2DPaneFv
/* 803CA838 003C7778  7C 7C 1B 78 */	mr r28, r3
/* 803CA83C 003C777C  4B C6 E0 ED */	bl getFirstChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA840 003C7780  7C 64 1B 78 */	mr r4, r3
/* 803CA844 003C7784  38 61 00 08 */	addi r3, r1, 8
/* 803CA848 003C7788  4B C6 E0 CD */	bl __ct__25JSUTreeIterator$$07J2DPane$$1FP17JSUTree$$07J2DPane$$1
/* 803CA84C 003C778C  48 00 00 18 */	b lbl_803CA864
lbl_803CA850:
/* 803CA850 003C7790  38 61 00 08 */	addi r3, r1, 8
/* 803CA854 003C7794  4B F3 8C 95 */	bl getObject__25JSUTreeIterator$$07J2DPane$$1CFv
/* 803CA858 003C7798  4B FF FF 15 */	bl E2DPane_setTreeHide__3ebiFP7J2DPane
/* 803CA85C 003C779C  38 61 00 08 */	addi r3, r1, 8
/* 803CA860 003C77A0  4B C6 E0 99 */	bl __pp__25JSUTreeIterator$$07J2DPane$$1Fv
lbl_803CA864:
/* 803CA864 003C77A4  7F 83 E3 78 */	mr r3, r28
/* 803CA868 003C77A8  4B C6 E0 89 */	bl getEndChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA86C 003C77AC  7C 64 1B 78 */	mr r4, r3
/* 803CA870 003C77B0  38 61 00 08 */	addi r3, r1, 8
/* 803CA874 003C77B4  4B C6 E0 65 */	bl __ne__25JSUTreeIterator$$07J2DPane$$1CFPC17JSUTree$$07J2DPane$$1
/* 803CA878 003C77B8  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 803CA87C 003C77BC  40 82 FF D4 */	bne lbl_803CA850
/* 803CA880 003C77C0  7F 23 CB 78 */	mr r3, r25
/* 803CA884 003C77C4  4B C6 E0 41 */	bl getNextChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA888 003C77C8  7C 79 1B 78 */	mr r25, r3
lbl_803CA88C:
/* 803CA88C 003C77CC  7F 63 DB 78 */	mr r3, r27
/* 803CA890 003C77D0  4B C6 E0 61 */	bl getEndChild__17JSUTree$$07J2DPane$$1CFv
/* 803CA894 003C77D4  7C 19 18 40 */	cmplw r25, r3
/* 803CA898 003C77D8  40 82 FF 88 */	bne lbl_803CA820
/* 803CA89C 003C77DC  83 5A 00 18 */	lwz r26, 0x18(r26)
/* 803CA8A0 003C77E0  28 1A 00 00 */	cmplwi r26, 0
/* 803CA8A4 003C77E4  41 82 00 08 */	beq lbl_803CA8AC
/* 803CA8A8 003C77E8  3B 5A FF F4 */	addi r26, r26, -12
lbl_803CA8AC:
/* 803CA8AC 003C77EC  28 1A 00 00 */	cmplwi r26, 0
/* 803CA8B0 003C77F0  40 82 FF 50 */	bne lbl_803CA800
/* 803CA8B4 003C77F4  83 BD 00 18 */	lwz r29, 0x18(r29)
/* 803CA8B8 003C77F8  28 1D 00 00 */	cmplwi r29, 0
/* 803CA8BC 003C77FC  41 82 00 08 */	beq lbl_803CA8C4
/* 803CA8C0 003C7800  3B BD FF F4 */	addi r29, r29, -12
lbl_803CA8C4:
/* 803CA8C4 003C7804  28 1D 00 00 */	cmplwi r29, 0
/* 803CA8C8 003C7808  40 82 FF 10 */	bne lbl_803CA7D8
/* 803CA8CC 003C780C  83 DE 00 18 */	lwz r30, 0x18(r30)
/* 803CA8D0 003C7810  28 1E 00 00 */	cmplwi r30, 0
/* 803CA8D4 003C7814  41 82 00 08 */	beq lbl_803CA8DC
/* 803CA8D8 003C7818  3B DE FF F4 */	addi r30, r30, -12
lbl_803CA8DC:
/* 803CA8DC 003C781C  28 1E 00 00 */	cmplwi r30, 0
/* 803CA8E0 003C7820  40 82 FE D8 */	bne lbl_803CA7B8
/* 803CA8E4 003C7824  83 FF 00 18 */	lwz r31, 0x18(r31)
/* 803CA8E8 003C7828  28 1F 00 00 */	cmplwi r31, 0
/* 803CA8EC 003C782C  41 82 00 08 */	beq lbl_803CA8F4
/* 803CA8F0 003C7830  3B FF FF F4 */	addi r31, r31, -12
lbl_803CA8F4:
/* 803CA8F4 003C7834  28 1F 00 00 */	cmplwi r31, 0
/* 803CA8F8 003C7838  40 82 FE A0 */	bne lbl_803CA798
/* 803CA8FC 003C783C  BB 21 00 14 */	lmw r25, 0x14(r1)
/* 803CA900 003C7840  80 01 00 34 */	lwz r0, 0x34(r1)
/* 803CA904 003C7844  7C 08 03 A6 */	mtlr r0
/* 803CA908 003C7848  38 21 00 30 */	addi r1, r1, 0x30
/* 803CA90C 003C784C  4E 80 00 20 */	blr 

.global hide__7J2DPaneFv
hide__7J2DPaneFv:
/* 803CA910 003C7850  38 00 00 00 */	li r0, 0
/* 803CA914 003C7854  98 03 00 B0 */	stb r0, 0xb0(r3)
/* 803CA918 003C7858  4E 80 00 20 */	blr 

.global E2DPane_setTreeCallBackMessage__3ebiFPQ29P2DScreen3MgrP7J2DPane
E2DPane_setTreeCallBackMessage__3ebiFPQ29P2DScreen3MgrP7J2DPane:
/* 803CA91C 003C785C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 803CA920 003C7860  7C 08 02 A6 */	mflr r0
/* 803CA924 003C7864  90 01 00 44 */	stw r0, 0x44(r1)
/* 803CA928 003C7868  BE E1 00 1C */	stmw r23, 0x1c(r1)
/* 803CA92C 003C786C  7C 9A 23 78 */	mr r26, r4
/* 803CA930 003C7870  7C 7F 1B 78 */	mr r31, r3
/* 803CA934 003C7874  7F 43 D3 78 */	mr r3, r26
/* 803CA938 003C7878  81 9A 00 00 */	lwz r12, 0(r26)
/* 803CA93C 003C787C  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 803CA940 003C7880  7D 89 03 A6 */	mtctr r12
/* 803CA944 003C7884  4E 80 04 21 */	bctrl 
/* 803CA948 003C7888  54 60 04 3E */	clrlwi r0, r3, 0x10
/* 803CA94C 003C788C  28 00 00 13 */	cmplwi r0, 0x13
/* 803CA950 003C7890  40 82 00 90 */	bne lbl_803CA9E0
/* 803CA954 003C7894  3C 60 30 30 */	lis r3, 0x30303030@ha
/* 803CA958 003C7898  80 9A 00 18 */	lwz r4, 0x18(r26)
/* 803CA95C 003C789C  38 63 30 30 */	addi r3, r3, 0x30303030@l
/* 803CA960 003C78A0  80 BA 00 1C */	lwz r5, 0x1c(r26)
/* 803CA964 003C78A4  7C 80 1A 78 */	xor r0, r4, r3
/* 803CA968 003C78A8  7C A3 1A 78 */	xor r3, r5, r3
/* 803CA96C 003C78AC  7C 60 03 79 */	or. r0, r3, r0
/* 803CA970 003C78B0  41 82 00 70 */	beq lbl_803CA9E0
/* 803CA974 003C78B4  38 00 00 00 */	li r0, 0
/* 803CA978 003C78B8  7C A3 02 78 */	xor r3, r5, r0
/* 803CA97C 003C78BC  7C 80 02 78 */	xor r0, r4, r0
/* 803CA980 003C78C0  7C 60 03 79 */	or. r0, r3, r0
/* 803CA984 003C78C4  41 82 00 5C */	beq lbl_803CA9E0
/* 803CA988 003C78C8  83 1A 00 10 */	lwz r24, 0x10(r26)
/* 803CA98C 003C78CC  38 60 00 48 */	li r3, 0x48
/* 803CA990 003C78D0  83 3A 00 14 */	lwz r25, 0x14(r26)
/* 803CA994 003C78D4  4B C5 95 11 */	bl __nw__FUl
/* 803CA998 003C78D8  7C 7B 1B 79 */	or. r27, r3, r3
/* 803CA99C 003C78DC  41 82 00 0C */	beq lbl_803CA9A8
/* 803CA9A0 003C78E0  4B F3 EC 75 */	bl __ct__Q32og6Screen16CallBack_MessageFv
/* 803CA9A4 003C78E4  7C 7B 1B 78 */	mr r27, r3
lbl_803CA9A8:
/* 803CA9A8 003C78E8  28 1B 00 00 */	cmplwi r27, 0
/* 803CA9AC 003C78EC  40 82 00 20 */	bne lbl_803CA9CC
/* 803CA9B0 003C78F0  3C 60 80 49 */	lis r3, lbl_80496428@ha
/* 803CA9B4 003C78F4  3C A0 80 49 */	lis r5, lbl_80496438@ha
/* 803CA9B8 003C78F8  38 63 64 28 */	addi r3, r3, lbl_80496428@l
/* 803CA9BC 003C78FC  38 80 00 4F */	li r4, 0x4f
/* 803CA9C0 003C7900  38 A5 64 38 */	addi r5, r5, lbl_80496438@l
/* 803CA9C4 003C7904  4C C6 31 82 */	crclr 6
/* 803CA9C8 003C7908  4B C5 FC 79 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_803CA9CC:
/* 803CA9CC 003C790C  7F E3 FB 78 */	mr r3, r31
/* 803CA9D0 003C7910  7F 26 CB 78 */	mr r6, r25
/* 803CA9D4 003C7914  7F 05 C3 78 */	mr r5, r24
/* 803CA9D8 003C7918  7F 67 DB 78 */	mr r7, r27
/* 803CA9DC 003C791C  48 06 A1 49 */	bl addCallBack__Q29P2DScreen3MgrFUxPQ29P2DScreen4Node
lbl_803CA9E0:
/* 803CA9E0 003C7920  83 9A 00 DC */	lwz r28, 0xdc(r26)
/* 803CA9E4 003C7924  28 1C 00 00 */	cmplwi r28, 0
/* 803CA9E8 003C7928  41 82 02 F4 */	beq lbl_803CACDC
/* 803CA9EC 003C792C  3B 9C FF F4 */	addi r28, r28, -12
/* 803CA9F0 003C7930  48 00 02 EC */	b lbl_803CACDC
lbl_803CA9F4:
/* 803CA9F4 003C7934  83 1C 00 0C */	lwz r24, 0xc(r28)
/* 803CA9F8 003C7938  7F 03 C3 78 */	mr r3, r24
/* 803CA9FC 003C793C  81 98 00 00 */	lwz r12, 0(r24)
/* 803CAA00 003C7940  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 803CAA04 003C7944  7D 89 03 A6 */	mtctr r12
/* 803CAA08 003C7948  4E 80 04 21 */	bctrl 
/* 803CAA0C 003C794C  54 60 04 3E */	clrlwi r0, r3, 0x10
/* 803CAA10 003C7950  28 00 00 13 */	cmplwi r0, 0x13
/* 803CAA14 003C7954  40 82 00 90 */	bne lbl_803CAAA4
/* 803CAA18 003C7958  3C 60 30 30 */	lis r3, 0x30303030@ha
/* 803CAA1C 003C795C  80 98 00 18 */	lwz r4, 0x18(r24)
/* 803CAA20 003C7960  38 63 30 30 */	addi r3, r3, 0x30303030@l
/* 803CAA24 003C7964  80 B8 00 1C */	lwz r5, 0x1c(r24)
/* 803CAA28 003C7968  7C 80 1A 78 */	xor r0, r4, r3
/* 803CAA2C 003C796C  7C A3 1A 78 */	xor r3, r5, r3
/* 803CAA30 003C7970  7C 60 03 79 */	or. r0, r3, r0
/* 803CAA34 003C7974  41 82 00 70 */	beq lbl_803CAAA4
/* 803CAA38 003C7978  38 00 00 00 */	li r0, 0
/* 803CAA3C 003C797C  7C A3 02 78 */	xor r3, r5, r0
/* 803CAA40 003C7980  7C 80 02 78 */	xor r0, r4, r0
/* 803CAA44 003C7984  7C 60 03 79 */	or. r0, r3, r0
/* 803CAA48 003C7988  41 82 00 5C */	beq lbl_803CAAA4
/* 803CAA4C 003C798C  83 38 00 10 */	lwz r25, 0x10(r24)
/* 803CAA50 003C7990  38 60 00 48 */	li r3, 0x48
/* 803CAA54 003C7994  83 58 00 14 */	lwz r26, 0x14(r24)
/* 803CAA58 003C7998  4B C5 94 4D */	bl __nw__FUl
/* 803CAA5C 003C799C  7C 7B 1B 79 */	or. r27, r3, r3
/* 803CAA60 003C79A0  41 82 00 0C */	beq lbl_803CAA6C
/* 803CAA64 003C79A4  4B F3 EB B1 */	bl __ct__Q32og6Screen16CallBack_MessageFv
/* 803CAA68 003C79A8  7C 7B 1B 78 */	mr r27, r3
lbl_803CAA6C:
/* 803CAA6C 003C79AC  28 1B 00 00 */	cmplwi r27, 0
/* 803CAA70 003C79B0  40 82 00 20 */	bne lbl_803CAA90
/* 803CAA74 003C79B4  3C 60 80 49 */	lis r3, lbl_80496428@ha
/* 803CAA78 003C79B8  3C A0 80 49 */	lis r5, lbl_80496438@ha
/* 803CAA7C 003C79BC  38 63 64 28 */	addi r3, r3, lbl_80496428@l
/* 803CAA80 003C79C0  38 80 00 4F */	li r4, 0x4f
/* 803CAA84 003C79C4  38 A5 64 38 */	addi r5, r5, lbl_80496438@l
/* 803CAA88 003C79C8  4C C6 31 82 */	crclr 6
/* 803CAA8C 003C79CC  4B C5 FB B5 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_803CAA90:
/* 803CAA90 003C79D0  7F E3 FB 78 */	mr r3, r31
/* 803CAA94 003C79D4  7F 46 D3 78 */	mr r6, r26
/* 803CAA98 003C79D8  7F 25 CB 78 */	mr r5, r25
/* 803CAA9C 003C79DC  7F 67 DB 78 */	mr r7, r27
/* 803CAAA0 003C79E0  48 06 A0 85 */	bl addCallBack__Q29P2DScreen3MgrFUxPQ29P2DScreen4Node
lbl_803CAAA4:
/* 803CAAA4 003C79E4  38 78 00 DC */	addi r3, r24, 0xdc
/* 803CAAA8 003C79E8  4B C5 91 79 */	bl getFirstLink__10JSUPtrListCFv
/* 803CAAAC 003C79EC  28 03 00 00 */	cmplwi r3, 0
/* 803CAAB0 003C79F0  41 82 00 08 */	beq lbl_803CAAB8
/* 803CAAB4 003C79F4  38 63 FF F4 */	addi r3, r3, -12
lbl_803CAAB8:
/* 803CAAB8 003C79F8  7C 7D 1B 78 */	mr r29, r3
/* 803CAABC 003C79FC  48 00 02 08 */	b lbl_803CACC4
lbl_803CAAC0:
/* 803CAAC0 003C7A00  83 7D 00 0C */	lwz r27, 0xc(r29)
/* 803CAAC4 003C7A04  7F 63 DB 78 */	mr r3, r27
/* 803CAAC8 003C7A08  81 9B 00 00 */	lwz r12, 0(r27)
/* 803CAACC 003C7A0C  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 803CAAD0 003C7A10  7D 89 03 A6 */	mtctr r12
/* 803CAAD4 003C7A14  4E 80 04 21 */	bctrl 
/* 803CAAD8 003C7A18  54 60 04 3E */	clrlwi r0, r3, 0x10
/* 803CAADC 003C7A1C  28 00 00 13 */	cmplwi r0, 0x13
/* 803CAAE0 003C7A20  40 82 00 90 */	bne lbl_803CAB70
/* 803CAAE4 003C7A24  3C 60 30 30 */	lis r3, 0x30303030@ha
/* 803CAAE8 003C7A28  80 9B 00 18 */	lwz r4, 0x18(r27)
/* 803CAAEC 003C7A2C  38 63 30 30 */	addi r3, r3, 0x30303030@l
/* 803CAAF0 003C7A30  80 BB 00 1C */	lwz r5, 0x1c(r27)
/* 803CAAF4 003C7A34  7C 80 1A 78 */	xor r0, r4, r3
/* 803CAAF8 003C7A38  7C A3 1A 78 */	xor r3, r5, r3
/* 803CAAFC 003C7A3C  7C 60 03 79 */	or. r0, r3, r0
/* 803CAB00 003C7A40  41 82 00 70 */	beq lbl_803CAB70
/* 803CAB04 003C7A44  38 00 00 00 */	li r0, 0
/* 803CAB08 003C7A48  7C A3 02 78 */	xor r3, r5, r0
/* 803CAB0C 003C7A4C  7C 80 02 78 */	xor r0, r4, r0
/* 803CAB10 003C7A50  7C 60 03 79 */	or. r0, r3, r0
/* 803CAB14 003C7A54  41 82 00 5C */	beq lbl_803CAB70
/* 803CAB18 003C7A58  83 1B 00 10 */	lwz r24, 0x10(r27)
/* 803CAB1C 003C7A5C  38 60 00 48 */	li r3, 0x48
/* 803CAB20 003C7A60  83 3B 00 14 */	lwz r25, 0x14(r27)
/* 803CAB24 003C7A64  4B C5 93 81 */	bl __nw__FUl
/* 803CAB28 003C7A68  7C 7A 1B 79 */	or. r26, r3, r3
/* 803CAB2C 003C7A6C  41 82 00 0C */	beq lbl_803CAB38
/* 803CAB30 003C7A70  4B F3 EA E5 */	bl __ct__Q32og6Screen16CallBack_MessageFv
/* 803CAB34 003C7A74  7C 7A 1B 78 */	mr r26, r3
lbl_803CAB38:
/* 803CAB38 003C7A78  28 1A 00 00 */	cmplwi r26, 0
/* 803CAB3C 003C7A7C  40 82 00 20 */	bne lbl_803CAB5C
/* 803CAB40 003C7A80  3C 60 80 49 */	lis r3, lbl_80496428@ha
/* 803CAB44 003C7A84  3C A0 80 49 */	lis r5, lbl_80496438@ha
/* 803CAB48 003C7A88  38 63 64 28 */	addi r3, r3, lbl_80496428@l
/* 803CAB4C 003C7A8C  38 80 00 4F */	li r4, 0x4f
/* 803CAB50 003C7A90  38 A5 64 38 */	addi r5, r5, lbl_80496438@l
/* 803CAB54 003C7A94  4C C6 31 82 */	crclr 6
/* 803CAB58 003C7A98  4B C5 FA E9 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_803CAB5C:
/* 803CAB5C 003C7A9C  7F E3 FB 78 */	mr r3, r31
/* 803CAB60 003C7AA0  7F 26 CB 78 */	mr r6, r25
/* 803CAB64 003C7AA4  7F 05 C3 78 */	mr r5, r24
/* 803CAB68 003C7AA8  7F 47 D3 78 */	mr r7, r26
/* 803CAB6C 003C7AAC  48 06 9F B9 */	bl addCallBack__Q29P2DScreen3MgrFUxPQ29P2DScreen4Node
lbl_803CAB70:
/* 803CAB70 003C7AB0  3B DB 00 DC */	addi r30, r27, 0xdc
/* 803CAB74 003C7AB4  7F C3 F3 78 */	mr r3, r30
/* 803CAB78 003C7AB8  4B C6 DD B1 */	bl getFirstChild__17JSUTree$$07J2DPane$$1CFv
/* 803CAB7C 003C7ABC  7C 7B 1B 78 */	mr r27, r3
/* 803CAB80 003C7AC0  48 00 01 24 */	b lbl_803CACA4
lbl_803CAB84:
/* 803CAB84 003C7AC4  7F 63 DB 78 */	mr r3, r27
/* 803CAB88 003C7AC8  4B C6 DD B5 */	bl getObject__17JSUTree$$07J2DPane$$1CFv
/* 803CAB8C 003C7ACC  81 83 00 00 */	lwz r12, 0(r3)
/* 803CAB90 003C7AD0  7C 7A 1B 78 */	mr r26, r3
/* 803CAB94 003C7AD4  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 803CAB98 003C7AD8  7D 89 03 A6 */	mtctr r12
/* 803CAB9C 003C7ADC  4E 80 04 21 */	bctrl 
/* 803CABA0 003C7AE0  54 60 04 3E */	clrlwi r0, r3, 0x10
/* 803CABA4 003C7AE4  28 00 00 13 */	cmplwi r0, 0x13
/* 803CABA8 003C7AE8  40 82 00 98 */	bne lbl_803CAC40
/* 803CABAC 003C7AEC  7F 43 D3 78 */	mr r3, r26
/* 803CABB0 003C7AF0  4B F3 F1 E9 */	bl getUserInfo__7J2DPaneCFv
/* 803CABB4 003C7AF4  3C A0 30 30 */	lis r5, 0x30303030@ha
/* 803CABB8 003C7AF8  38 05 30 30 */	addi r0, r5, 0x30303030@l
/* 803CABBC 003C7AFC  7C 85 02 78 */	xor r5, r4, r0
/* 803CABC0 003C7B00  7C 60 02 78 */	xor r0, r3, r0
/* 803CABC4 003C7B04  7C A0 03 79 */	or. r0, r5, r0
/* 803CABC8 003C7B08  41 82 00 78 */	beq lbl_803CAC40
/* 803CABCC 003C7B0C  38 00 00 00 */	li r0, 0
/* 803CABD0 003C7B10  7C 84 02 78 */	xor r4, r4, r0
/* 803CABD4 003C7B14  7C 60 02 78 */	xor r0, r3, r0
/* 803CABD8 003C7B18  7C 80 03 79 */	or. r0, r4, r0
/* 803CABDC 003C7B1C  41 82 00 64 */	beq lbl_803CAC40
/* 803CABE0 003C7B20  7F 43 D3 78 */	mr r3, r26
/* 803CABE4 003C7B24  4B F3 89 19 */	bl getTagName__7J2DPaneCFv
/* 803CABE8 003C7B28  7C 79 1B 78 */	mr r25, r3
/* 803CABEC 003C7B2C  7C 98 23 78 */	mr r24, r4
/* 803CABF0 003C7B30  38 60 00 48 */	li r3, 0x48
/* 803CABF4 003C7B34  4B C5 92 B1 */	bl __nw__FUl
/* 803CABF8 003C7B38  7C 77 1B 79 */	or. r23, r3, r3
/* 803CABFC 003C7B3C  41 82 00 0C */	beq lbl_803CAC08
/* 803CAC00 003C7B40  4B F3 EA 15 */	bl __ct__Q32og6Screen16CallBack_MessageFv
/* 803CAC04 003C7B44  7C 77 1B 78 */	mr r23, r3
lbl_803CAC08:
/* 803CAC08 003C7B48  28 17 00 00 */	cmplwi r23, 0
/* 803CAC0C 003C7B4C  40 82 00 20 */	bne lbl_803CAC2C
/* 803CAC10 003C7B50  3C 60 80 49 */	lis r3, lbl_80496428@ha
/* 803CAC14 003C7B54  3C A0 80 49 */	lis r5, lbl_80496438@ha
/* 803CAC18 003C7B58  38 63 64 28 */	addi r3, r3, lbl_80496428@l
/* 803CAC1C 003C7B5C  38 80 00 4F */	li r4, 0x4f
/* 803CAC20 003C7B60  38 A5 64 38 */	addi r5, r5, lbl_80496438@l
/* 803CAC24 003C7B64  4C C6 31 82 */	crclr 6
/* 803CAC28 003C7B68  4B C5 FA 19 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_803CAC2C:
/* 803CAC2C 003C7B6C  7F E3 FB 78 */	mr r3, r31
/* 803CAC30 003C7B70  7F 06 C3 78 */	mr r6, r24
/* 803CAC34 003C7B74  7F 25 CB 78 */	mr r5, r25
/* 803CAC38 003C7B78  7E E7 BB 78 */	mr r7, r23
/* 803CAC3C 003C7B7C  48 06 9E E9 */	bl addCallBack__Q29P2DScreen3MgrFUxPQ29P2DScreen4Node
lbl_803CAC40:
/* 803CAC40 003C7B80  7F 43 D3 78 */	mr r3, r26
/* 803CAC44 003C7B84  4B F3 88 B1 */	bl getPaneTree__7J2DPaneFv
/* 803CAC48 003C7B88  7C 7A 1B 78 */	mr r26, r3
/* 803CAC4C 003C7B8C  4B C6 DC DD */	bl getFirstChild__17JSUTree$$07J2DPane$$1CFv
/* 803CAC50 003C7B90  7C 64 1B 78 */	mr r4, r3
/* 803CAC54 003C7B94  38 61 00 08 */	addi r3, r1, 8
/* 803CAC58 003C7B98  4B C6 DC BD */	bl __ct__25JSUTreeIterator$$07J2DPane$$1FP17JSUTree$$07J2DPane$$1
/* 803CAC5C 003C7B9C  48 00 00 20 */	b lbl_803CAC7C
lbl_803CAC60:
/* 803CAC60 003C7BA0  38 61 00 08 */	addi r3, r1, 8
/* 803CAC64 003C7BA4  4B F3 88 85 */	bl getObject__25JSUTreeIterator$$07J2DPane$$1CFv
/* 803CAC68 003C7BA8  7C 64 1B 78 */	mr r4, r3
/* 803CAC6C 003C7BAC  7F E3 FB 78 */	mr r3, r31
/* 803CAC70 003C7BB0  4B FF FC AD */	bl E2DPane_setTreeCallBackMessage__3ebiFPQ29P2DScreen3MgrP7J2DPane
/* 803CAC74 003C7BB4  38 61 00 08 */	addi r3, r1, 8
/* 803CAC78 003C7BB8  4B C6 DC 81 */	bl __pp__25JSUTreeIterator$$07J2DPane$$1Fv
lbl_803CAC7C:
/* 803CAC7C 003C7BBC  7F 43 D3 78 */	mr r3, r26
/* 803CAC80 003C7BC0  4B C6 DC 71 */	bl getEndChild__17JSUTree$$07J2DPane$$1CFv
/* 803CAC84 003C7BC4  7C 64 1B 78 */	mr r4, r3
/* 803CAC88 003C7BC8  38 61 00 08 */	addi r3, r1, 8
/* 803CAC8C 003C7BCC  4B C6 DC 4D */	bl __ne__25JSUTreeIterator$$07J2DPane$$1CFPC17JSUTree$$07J2DPane$$1
/* 803CAC90 003C7BD0  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 803CAC94 003C7BD4  40 82 FF CC */	bne lbl_803CAC60
/* 803CAC98 003C7BD8  7F 63 DB 78 */	mr r3, r27
/* 803CAC9C 003C7BDC  4B C6 DC 29 */	bl getNextChild__17JSUTree$$07J2DPane$$1CFv
/* 803CACA0 003C7BE0  7C 7B 1B 78 */	mr r27, r3
lbl_803CACA4:
/* 803CACA4 003C7BE4  7F C3 F3 78 */	mr r3, r30
/* 803CACA8 003C7BE8  4B C6 DC 49 */	bl getEndChild__17JSUTree$$07J2DPane$$1CFv
/* 803CACAC 003C7BEC  7C 1B 18 40 */	cmplw r27, r3
/* 803CACB0 003C7BF0  40 82 FE D4 */	bne lbl_803CAB84
/* 803CACB4 003C7BF4  83 BD 00 18 */	lwz r29, 0x18(r29)
/* 803CACB8 003C7BF8  28 1D 00 00 */	cmplwi r29, 0
/* 803CACBC 003C7BFC  41 82 00 08 */	beq lbl_803CACC4
/* 803CACC0 003C7C00  3B BD FF F4 */	addi r29, r29, -12
lbl_803CACC4:
/* 803CACC4 003C7C04  28 1D 00 00 */	cmplwi r29, 0
/* 803CACC8 003C7C08  40 82 FD F8 */	bne lbl_803CAAC0
/* 803CACCC 003C7C0C  83 9C 00 18 */	lwz r28, 0x18(r28)
/* 803CACD0 003C7C10  28 1C 00 00 */	cmplwi r28, 0
/* 803CACD4 003C7C14  41 82 00 08 */	beq lbl_803CACDC
/* 803CACD8 003C7C18  3B 9C FF F4 */	addi r28, r28, -12
lbl_803CACDC:
/* 803CACDC 003C7C1C  28 1C 00 00 */	cmplwi r28, 0
/* 803CACE0 003C7C20  40 82 FD 14 */	bne lbl_803CA9F4
/* 803CACE4 003C7C24  BA E1 00 1C */	lmw r23, 0x1c(r1)
/* 803CACE8 003C7C28  80 01 00 44 */	lwz r0, 0x44(r1)
/* 803CACEC 003C7C2C  7C 08 03 A6 */	mtlr r0
/* 803CACF0 003C7C30  38 21 00 40 */	addi r1, r1, 0x40
/* 803CACF4 003C7C34  4E 80 00 20 */	blr 

.global E2DPane_getGlbCenter__3ebiFP7J2DPane
E2DPane_getGlbCenter__3ebiFP7J2DPane:
/* 803CACF8 003C7C38  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 803CACFC 003C7C3C  7C 08 02 A6 */	mflr r0
/* 803CAD00 003C7C40  90 01 00 44 */	stw r0, 0x44(r1)
/* 803CAD04 003C7C44  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 803CAD08 003C7C48  7C 9F 23 79 */	or. r31, r4, r4
/* 803CAD0C 003C7C4C  93 C1 00 38 */	stw r30, 0x38(r1)
/* 803CAD10 003C7C50  7C 7E 1B 78 */	mr r30, r3
/* 803CAD14 003C7C54  40 82 00 20 */	bne lbl_803CAD34
/* 803CAD18 003C7C58  3C 60 80 49 */	lis r3, lbl_80496428@ha
/* 803CAD1C 003C7C5C  3C A0 80 49 */	lis r5, lbl_80496438@ha
/* 803CAD20 003C7C60  38 63 64 28 */	addi r3, r3, lbl_80496428@l
/* 803CAD24 003C7C64  38 80 00 73 */	li r4, 0x73
/* 803CAD28 003C7C68  38 A5 64 38 */	addi r5, r5, lbl_80496438@l
/* 803CAD2C 003C7C6C  4C C6 31 82 */	crclr 6
/* 803CAD30 003C7C70  4B C5 F9 11 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_803CAD34:
/* 803CAD34 003C7C74  7F E4 FB 78 */	mr r4, r31
/* 803CAD38 003C7C78  38 61 00 14 */	addi r3, r1, 0x14
/* 803CAD3C 003C7C7C  38 A0 00 00 */	li r5, 0
/* 803CAD40 003C7C80  4B C6 E2 59 */	bl getGlbVtx__7J2DPaneCFUc
/* 803CAD44 003C7C84  80 A1 00 14 */	lwz r5, 0x14(r1)
/* 803CAD48 003C7C88  7F E4 FB 78 */	mr r4, r31
/* 803CAD4C 003C7C8C  80 C1 00 18 */	lwz r6, 0x18(r1)
/* 803CAD50 003C7C90  38 61 00 08 */	addi r3, r1, 8
/* 803CAD54 003C7C94  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 803CAD58 003C7C98  90 A1 00 2C */	stw r5, 0x2c(r1)
/* 803CAD5C 003C7C9C  38 A0 00 03 */	li r5, 3
/* 803CAD60 003C7CA0  90 C1 00 30 */	stw r6, 0x30(r1)
/* 803CAD64 003C7CA4  90 01 00 34 */	stw r0, 0x34(r1)
/* 803CAD68 003C7CA8  4B C6 E2 31 */	bl getGlbVtx__7J2DPaneCFUc
/* 803CAD6C 003C7CAC  80 01 00 08 */	lwz r0, 8(r1)
/* 803CAD70 003C7CB0  80 61 00 0C */	lwz r3, 0xc(r1)
/* 803CAD74 003C7CB4  90 01 00 20 */	stw r0, 0x20(r1)
/* 803CAD78 003C7CB8  80 01 00 10 */	lwz r0, 0x10(r1)
/* 803CAD7C 003C7CBC  90 61 00 24 */	stw r3, 0x24(r1)
/* 803CAD80 003C7CC0  C0 61 00 2C */	lfs f3, 0x2c(r1)
/* 803CAD84 003C7CC4  C0 41 00 20 */	lfs f2, 0x20(r1)
/* 803CAD88 003C7CC8  C0 21 00 30 */	lfs f1, 0x30(r1)
/* 803CAD8C 003C7CCC  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 803CAD90 003C7CD0  EC 43 10 2A */	fadds f2, f3, f2
/* 803CAD94 003C7CD4  C0 62 16 9C */	lfs f3, lbl_8051F9FC@sda21(r2)
/* 803CAD98 003C7CD8  EC 01 00 2A */	fadds f0, f1, f0
/* 803CAD9C 003C7CDC  90 01 00 28 */	stw r0, 0x28(r1)
/* 803CADA0 003C7CE0  EC 23 00 B2 */	fmuls f1, f3, f2
/* 803CADA4 003C7CE4  EC 03 00 32 */	fmuls f0, f3, f0
/* 803CADA8 003C7CE8  D0 3E 00 00 */	stfs f1, 0(r30)
/* 803CADAC 003C7CEC  D0 1E 00 04 */	stfs f0, 4(r30)
/* 803CADB0 003C7CF0  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 803CADB4 003C7CF4  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 803CADB8 003C7CF8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 803CADBC 003C7CFC  7C 08 03 A6 */	mtlr r0
/* 803CADC0 003C7D00  38 21 00 40 */	addi r1, r1, 0x40
/* 803CADC4 003C7D04  4E 80 00 20 */	blr 

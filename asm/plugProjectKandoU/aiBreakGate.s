.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global __ct__Q26PikiAI12ActBreakGateFPQ24Game4Piki
__ct__Q26PikiAI12ActBreakGateFPQ24Game4Piki:
/* 801D04E8 001CD428  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 801D04EC 001CD42C  7C 08 02 A6 */	mflr r0
/* 801D04F0 001CD430  90 01 00 14 */	stw r0, 0x14(r1)
/* 801D04F4 001CD434  7C 80 07 35 */	extsh. r0, r4
/* 801D04F8 001CD438  93 E1 00 0C */	stw r31, 0xc(r1)
/* 801D04FC 001CD43C  7C BF 2B 78 */	mr r31, r5
/* 801D0500 001CD440  93 C1 00 08 */	stw r30, 8(r1)
/* 801D0504 001CD444  7C 7E 1B 78 */	mr r30, r3
/* 801D0508 001CD448  41 82 00 18 */	beq lbl_801D0520
/* 801D050C 001CD44C  38 1E 00 34 */	addi r0, r30, 0x34
/* 801D0510 001CD450  3C 60 80 4B */	lis r3, __vt__Q28SysShape14MotionListener@ha
/* 801D0514 001CD454  90 1E 00 0C */	stw r0, 0xc(r30)
/* 801D0518 001CD458  38 03 A6 6C */	addi r0, r3, __vt__Q28SysShape14MotionListener@l
/* 801D051C 001CD45C  90 1E 00 34 */	stw r0, 0x34(r30)
lbl_801D0520:
/* 801D0520 001CD460  7F C3 F3 78 */	mr r3, r30
/* 801D0524 001CD464  7F E4 FB 78 */	mr r4, r31
/* 801D0528 001CD468  4B FC 64 F1 */	bl __ct__Q26PikiAI6ActionFPQ24Game4Piki
/* 801D052C 001CD46C  3C 60 80 4B */	lis r3, __vt__Q26PikiAI12ActBreakGate@ha
/* 801D0530 001CD470  38 1E 00 34 */	addi r0, r30, 0x34
/* 801D0534 001CD474  38 83 79 14 */	addi r4, r3, __vt__Q26PikiAI12ActBreakGate@l
/* 801D0538 001CD478  38 60 00 2C */	li r3, 0x2c
/* 801D053C 001CD47C  90 9E 00 00 */	stw r4, 0(r30)
/* 801D0540 001CD480  38 A4 00 40 */	addi r5, r4, 0x40
/* 801D0544 001CD484  80 9E 00 0C */	lwz r4, 0xc(r30)
/* 801D0548 001CD488  90 A4 00 00 */	stw r5, 0(r4)
/* 801D054C 001CD48C  80 9E 00 0C */	lwz r4, 0xc(r30)
/* 801D0550 001CD490  7C 04 00 50 */	subf r0, r4, r0
/* 801D0554 001CD494  90 04 00 04 */	stw r0, 4(r4)
/* 801D0558 001CD498  4B E5 39 4D */	bl __nw__FUl
/* 801D055C 001CD49C  7C 60 1B 79 */	or. r0, r3, r3
/* 801D0560 001CD4A0  41 82 00 14 */	beq lbl_801D0574
/* 801D0564 001CD4A4  7F E5 FB 78 */	mr r5, r31
/* 801D0568 001CD4A8  38 80 00 01 */	li r4, 1
/* 801D056C 001CD4AC  4B FC B7 4D */	bl __ct__Q26PikiAI14ActStickAttackFPQ24Game4Piki
/* 801D0570 001CD4B0  7C 60 1B 78 */	mr r0, r3
lbl_801D0574:
/* 801D0574 001CD4B4  90 1E 00 18 */	stw r0, 0x18(r30)
/* 801D0578 001CD4B8  38 60 00 1C */	li r3, 0x1c
/* 801D057C 001CD4BC  4B E5 39 29 */	bl __nw__FUl
/* 801D0580 001CD4C0  7C 60 1B 79 */	or. r0, r3, r3
/* 801D0584 001CD4C4  41 82 00 10 */	beq lbl_801D0594
/* 801D0588 001CD4C8  7F E4 FB 78 */	mr r4, r31
/* 801D058C 001CD4CC  4B FC 6D 51 */	bl __ct__Q26PikiAI10ActGotoPosFPQ24Game4Piki
/* 801D0590 001CD4D0  7C 60 1B 78 */	mr r0, r3
lbl_801D0594:
/* 801D0594 001CD4D4  90 1E 00 1C */	stw r0, 0x1c(r30)
/* 801D0598 001CD4D8  38 60 00 10 */	li r3, 0x10
/* 801D059C 001CD4DC  4B E5 39 09 */	bl __nw__FUl
/* 801D05A0 001CD4E0  7C 60 1B 79 */	or. r0, r3, r3
/* 801D05A4 001CD4E4  41 82 00 10 */	beq lbl_801D05B4
/* 801D05A8 001CD4E8  7F E4 FB 78 */	mr r4, r31
/* 801D05AC 001CD4EC  4B FC C6 69 */	bl __ct__Q26PikiAI20ActFollowVectorFieldFPQ24Game4Piki
/* 801D05B0 001CD4F0  7C 60 1B 78 */	mr r0, r3
lbl_801D05B4:
/* 801D05B4 001CD4F4  3C 60 80 48 */	lis r3, lbl_80480470@ha
/* 801D05B8 001CD4F8  90 1E 00 20 */	stw r0, 0x20(r30)
/* 801D05BC 001CD4FC  38 03 04 70 */	addi r0, r3, lbl_80480470@l
/* 801D05C0 001CD500  7F C3 F3 78 */	mr r3, r30
/* 801D05C4 001CD504  90 1E 00 08 */	stw r0, 8(r30)
/* 801D05C8 001CD508  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 801D05CC 001CD50C  83 C1 00 08 */	lwz r30, 8(r1)
/* 801D05D0 001CD510  80 01 00 14 */	lwz r0, 0x14(r1)
/* 801D05D4 001CD514  7C 08 03 A6 */	mtlr r0
/* 801D05D8 001CD518  38 21 00 10 */	addi r1, r1, 0x10
/* 801D05DC 001CD51C  4E 80 00 20 */	blr 

.global init__Q26PikiAI12ActBreakGateFPQ26PikiAI9ActionArg
init__Q26PikiAI12ActBreakGateFPQ26PikiAI9ActionArg:
/* 801D05E0 001CD520  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801D05E4 001CD524  7C 08 02 A6 */	mflr r0
/* 801D05E8 001CD528  90 01 00 24 */	stw r0, 0x24(r1)
/* 801D05EC 001CD52C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801D05F0 001CD530  93 C1 00 18 */	stw r30, 0x18(r1)
/* 801D05F4 001CD534  3B C0 00 00 */	li r30, 0
/* 801D05F8 001CD538  93 A1 00 14 */	stw r29, 0x14(r1)
/* 801D05FC 001CD53C  7C 9D 23 79 */	or. r29, r4, r4
/* 801D0600 001CD540  3C 80 80 48 */	lis r4, lbl_80480460@ha
/* 801D0604 001CD544  93 81 00 10 */	stw r28, 0x10(r1)
/* 801D0608 001CD548  7C 7C 1B 78 */	mr r28, r3
/* 801D060C 001CD54C  3B E4 04 60 */	addi r31, r4, lbl_80480460@l
/* 801D0610 001CD550  41 82 00 34 */	beq lbl_801D0644
/* 801D0614 001CD554  7F A3 EB 78 */	mr r3, r29
/* 801D0618 001CD558  81 9D 00 00 */	lwz r12, 0(r29)
/* 801D061C 001CD55C  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D0620 001CD560  7D 89 03 A6 */	mtctr r12
/* 801D0624 001CD564  4E 80 04 21 */	bctrl 
/* 801D0628 001CD568  7C 64 1B 78 */	mr r4, r3
/* 801D062C 001CD56C  38 7F 00 1C */	addi r3, r31, 0x1c
/* 801D0630 001CD570  4B EF A0 91 */	bl strcmp
/* 801D0634 001CD574  7C 60 00 34 */	cntlzw r0, r3
/* 801D0638 001CD578  54 00 DE 3F */	rlwinm. r0, r0, 0x1b, 0x18, 0x1f
/* 801D063C 001CD57C  41 82 00 08 */	beq lbl_801D0644
/* 801D0640 001CD580  3B C0 00 01 */	li r30, 1
lbl_801D0644:
/* 801D0644 001CD584  57 C0 06 3F */	clrlwi. r0, r30, 0x18
/* 801D0648 001CD588  40 82 00 18 */	bne lbl_801D0660
/* 801D064C 001CD58C  38 7F 00 2C */	addi r3, r31, 0x2c
/* 801D0650 001CD590  38 BF 00 3C */	addi r5, r31, 0x3c
/* 801D0654 001CD594  38 80 00 62 */	li r4, 0x62
/* 801D0658 001CD598  4C C6 31 82 */	crclr 6
/* 801D065C 001CD59C  4B E5 9F E5 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_801D0660:
/* 801D0660 001CD5A0  3C 60 80 51 */	lis r3, workPikis__Q24Game8GameStat@ha
/* 801D0664 001CD5A4  80 9C 00 04 */	lwz r4, 4(r28)
/* 801D0668 001CD5A8  38 63 25 0C */	addi r3, r3, workPikis__Q24Game8GameStat@l
/* 801D066C 001CD5AC  48 00 0C FD */	bl inc__Q34Game8GameStat15PikiNaviCounterFPQ24Game4Piki
/* 801D0670 001CD5B0  80 9D 00 04 */	lwz r4, 4(r29)
/* 801D0674 001CD5B4  38 00 00 00 */	li r0, 0
/* 801D0678 001CD5B8  7F 83 E3 78 */	mr r3, r28
/* 801D067C 001CD5BC  90 9C 00 10 */	stw r4, 0x10(r28)
/* 801D0680 001CD5C0  98 1C 00 24 */	stb r0, 0x24(r28)
/* 801D0684 001CD5C4  48 00 00 25 */	bl initFollow__Q26PikiAI12ActBreakGateFv
/* 801D0688 001CD5C8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801D068C 001CD5CC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801D0690 001CD5D0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801D0694 001CD5D4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 801D0698 001CD5D8  83 81 00 10 */	lwz r28, 0x10(r1)
/* 801D069C 001CD5DC  7C 08 03 A6 */	mtlr r0
/* 801D06A0 001CD5E0  38 21 00 20 */	addi r1, r1, 0x20
/* 801D06A4 001CD5E4  4E 80 00 20 */	blr 

.global initFollow__Q26PikiAI12ActBreakGateFv
initFollow__Q26PikiAI12ActBreakGateFv:
/* 801D06A8 001CD5E8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801D06AC 001CD5EC  7C 08 02 A6 */	mflr r0
/* 801D06B0 001CD5F0  90 01 00 24 */	stw r0, 0x24(r1)
/* 801D06B4 001CD5F4  38 81 00 08 */	addi r4, r1, 8
/* 801D06B8 001CD5F8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801D06BC 001CD5FC  7C 7F 1B 78 */	mr r31, r3
/* 801D06C0 001CD600  3C 60 80 4B */	lis r3, __vt__Q26PikiAI9ActionArg@ha
/* 801D06C4 001CD604  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 801D06C8 001CD608  38 03 05 30 */	addi r0, r3, __vt__Q26PikiAI9ActionArg@l
/* 801D06CC 001CD60C  3C 60 80 4B */	lis r3, __vt__Q26PikiAI26FollowVectorFieldActionArg@ha
/* 801D06D0 001CD610  90 01 00 08 */	stw r0, 8(r1)
/* 801D06D4 001CD614  38 03 79 08 */	addi r0, r3, __vt__Q26PikiAI26FollowVectorFieldActionArg@l
/* 801D06D8 001CD618  90 01 00 08 */	stw r0, 8(r1)
/* 801D06DC 001CD61C  90 A1 00 0C */	stw r5, 0xc(r1)
/* 801D06E0 001CD620  80 7F 00 20 */	lwz r3, 0x20(r31)
/* 801D06E4 001CD624  81 83 00 00 */	lwz r12, 0(r3)
/* 801D06E8 001CD628  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D06EC 001CD62C  7D 89 03 A6 */	mtctr r12
/* 801D06F0 001CD630  4E 80 04 21 */	bctrl 
/* 801D06F4 001CD634  38 00 00 01 */	li r0, 1
/* 801D06F8 001CD638  B0 1F 00 14 */	sth r0, 0x14(r31)
/* 801D06FC 001CD63C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801D0700 001CD640  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801D0704 001CD644  7C 08 03 A6 */	mtlr r0
/* 801D0708 001CD648  38 21 00 20 */	addi r1, r1, 0x20
/* 801D070C 001CD64C  4E 80 00 20 */	blr 

.global exec__Q26PikiAI12ActBreakGateFv
exec__Q26PikiAI12ActBreakGateFv:
/* 801D0710 001CD650  94 21 FF 50 */	stwu r1, -0xb0(r1)
/* 801D0714 001CD654  7C 08 02 A6 */	mflr r0
/* 801D0718 001CD658  90 01 00 B4 */	stw r0, 0xb4(r1)
/* 801D071C 001CD65C  93 E1 00 AC */	stw r31, 0xac(r1)
/* 801D0720 001CD660  7C 7F 1B 78 */	mr r31, r3
/* 801D0724 001CD664  93 C1 00 A8 */	stw r30, 0xa8(r1)
/* 801D0728 001CD668  80 63 00 10 */	lwz r3, 0x10(r3)
/* 801D072C 001CD66C  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0730 001CD670  81 8C 00 A8 */	lwz r12, 0xa8(r12)
/* 801D0734 001CD674  7D 89 03 A6 */	mtctr r12
/* 801D0738 001CD678  4E 80 04 21 */	bctrl 
/* 801D073C 001CD67C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 801D0740 001CD680  40 82 00 0C */	bne lbl_801D074C
/* 801D0744 001CD684  38 60 00 00 */	li r3, 0
/* 801D0748 001CD688  48 00 04 48 */	b lbl_801D0B90
lbl_801D074C:
/* 801D074C 001CD68C  A0 1F 00 14 */	lhz r0, 0x14(r31)
/* 801D0750 001CD690  2C 00 00 01 */	cmpwi r0, 1
/* 801D0754 001CD694  41 82 02 28 */	beq lbl_801D097C
/* 801D0758 001CD698  40 80 00 10 */	bge lbl_801D0768
/* 801D075C 001CD69C  2C 00 00 00 */	cmpwi r0, 0
/* 801D0760 001CD6A0  40 80 03 24 */	bge lbl_801D0A84
/* 801D0764 001CD6A4  48 00 04 28 */	b lbl_801D0B8C
lbl_801D0768:
/* 801D0768 001CD6A8  2C 00 00 03 */	cmpwi r0, 3
/* 801D076C 001CD6AC  40 80 04 20 */	bge lbl_801D0B8C
/* 801D0770 001CD6B0  80 7F 00 20 */	lwz r3, 0x20(r31)
/* 801D0774 001CD6B4  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0778 001CD6B8  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 801D077C 001CD6BC  7D 89 03 A6 */	mtctr r12
/* 801D0780 001CD6C0  4E 80 04 21 */	bctrl 
/* 801D0784 001CD6C4  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D0788 001CD6C8  81 83 00 00 */	lwz r12, 0(r3)
/* 801D078C 001CD6CC  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 801D0790 001CD6D0  7D 89 03 A6 */	mtctr r12
/* 801D0794 001CD6D4  4E 80 04 21 */	bctrl 
/* 801D0798 001CD6D8  2C 03 00 00 */	cmpwi r3, 0
/* 801D079C 001CD6DC  40 82 00 EC */	bne lbl_801D0888
/* 801D07A0 001CD6E0  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 801D07A4 001CD6E4  3B C0 00 01 */	li r30, 1
/* 801D07A8 001CD6E8  88 03 02 7C */	lbz r0, 0x27c(r3)
/* 801D07AC 001CD6EC  28 00 00 01 */	cmplwi r0, 1
/* 801D07B0 001CD6F0  40 82 00 0C */	bne lbl_801D07BC
/* 801D07B4 001CD6F4  3B C0 00 02 */	li r30, 2
/* 801D07B8 001CD6F8  48 00 00 14 */	b lbl_801D07CC
lbl_801D07BC:
/* 801D07BC 001CD6FC  88 03 02 18 */	lbz r0, 0x218(r3)
/* 801D07C0 001CD700  28 00 00 00 */	cmplwi r0, 0
/* 801D07C4 001CD704  41 82 00 08 */	beq lbl_801D07CC
/* 801D07C8 001CD708  3B C0 00 03 */	li r30, 3
lbl_801D07CC:
/* 801D07CC 001CD70C  88 1F 00 24 */	lbz r0, 0x24(r31)
/* 801D07D0 001CD710  28 00 00 00 */	cmplwi r0, 0
/* 801D07D4 001CD714  40 82 00 58 */	bne lbl_801D082C
/* 801D07D8 001CD718  80 7F 00 04 */	lwz r3, 4(r31)
/* 801D07DC 001CD71C  4B F7 8D 11 */	bl getAttackDamage__Q24Game4PikiFv
/* 801D07E0 001CD720  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 801D07E4 001CD724  3C 60 80 4B */	lis r3, __vt__Q26PikiAI9ActionArg@ha
/* 801D07E8 001CD728  38 03 05 30 */	addi r0, r3, __vt__Q26PikiAI9ActionArg@l
/* 801D07EC 001CD72C  38 81 00 80 */	addi r4, r1, 0x80
/* 801D07F0 001CD730  3C 60 80 4B */	lis r3, __vt__Q26PikiAI20StickAttackActionArg@ha
/* 801D07F4 001CD734  90 01 00 80 */	stw r0, 0x80(r1)
/* 801D07F8 001CD738  38 63 4E A4 */	addi r3, r3, __vt__Q26PikiAI20StickAttackActionArg@l
/* 801D07FC 001CD73C  38 00 FF FF */	li r0, -1
/* 801D0800 001CD740  90 61 00 80 */	stw r3, 0x80(r1)
/* 801D0804 001CD744  D0 21 00 84 */	stfs f1, 0x84(r1)
/* 801D0808 001CD748  90 A1 00 88 */	stw r5, 0x88(r1)
/* 801D080C 001CD74C  90 01 00 8C */	stw r0, 0x8c(r1)
/* 801D0810 001CD750  9B C1 00 90 */	stb r30, 0x90(r1)
/* 801D0814 001CD754  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D0818 001CD758  81 83 00 00 */	lwz r12, 0(r3)
/* 801D081C 001CD75C  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D0820 001CD760  7D 89 03 A6 */	mtctr r12
/* 801D0824 001CD764  4E 80 04 21 */	bctrl 
/* 801D0828 001CD768  48 00 00 54 */	b lbl_801D087C
lbl_801D082C:
/* 801D082C 001CD76C  80 7F 00 04 */	lwz r3, 4(r31)
/* 801D0830 001CD770  4B F7 8C BD */	bl getAttackDamage__Q24Game4PikiFv
/* 801D0834 001CD774  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 801D0838 001CD778  3C 60 80 4B */	lis r3, __vt__Q26PikiAI9ActionArg@ha
/* 801D083C 001CD77C  38 03 05 30 */	addi r0, r3, __vt__Q26PikiAI9ActionArg@l
/* 801D0840 001CD780  38 81 00 94 */	addi r4, r1, 0x94
/* 801D0844 001CD784  3C 60 80 4B */	lis r3, __vt__Q26PikiAI20StickAttackActionArg@ha
/* 801D0848 001CD788  90 01 00 94 */	stw r0, 0x94(r1)
/* 801D084C 001CD78C  38 63 4E A4 */	addi r3, r3, __vt__Q26PikiAI20StickAttackActionArg@l
/* 801D0850 001CD790  38 00 00 19 */	li r0, 0x19
/* 801D0854 001CD794  90 61 00 94 */	stw r3, 0x94(r1)
/* 801D0858 001CD798  D0 21 00 98 */	stfs f1, 0x98(r1)
/* 801D085C 001CD79C  90 A1 00 9C */	stw r5, 0x9c(r1)
/* 801D0860 001CD7A0  90 01 00 A0 */	stw r0, 0xa0(r1)
/* 801D0864 001CD7A4  9B C1 00 A4 */	stb r30, 0xa4(r1)
/* 801D0868 001CD7A8  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D086C 001CD7AC  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0870 001CD7B0  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D0874 001CD7B4  7D 89 03 A6 */	mtctr r12
/* 801D0878 001CD7B8  4E 80 04 21 */	bctrl 
lbl_801D087C:
/* 801D087C 001CD7BC  38 00 00 02 */	li r0, 2
/* 801D0880 001CD7C0  B0 1F 00 14 */	sth r0, 0x14(r31)
/* 801D0884 001CD7C4  48 00 03 08 */	b lbl_801D0B8C
lbl_801D0888:
/* 801D0888 001CD7C8  2C 03 00 02 */	cmpwi r3, 2
/* 801D088C 001CD7CC  40 82 03 04 */	bne lbl_801D0B90
/* 801D0890 001CD7D0  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 801D0894 001CD7D4  3B C0 00 01 */	li r30, 1
/* 801D0898 001CD7D8  88 03 02 7C */	lbz r0, 0x27c(r3)
/* 801D089C 001CD7DC  28 00 00 01 */	cmplwi r0, 1
/* 801D08A0 001CD7E0  40 82 00 0C */	bne lbl_801D08AC
/* 801D08A4 001CD7E4  3B C0 00 02 */	li r30, 2
/* 801D08A8 001CD7E8  48 00 00 14 */	b lbl_801D08BC
lbl_801D08AC:
/* 801D08AC 001CD7EC  88 03 02 18 */	lbz r0, 0x218(r3)
/* 801D08B0 001CD7F0  28 00 00 00 */	cmplwi r0, 0
/* 801D08B4 001CD7F4  41 82 00 08 */	beq lbl_801D08BC
/* 801D08B8 001CD7F8  3B C0 00 03 */	li r30, 3
lbl_801D08BC:
/* 801D08BC 001CD7FC  88 1F 00 24 */	lbz r0, 0x24(r31)
/* 801D08C0 001CD800  28 00 00 00 */	cmplwi r0, 0
/* 801D08C4 001CD804  40 82 00 58 */	bne lbl_801D091C
/* 801D08C8 001CD808  80 7F 00 04 */	lwz r3, 4(r31)
/* 801D08CC 001CD80C  4B F7 8C 21 */	bl getAttackDamage__Q24Game4PikiFv
/* 801D08D0 001CD810  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 801D08D4 001CD814  3C 60 80 4B */	lis r3, __vt__Q26PikiAI9ActionArg@ha
/* 801D08D8 001CD818  38 03 05 30 */	addi r0, r3, __vt__Q26PikiAI9ActionArg@l
/* 801D08DC 001CD81C  38 81 00 58 */	addi r4, r1, 0x58
/* 801D08E0 001CD820  3C 60 80 4B */	lis r3, __vt__Q26PikiAI20StickAttackActionArg@ha
/* 801D08E4 001CD824  90 01 00 58 */	stw r0, 0x58(r1)
/* 801D08E8 001CD828  38 63 4E A4 */	addi r3, r3, __vt__Q26PikiAI20StickAttackActionArg@l
/* 801D08EC 001CD82C  38 00 FF FF */	li r0, -1
/* 801D08F0 001CD830  90 61 00 58 */	stw r3, 0x58(r1)
/* 801D08F4 001CD834  D0 21 00 5C */	stfs f1, 0x5c(r1)
/* 801D08F8 001CD838  90 A1 00 60 */	stw r5, 0x60(r1)
/* 801D08FC 001CD83C  90 01 00 64 */	stw r0, 0x64(r1)
/* 801D0900 001CD840  9B C1 00 68 */	stb r30, 0x68(r1)
/* 801D0904 001CD844  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D0908 001CD848  81 83 00 00 */	lwz r12, 0(r3)
/* 801D090C 001CD84C  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D0910 001CD850  7D 89 03 A6 */	mtctr r12
/* 801D0914 001CD854  4E 80 04 21 */	bctrl 
/* 801D0918 001CD858  48 00 00 54 */	b lbl_801D096C
lbl_801D091C:
/* 801D091C 001CD85C  80 7F 00 04 */	lwz r3, 4(r31)
/* 801D0920 001CD860  4B F7 8B CD */	bl getAttackDamage__Q24Game4PikiFv
/* 801D0924 001CD864  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 801D0928 001CD868  3C 60 80 4B */	lis r3, __vt__Q26PikiAI9ActionArg@ha
/* 801D092C 001CD86C  38 03 05 30 */	addi r0, r3, __vt__Q26PikiAI9ActionArg@l
/* 801D0930 001CD870  38 81 00 6C */	addi r4, r1, 0x6c
/* 801D0934 001CD874  3C 60 80 4B */	lis r3, __vt__Q26PikiAI20StickAttackActionArg@ha
/* 801D0938 001CD878  90 01 00 6C */	stw r0, 0x6c(r1)
/* 801D093C 001CD87C  38 63 4E A4 */	addi r3, r3, __vt__Q26PikiAI20StickAttackActionArg@l
/* 801D0940 001CD880  38 00 00 19 */	li r0, 0x19
/* 801D0944 001CD884  90 61 00 6C */	stw r3, 0x6c(r1)
/* 801D0948 001CD888  D0 21 00 70 */	stfs f1, 0x70(r1)
/* 801D094C 001CD88C  90 A1 00 74 */	stw r5, 0x74(r1)
/* 801D0950 001CD890  90 01 00 78 */	stw r0, 0x78(r1)
/* 801D0954 001CD894  9B C1 00 7C */	stb r30, 0x7c(r1)
/* 801D0958 001CD898  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D095C 001CD89C  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0960 001CD8A0  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D0964 001CD8A4  7D 89 03 A6 */	mtctr r12
/* 801D0968 001CD8A8  4E 80 04 21 */	bctrl 
lbl_801D096C:
/* 801D096C 001CD8AC  38 00 00 02 */	li r0, 2
/* 801D0970 001CD8B0  B0 1F 00 14 */	sth r0, 0x14(r31)
/* 801D0974 001CD8B4  48 00 02 18 */	b lbl_801D0B8C
/* 801D0978 001CD8B8  48 00 02 18 */	b lbl_801D0B90
lbl_801D097C:
/* 801D097C 001CD8BC  80 7F 00 20 */	lwz r3, 0x20(r31)
/* 801D0980 001CD8C0  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0984 001CD8C4  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 801D0988 001CD8C8  7D 89 03 A6 */	mtctr r12
/* 801D098C 001CD8CC  4E 80 04 21 */	bctrl 
/* 801D0990 001CD8D0  2C 03 00 00 */	cmpwi r3, 0
/* 801D0994 001CD8D4  40 82 01 FC */	bne lbl_801D0B90
/* 801D0998 001CD8D8  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 801D099C 001CD8DC  3B C0 00 01 */	li r30, 1
/* 801D09A0 001CD8E0  88 03 02 7C */	lbz r0, 0x27c(r3)
/* 801D09A4 001CD8E4  28 00 00 01 */	cmplwi r0, 1
/* 801D09A8 001CD8E8  40 82 00 0C */	bne lbl_801D09B4
/* 801D09AC 001CD8EC  3B C0 00 02 */	li r30, 2
/* 801D09B0 001CD8F0  48 00 00 14 */	b lbl_801D09C4
lbl_801D09B4:
/* 801D09B4 001CD8F4  88 03 02 18 */	lbz r0, 0x218(r3)
/* 801D09B8 001CD8F8  28 00 00 00 */	cmplwi r0, 0
/* 801D09BC 001CD8FC  41 82 00 08 */	beq lbl_801D09C4
/* 801D09C0 001CD900  3B C0 00 03 */	li r30, 3
lbl_801D09C4:
/* 801D09C4 001CD904  88 1F 00 24 */	lbz r0, 0x24(r31)
/* 801D09C8 001CD908  28 00 00 00 */	cmplwi r0, 0
/* 801D09CC 001CD90C  40 82 00 58 */	bne lbl_801D0A24
/* 801D09D0 001CD910  80 7F 00 04 */	lwz r3, 4(r31)
/* 801D09D4 001CD914  4B F7 8B 19 */	bl getAttackDamage__Q24Game4PikiFv
/* 801D09D8 001CD918  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 801D09DC 001CD91C  3C 60 80 4B */	lis r3, __vt__Q26PikiAI9ActionArg@ha
/* 801D09E0 001CD920  38 03 05 30 */	addi r0, r3, __vt__Q26PikiAI9ActionArg@l
/* 801D09E4 001CD924  38 81 00 30 */	addi r4, r1, 0x30
/* 801D09E8 001CD928  3C 60 80 4B */	lis r3, __vt__Q26PikiAI20StickAttackActionArg@ha
/* 801D09EC 001CD92C  90 01 00 30 */	stw r0, 0x30(r1)
/* 801D09F0 001CD930  38 63 4E A4 */	addi r3, r3, __vt__Q26PikiAI20StickAttackActionArg@l
/* 801D09F4 001CD934  38 00 FF FF */	li r0, -1
/* 801D09F8 001CD938  90 61 00 30 */	stw r3, 0x30(r1)
/* 801D09FC 001CD93C  D0 21 00 34 */	stfs f1, 0x34(r1)
/* 801D0A00 001CD940  90 A1 00 38 */	stw r5, 0x38(r1)
/* 801D0A04 001CD944  90 01 00 3C */	stw r0, 0x3c(r1)
/* 801D0A08 001CD948  9B C1 00 40 */	stb r30, 0x40(r1)
/* 801D0A0C 001CD94C  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D0A10 001CD950  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0A14 001CD954  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D0A18 001CD958  7D 89 03 A6 */	mtctr r12
/* 801D0A1C 001CD95C  4E 80 04 21 */	bctrl 
/* 801D0A20 001CD960  48 00 00 54 */	b lbl_801D0A74
lbl_801D0A24:
/* 801D0A24 001CD964  80 7F 00 04 */	lwz r3, 4(r31)
/* 801D0A28 001CD968  4B F7 8A C5 */	bl getAttackDamage__Q24Game4PikiFv
/* 801D0A2C 001CD96C  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 801D0A30 001CD970  3C 60 80 4B */	lis r3, __vt__Q26PikiAI9ActionArg@ha
/* 801D0A34 001CD974  38 03 05 30 */	addi r0, r3, __vt__Q26PikiAI9ActionArg@l
/* 801D0A38 001CD978  38 81 00 44 */	addi r4, r1, 0x44
/* 801D0A3C 001CD97C  3C 60 80 4B */	lis r3, __vt__Q26PikiAI20StickAttackActionArg@ha
/* 801D0A40 001CD980  90 01 00 44 */	stw r0, 0x44(r1)
/* 801D0A44 001CD984  38 63 4E A4 */	addi r3, r3, __vt__Q26PikiAI20StickAttackActionArg@l
/* 801D0A48 001CD988  38 00 00 19 */	li r0, 0x19
/* 801D0A4C 001CD98C  90 61 00 44 */	stw r3, 0x44(r1)
/* 801D0A50 001CD990  D0 21 00 48 */	stfs f1, 0x48(r1)
/* 801D0A54 001CD994  90 A1 00 4C */	stw r5, 0x4c(r1)
/* 801D0A58 001CD998  90 01 00 50 */	stw r0, 0x50(r1)
/* 801D0A5C 001CD99C  9B C1 00 54 */	stb r30, 0x54(r1)
/* 801D0A60 001CD9A0  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D0A64 001CD9A4  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0A68 001CD9A8  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D0A6C 001CD9AC  7D 89 03 A6 */	mtctr r12
/* 801D0A70 001CD9B0  4E 80 04 21 */	bctrl 
lbl_801D0A74:
/* 801D0A74 001CD9B4  38 00 00 02 */	li r0, 2
/* 801D0A78 001CD9B8  B0 1F 00 14 */	sth r0, 0x14(r31)
/* 801D0A7C 001CD9BC  48 00 01 10 */	b lbl_801D0B8C
/* 801D0A80 001CD9C0  48 00 01 10 */	b lbl_801D0B90
lbl_801D0A84:
/* 801D0A84 001CD9C4  80 7F 00 1C */	lwz r3, 0x1c(r31)
/* 801D0A88 001CD9C8  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0A8C 001CD9CC  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 801D0A90 001CD9D0  7D 89 03 A6 */	mtctr r12
/* 801D0A94 001CD9D4  4E 80 04 21 */	bctrl 
/* 801D0A98 001CD9D8  2C 03 00 00 */	cmpwi r3, 0
/* 801D0A9C 001CD9DC  40 82 00 F4 */	bne lbl_801D0B90
/* 801D0AA0 001CD9E0  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 801D0AA4 001CD9E4  3B C0 00 01 */	li r30, 1
/* 801D0AA8 001CD9E8  88 03 02 7C */	lbz r0, 0x27c(r3)
/* 801D0AAC 001CD9EC  28 00 00 01 */	cmplwi r0, 1
/* 801D0AB0 001CD9F0  40 82 00 0C */	bne lbl_801D0ABC
/* 801D0AB4 001CD9F4  3B C0 00 02 */	li r30, 2
/* 801D0AB8 001CD9F8  48 00 00 14 */	b lbl_801D0ACC
lbl_801D0ABC:
/* 801D0ABC 001CD9FC  88 03 02 18 */	lbz r0, 0x218(r3)
/* 801D0AC0 001CDA00  28 00 00 00 */	cmplwi r0, 0
/* 801D0AC4 001CDA04  41 82 00 08 */	beq lbl_801D0ACC
/* 801D0AC8 001CDA08  3B C0 00 03 */	li r30, 3
lbl_801D0ACC:
/* 801D0ACC 001CDA0C  88 1F 00 24 */	lbz r0, 0x24(r31)
/* 801D0AD0 001CDA10  28 00 00 00 */	cmplwi r0, 0
/* 801D0AD4 001CDA14  40 82 00 58 */	bne lbl_801D0B2C
/* 801D0AD8 001CDA18  80 7F 00 04 */	lwz r3, 4(r31)
/* 801D0ADC 001CDA1C  4B F7 8A 11 */	bl getAttackDamage__Q24Game4PikiFv
/* 801D0AE0 001CDA20  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 801D0AE4 001CDA24  3C 60 80 4B */	lis r3, __vt__Q26PikiAI9ActionArg@ha
/* 801D0AE8 001CDA28  38 03 05 30 */	addi r0, r3, __vt__Q26PikiAI9ActionArg@l
/* 801D0AEC 001CDA2C  38 81 00 08 */	addi r4, r1, 8
/* 801D0AF0 001CDA30  3C 60 80 4B */	lis r3, __vt__Q26PikiAI20StickAttackActionArg@ha
/* 801D0AF4 001CDA34  90 01 00 08 */	stw r0, 8(r1)
/* 801D0AF8 001CDA38  38 63 4E A4 */	addi r3, r3, __vt__Q26PikiAI20StickAttackActionArg@l
/* 801D0AFC 001CDA3C  38 00 FF FF */	li r0, -1
/* 801D0B00 001CDA40  90 61 00 08 */	stw r3, 8(r1)
/* 801D0B04 001CDA44  D0 21 00 0C */	stfs f1, 0xc(r1)
/* 801D0B08 001CDA48  90 A1 00 10 */	stw r5, 0x10(r1)
/* 801D0B0C 001CDA4C  90 01 00 14 */	stw r0, 0x14(r1)
/* 801D0B10 001CDA50  9B C1 00 18 */	stb r30, 0x18(r1)
/* 801D0B14 001CDA54  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D0B18 001CDA58  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0B1C 001CDA5C  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D0B20 001CDA60  7D 89 03 A6 */	mtctr r12
/* 801D0B24 001CDA64  4E 80 04 21 */	bctrl 
/* 801D0B28 001CDA68  48 00 00 54 */	b lbl_801D0B7C
lbl_801D0B2C:
/* 801D0B2C 001CDA6C  80 7F 00 04 */	lwz r3, 4(r31)
/* 801D0B30 001CDA70  4B F7 89 BD */	bl getAttackDamage__Q24Game4PikiFv
/* 801D0B34 001CDA74  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 801D0B38 001CDA78  3C 60 80 4B */	lis r3, __vt__Q26PikiAI9ActionArg@ha
/* 801D0B3C 001CDA7C  38 03 05 30 */	addi r0, r3, __vt__Q26PikiAI9ActionArg@l
/* 801D0B40 001CDA80  38 81 00 1C */	addi r4, r1, 0x1c
/* 801D0B44 001CDA84  3C 60 80 4B */	lis r3, __vt__Q26PikiAI20StickAttackActionArg@ha
/* 801D0B48 001CDA88  90 01 00 1C */	stw r0, 0x1c(r1)
/* 801D0B4C 001CDA8C  38 63 4E A4 */	addi r3, r3, __vt__Q26PikiAI20StickAttackActionArg@l
/* 801D0B50 001CDA90  38 00 00 19 */	li r0, 0x19
/* 801D0B54 001CDA94  90 61 00 1C */	stw r3, 0x1c(r1)
/* 801D0B58 001CDA98  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 801D0B5C 001CDA9C  90 A1 00 24 */	stw r5, 0x24(r1)
/* 801D0B60 001CDAA0  90 01 00 28 */	stw r0, 0x28(r1)
/* 801D0B64 001CDAA4  9B C1 00 2C */	stb r30, 0x2c(r1)
/* 801D0B68 001CDAA8  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D0B6C 001CDAAC  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0B70 001CDAB0  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D0B74 001CDAB4  7D 89 03 A6 */	mtctr r12
/* 801D0B78 001CDAB8  4E 80 04 21 */	bctrl 
lbl_801D0B7C:
/* 801D0B7C 001CDABC  38 00 00 02 */	li r0, 2
/* 801D0B80 001CDAC0  B0 1F 00 14 */	sth r0, 0x14(r31)
/* 801D0B84 001CDAC4  48 00 00 08 */	b lbl_801D0B8C
/* 801D0B88 001CDAC8  48 00 00 08 */	b lbl_801D0B90
lbl_801D0B8C:
/* 801D0B8C 001CDACC  38 60 00 01 */	li r3, 1
lbl_801D0B90:
/* 801D0B90 001CDAD0  80 01 00 B4 */	lwz r0, 0xb4(r1)
/* 801D0B94 001CDAD4  83 E1 00 AC */	lwz r31, 0xac(r1)
/* 801D0B98 001CDAD8  83 C1 00 A8 */	lwz r30, 0xa8(r1)
/* 801D0B9C 001CDADC  7C 08 03 A6 */	mtlr r0
/* 801D0BA0 001CDAE0  38 21 00 B0 */	addi r1, r1, 0xb0
/* 801D0BA4 001CDAE4  4E 80 00 20 */	blr 

.global cleanup__Q26PikiAI12ActBreakGateFv
cleanup__Q26PikiAI12ActBreakGateFv:
/* 801D0BA8 001CDAE8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 801D0BAC 001CDAEC  7C 08 02 A6 */	mflr r0
/* 801D0BB0 001CDAF0  90 01 00 14 */	stw r0, 0x14(r1)
/* 801D0BB4 001CDAF4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 801D0BB8 001CDAF8  7C 7F 1B 78 */	mr r31, r3
/* 801D0BBC 001CDAFC  3C 60 80 51 */	lis r3, workPikis__Q24Game8GameStat@ha
/* 801D0BC0 001CDB00  80 9F 00 04 */	lwz r4, 4(r31)
/* 801D0BC4 001CDB04  38 63 25 0C */	addi r3, r3, workPikis__Q24Game8GameStat@l
/* 801D0BC8 001CDB08  48 00 08 4D */	bl dec__Q34Game8GameStat15PikiNaviCounterFPQ24Game4Piki
/* 801D0BCC 001CDB0C  A0 1F 00 14 */	lhz r0, 0x14(r31)
/* 801D0BD0 001CDB10  2C 00 00 02 */	cmpwi r0, 2
/* 801D0BD4 001CDB14  41 82 00 08 */	beq lbl_801D0BDC
/* 801D0BD8 001CDB18  48 00 00 18 */	b lbl_801D0BF0
lbl_801D0BDC:
/* 801D0BDC 001CDB1C  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D0BE0 001CDB20  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0BE4 001CDB24  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 801D0BE8 001CDB28  7D 89 03 A6 */	mtctr r12
/* 801D0BEC 001CDB2C  4E 80 04 21 */	bctrl 
lbl_801D0BF0:
/* 801D0BF0 001CDB30  80 01 00 14 */	lwz r0, 0x14(r1)
/* 801D0BF4 001CDB34  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 801D0BF8 001CDB38  7C 08 03 A6 */	mtlr r0
/* 801D0BFC 001CDB3C  38 21 00 10 */	addi r1, r1, 0x10
/* 801D0C00 001CDB40  4E 80 00 20 */	blr 

.global emotion_success__Q26PikiAI12ActBreakGateFv
emotion_success__Q26PikiAI12ActBreakGateFv:
/* 801D0C04 001CDB44  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 801D0C08 001CDB48  7C 08 02 A6 */	mflr r0
/* 801D0C0C 001CDB4C  38 A0 00 13 */	li r5, 0x13
/* 801D0C10 001CDB50  90 01 00 14 */	stw r0, 0x14(r1)
/* 801D0C14 001CDB54  38 00 00 01 */	li r0, 1
/* 801D0C18 001CDB58  38 C1 00 08 */	addi r6, r1, 8
/* 801D0C1C 001CDB5C  B0 01 00 08 */	sth r0, 8(r1)
/* 801D0C20 001CDB60  80 83 00 04 */	lwz r4, 4(r3)
/* 801D0C24 001CDB64  80 64 02 8C */	lwz r3, 0x28c(r4)
/* 801D0C28 001CDB68  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0C2C 001CDB6C  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 801D0C30 001CDB70  7D 89 03 A6 */	mtctr r12
/* 801D0C34 001CDB74  4E 80 04 21 */	bctrl 
/* 801D0C38 001CDB78  80 01 00 14 */	lwz r0, 0x14(r1)
/* 801D0C3C 001CDB7C  7C 08 03 A6 */	mtlr r0
/* 801D0C40 001CDB80  38 21 00 10 */	addi r1, r1, 0x10
/* 801D0C44 001CDB84  4E 80 00 20 */	blr 

.global platCallback__Q26PikiAI12ActBreakGateFPQ24Game4PikiRQ24Game9PlatEvent
platCallback__Q26PikiAI12ActBreakGateFPQ24Game4PikiRQ24Game9PlatEvent:
/* 801D0C48 001CDB88  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 801D0C4C 001CDB8C  7C 08 02 A6 */	mflr r0
/* 801D0C50 001CDB90  C0 02 B2 D0 */	lfs f0, lbl_80519630@sda21(r2)
/* 801D0C54 001CDB94  90 01 00 44 */	stw r0, 0x44(r1)
/* 801D0C58 001CDB98  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 801D0C5C 001CDB9C  7C 7F 1B 78 */	mr r31, r3
/* 801D0C60 001CDBA0  93 C1 00 38 */	stw r30, 0x38(r1)
/* 801D0C64 001CDBA4  C0 25 00 08 */	lfs f1, 8(r5)
/* 801D0C68 001CDBA8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 801D0C6C 001CDBAC  40 81 00 10 */	ble lbl_801D0C7C
/* 801D0C70 001CDBB0  38 00 00 01 */	li r0, 1
/* 801D0C74 001CDBB4  98 1F 00 24 */	stb r0, 0x24(r31)
/* 801D0C78 001CDBB8  48 00 00 0C */	b lbl_801D0C84
lbl_801D0C7C:
/* 801D0C7C 001CDBBC  38 00 00 00 */	li r0, 0
/* 801D0C80 001CDBC0  98 1F 00 24 */	stb r0, 0x24(r31)
lbl_801D0C84:
/* 801D0C84 001CDBC4  A0 1F 00 14 */	lhz r0, 0x14(r31)
/* 801D0C88 001CDBC8  28 00 00 01 */	cmplwi r0, 1
/* 801D0C8C 001CDBCC  40 82 00 E8 */	bne lbl_801D0D74
/* 801D0C90 001CDBD0  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 801D0C94 001CDBD4  3B C0 00 01 */	li r30, 1
/* 801D0C98 001CDBD8  88 03 02 7C */	lbz r0, 0x27c(r3)
/* 801D0C9C 001CDBDC  28 00 00 01 */	cmplwi r0, 1
/* 801D0CA0 001CDBE0  40 82 00 0C */	bne lbl_801D0CAC
/* 801D0CA4 001CDBE4  3B C0 00 02 */	li r30, 2
/* 801D0CA8 001CDBE8  48 00 00 14 */	b lbl_801D0CBC
lbl_801D0CAC:
/* 801D0CAC 001CDBEC  88 03 02 18 */	lbz r0, 0x218(r3)
/* 801D0CB0 001CDBF0  28 00 00 00 */	cmplwi r0, 0
/* 801D0CB4 001CDBF4  41 82 00 08 */	beq lbl_801D0CBC
/* 801D0CB8 001CDBF8  3B C0 00 03 */	li r30, 3
lbl_801D0CBC:
/* 801D0CBC 001CDBFC  88 1F 00 24 */	lbz r0, 0x24(r31)
/* 801D0CC0 001CDC00  28 00 00 00 */	cmplwi r0, 0
/* 801D0CC4 001CDC04  40 82 00 58 */	bne lbl_801D0D1C
/* 801D0CC8 001CDC08  80 7F 00 04 */	lwz r3, 4(r31)
/* 801D0CCC 001CDC0C  4B F7 88 21 */	bl getAttackDamage__Q24Game4PikiFv
/* 801D0CD0 001CDC10  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 801D0CD4 001CDC14  3C 60 80 4B */	lis r3, __vt__Q26PikiAI9ActionArg@ha
/* 801D0CD8 001CDC18  38 03 05 30 */	addi r0, r3, __vt__Q26PikiAI9ActionArg@l
/* 801D0CDC 001CDC1C  38 81 00 08 */	addi r4, r1, 8
/* 801D0CE0 001CDC20  3C 60 80 4B */	lis r3, __vt__Q26PikiAI20StickAttackActionArg@ha
/* 801D0CE4 001CDC24  90 01 00 08 */	stw r0, 8(r1)
/* 801D0CE8 001CDC28  38 63 4E A4 */	addi r3, r3, __vt__Q26PikiAI20StickAttackActionArg@l
/* 801D0CEC 001CDC2C  38 00 FF FF */	li r0, -1
/* 801D0CF0 001CDC30  90 61 00 08 */	stw r3, 8(r1)
/* 801D0CF4 001CDC34  D0 21 00 0C */	stfs f1, 0xc(r1)
/* 801D0CF8 001CDC38  90 A1 00 10 */	stw r5, 0x10(r1)
/* 801D0CFC 001CDC3C  90 01 00 14 */	stw r0, 0x14(r1)
/* 801D0D00 001CDC40  9B C1 00 18 */	stb r30, 0x18(r1)
/* 801D0D04 001CDC44  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D0D08 001CDC48  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0D0C 001CDC4C  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D0D10 001CDC50  7D 89 03 A6 */	mtctr r12
/* 801D0D14 001CDC54  4E 80 04 21 */	bctrl 
/* 801D0D18 001CDC58  48 00 00 54 */	b lbl_801D0D6C
lbl_801D0D1C:
/* 801D0D1C 001CDC5C  80 7F 00 04 */	lwz r3, 4(r31)
/* 801D0D20 001CDC60  4B F7 87 CD */	bl getAttackDamage__Q24Game4PikiFv
/* 801D0D24 001CDC64  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 801D0D28 001CDC68  3C 60 80 4B */	lis r3, __vt__Q26PikiAI9ActionArg@ha
/* 801D0D2C 001CDC6C  38 03 05 30 */	addi r0, r3, __vt__Q26PikiAI9ActionArg@l
/* 801D0D30 001CDC70  38 81 00 1C */	addi r4, r1, 0x1c
/* 801D0D34 001CDC74  3C 60 80 4B */	lis r3, __vt__Q26PikiAI20StickAttackActionArg@ha
/* 801D0D38 001CDC78  90 01 00 1C */	stw r0, 0x1c(r1)
/* 801D0D3C 001CDC7C  38 63 4E A4 */	addi r3, r3, __vt__Q26PikiAI20StickAttackActionArg@l
/* 801D0D40 001CDC80  38 00 00 19 */	li r0, 0x19
/* 801D0D44 001CDC84  90 61 00 1C */	stw r3, 0x1c(r1)
/* 801D0D48 001CDC88  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 801D0D4C 001CDC8C  90 A1 00 24 */	stw r5, 0x24(r1)
/* 801D0D50 001CDC90  90 01 00 28 */	stw r0, 0x28(r1)
/* 801D0D54 001CDC94  9B C1 00 2C */	stb r30, 0x2c(r1)
/* 801D0D58 001CDC98  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801D0D5C 001CDC9C  81 83 00 00 */	lwz r12, 0(r3)
/* 801D0D60 001CDCA0  81 8C 00 08 */	lwz r12, 8(r12)
/* 801D0D64 001CDCA4  7D 89 03 A6 */	mtctr r12
/* 801D0D68 001CDCA8  4E 80 04 21 */	bctrl 
lbl_801D0D6C:
/* 801D0D6C 001CDCAC  38 00 00 02 */	li r0, 2
/* 801D0D70 001CDCB0  B0 1F 00 14 */	sth r0, 0x14(r31)
lbl_801D0D74:
/* 801D0D74 001CDCB4  80 01 00 44 */	lwz r0, 0x44(r1)
/* 801D0D78 001CDCB8  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 801D0D7C 001CDCBC  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 801D0D80 001CDCC0  7C 08 03 A6 */	mtlr r0
/* 801D0D84 001CDCC4  38 21 00 40 */	addi r1, r1, 0x40
/* 801D0D88 001CDCC8  4E 80 00 20 */	blr 

.global collisionCallback__Q26PikiAI12ActBreakGateFPQ24Game4PikiRQ24Game9CollEvent
collisionCallback__Q26PikiAI12ActBreakGateFPQ24Game4PikiRQ24Game9CollEvent:
/* 801D0D8C 001CDCCC  4E 80 00 20 */	blr 

.global bounceCallback__Q26PikiAI12ActBreakGateFPQ24Game4PikiPQ23Sys8Triangle
bounceCallback__Q26PikiAI12ActBreakGateFPQ24Game4PikiPQ23Sys8Triangle:
/* 801D0D90 001CDCD0  4E 80 00 20 */	blr 

.global onKeyEvent__Q26PikiAI12ActBreakGateFRCQ28SysShape8KeyEvent
onKeyEvent__Q26PikiAI12ActBreakGateFRCQ28SysShape8KeyEvent:
/* 801D0D94 001CDCD4  4E 80 00 20 */	blr 

.global getName__Q26PikiAI26FollowVectorFieldActionArgFv
getName__Q26PikiAI26FollowVectorFieldActionArgFv:
/* 801D0D98 001CDCD8  3C 60 80 48 */	lis r3, lbl_804804E0@ha
/* 801D0D9C 001CDCDC  38 63 04 E0 */	addi r3, r3, lbl_804804E0@l
/* 801D0DA0 001CDCE0  4E 80 00 20 */	blr 

.global "@52@4@onKeyEvent__Q26PikiAI12ActBreakGateFRCQ28SysShape8KeyEvent"
"@52@4@onKeyEvent__Q26PikiAI12ActBreakGateFRCQ28SysShape8KeyEvent":
/* 801D0DA4 001CDCE4  39 60 00 04 */	li r11, 4
/* 801D0DA8 001CDCE8  7D 63 58 2E */	lwzx r11, r3, r11
/* 801D0DAC 001CDCEC  7C 63 5A 14 */	add r3, r3, r11
/* 801D0DB0 001CDCF0  38 63 FF CC */	addi r3, r3, -52
/* 801D0DB4 001CDCF4  4B FF FF E0 */	b onKeyEvent__Q26PikiAI12ActBreakGateFRCQ28SysShape8KeyEvent
